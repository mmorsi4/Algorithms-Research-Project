/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.devideandconquer;


public class DevideandConquer {
    private static int moveCount = 0;

    // Main recursive function
    private static void solveHanoi(int n, char source, char target, 
                                 char aux1, char aux2) {
        if (n == 1) {
            moveDisk(source, target);
            return;
        }
        
        // Split disks into two roughly equal groups
        int split = n / 2;
        
        // Move top split disks to first auxiliary peg
        solveHanoi(split, source, aux1, target, aux2);
        
        // Move remaining disks to target using 3 pegs
        solveHanoi3Pegs(n - split, source, target, aux2);
        
        // Move split disks from first auxiliary to target
        solveHanoi(split, aux1, target, source, aux2);
    }

    // Standard 3-peg implementation
    private static void solveHanoi3Pegs(int n, char source, char target, 
                                      char auxiliary) {
        if (n == 0) return;
        
        solveHanoi3Pegs(n - 1, source, auxiliary, target);
        moveDisk(source, target);
        solveHanoi3Pegs(n - 1, auxiliary, target, source);
    }

    // Helper method to track moves
    private static void moveDisk(char from, char to) {
        System.out.println("Move " + (++moveCount) + ": Disk from " + 
                         from + " to " + to);
    }

    public static void main(String[] args) {
        int disks = 3;
        System.out.println("Solving 4-peg Tower of Hanoi with " + disks + " disks:");
        
        // A, B, C, D are the peg names
        solveHanoi(disks, 'A', 'D', 'B', 'C');
        
        System.out.println("\nTotal moves: " + moveCount);
    }
}