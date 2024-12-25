package methods;

public class CalculateArea {
    // Method to calculate area of a rectangle
    public static double calculateArea(double width, double height) {
        return width * height;
    }

    public static void main(String[] args) {
        // Calling the calculateArea method and displaying the result
        double area = calculateArea(5.0, 10.0);
        System.out.println("The area of the rectangle is: " + area);
    }
}
