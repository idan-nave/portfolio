package src;

import java.util.ArrayList;

// Main class to demonstrate different constructors and polymorphism
public class Main {
    public static void main(String[] args) {

        // Create an ArrayList to store Person objects and iteration template
        ArrayList<Person> people = new ArrayList<>();

        // Demonstrating the Default Constructor
        System.out.println("Creating a Person using the Default Constructor:");
        Person person1 = new Person(); // Calls the default constructor
        person1.displayInfo(); // Calls the overridden displayInfo method from Person
        people.add(person1);  // Add to the list

        System.out.println("\nCreating a Person using the Parameterized Constructor:");
        // Demonstrating the Parameterized Constructor
        Person person2 = new Person("John", 30); // Calls the parameterized constructor
        person2.displayInfo(); // Calls the overridden displayInfo method from Person
        people.add(person2);  // Add to the list


        System.out.println("\nCreating a Person using the Copy Constructor:");
        // Demonstrating the Copy Constructor
        Person person3 = new Person(person2); // Calls the copy constructor
        person3.displayInfo(); // Calls the overridden displayInfo method from Person
        people.add(person3);  // Add to the list

        // Demonstrating the David subclass and both polymorphism types
        System.out.println("\nCreating a David using the Parameterized Constructor:");
        David david1 = new David("David", 25); // Calls the David constructor (parameterized)
        
        david1.displayInfo(); // Calls the overridden displayInfo method in David (overriding)

        System.out.println("\nDemonstrating Overloaded displayInfo Method for David:");
        david1.displayInfo("Software Developer"); // Calls the overloaded displayInfo method for David

        // Polymorphism: Person reference pointing to a David object
        System.out.println("\nUsing Polymorphism: Person reference pointing to David object:");
        Person person4 = new David("David Jr.", 22); // Person reference, but it's a David object
        person4.displayInfo(); // Calls the overridden displayInfo method from David (polymorphism)
        people.add(person4);  // Add to the list


        // Cleaning up by setting each person object to null and requesting garbage
        // collection.
        System.out.println("\nStarting cleanup process...");

        // Loop through the list of people and set them to null
        for (int i = 0; i < people.size(); i++) {
            people.set(i, null); // Set each person reference to null
        }

        // Request garbage collection (though it is not guaranteed to run immediately)
        System.gc();

        // Confirm that the cleanup process is complete
        System.out.println("Cleanup complete. Objects have been nullified and garbage collection requested.");
    }
}

// OUTPUT:
// Creating a Person using the Default Constructor:
// Default Constructor: Person is created with default values.
// Person: Unknown, Age: 0

// Creating a Person using the Parameterized Constructor:
// Parameterized Constructor: Person is created with name John and age 30
// Person: John, Age: 30

// Creating a Person using the Copy Constructor:
// Copy Constructor: Person is created by copying from another person.
// Person: John, Age: 30

// Creating a David using the Parameterized Constructor:
// Parameterized Constructor: Person is created with name David and age 25
// David Constructor: David is a David!
// David (Overridden): David, Age: 25

// Demonstrating Overloaded displayInfo Method for David:
// David: David, Age: 25, Occupation: Software Developer

// Using Polymorphism: Person reference pointing to David object:
// Parameterized Constructor: Person is created with name David Jr. and age 22
// David Constructor: David Jr. is a David!
// David (Overridden): David Jr., Age: 22
