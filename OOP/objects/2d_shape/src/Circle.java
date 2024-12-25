package src;

public class Circle extends TwoDimensionalShape {
	{
		NUM_VERTICES = 0;
	}

	private double _radius;
	private double _diamater;

	public Circle(double rad) {
		if (rad > 0) {
			this._radius = rad;
		} else {
			// Throw an exception to indicate the input is invalid
			throw new IllegalArgumentException("Radius must be positive");
		}
	}

	public double getRadius() {
		return _radius;
	}

	public double getDiameter() {
		return _diamater;
	}

	@Override
	protected double area() {
		return Math.PI * Math.pow(this._radius, 2);
	}

	@Override
	protected double perimeter() {
		return this._diamater * Math.PI;
	}

	@Override
	public String toString() {
		return "This circle of radius " + this._radius + "\n" +
				"with the area of " + this.area() + "\n" +
				"and the perimeter of " + this.perimeter() + "\n";
	}

	@Override
	protected void logCreate() {
		System.out.println("Circle #" + COUNTER + " was Created");
	}
}
