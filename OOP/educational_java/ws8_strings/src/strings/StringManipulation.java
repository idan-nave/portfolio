package strings;

public class StringManipulation {
    public static void main(String[] args) {
        String str = "Hello, World!";

        // Convert to uppercase and lowercase
        System.out.println("Uppercase: " + str.toUpperCase());
        System.out.println("Lowercase: " + str.toLowerCase());

        // Find the length of a string
        System.out.println("Length of string: " + str.length());

        // Extract a substring
        System.out.println("Substring (from index 7): " + str.substring(7));
    }
}
