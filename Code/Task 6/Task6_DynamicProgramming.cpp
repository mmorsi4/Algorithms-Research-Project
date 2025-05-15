 Task 6 - DP 

#include bitsstdc++.h
using namespace std;

const int boardsize = 15;  limited outer board size
int id = 1;  keep track of line ID if required

 print the board with lines visually represented
void printBoard(const vectorvectorchar &board) {
    for (int i = 0; i  boardsize; i++) {
        for (int j = 0; j  boardsize; j++) {
            cout  setw(2)  board[i][j]   ;
        }
        cout  endl;
    }
    cout  endl;
}

 main decrease and conquer function
void crossingDots(vectorvectorchar &board, int nOriginal) {
    pairint, int startIndex = {board[0].size()  2 + 2, board[0].size()  2 - 2};  Starting point
    pairint, int endIndex;
    pairint, int currIndex = startIndex;
    pairint, int drawingIndex = startIndex;
    
     Draw the original grid
    
     determine bottom left of grid to start drawing
    for(int i = 4; i = nOriginal; i++){
        if(i % 2 == 0) drawingIndex.first++;
        else drawingIndex.second--;
    }
    
    
     start drawing
    for(int i = 0; i  nOriginal; i++){
        for(int j = 0; j  nOriginal; j++){
            board[drawingIndex.first-i-1][drawingIndex.second+j+1] = '.';
        }
    }
    printBoard(board);
    
     Solving the first case, n = 3
    
    cout  Starting n = 3  endl  endl;;
    
    for (int i = 0; i  3; i++) {
        currIndex.first -= 1;
        currIndex.second += 1;
        board[currIndex.first][currIndex.second] = '';   Mark the line
    }
    id++;
    printBoard(board);
    
     2nd line
    for (int i = 0; i  3; i++) {
        currIndex.first += 1;
        board[currIndex.first][currIndex.second] = '';
    }
    id++;
    printBoard(board);

     3rd line
    for (int i = 0; i  3; i++) {
        currIndex.first -= 1;
        currIndex.second -= 1;
        board[currIndex.first][currIndex.second] = '';
    }
    id++;
    printBoard(board);
    
     4th line
    for (int i = 0; i  4; i++) {
        currIndex.second += 1;
        board[currIndex.first][currIndex.second] = '';
    }
    id++;
    printBoard(board);

    endIndex = currIndex;
    
    cout  n = 3 finished! Total moves 4  endl  endl;;
    if (nOriginal == 3) return;   If n = 3, no need to go further
    
    
    int n = 4;

     Decrease and Conquer by 1

    while (n = nOriginal) {
        
        cout  Starting n =   n  endl  endl;
        
        if (board[currIndex.first][currIndex.second + 1] != '') {
            for (int i = 0; i  n - 1; i++) {
                currIndex.first += 1;
                board[currIndex.first][currIndex.second] = '';
            }
            id++;
            printBoard(board);

            for (int i = 0; i  n; i++) {
                currIndex.second -= 1;
                board[currIndex.first][currIndex.second] = '';
            }
            id++;
            printBoard(board);
        }
        
        else if (board[currIndex.first][currIndex.second - 1] != '') {
            for (int i = 0; i  n - 1; i++) {
                currIndex.first -= 1;
                board[currIndex.first][currIndex.second] = '';
            }
            id++;
            printBoard(board);

            for (int i = 0; i  n; i++) {
                currIndex.second += 1;
                board[currIndex.first][currIndex.second] = '';
            }
            id++;
            printBoard(board);
        }
        
        cout  n =   n   finished! Total moves   2n-2  endl  endl;
        n++;
    }
}

int main() {
    vectorvectorchar board(boardsize, vectorchar(boardsize, ' '));

    int n;
    cout  n ; cin  n;

    crossingDots(board, n);
    return 0;
}