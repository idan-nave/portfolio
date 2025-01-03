package src;

// Implement a Java class Car with private fields make, model, and year. Include methods to start the car, stop the car, and display its details.

public class Car {

	private String make;
	private String model;
	private int year;

	public Car(String make, String model, int year) {
		this.make = make;
		this.model = model;
		this.year = year;
	}

	public void start() {
		System.out.println("ENGINE IS RUNNING");
	}

	public void stop() {
		System.out.println("ENGINE IS OFF");

	}

	// display car details
	@Override
	public String toString() {
		return "Make: " + make + "\nModel: " + model + "\nYear: " + year;
	}

	public static void main(String[] args) {
		Car myCar = new Car("MAZDA", "3", 2025);
		System.out.println(myCar.toString());
		myCar.start();
		myCar.stop();
	}
}
