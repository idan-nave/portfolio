package rigged_shape;

public class Square extends TwoDimensionalShape {
	{
		NUM_VERTICES = 4;
		_angles = new double[NUM_VERTICES];
		_sections = new double[NUM_VERTICES];
		System.out.println("DEBUG B");

	}

	protected static final int SUM_ANGLES = 360;

	protected double[] _angles; // Angles of the square
	protected double[] _sections; // Sections length
	protected int _numParallelSectionPairs;
	protected int _numEqualSectionPairs;

	// Default Constructor (random angles)
	public Square() {
		System.out.println("DEBUG A");

		// Generate random angles (but ensure the total sum is 360 degrees)
		this._angles[0] = Math.random() * 90; // First angle
		this._angles[1] = Math.random() * 90; // Second angle
		this._angles[2] = Math.random() * 90; // Third angle
		// Fourth angle ensures the sum of all angles is 360 degrees
		this._angles[3] = SUM_ANGLES - (this._angles[0] + this._angles[1] + this._angles[2]);

		// Initialize random section pairs (parallel and equal)
		this._numParallelSectionPairs = (int) (Math.ceil(Math.random() * 2)); // Randomly 1 or 2 pairs
		this._numEqualSectionPairs = (int) (Math.ceil(Math.random() * 2)); // Randomly 1 or 2 pairs

		// Initialize the sections array (for 4 sides in a square)
		calculateSections();
	}

	// Constructor for initializing with angles directly
	public Square(double[] angArr) {
		for (int i = 0; i < angArr.length; i++) {
			_angles[i] = angArr[i]; // Assign the angles values
		}
		calculateSections(); // Calculate sections based on angles
	}

	// Constructor for initializing sections
	public Square(int[] sectionArr) {
		for (int i = 0; i < sectionArr.length; i++) {
			_sections[i] = (double) sectionArr[i]; // Assign the section values
		}
		calculateAngles(); // Calculate angles based on angles
	}

	@Override
	protected double area() {
		return this._sections[0] * this._sections[1];
	}

	@Override
	protected double perimeter() {
		return 2 * (this._sections[0] + this._sections[1]);
	}

	@Override
	protected void logCreate() {
		System.out.println("\nSQUARE #" + COUNTER + " was Created");
		log2DAttributes();
		logSquareAttributes();
	}

	protected void logSquareAttributes()
	{
		System.out.println("\t" + this._numParallelSectionPairs + " pair of parallel sections");
		System.out.println("\t" + this._numEqualSectionPairs + " pair of equal sections");
	}

	public void printSections() {
		System.out.println("\tSections: ");
		for (double section : _sections) {
			System.out.printf("\t%.1f", section);
			System.out.print(", ");
		}
		System.out.println();
	}

	public void printAngles() {
		System.out.println("\tAngles: ");
		for (double angle : _angles) {
			System.out.printf("\t%.1f", angle);
			System.out.print(", ");
		}
		System.out.println();
	}

	// Method to calculate the sections array based on angles
	private void calculateSections() {
		System.out.println("DEBUG C");

		// For each section, assign its value based on the angle's proportion of 360 deg
		for (int i = 0; i < _angles.length; i++) {
			this._sections[i] = (_angles[i] / SUM_ANGLES) * 100.0;
		}
	}

	// Method to calculate angles array based on sections
	private void calculateAngles() {
		double sumSection = 0;
		for (double section : _sections) {
			sumSection += section; // Sum up the sections
		}

		// For each angle, assign its value based on the section's proportion of total
		// sections
		for (int i = 0; i < _sections.length; i++) {
			this._angles[i] = (_sections[i] / sumSection) * SUM_ANGLES;
		}
	}
}
