#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;

const int ROWS = 4;
const int COLS = 3;
const int NUM_KNIGHTS = 3;

const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

enum KnightColor { EMPTY = 0, WHITE = 1, BLACK = 2 };

struct Knight {
    int row;
    int col;
    KnightColor color;

    Knight(int r, int c, KnightColor clr) : row(r), col(c), color(clr) {}

    bool operator==(const Knight& other) const {
        return row == other.row && col == other.col && color == other.color;
    }
};

struct State {
    vector<vector<KnightColor>> board;
    vector<Knight> knights;
    int g;
    int h;
    int f;
    string moveHistory;
    string lastMove;

    State() : g(0), h(0), f(0) {
        board = vector<vector<KnightColor>>(ROWS, vector<KnightColor>(COLS, EMPTY));
        moveHistory = "";
        lastMove = "";
    }

    bool operator==(const State& other) const {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] != other.board[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
};

namespace std {
    template <>
    struct hash<State> {
        size_t operator()(const State& state) const {
            size_t hash_val = 0;
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    hash_val = hash_val * 3 + state.board[i][j];
                }
            }
            return hash_val;
        }
    };
}

bool isValid(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

void printBoard(const State& state) {
    cout << "  a b c" << endl;
    for (int i = ROWS - 1; i >= 0; --i) {
        cout << i + 1 << " ";
        for (int j = 0; j < COLS; ++j) {
            if (state.board[i][j] == WHITE) {
                cout << "W ";
            } else if (state.board[i][j] == BLACK) {
                cout << "B ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool isGoalState(const State& state) {
    for (int j = 0; j < COLS; ++j) {
        if (state.board[ROWS - 1][j] != WHITE) {
            return false;
        }
    }
    for (int j = 0; j < COLS; ++j) {
        if (state.board[0][j] != BLACK) {
            return false;
        }
    }
    return true;
}

int minKnightMoves(int srcRow, int srcCol, int destRow, int destCol) {
    if (srcRow == destRow && srcCol == destCol) {
        return 0;
    }
    vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
    queue<pair<pair<int, int>, int>> q;
    q.push({{srcRow, srcCol}, 0});
    visited[srcRow][srcCol] = true;
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        int row = curr.first.first;
        int col = curr.first.second;
        int dist = curr.second;
        if (row == destRow && col == destCol) {
            return dist;
        }
        for (int k = 0; k < 8; ++k) {
            int newRow = row + dx[k];
            int newCol = col + dy[k];
            if (isValid(newRow, newCol) && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                q.push({{newRow, newCol}, dist + 1});
            }
        }
    }
    return -1;
}

int calculateHeuristic(const State& state) {
    int total = 0;
    for (const Knight& knight : state.knights) {
        if (knight.color == WHITE) {
            int minMoves = INT_MAX;
            for (int j = 0; j < COLS; ++j) {
                if (state.board[ROWS - 1][j] == EMPTY || (state.board[ROWS - 1][j] == WHITE && knight.row == ROWS - 1 && knight.col == j)) {
                    int moves = minKnightMoves(knight.row, knight.col, ROWS - 1, j);
                    minMoves = min(minMoves, moves);
                }
            }
            total += minMoves;
        }
        else if (knight.color == BLACK) {
            int minMoves = INT_MAX;
            for (int j = 0; j < COLS; ++j) {
                if (state.board[0][j] == EMPTY || (state.board[0][j] == BLACK && knight.row == 0 && knight.col == j)) {
                    int moves = minKnightMoves(knight.row, knight.col, 0, j);
                    minMoves = min(minMoves, moves);
                }
            }
            total += minMoves;
        }
    }
    return total;
}

vector<State> getNextStates(const State& current) {
    vector<State> nextStates;
    for (int k = 0; k < current.knights.size(); ++k) {
        const Knight& knight = current.knights[k];
        for (int i = 0; i < 8; ++i) {
            int newRow = knight.row + dx[i];
            int newCol = knight.col + dy[i];
            if (isValid(newRow, newCol) && current.board[newRow][newCol] == EMPTY) {
                State nextState = current;
                nextState.board[knight.row][knight.col] = EMPTY;
                nextState.board[newRow][newCol] = knight.color;
                nextState.knights[k].row = newRow;
                nextState.knights[k].col = newCol;
                nextState.g = current.g + 1;
                nextState.h = calculateHeuristic(nextState);
                nextState.f = nextState.g + nextState.h;
                char colFrom = 'a' + knight.col;
                char colTo = 'a' + newCol;
                nextState.lastMove = (knight.color == WHITE ? "W" : "B") +
                    string(1, colFrom) + to_string(knight.row + 1) + "-" +
                    string(1, colTo) + to_string(newRow + 1);
                nextState.moveHistory = current.moveHistory + (current.moveHistory.empty() ? "" : ", ") + nextState.lastMove;
                nextStates.push_back(nextState);
            }
        }
    }
    return nextStates;
}

State solveKnightSwap() {
    auto startTime = chrono::high_resolution_clock::now();
    State initialState;
    for (int j = 0; j < COLS; ++j) {
        initialState.board[0][j] = WHITE;
        initialState.knights.push_back(Knight(0, j, WHITE));
    }
    for (int j = 0; j < COLS; ++j) {
        initialState.board[ROWS - 1][j] = BLACK;
        initialState.knights.push_back(Knight(ROWS - 1, j, BLACK));
    }
    initialState.h = calculateHeuristic(initialState);
    initialState.f = initialState.h;
    auto compare = [](const State& a, const State& b) {
        if (a.f != b.f) {
            return a.f > b.f;
        }
        return a.g < b.g;
    };
    priority_queue<State, vector<State>, decltype(compare)> openSet(compare);
    unordered_set<State> closedSet;
    unordered_map<size_t, State> stateMap;
    openSet.push(initialState);
    int nodesExplored = 0;
    while (!openSet.empty()) {
        State current = openSet.top();
        openSet.pop();
        nodesExplored++;
        if (isGoalState(current)) {
            auto endTime = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
            cout << "Solution found in " << current.g << " moves" << endl;
            cout << "Nodes explored: " << nodesExplored << endl;
            cout << "Time taken: " << duration << " ms" << endl;
            return current;
        }
        if (closedSet.find(current) != closedSet.end()) {
            continue;
        }
        closedSet.insert(current);
        vector<State> nextStates = getNextStates(current);
        for (const State& nextState : nextStates) {
            if (closedSet.find(nextState) != closedSet.end()) {
                continue;
            }
            openSet.push(nextState);
        }
    }
    cout << "No solution found" << endl;
    return initialState;
}

void visualizeSolution(const State& solution) {
    if (solution.moveHistory.empty()) {
        cout << "No moves to visualize." << endl;
        return;
    }
    State currentState;
    for (int j = 0; j < COLS; ++j) {
        currentState.board[0][j] = WHITE;
        currentState.knights.push_back(Knight(0, j, WHITE));
    }
    for (int j = 0; j < COLS; ++j) {
        currentState.board[ROWS - 1][j] = BLACK;
        currentState.knights.push_back(Knight(ROWS - 1, j, BLACK));
    }
    cout << "Initial state:" << endl;
    printBoard(currentState);
    istringstream iss(solution.moveHistory);
    string move;
    int moveNumber = 1;
    while (getline(iss, move, ',')) {
        move.erase(0, move.find_first_not_of(" \t"));
        move.erase(move.find_last_not_of(" \t") + 1);
        char color = move[0];
        char fromCol = move[1];
        int fromRow = move[2] - '0';
        char toCol = move[4];
        int toRow = move[5] - '0';
        int srcRow = fromRow - 1;
        int srcCol = fromCol - 'a';
        int destRow = toRow - 1;
        int destCol = toCol - 'a';
        for (int i = 0; i < currentState.knights.size(); ++i) {
            Knight& knight = currentState.knights[i];
            if (knight.row == srcRow && knight.col == srcCol) {
                currentState.board[srcRow][srcCol] = EMPTY;
                currentState.board[destRow][destCol] = knight.color;
                knight.row = destRow;
                knight.col = destCol;
                break;
            }
        }
        cout << "Move " << moveNumber << ": " << move << endl;
        printBoard(currentState);
        moveNumber++;
    }
}

int main() {
    cout << "Knight Swap Puzzle Solver" << endl;
    cout << "-------------------------" << endl;
    cout << "Initial state: White knights at bottom, Black knights at top" << endl;
    cout << "Goal state: White knights at top, Black knights at bottom" << endl;
    cout << "Finding minimal solution using A* algorithm..." << endl << endl;
    State solution = solveKnightSwap();
    cout << endl << "Solution path: " << solution.moveHistory << endl << endl;
    cout << "Visualizing solution step by step:" << endl;
    visualizeSolution(solution);
    return 0;
}