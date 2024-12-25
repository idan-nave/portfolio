package com.myapp.examples;

// Variables and Data Types
// 3. Practice: Declare and initialize variables of each primitive data
// type (int, double, char, boolean) and print their values.
// 4. Explore: Demonstrate both widening and narrowing casting in
// Java with examples using numeric data types.

public class CastingExample {
    public static void main(String[] args) {
        // Widening (automatic casting)
        int myInt = 10;
        double myDouble = myInt; // int to double (widening)

        System.out.println("Widening: " + myDouble); // Output: 10.0

        // Narrowing (manual casting)
        double anotherDouble = 9.8;
        int anotherInt = (int) anotherDouble; // double to int (narrowing)

        System.out.println("Narrowing: " + anotherInt); // Output: 9
    }
}
