/*
Computer Engineering and Artificial Intelligence Program
CSE245: Advanced Algorithms and Complexity – Spring 2025
Task 1 - Tiling Trominoes
*/

#include <bits/stdc++.h>
using namespace std;

int tromino_id = 0;

// The main recursive function to place trominoes
void locateTromino(vector<vector<int>> &board, int size, int istart, int iend, int jstart, int jend, int missing_i, int missing_j){
    
    // Base case (reached a single cell)
    if(size == 1) return;
    
    // Determine quad of missing cell
    int quad;
    if(missing_i >= istart && missing_i <= (istart+iend)/2){
        if(missing_j >= ((jstart+jend)/2)+1 && missing_j <= jend) quad = 1;
        else quad = 2;
    }
    else if(missing_i >= ((istart+iend)/2)+1 && missing_i <= iend){
        if(missing_j >= jstart && missing_j <= (jstart+jend)/2) quad = 3;
        else quad = 4;
    }
    
    // Increment tromino ID (to place a different one)
    tromino_id++;
    
    // Determine tromino orientation based on quad of missing cell
    switch(quad){
        case 1: 
            // 1st quad: L shape
            board[(istart+iend)/2][(jstart+jend)/2] = tromino_id; // Top left
            board[((istart+iend)/2)+1][(jstart+jend)/2] = tromino_id; // Bottom left
            board[((istart+iend)/2)+1][((jstart+jend)/2)+1] = tromino_id; // Bottom right
            
            // Quadruple recursion
            locateTromino(board, size/2, istart, istart+(size/2)-1, jstart+(size/2), jstart+(size-1), missing_i, missing_j); // 1ST QUAD
            locateTromino(board, size/2, istart, istart+(size/2)-1, jstart, jstart+(size/2)-1, istart+(size/2)-1, jstart+(size/2)-1); // 2nd quad
            locateTromino(board, size/2, istart+(size/2), istart+(size-1), jstart, jstart+(size/2)-1, istart+(size/2), jstart+(size/2)-1); // 3rd quad
            locateTromino(board, size/2, istart+(size/2), istart+size-1, jstart+(size/2), jstart+size-1, istart+(size/2), jstart+(size/2)); // 4th quad
        break;
        
        case 2: 
            // 2nd quad: Mirrored L shape
            board[(istart+iend)/2][((jstart+jend)/2)+1] = tromino_id; // Top right
            board[((istart+iend)/2)+1][(jstart+jend)/2] = tromino_id; // Bottom left
            board[((istart+iend)/2)+1][((jstart+jend)/2)+1] = tromino_id; // Bottom right
            
            // Quadruple recursion
            locateTromino(board, size/2, istart, istart+(size/2)-1, jstart+(size/2), jstart+(size-1), istart+(size/2)-1, jstart+(size/2)); // 1st quad
            locateTromino(board, size/2, istart, istart+(size/2)-1, jstart, jstart+(size/2)-1, missing_i, missing_j); // 2ND QUAD
            locateTromino(board, size/2, istart+(size/2), istart+(size-1), jstart, jstart+(size/2)-1, istart+(size/2), jstart+(size/2)-1); // 3rd quad
            locateTromino(board, size/2, istart+(size/2), istart+size-1, jstart+(size/2), jstart+size-1, istart+(size/2), jstart+(size/2)); // 4th quad
        break;
        
        case 3: 
            // 3rd quad: Left T
            board[(istart+iend)/2][((jstart+jend)/2)+1] = tromino_id; // Top right
            board[(istart+iend)/2][(jstart+jend)/2] = tromino_id; // Top left
            board[((istart+iend)/2)+1][((jstart+jend)/2)+1] = tromino_id; // Bottom right
            
            // Quadruple recursion
            locateTromino(board, size/2, istart, istart+(size/2)-1, jstart+(size/2), jstart+(size-1), istart+(size/2)-1, jstart+(size/2)); // 1st quad
            locateTromino(board, size/2, istart, istart+(size/2)-1, jstart, jstart+(size/2)-1, istart+(size/2)-1, jstart+(size/2)-1); // 2nd quad
            locateTromino(board, size/2, istart+(size/2), istart+(size-1), jstart, jstart+(size/2)-1, missing_i, missing_j); // 3RD QUAD
            locateTromino(board, size/2, istart+(size/2), istart+size-1, jstart+(size/2), jstart+size-1, istart+(size/2), jstart+(size/2)); // 4th quad
        break;
        
        case 4: 
            // 4th quad: Right T
            board[(istart+iend)/2][(jstart+jend)/2] = tromino_id; // Top left
            board[(istart+iend)/2][((jstart+jend)/2)+1] = tromino_id; // Top right
            board[((istart+iend)/2)+1][(jstart+jend)/2] = tromino_id; // Bottom left
            
            // Quadruple recursion
            locateTromino(board, size/2, istart, istart+(size/2)-1, jstart+(size/2), jstart+(size-1), istart+(size/2)-1, jstart+(size/2)); // 1st quad
            locateTromino(board, size/2, istart, istart+(size/2)-1, jstart, jstart+(size/2)-1, istart+(size/2)-1, jstart+(size/2)-1); // 2nd quad
            locateTromino(board, size/2, istart+(size/2), istart+(size-1), jstart, jstart+(size/2)-1, istart+(size/2), jstart+(size/2)-1); // 3rd quad
            locateTromino(board, size/2, istart+(size/2), istart+size-1, jstart+(size/2), jstart+size-1, missing_i, missing_j); // 4TH QUAD
        break;
    }
}

