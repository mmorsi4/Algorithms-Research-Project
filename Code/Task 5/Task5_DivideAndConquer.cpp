#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int n;                 // Total number of hiding spots
int target_position;   // Actual position of the moving target
int shots_taken = 0;   // Counter for number of shots

// Function to move the target to an adjacent position
void move_target() {
    if (shots_taken%2!=0) return; // Only move after  2 consective shots
    
    int direction = rand() % 2; // 0 for left, 1 for right
    if (direction == 0 && target_position > 1) {
        target_position--;
    } else if (direction == 1 && target_position < n) {
        target_position++;
    }
    // If can't move in chosen direction, stays in place
}

bool hit(int position) {
    shots_taken++;
    cout << "Shot " << shots_taken << ": Shooting at position " << position;
    cout << " (Target is at " << target_position << ")";
    
    if (position == target_position) {
        cout << " — HIT!" <<endl;
        cout << "\nTarget destroyed in " << shots_taken << " shots!" <<endl;
        return true;
    } else {
        cout << " — Missed." << endl;
        move_target(); // Target moves only after 2 consective shots
        return false;
    }
}

// Recursive Divide & Conquer shooting strategy
void shoot_target(int left, int right,bool& s) {
    if (left > right || s) return; // stop recursion if already hit
    // Base case - single position
    if (left == right) {
        s=hit(left);
        return;
    }
    // Midpoint shoot
    int mid = left + (right - left) / 2;
    s=hit(mid);
    if (s) return; // Stop further shooting if target hit
    // Recursively search left and right halves
    shoot_target(left, mid - 1,s);
    shoot_target(mid + 1, right,s);
}

int main() {
    srand(time(0));
    cout << "Enter the number of hiding spots (n): ";
    cin >> n;
    bool s = false;
    if (n < 1) {
        cerr << "Invalid value for n." << endl;
        return 1;
    }
    target_position = 1 + rand() % n;
    cout << "Target starts at position " << target_position << endl;
    cout << "Target will move after the 2nd shot\n" << endl;
    while (!s) {
        shoot_target(1, n, s);
    }
    return 0;
}