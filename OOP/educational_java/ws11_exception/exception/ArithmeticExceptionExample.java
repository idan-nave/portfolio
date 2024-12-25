package exception;

public class ArithmeticExceptionExample {
    public static void main(String[] args) {
        int result = 0;
        try {
            result = 10 / 0;  // This will throw ArithmeticException
        } catch (ArithmeticException e) {
            System.out.println("Caught an ArithmeticException: " + e.getMessage());
        } finally {
            System.out.println("This block is always executed for resource cleanup.");
        }
    }
}
