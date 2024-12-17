package src;

// David class extends Person, demonstrating Overloading and Overriding
class David extends Person {
    // Constructor for David (calls the parameterized constructor of the superclass)
    public David(String name, int age) {
        super(name, age);  // Calls the parameterized constructor of the Person class
        System.out.println("David Constructor: " + name + " is a David!");
    }

    // Overloaded method: Different way to display information based on additional information (overloading)
    public void displayInfo(String occupation) {
        System.out.println("David: " + getName() + ", Age: " + getAge() + ", Occupation: " + occupation + ", !IM HIDING MY ID!");
    }

    // Overridden method: Display Info for David (overrides the displayInfo in Person)
    @Override
    public void displayInfo() {
        System.out.println("David (Overridden): " + getName() + ", Age: " + getAge());
    }
}
