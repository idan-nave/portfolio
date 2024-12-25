package oop;

public class StudentWithGettersSetters {
    private String name;
    private int rollNumber;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getRollNumber() {
        return rollNumber;
    }

    public void setRollNumber(int rollNumber) {
        this.rollNumber = rollNumber;
    }

    public static void main(String[] args) {
        StudentWithGettersSetters student = new StudentWithGettersSetters();
        student.setName("Alice");
        student.setRollNumber(123);
        System.out.println("Student Name: " + student.getName() + ", Roll Number: " + student.getRollNumber());
    }
}
