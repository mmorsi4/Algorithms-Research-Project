package com.mycompany.algoproject;

import java.util.*;

public class AlgoProject {

    // Class representing a rod in the Tower of Hanoi
    static class Rod {
        int num;
        String name;

        public Rod(int num, String name) {
            this.num = num;
            this.name = name;
        }
    }

    // Helper function to move an element (disk) from one rod to another
    public static void moveElement(Rod src, Rod dst) {
        System.out.println("Disk " + src.num + " moves from " + src.name + " to " + dst.name);
    }

    // Frame-Stewart Algorithm for Tower of Hanoi with 4 rods
    public static void hanoi4(int n, Rod src, Rod dst, Rod[] rods, int[] moves) {
        // Base case: if there's only one disk, move it directly
        if (n == 1) {
            moveElement(src, dst);
            moves[0]++;
            return;
        }

        // Step 1: Split the problem into two parts using Frame-Stewart approach
        int k = n / 2; // Divide the disks into two parts: k disks and (n - k) disks

        // Create an array for spare rods (rods that are not the source or destination)
        List<Rod> spareRods = new ArrayList<>();
        for (Rod rod : rods) {
            if (rod != src && rod != dst) {
                spareRods.add(rod);
            }
        }

        // Step 2: Move the first k disks from src to spare rod using all rods
        hanoi4(k, src, spareRods.get(0), rods, moves);

        // Step 3: Move the remaining n - k disks from src to dst using only the first two rods
        hanoi3(n - k, src, dst, rods, moves);

        // Step 4: Move the k disks from the spare rod to dst using all rods
        hanoi4(k, spareRods.get(0), dst, rods, moves);
    }

    // Helper function to move disks with 3 rods (simpler case)
    public static void hanoi3(int n, Rod src, Rod dst, Rod[] rods, int[] moves) {
        if (n == 1) {
            moveElement(src, dst);
            moves[0]++;
            return;
        }

        // Recursive case: Move (n-1) disks to spare rod
        List<Rod> spareRods = new ArrayList<>();
        for (Rod rod : rods) {
            if (rod != src && rod != dst) {
                spareRods.add(rod);
            }
        }

        hanoi3(n - 1, src, spareRods.get(0), rods, moves);

        // Move the last disk directly from src to dst
        moveElement(src, dst);
        moves[0]++;

        // Move the (n-1) disks from spare rod to dst
        hanoi3(n - 1, spareRods.get(0), dst, rods, moves);
    }

    // Main function for the Tower of Hanoi with 4 rods and n disks
    public static void hanoiAlg(Rod[] rods, int n, int[] moves) {
        hanoi4(n, rods[0], rods[rods.length - 1], rods, moves);
    }

    // Main method to test the algorithm with dynamic pegs and disks
    public static void main(String[] args) {
        int rodsCount = 4;  // Number of rods (pegs)
        int maxSize = 3;    // Number of disks

        // Dynamically create rods for the tower
        Rod[] rods = new Rod[rodsCount];
        for (int i = 0; i < rodsCount; i++) {
            char pegName = (char) ('a' + i);  // Generate 'a', 'b', 'c', 'd', etc.
            rods[i] = new Rod(i + 1, String.valueOf(pegName));
        }

        int[] moves = new int[1];  // To keep track of the number of moves
        hanoiAlg(rods, maxSize, moves);
        System.out.println("Total moves for " + maxSize + " disks with " + rodsCount + " rods: " + moves[0]);
    }
}
