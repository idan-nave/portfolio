package oop;

class Person {
    String name;

    // Constructor to initialize the name
    public Person(String name) {
        this.name = name;
    }
}

class Teacher extends Person {
    public Teacher(String name) {
        super(name); // Call the constructor of the parent class
    }

    public static void main(String[] args) {
        Teacher teacher = new Teacher("Mr. Smith");
        System.out.println("Teacher Name: " + teacher.name);
    }
}
