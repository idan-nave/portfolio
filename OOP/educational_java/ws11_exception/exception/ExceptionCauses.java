package exception;

public class ExceptionCauses {
    public static void main(String[] args) {
        System.out.println("Common causes of exceptions in Java:");
        System.out.println("1. Divide by zero.");
        System.out.println("2. Null pointer reference.");
        System.out.println("3. Array index out of bounds.");
        System.out.println("4. Invalid user input.");
        System.out.println("5. File not found or I/O issues.");
        
        System.out.println("\nDifference between Error and Exception:");
        System.out.println("Error: A severe problem that occurs beyond the control of the program, such as 'OutOfMemoryError'.");
        System.out.println("Exception: A problem that can be caught and handled in the program, like 'ArithmeticException'.");
    }
}
