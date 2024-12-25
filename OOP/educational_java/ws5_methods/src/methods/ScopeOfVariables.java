package methods;

public class ScopeOfVariables {
    public static void testScope() {
        int localVar = 10; // Local variable inside the method
        System.out.println("Inside method: " + localVar);
    }

    public static void main(String[] args) {
        // Local variable cannot be accessed outside the method
        // System.out.println("Outside method: " + localVar); // This will cause an error
        testScope();
    }
}
