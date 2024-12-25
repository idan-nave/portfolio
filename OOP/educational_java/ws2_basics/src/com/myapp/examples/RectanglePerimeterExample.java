package com.myapp.examples;

// 8. Extend: Enhance the RectangleArea program to also calculate
// and display the perimeter of the rectangle.

import java.util.Scanner;

public class RectanglePerimeterExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Take user input for rectangle length and width
        System.out.print("Enter the length of the rectangle: ");
        double length = scanner.nextDouble();

        System.out.print("Enter the width of the rectangle: ");
        double width = scanner.nextDouble();

        // Calculate and display the area
        double area = length * width;
        double perimeter = 2 * (length + width);

        System.out.println("The area of the rectangle is: " + area);
        System.out.println("The perimeter of the rectangle is: " + perimeter);

        scanner.close();
    }
}
