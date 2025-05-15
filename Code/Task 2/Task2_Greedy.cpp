/* 
Computer Engineering and Artificial Intelligence Program 
CSE245: Advanced Algorithms and Complexity – Spring 2025 
Task 2 – Knight’s Tour 
*/ 
 
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <cstdio> 
#define N 8 
// Move pattern on basis of the change of 
// x coordinates and y coordinates respectively 
static int cx[N] = {1, 1, 2, 2, -1, -1, -2, -2}; 
static int cy[N] = {2, -2, 1, -1, 2, -2, 1, -1}; 
  
// function restricts the knight to remain within 
// the 8x8 chessboard 
bool limits(int x, int y) 
{ 
    return ((x >= 0 && y >= 0) && (x < N && y < N)); 
} 
  
/* Checks whether a square is valid and empty or not */ 
bool isempty(int a[], int x, int y) 
{ 
    return (limits(x, y)) && (a[y * N + x] < 0); 
} 
  
/* Returns the number of empty squares adjacent 
to (x, y) */ 
int getDegree(int a[], int x, int y) 
{ 
    int count = 0; 
    for (int i = 0; i < N; ++i) 
        if (isempty(a, (x + cx[i]), (y + cy[i]))) 
            count++; 
  
    return count; 
} 
  
// Picks next point using Warnsdorff's heuristic. 
// Returns false if it is not possible to pick 
// next point. 
bool nextMove(int a[], int *x, int *y) 
{ 
    int min_deg_idx = -1, c, min_deg = (N + 1), nx, ny; 
  
    // Try all N adjacent of (*x, *y) starting 
    // from a random adjacent. Find the adjacent 
    // with minimum degree. 
    int start = rand() % N; 
    for (int count = 0; count < N; ++count) 
    { 
        int i = (start + count) % N; 
        nx = *x + cx[i]; 
        ny = *y + cy[i]; 
        if ((isempty(a, nx, ny)) && 
            (c = getDegree(a, nx, ny)) < min_deg) 
        { 
            min_deg_idx = i; 
            min_deg = c; 
        } 
    } 
  
    // IF we could not find a next cell 
    if (min_deg_idx == -1) 
        return false; 
  
    // Store coordinates of next point 
    nx = *x + cx[min_deg_idx]; 
    ny = *y + cy[min_deg_idx]; 
  
    // Mark next move 
    a[ny * N + nx] = a[(*y) * N + (*x)] + 1; 
  
    // Update next point 
    *x = nx; 
    *y = ny; 
  
    return true; 
} 
  
/* displays the chessboard with all the 
legal knight's moves */ 
void print(int a[]) 
{ 
    for (int i = 0; i < N; ++i) 
    { 
        for (int j = 0; j < N; ++j) 
            printf("%d\t", a[j * N + i]); 
        printf("\n"); 
    } 
} 
  
/* checks its neighbouring squares */ 
/* If the knight ends on a square that is one 
knight's move from the beginning square, 
then tour is closed */ 
bool neighbour(int x, int y, int xx, int yy) 
{ 
    for (int i = 0; i < N; ++i) 
        if (((x + cx[i]) == xx) && ((y + cy[i]) == yy)) 
            return true; 
  
    return false; 
} 
  
/* Generates the legal moves using Warnsdorff's 
heuristics. Returns false if not possible */ 
bool findClosedTour() 
{ 
    // Filling up the chessboard matrix with -1's 
    int a[N * N]; 
    for (int i = 0; i < N * N; ++i) 
        a[i] = -1; 
  
    // Random initial position 
 
    int sx = rand() % N; 
    int sy = rand() % N; 
  
    // Current points are same as initial points 
    int x = sx, y = sy; 
    a[y * N + x] = 1; // Mark first move. 
  
    int moveCount = 1;  // Start the move count 
  
 
 
    // Keep picking next points using 
    // Warnsdorff's heuristic 
    for (int i = 0; i < N * N - 1; ++i) 
    { 
        if (nextMove(a, &x, &y) == 0) 
            return false; 
        moveCount++; // Increment the move count 
    } 
  
    // Check if tour is closed (Can end 
    // at starting point) 
    if (!neighbour(x, y, sx, sy)) 
        return false; 
  
    print(a); 
    std::cout << "Minimum number of moves: " << moveCount << std::endl; 
    return true; 
} 
  
int main() 
{ 
    // To make sure that different random 
    // initial positions are picked. 
    srand(time(NULL)); 
  
    // While we don't get a solution 
    while (!findClosedTour()) 
    { 
        ;   
    } 
  
    return 0; 
}
