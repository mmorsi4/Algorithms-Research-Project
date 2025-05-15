/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.iterativesolution;

/*import java.util.*;

public class IterativeSolution {

    public static void main(String[] args) {
        int n = 5;  // Number of discs
        solveIterative4PegHanoi(n, "a", "b", "c", "d");
    }

    public static void solveIterative4PegHanoi(int n, String S, String D, String A1, String A2) {
        int m = (int) Math.floor(Math.sqrt(2 * n + 0.25) - 0.5);

        // Step 1: Compute initial slice sizes
        int[] slices = new int[m];
        for (int i = 0; i < m; i++) {
            slices[i] = m - i;
        }

        // Step 2: Adjust slices cyclically to sum to n
        int sum = Arrays.stream(slices).sum();
        int index = 0;
        while (sum < n) {
            slices[index % m]++;
            sum++;
            index++;
        }

        // Print slices
        System.out.println("Slice sizes: " + Arrays.toString(slices));
        System.out.println();

        // Step 3: Determine cyclic move order
        List<String> pegCycle = new ArrayList<>();
        if (m % 2 == 0) {
            Collections.addAll(pegCycle, S, A1, D);
        } else {
            Collections.addAll(pegCycle, S, D, A1);
        }

        int totalMoves = (int) Math.pow(2, n) - 1;
        int moveCount = 0;
        int smallestDisc = 1;

        // Simulate iterative moves (mock logic)
        while (moveCount < totalMoves) {
            String from = pegCycle.get(moveCount % pegCycle.size());
            String to = pegCycle.get((moveCount + 1) % pegCycle.size());

            // Move smallest disc
            System.out.println("Disk " + smallestDisc + " moves from " + from + " to " + to);
            moveCount++;

            // Move larger disc (simulated)
            if (moveCount < totalMoves) {
                int simulatedLargerDisc = Math.min(n, smallestDisc + 1 + (moveCount % (n - 1)));
                String largerFrom = pegCycle.get((moveCount + 1) % pegCycle.size());
                String largerTo = pegCycle.get((moveCount + 2) % pegCycle.size());
                System.out.println("Disk " + simulatedLargerDisc + " moves from " + largerFrom + " to " + largerTo);
                moveCount++;
            }
        }

        System.out.println("\nTotal moves: " + moveCount);
    }
}*/
/*import java.util.*;

public class IterativeSolution {

    // Stack implementation
    class Stack {
        int capacity;
        int top;
        int[] array;
        
        Stack(int capacity) {
            this.capacity = capacity;
            this.top = -1;
            this.array = new int[capacity];
        }
    }

    private Stack src, dest, aux1, aux2;
    private int moveCount = 0;
    private char[] pegNames = {'S', 'D', 'A', 'B'};

    // Initialize stacks
    void initStacks(int n) {
        src = new Stack(n);
        dest = new Stack(n);
        aux1 = new Stack(n);
        aux2 = new Stack(n);
        
        // Fill source stack with disks
        for (int i = n; i >= 1; i--) {
            push(src, i);
        }
    }

    boolean isFull(Stack st) {
        return st.top == st.capacity - 1;
    }

    boolean isEmpty(Stack st) {
        return st.top == -1;
    }

    void push(Stack st, int item) {
        if (!isFull(st)) {
            st.array[++st.top] = item;
        }
    }

    int pop(Stack st) {
        return isEmpty(st) ? Integer.MIN_VALUE : st.array[st.top--];
    }

    int peek(Stack st) {
        return isEmpty(st) ? Integer.MIN_VALUE : st.array[st.top];
    }

    void printMove(char from, char to, int disk) {
        System.out.println("Move " + (++moveCount) + ": Disk " + disk + 
                          " from " + from + " to " + to);
    }

    // iterative approach for 4 pegs
    void solveIterative(int n) {
        initStacks(n);
        List<Stack> pegs = Arrays.asList(src, dest, aux1, aux2);
        
        // Determine total moves needed (this is a placeholder - actual count will vary)
        long maxMoves = (long)Math.pow(2, n) - 1; // Upper bound
        
        while (!isEmpty(src) || !isEmpty(aux1) || !isEmpty(aux2)) {
            // Try all possible non-cyclic moves
            for (int i = 0; i < pegs.size(); i++) {
                for (int j = 0; j < pegs.size(); j++) {
                    if (i != j) {
                        Stack from = pegs.get(i);
                        Stack to = pegs.get(j);
                        
                        if (!isEmpty(from) && 
                            (isEmpty(to) || peek(from) < peek(to))) {
                            int disk = pop(from);
                            push(to, disk);
                            printMove(pegNames[i], pegNames[j], disk);
                            break; // Make one move at a time
                        }
                    }
                }
            }
            
            // Additional optimization to prevent infinite loops
            if (moveCount > maxMoves) {
                System.out.println("Reached maximum move limit");
                break;
            }
        }
        
        System.out.println("Total moves: " + moveCount);
    }

    public static void main(String[] args) {
        IterativeSolution solver = new IterativeSolution();
        int disks = 5;
        System.out.println("Solving 4-peg Tower of Hanoi with " + disks + " disks");
        solver.solveIterative(disks);
    }
}*/
import java.util.*;

