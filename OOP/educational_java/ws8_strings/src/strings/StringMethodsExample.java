package strings;

public class StringMethodsExample {
    public static void main(String[] args) {
        String str = "Hello, World!";

        // indexOf()
        int index = str.indexOf("World");
        System.out.println("Index of 'World': " + index);

        // charAt()
        char character = str.charAt(6); // Character at index 6
        System.out.println("Character at index 6: " + character);

        // replace()
        String replaced = str.replace("World", "Java");
        System.out.println("Replaced string: " + replaced);
    }
}
