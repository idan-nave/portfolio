package strings;

public class ImmutabilityExample {
    public static void main(String[] args) {
        String originalString = "Hello";
        String modifiedString = originalString.concat(" World");

        System.out.println("Original String: " + originalString); // "Hello"
        System.out.println("Modified String: " + modifiedString); // "Hello World"

        // The original string remains unchanged, demonstrating immutability
        System.out.println("Is original string changed? " + (originalString == modifiedString)); // False
    }
}
