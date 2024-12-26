package src;

// Person class with different constructors, demonstrating Encapsulation, Inheritance, and Polymorphism
class Person {
    // Static & Encapsulation: a static quality of the class shared by all objects, will be setted with constructor / method
    private static int ID_COUNTER = 100000000;
    
    // Encapsulation: Private variables with _ prefix
    private String _name;
    private int _age;
    private int _id;

    // Default constructor (no parameters)
    public Person() {
        _name = "Unknown";
        _age = 0;
        _id = genID();
        System.out.println("Default Constructor: Person is created with default values.");
    }

    // Parameterized constructor (initializes with given values)
    public Person(String name, int age) {
        _name = name;
        _age = age;
        _id = genID();
        System.out.println("Parameterized Constructor: Person is created with name " + _name + " and age " + _age);
    }

    // Copy constructor (creates a new object from an existing one)
    public Person(Person other) {
        _name = other._name;
        _age = other._age;
        _id = genID();
        System.out.println("Copy Constructor: Person is created by copying from another person.");
    }

    // Getter for _name (Encapsulation)
    public String getName() {
        return _name;
    }

    // Getter for _age (Encapsulation)
    public int getAge() {
        return _age;
    }

    // Method to display information about the person (this will be overridden by subclasses)
    public void displayInfo() {
        System.out.println("Person: " + _name + ", Age: " + _age + "ID: " + _id);
    }

    // Method to increment the id of the new person,
    // belongs to Person class, and no to any of Person instances, and only Once!
    protected static int genID()
    {
        return ++ID_COUNTER;
    }
}
