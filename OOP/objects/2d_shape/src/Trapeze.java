package src;

public class Trapeze extends Square {

	public Trapeze() {
		super();
		this._numParallelSectionPairs = 1; // exactly 1 pair
	}

	public Trapeze(double[] angArr) {
		super(angArr);
		this._numParallelSectionPairs = 1; // exactly 1 pair
	}

	@Override
	protected void logCreate() {
		System.out.println("\nTRAPEZE #" + COUNTER + " was Created");
		System.out.println("\t" + _numParallelSectionPairs + " pair of parallel sections");
		System.out.println("\t" + _numEqualSectionPairs + " pair of equal sections");
	}
}
