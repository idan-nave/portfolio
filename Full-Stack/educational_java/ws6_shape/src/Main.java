package src;

public class Main {

	public static void main(String[] args) {

		Circle c1 = new Circle(12.4);
		Circle c2 = new Circle(23.2);
		// Circle c3 = new Circle(-4.5); //ERROR HANDLED

		System.out.println(c1);
		System.out.println(c2);
		// System.out.println(c3);

		// Example 1: Square with randomly generated angles
		Square square = new Square();
		square.printSections();
		square.printAngles();

		// Example 2: Square with specified sections
		double[] sections = { 25.0, 25.0, 25.0, 25.0 }; // Example section values
		Square squareWithS = new Square(sections);
		squareWithS.printSections();
		squareWithS.printAngles();

		// Example 3: Square with specified angles
		double[] angles = { 90, 90, 90, 90 }; // All angles in a square
		Square squareA = new Square(angles);
		squareA.printSections();
		squareA.printAngles();

	}
}