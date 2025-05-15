#include <iostream> 
#include <iomanip>  
#include <cstdlib> 
#include <ctime> 
using namespace std; 
  
#define N 8 
  
// Function declarations 
int solveKTUtil(int x, int y, int movei, int sol[N][N], 
                int xMove[], int yMove[], int &moveCount); 
  
bool isSafe(int x, int y, int sol[N][N]) { 
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1); 
} 

void printSolution(int sol[N][N]) { 
    for (int x = 0; x < N; x++) { 
        for (int y = 0; y < N; y++) 
            cout << " " << setw(2) << sol[x][y] << " "; 
        cout << endl; 
    } 
} 
  
int solveKT() { 
    int sol[N][N]; 
    int moveCount = 0;  // To track number of steps 
  
    // Initialize all cells to -1 
    for (int x = 0; x < N; x++) 
        for (int y = 0; y < N; y++) 
            sol[x][y] = -1; 
  
    // Possible knight moves 
    int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 }; 
    int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 }; 
  
    // Starting position 
    sol[0][0] = 0; 
  
    // Try to solve the tour 
    if (solveKTUtil(0, 0, 1, sol, xMove, yMove, moveCount) == 0) { 
        cout << "Solution does not exist" << endl; 
        return 0; 
    } else { 
        printSolution(sol); 
        cout << "Minimum number of steps: " << moveCount << endl; 
    } 
  
    return 1; 
} 
  
int solveKTUtil(int x, int y, int movei, int sol[N][N], 
                int xMove[8], int yMove[8], int &moveCount) { 
    int k, next_x, next_y; 
  
    if (movei == N * N) 
        return 1; 
 
    // Try all next moves from the current coordinate x, y 
    for (k = 0; k < 8; k++) { 
        next_x = x + xMove[k]; 
        next_y = y + yMove[k]; 
        if (isSafe(next_x, next_y, sol)) { 
            sol[next_x][next_y] = movei; 
            moveCount++; // Count this step 
  
            if (solveKTUtil(next_x, next_y, movei + 1, sol, xMove, yMove, moveCount) == 1) 
                return 1; 
            else { 
                // Backtracking 
                sol[next_x][next_y] = -1; 
                moveCount--; // Undo the step 
            } 
        } 
    } 
    return 0; 
} 
  
// Main function 
int main() { 
    solveKT(); 
    return 0; 
} 
