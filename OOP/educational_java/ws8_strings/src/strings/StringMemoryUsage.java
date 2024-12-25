package strings;

public class StringMemoryUsage {
    public static void main(String[] args) {
        // Using string literals
        String literalString = "Java";

        // Using the new keyword
        String newString = new String("Java");

        // Print their hash codes to show memory addresses
        System.out.println("Literal String HashCode: " + literalString.hashCode());
        System.out.println("New String HashCode: " + newString.hashCode());

        // String literals are stored in the String Pool, reducing memory usage.
    }
}
