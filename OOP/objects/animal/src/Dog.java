package src;

// Derived class demonstrating inheritance and polymorphism
class Dog extends Animal { // Inheritance: Dog class inherits from Animal class

    // Constructor for Dog class
    public Dog(String name, int age) {
        super(name, age); // Call the constructor of the Animal class
    }

    // Override the makeSound() function (polymorphism)
    @Override
    public void makeSound() {
        System.out.println(getName() + " says: Woof!"); // Polymorphism: Dog's own implementation
    }
}
