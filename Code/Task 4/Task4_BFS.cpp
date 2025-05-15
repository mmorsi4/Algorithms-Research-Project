#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int depl[12][8] = {};

void init_moves() {
    for (int i = 0; i < 12; ++i) {
        int x = i / 3;
        int y = i % 3;
        int count = 0;
        for (int dx : {-2, -1, 1, 2}) {
            for (int dy : {-2, -1, 1, 2}) {
                if (abs(dx * dy) == 2) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < 4 && ny >= 0 && ny < 3) {
                        depl[i][count++] = nx * 3 + ny;
                    }
                }
            }
        }
        while (count < 8) depl[i][count++] = -1;
    }
}

struct position {
    array<int, 3> B;
    array<int, 3> W;
    int hash;
    position *up = nullptr;
    position(int w0, int w1, int w2, int b0, int b1, int b2) {
        W = {w0, w1, w2};
        B = {b0, b1, b2};
        sort(W.begin(), W.end());
        sort(B.begin(), B.end());
        cal_hash();
    }
    position() {};
    void cal_hash() {
        hash = 0;
        for (int i = 0; i < 3; ++i) {
            hash = hash * 12 + B[i];
        }
        for (int i = 0; i < 3; ++i) {
            hash = hash * 12 + W[i];
        }
    }
    vector<position> gene_mov(int white_black) {
        vector<position> res;
        if (!white_black) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 8 && depl[W[i]][j] != -1; ++j) {
                    int pos = depl[W[i]][j];
                    if (find(W.begin(), W.end(), pos) == W.end() &&
                        find(B.begin(), B.end(), pos) == B.end()) {
                        auto Wnew = W; Wnew[i] = pos; sort(Wnew.begin(), Wnew.end());
                        res.emplace_back(Wnew[0], Wnew[1], Wnew[2], B[0], B[1], B[2]);
                    }
                }
            }
        } else {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 8 && depl[B[i]][j] != -1; ++j) {
                    int pos = depl[B[i]][j];
                    if (find(B.begin(), B.end(), pos) == B.end() &&
                        find(W.begin(), W.end(), pos) == W.end()) {
                        auto Bnew = B; Bnew[i] = pos; sort(Bnew.begin(), Bnew.end());
                        res.emplace_back(W[0], W[1], W[2], Bnew[0], Bnew[1], Bnew[2]);
                    }
                }
            }
        }
        return res;
    }
    void print(int shift = 0) {
        char displ[4][3] = {{'.','.','.'},{'.','.','.'},{'.','.','.'},{'.','.','.'}};
        for (auto w : W) displ[3 - w / 3][w % 3] = 'W';
        for (auto b : B) displ[3 - b / 3][b % 3] = 'B';
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; j++) {
                cout << "| " << displ[i][j] << " ";
            }
            cout << "|\n";
            cout << "+---+---+---+\n";
        }
    }
};

tuple<bool, int, vector<position>> find_moves(position &first, position &end) {
    vector<position> moves;
    vector<bool> pos_found(2985984, false);
   
    vector<vector<position>> dfs;
    dfs.push_back({first});

    int iter = 1;
    int white_black = 0;
    while (true) {
        int n = dfs[iter-1].size();
        if (n == 0) return make_tuple(false, 0, moves);
        dfs.push_back({});
        for (int i = 0; i < n; ++i) {
            auto candidates = dfs[iter-1][i].gene_mov(white_black);
            for (auto &c : candidates) {
                if (pos_found[c.hash]) continue;
                c.up = &dfs[iter-1][i];
                if (c.hash == end.hash) {
                    moves.resize(iter+1);
                    moves[iter] = c;
                    for (int i = iter - 1; i >= 0; i--) {
                        moves[i] = *(moves[i+1].up);
                    }
                    return make_tuple(true, iter, moves);
                }
                pos_found[c.hash] = true;
                dfs[iter].push_back(c);
            }
        }
        iter++;
        white_black = 1 - white_black;
    }
    return make_tuple(false, -1, moves);
}

int main() {
    init_moves();
    position first(9, 10, 11, 0, 1, 2);
    position end(0, 1, 2, 9, 10, 11);

    bool success;
    int n_iter;
    vector<position> moves;
    tie(success, n_iter, moves) = find_moves(first, end);
    cout << "success = " << success << "\n";
    cout << "n_iter = " << n_iter << "\n\n";

    for (auto &m : moves) {
        m.print();
        cout << "\n";
    }
    return 0;
}