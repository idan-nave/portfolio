package methods;

public class ReturnTypesExample {
    // Method that adds two integers and returns the sum
    public static int addNumbers(int a, int b) {
        return a + b;
    }

    public static void main(String[] args) {
        // Calling the addNumbers method and printing the result
        int result = addNumbers(10, 5);
        System.out.println("The sum is: " + result);
    }
}
