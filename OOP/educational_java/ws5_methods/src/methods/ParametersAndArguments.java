package methods;

public class ParametersAndArguments {
    // Method that takes name and age as parameters
    public static void displayUserDetails(String name, int age) {
        System.out.println("Name: " + name + ", Age: " + age);
    }

    public static void main(String[] args) {
        // Calling the displayUserDetails method with arguments
        displayUserDetails("John Doe", 30);
    }
}
