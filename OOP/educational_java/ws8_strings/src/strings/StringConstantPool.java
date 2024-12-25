package strings;

public class StringConstantPool {
    public static void main(String[] args) {
        // Creating strings using literals
        String s1 = "Java";
        String s2 = "Java"; // Refers to the same object in the string pool

        // Creating strings using new keyword
        String s3 = new String("Java"); // A new object is created in the heap

        System.out.println("s1 == s2: " + (s1 == s2)); // True, they point to the same object in the pool
        System.out.println("s1 == s3: " + (s1 == s3)); // False, s3 points to a new object
    }
}
