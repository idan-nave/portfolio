package exception;

public class MultipleCatchExample {
    public static void main(String[] args) {
        String[] arr = {"A", "B", "C"};
        String str = null;

        try {
            // Generate ArrayIndexOutOfBoundsException
            System.out.println(arr[3]);  // This will throw ArrayIndexOutOfBoundsException
            
            // Generate NullPointerException
            System.out.println(str.length());  // This will throw NullPointerException
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Caught ArrayIndexOutOfBoundsException: " + e.getMessage());
        } catch (NullPointerException e) {
            System.out.println("Caught NullPointerException: " + e.getMessage());
        }
    }
}
