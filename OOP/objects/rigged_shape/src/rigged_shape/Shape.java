package rigged_shape;

public abstract class Shape {
	{
		COUNTER++;
		logCreate();
	}
	public static int COUNTER = 0;
	public static int NUM_VERTICES = 0;
	
	protected abstract void logCreate(); 

}
