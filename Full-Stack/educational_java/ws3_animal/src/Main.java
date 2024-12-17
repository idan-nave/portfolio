package src;

// Main class demonstrating encapsulation, polymorphism, and inheritance
public class Main {
    public static void main(String[] args) {
        // Create a Dog object (polymorphism in action, Dog object is treated as Animal)
        Animal myDog = new Dog("Buddy", 5);

        // Encapsulation: Accessing the properties via getter methods
        System.out.println("Name: " + myDog.getName());
        System.out.println("Age: " + myDog.getAge());

        // Polymorphism: Calling the makeSound function (resolved at runtime)
        myDog.makeSound(); // Outputs: Buddy says: Woof!

        // Explicit cleanup method call (manual destructor-like behavior)
        myDog.cleanup(); // Outputs: Buddy is being cleaned up!

        // Optionally, simulate garbage collection
        myDog = null; // Dereference the Dog object
        System.gc(); // Request garbage collection (not guaranteed to run immediately)

        // End of main method, output:
        // Name: Buddy
        // Age: 5
        // Buddy says: Woof!
        // Buddy is being destroyed
    }

}
