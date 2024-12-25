package oop;

public class Student {
    private String name;
    private int rollNumber;

    // Default constructor
    public Student() {
        this.name = "Unknown";
        this.rollNumber = 0;
    }

    // Parameterized constructor
    public Student(String name, int rollNumber) {
        this.name = name;
        this.rollNumber = rollNumber;
    }

    public static void main(String[] args) {
        Student student1 = new Student();
        System.out.println("Student1 - Name: " + student1.name + ", Roll Number: " + student1.rollNumber);

        Student student2 = new Student("John Doe", 101);
        System.out.println("Student2 - Name: " + student2.name + ", Roll Number: " + student2.rollNumber);
    }
}
