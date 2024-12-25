package strings;

public class StringBuilderEfficiency {
    public static void main(String[] args) {
        // Using StringBuilder for efficient string concatenation
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 1000; i++) {
            sb.append("Hello ");
        }

        String result = sb.toString();
        System.out.println("StringBuilder Result Length: " + result.length());

        // Comparing with using + operator
        String str = "";
        for (int i = 0; i < 1000; i++) {
            str += "Hello "; // Inefficient, creates a new object each time
        }
        System.out.println("Using + operator Result Length: " + str.length());
    }
}
