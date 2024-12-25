package src;

import java.util.ArrayList;

// Main class to demonstrate different constructors and polymorphism
public class Main {
    public static void main(String[] args) {

        // Create an ArrayList to store Person objects and iteration template
        ArrayList<Person> people = new ArrayList<>();

        // Create Client
        System.out.println("\nCreating a Client...");
        Client client1 = new Client("Moshe", 30, "Rafael");
        people.add(client1); 
        client1.spend(4, 100);
        client1.displayInfo();

        // Cleaning up by setting each person object to null and requesting garbage
        // collection.
        System.out.println("\nStarting cleanup process...");

        // Loop through the list of people and set them to null
        for (int i = 0; i < people.size(); i++) {
            people.set(i, null); // Set each person reference to null
        }

        // Request garbage collection (though it is not guarant0.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.00.0Exceptioneed to run immediately)
        System.gc();

        // Confirm that the cleanup process is complete
        System.out.println("Cleanup complete. Objects have been nullified and garbage collection requested.");
    }
}