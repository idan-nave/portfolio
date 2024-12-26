package vehicle;
//Requirements:
//1. Base Class: Vehicle
//○ Add attributes like brand and implement methods
//start() and stop().
//2. Derived Classes:
//○ Car: Extend the Vehicle class. Add attributes like
//model and a method play_music(). Implement a
//details() method to display car-specific information.
//○ Motorcycle: Extend the Vehicle class. Add attributes
//like cc (engine capacity) and implement a details()
//method.
//○ Truck: Extend the Vehicle class. Add attributes like
//capacity (in tons) and implement a details()
//method.
//3. Demonstration:
//○ Create objects of Car, Motorcycle, and Truck.
//○ Call methods to start and stop each vehicle and display
//specific details.

public abstract class Vehicle implements Actions {
	{
		System.out.println("Hello");
	}
	
	private static int COUNTER = 0;
	
	protected String _brand;
	protected int _year;
	protected double _speed;
	protected int _id;
	
	public void start() {
		System.out.print(this._brand+" "+this._id+" is: ");
		System.out.println("Started moving");
	}
	
	public void stop() {
		System.out.print(this._brand+" "+this._id+" since "+this._year);
		System.out.println("\n\t\tSTOPPING!!!");
	}
	
	protected static int getCurrentCount() {
		return ++COUNTER;
	}
	
	protected static int checkYear(int year) {
		if (year > MIN_YEAR) {
			return year;
		} else {
			return MIN_YEAR;
		}
	}
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return super.toString();
	}
}
