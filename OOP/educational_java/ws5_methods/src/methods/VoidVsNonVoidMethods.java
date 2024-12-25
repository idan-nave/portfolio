package methods;

public class VoidVsNonVoidMethods {
    // Void method
    public static void displayGreeting() {
        System.out.println("Hello, welcome to the program!");
    }

    // Non-void method that returns a greeting message
    public static String getGreeting() {
        return "Hello, welcome to the program!";
    }

    public static void main(String[] args) {
        // Using void method
        displayGreeting();
        // Using non-void method
        System.out.println(getGreeting());
    }
}
