package vehicle;

public class Motor extends Vehicle{

	private String _roadType;
	
	public Motor(String brand, int year, double speed, String roadType) {
		super._brand = brand;
		super._speed = speed;
		super._year = super.checkYear(year);
		super._id = getCurrentCount();
		this._roadType = roadType;
	}

	public String get_roadType() {
		return _roadType;
	}

	public void set_roadType(String _roadType) {
		this._roadType = _roadType;
	}
	
	public void wheeli() {
		System.out.println("I love doing wheeli with my bike!");
	}

	@Override
	public void putGas(double fuel) {
		System.out.println("Run the car is blowing up!");
		
	}

	@Override
	public void blowUp() {
		System.out.println("This car moves too fast!");
	}
}
