package calc;

public class ArithmeticOperators {

    public static void main(String[] args) {
        // 1. Arithmetic Operators
        int a = 10;
        int b = 5;
        System.out.println("Arithmetic Operators:");
        System.out.println("a + b = " + (a + b));
        System.out.println("a - b = " + (a - b));
        System.out.println("a * b = " + (a * b));
        System.out.println("a / b = " + (a / b));
        System.out.println("a % b = " + (a % b));

        // 2. Increment and Decrement
        System.out.println("\nIncrement and Decrement:");
        int x = 5;
        System.out.println("Pre-Increment: " + (++x)); // Pre-increment
        System.out.println("Post-Increment: " + (x++)); // Post-increment
        System.out.println("Value of x after Post-Increment: " + x); // x after post-increment

        // 3. Logical Operators
        System.out.println("\nLogical Operators:");
        boolean val1 = true;
        boolean val2 = false;
        System.out.println("val1 && val2 = " + (val1 && val2));
        System.out.println("val1 || val2 = " + (val1 || val2));
        System.out.println("!val1 = " + !val1);

        // 4. Assignment Operators
        System.out.println("\nAssignment Operators:");
        int c = 5;
        c += 3; // c = c + 3
        System.out.println("c += 3: " + c);
        c -= 2; // c = c - 2
        System.out.println("c -= 2: " + c);
        c *= 4; // c = c * 4
        System.out.println("c *= 4: " + c);
        c /= 2; // c = c / 2
        System.out.println("c /= 2: " + c);
        c %= 3; // c = c % 3
        System.out.println("c %= 3: " + c);

        // 5. Comparison Operators
        System.out.println("\nComparison Operators:");
        int d = 8;
        int e = 10;
        System.out.println("d == e: " + (d == e));
        System.out.println("d != e: " + (d != e));
        System.out.println("d > e: " + (d > e));
        System.out.println("d < e: " + (d < e));
        System.out.println("d >= e: " + (d >= e));
        System.out.println("d <= e: " + (d <= e));

        // 6. Bitwise Operators
        System.out.println("\nBitwise Operators:");
        int f = 5; // 0101
        int g = 3; // 0011
        System.out.println("f & g: " + (f & g)); // AND
        System.out.println("f | g: " + (f | g)); // OR
        System.out.println("f ^ g: " + (f ^ g)); // XOR
        System.out.println("~f: " + (~f)); // NOT
        System.out.println("f << 1: " + (f << 1)); // Left Shift
        System.out.println("f >> 1: " + (f >> 1)); // Right Shift

        // 7. Practical Use of Logical and Comparison Operators
        System.out.println("\nLogical and Comparison Operators Combined:");
        int number = 15;
        System.out.println("Is number between 10 and 20? " + (number >= 10 && number <= 20));

        // 8. Explore Modulus
        System.out.println("\nExplore Modulus:");
        int constantValue = 3;
        for (int i = 1; i <= 10; i++) {
            System.out.println(i + " % " + constantValue + " = " + (i % constantValue));
        }
    }
}
