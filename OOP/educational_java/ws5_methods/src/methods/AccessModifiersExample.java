package methods;

public class AccessModifiersExample {
    // Public method
    public void publicMethod() {
        System.out.println("This is a public method.");
    }

    // Private method
    private void privateMethod() {
        System.out.println("This is a private method.");
    }

    public static void main(String[] args) {
        AccessModifiersExample obj = new AccessModifiersExample();
        // Calling public method
        obj.publicMethod();
        // Calling private method will cause an error
        // obj.privateMethod(); // Uncommenting this line will result in an error
    }
}
