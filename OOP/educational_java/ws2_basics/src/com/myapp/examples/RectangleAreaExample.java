package com.myapp.examples;

// 7. Basic Example - Area Calculation
// add functionality to accept length and width as user inputs
// instead of hardcoding them.

import java.util.Scanner;

public class RectangleAreaExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Take user input for rectangle length and width
        System.out.print("Enter the length of the rectangle: ");
        double length = scanner.nextDouble();

        System.out.print("Enter the width of the rectangle: ");
        double width = scanner.nextDouble();

        // Calculate and display the area
        double area = length * width;
        System.out.println("The area of the rectangle is: " + area);

        scanner.close();
    }
}