public class IterativeSolution {

    // Stack Class
    class Stack {
        int capacity;
        int top;
        int array[];
    }

    private int moveCount = 0; // Track total moves

    // Initialize stack
    Stack initStack(int capacity) {
        Stack st = new Stack();
        st.capacity = capacity;
        st.top = -1;
        st.array = new int[capacity];
        return st;
    }

    boolean isFull(Stack st) {
        return (st.top == st.capacity - 1);
    }

    boolean isEmpty(Stack st) {
        return (st.top == -1);
    }

    void push(Stack st, int item) {
        if (isFull(st)) return;
        st.array[++st.top] = item;
    }

    int pop(Stack st) {
        if (isEmpty(st)) return Integer.MIN_VALUE;
        return st.array[st.top--];
    }

    void printMove(char from, char to, int disk) {
        System.out.println("Move " + (++moveCount) + ": Disk " + disk + 
                         " from " + from + " to " + to);
    }

    void moveDisk(Stack src, Stack dest, char s, char d) {
        int disk1 = pop(src);
        int disk2 = pop(dest);

        if (disk1 == Integer.MIN_VALUE) {
            push(src, disk2);
            printMove(d, s, disk2);
        } 
        else if (disk2 == Integer.MIN_VALUE) {
            push(dest, disk1);
            printMove(s, d, disk1);
        } 
        else if (disk1 > disk2) {
            push(src, disk1);
            push(src, disk2);
            printMove(d, s, disk2);
        } 
        else {
            push(dest, disk2);
            push(dest, disk1);
            printMove(s, d, disk1);
        }
    }

    void iterative4PegHanoi(int n) {
        Stack src = initStack(n);
        Stack dest = initStack(n);
        Stack aux1 = initStack(n);
        Stack aux2 = initStack(n);
        
        char s = 'S', d = 'D', a1 = 'A', a2 = 'B';
        
        // Initialize source stack
        for (int i = n; i >= 1; i--) {
            push(src, i);
        }

        // Extended movement pattern for 4 pegs
        int cycle = 6; // Number of possible moves between 4 pegs
        int totalMoves = (int)(Math.pow(2, n)) - 1; // Upper bound
        
        for (int move = 1; move <= totalMoves; move++) {
            switch (move % cycle) {
                case 1: moveDisk(src, aux1, s, a1); break;
                case 2: moveDisk(src, aux2, s, a2); break;
                case 3: moveDisk(aux1, aux2, a1, a2); break;
                case 4: moveDisk(src, dest, s, d); break;
                case 5: moveDisk(aux2, dest, a2, d); break;
                case 0: moveDisk(aux1, dest, a1, d); break;
            }
            
            // Early termination if puzzle is solved
            if (dest.top == n - 1) break;
        }
        
        System.out.println("Total moves used: " + moveCount);
    }

    public static void main(String[] args) {
        IterativeSolution solver = new IterativeSolution();
        int disks = 8;
        System.out.println("Solving 4-peg Tower of Hanoi with " + disks + " disks");
        solver.iterative4PegHanoi(disks);
    }
}