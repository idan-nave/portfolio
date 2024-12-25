package com.myapp.examples;

// Input and Output
// 5. Experiment: Create a program using the Scanner class to take
// three different types of user inputs: String, int, and double.
// Display the inputs formatted in a sentence.

import java.util.Scanner;

public class UserInputExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Take String input
        System.out.print("Enter your name: ");
        String name = scanner.nextLine();

        // Take int input
        System.out.print("Enter your age: ");
        int age = scanner.nextInt();

        // Take double input
        System.out.print("Enter your height (in meters): ");
        double height = scanner.nextDouble();

        // Display the inputs in a sentence
        System.out.println("Hello, " + name + ". You are " + age + " years old and " + height + " meters tall.");

        scanner.close();
    }
}
