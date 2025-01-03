package src;

public class Circle {
    // Instance variable for the radius of the circle
    private double radius;

    // Constructor to initialize the radius
    public Circle(double radius) {
        this.radius = radius;
    }

    // Default constructor (radius = 1)
    public Circle() {
        this.radius = 1.0;
    }

    // Getter method for the radius
    public double getRadius() {
        return radius;
    }

    // Setter method for the radius
    public void setRadius(double radius) {
        this.radius = radius;
    }

    // Method to calculate the area of the circle
    public double getArea() {
        return Math.PI * radius * radius;
    }

    // Method to calculate the circumference of the circle
    public double getCircumference() {
        return 2 * Math.PI * radius;
    }

    // Method to display the details of the circle
    public void displayDetails() {
        System.out.println("Circle with radius: " + radius);
        System.out.println("Area: " + getArea());
        System.out.println("Circumference: " + getCircumference());
    }

    // Main method to test the Circle class
    public static void main(String[] args) {
        // Create a Circle object with a specific radius
        Circle circle = new Circle(5.0);

        // Display details of the circle
        circle.displayDetails();

        // Change the radius and display updated details
        circle.setRadius(10.0);
        circle.displayDetails();
    }
}
