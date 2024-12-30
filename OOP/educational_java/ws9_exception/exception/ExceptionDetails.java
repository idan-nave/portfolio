package exception;

public class ExceptionDetails {
    public static void main(String[] args) {
        try {
            int result = 10 / 0;  // This will throw ArithmeticException
        } catch (ArithmeticException e) {
            System.out.println("Exception message: " + e.getMessage());
            System.out.println("Exception toString: " + e.toString());
            System.out.print("Stack trace: ");
            e.printStackTrace();
        }
    }
}
