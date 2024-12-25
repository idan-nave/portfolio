package methods;

import java.util.Scanner;

public class ModularCodePractice {
    // Method to accept user input
    public static void inputDetails() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your name: ");
        String name = scanner.nextLine();
        System.out.print("Enter your age: ");
        int age = scanner.nextInt();
        processDetails(name, age);
    }

    // Method to process details
    public static void processDetails(String name, int age) {
        String message = "Hello " + name + ", you are " + age + " years old.";
        displayDetails(message);
    }

    // Method to display details
    public static void displayDetails(String message) {
        System.out.println(message);
    }

    public static void main(String[] args) {
        // Calling inputDetails to start the process
        inputDetails();
    }
}
