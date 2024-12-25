package strings;

public class StringCreation {
    public static void main(String[] args) {
        // String creation using literals
        String literalString = "Hello, World!";
        String anotherLiteralString = "Hello, World!"; // Same literal, refers to the same object in the pool

        // String creation using the new keyword
        String newString = new String("Hello, World!"); // Refers to a new object, even if the content is the same

        System.out.println("Literal String: " + literalString);
        System.out.println("New String: " + newString);

        // Check if both strings are pointing to the same object
        System.out.println("Are the literal and new string the same object? " + (literalString == anotherLiteralString)); // True
        System.out.println("Are the literal and new string the same object? " + (literalString == newString)); // False
    }
}
