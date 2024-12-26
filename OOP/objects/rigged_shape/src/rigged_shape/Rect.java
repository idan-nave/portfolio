package rigged_shape;

public class Rect extends Square {
	

	@Override
	protected void logCreate() {
		System.out.println("Rect #" + COUNTER + " was Created");
	}
}
