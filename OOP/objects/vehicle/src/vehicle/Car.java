package vehicle;

public class Car extends Vehicle {
	
	private int _numberOfSeats;
	
	public Car(String brand, int year, double speed, int numberOfSeats) {
		super._brand = brand;
		super._speed = speed;
		super._year = super.checkYear(year);
		super._id = getCurrentCount();
		this._numberOfSeats = numberOfSeats;
	}

	public int get_numberOfSeats() {
		return _numberOfSeats;
	}

	public void set_numberOfSeats(int _numberOfSeats) {
		this._numberOfSeats = _numberOfSeats;
	}
	
	public void playingMusic(String type) {
		System.out.println("Playing "+type+" In full volume");
	}
	
	@Override
	public void blowUp() {
		System.out.println("Run the car is blowing up!");
		
	}
	@Override
	public void putGas(double fuel) {
		System.out.println("This car moves too fast!");
		
	}
	
	
	
}