// Coloring the board after filling the board with trominoes
void colorBoard(vector<vector<int>> &board, int size){
    
    // STEP 1: ADJACENCY GRAPH

    // Mapping each node ID to its adjacent node IDs (used a set to prevent repetition)
    unordered_map<int, unordered_set<int>> adjacency;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int current = board[i][j];
            if (current <= 0) continue; // Ignore missing cell

            // To check all adjacent cells of a single cell (left, right, down, up)
            vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
            for (auto [di, dj] : directions) {
                int xi = i + di, xj = j + dj;
                if (xi >= 0 && xi < size && xj >= 0 && xj < size) {
                    int neighbor = board[xi][xj];
                    // Ignore the neighbor if its missing OR has the same ID as the current cell
                    if (neighbor > 0 && neighbor != current) {
                        // Add adjacency to both nodes: current and neighbor
                        adjacency[current].insert(neighbor);
                        adjacency[neighbor].insert(current);
                    }
                }
            }
        }
    }

    // STEP 2: GREEDY COLORING

    // To track each tromino ID and its color
    unordered_map<int, int> tromino_color;
    for (auto &entry : adjacency) {
        int tromino_id = entry.first;
        const unordered_set<int> &neighbors = entry.second;

        // Track used colors by neighbors for EACH entry
        bool used[3] = {false, false, false};

        for (int neighbor : neighbors) {
            if (tromino_color.count(neighbor)) { // Returns 1 if it has been colored before, 0 if not
                used[tromino_color[neighbor]] = true; // Mark it as used to prevent the current tromino_id to be the same color
            }
        }

        // Assign the first available color (GREEDY COLORING)
        for (int c = 0; c < 3; c++) { // 0, 1, 2 to navigate used array and also colors
            if (!used[c]) {
                tromino_color[tromino_id] = c;
                break;
            }
        }
    }

    // STEP 3: OVERWRITE EXISTING IDS WITH COLORS

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] > 0) { // If not missing
                board[i][j] = tromino_color[board[i][j]] + 1; // Shifted all colors by 1 to make them 1, 2, 3
            }
        }
    }

}

// To display board in the console
void displayBoard(vector<vector<int>> &board, int n){
    for(int i = 0; i < pow(2, n); i++){
        for(int j = 0; j < pow(2, n); j++){
            cout << setw(3) << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    
    int n;
    cout << "n: ";
    cin >> n;
    
    int missing_row, missing_col;
    cout << "Row of missing cell: ";
    cin >> missing_row;
    cout << "Column of missing cell: ";
    cin >> missing_col;
    
    int size = pow(2, n);
    // Initialize board
    vector<vector<int>> board(size, vector<int>(size, 0));
    // Remove missing cell
    board[missing_row-1][missing_col-1] = -1;
    
    // Display board
    displayBoard(board, n);
    
    // Start the divide and conquer algorithm
    locateTromino(board, size, 0, size-1, 0, size-1, missing_row-1, missing_col-1);
    // Color the board after tromino placement
    colorBoard(board, size);

    // Display board
    displayBoard(board, n);    
    
    return 0;
}