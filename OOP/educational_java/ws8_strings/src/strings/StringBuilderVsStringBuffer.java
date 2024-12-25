package strings;

public class StringBuilderVsStringBuffer {
    public static void main(String[] args) {
        // Using String (immutable)
        String str1 = "Hello";
        str1 = str1 + " World"; // Creates a new string object
        System.out.println("Using String: " + str1);

        // Using StringBuilder (mutable, not thread-safe)
        StringBuilder sb = new StringBuilder("Hello");
        sb.append(" World"); // Appends without creating a new object
        System.out.println("Using StringBuilder: " + sb);

        // Using StringBuffer (mutable, thread-safe)
        StringBuffer sbf = new StringBuffer("Hello");
        sbf.append(" World");
        System.out.println("Using StringBuffer: " + sbf);
    }
}
