package src;

public abstract class TwoDimensionalShape extends Shape {

	protected abstract double area();
	protected abstract double perimeter();
	protected void log2DAttributes()
	{
		System.out.printf("\t area: %.1f", this.area());
		System.out.printf("\t perimeter: %.1f", this.perimeter());
	}
}
