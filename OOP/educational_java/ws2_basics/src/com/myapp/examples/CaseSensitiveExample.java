package com.myapp.examples;

// Syntax and Basic Structure
// 1. Explain: Is Java case-sensitive? Provide an example showing the
// difference between two variables with similar names but different
// cases.

public class CaseSensitiveExample {
    public static void main(String[] args) {
        int number = 10;
        int Number = 20;

        System.out.println("number: " + number); // Output: 10
        System.out.println("Number: " + Number); // Output: 20
    }
}
