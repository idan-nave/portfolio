package simple_shape;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Shape> shapes = new ArrayList<>();

        // Create shapes
        shapes.add(new Rectangle(5, 10)); // Area = 50
        shapes.add(new Circle(7)); // Area ~ 154
        shapes.add(new Triangle(6, 8)); // Area = 24
        
        // Print areas
        printAreas(shapes);

        // Debugging nested calls
//        int num = debugExample(4, 2);
//        System.out.println(num);
     }

    public static void printAreas(List<Shape> shapes) {
        for (Shape shape : shapes) {
            System.out.println("The area of the " + shape.getName() + " is: " + shape.calculateArea());
        }
    }

    public static int debugExample(int a, int b) {
        int sum = add(a, b);
        int diff = subtract(a, b);
        return multiply(sum, diff);
    }

    public static int add(int x, int y) {
        return x + y;  // Place a breakpoint here
    }

    public static int subtract(int x, int y) {
        return x - y;
    }

    public static int multiply(int x, int y) {
        return x * y;  // Place another breakpoint here
    }
}
