package animal;

// Abstract base class demonstrating abstraction and encapsulation
abstract class Animal {
    private String name; // Encapsulation: Private data member
    private int age; // Encapsulation: Private data member

    // Constructor for Animal class
    public Animal(String name, int age) {
        this.name = name;
        this.age = age;
    }

    // Getter for name (encapsulation)
    public String getName() {
        return name;
    }

    // Setter for name (encapsulation)
    public void setName(String name) {
        this.name = name;
    }

    // Getter for age (encapsulation)
    public int getAge() {
        return age;
    }

    // Setter for age (encapsulation)
    public void setAge(int age) {
        this.age = age;
    }

    // Abstract method (abstract): Animal subclasses must implement this
    public abstract void makeSound(); // Abstract method enforces subclass implementation

    // Destructor-like method in Java (not used much, Java uses garbage collection)
    protected void cleanup() {
        System.out.println(getName() + " is being destroyed");
        // Here you can handle resource cleanup, such as closing file handles, database
        // connections, etc.
    }
}
