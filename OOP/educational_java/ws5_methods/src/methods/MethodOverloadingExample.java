package methods;

public class MethodOverloadingExample {
    // Method that takes a String
    public static void printMessage(String message) {
        System.out.println("Message: " + message);
    }

    // Method that takes an int
    public static void printMessage(int number) {
        System.out.println("Number: " + number);
    }

    public static void main(String[] args) {
        // Calling overloaded methods
        printMessage("Hello!");
        printMessage(123);
    }
}
