package com.myapp.examples;

// Input and Output
// 6. Error Handling: Modify the provided input example to handle
// cases where the user enters an invalid input type (e.g., entering
// text where a number is expected).

import java.util.Scanner;

public class ErrorHandlingExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Take String input
        System.out.print("Enter your age: ");
        try {
            int age = Integer.parseInt(scanner.nextLine()); // Try to parse the integer
            System.out.println("Your age is: " + age);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input! Please enter a valid number.");
        }

        scanner.close();
    }
}
