package strings;

public class UTF16Encoding {
    public static void main(String[] args) {
        // A simple string containing different characters
        String str = "Hello 🌍";

        // UTF-16 encoding in Java
        System.out.println("String: " + str);
        System.out.println("String length (UTF-16 encoded): " + str.length());
    }
}
