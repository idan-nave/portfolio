package src;

public class Trapeze extends Square {

	
	public Trapeze(double[] angArr) {
		_angles = angArr;
	}

	@Override
	protected void logCreate() {
		System.out.println("Trapeze #" + COUNTER + " was Created");
	}
}
