package src;

public class Main {

	public static void main(String[] args) {
		Car c1 = new Car("Mazda", 1932, 230.5, 5);
		Car c2 = new Car("Mercedes", 2015, 330.5, 8);
		Motor m3 = new Motor("Ducati", 2020, 400, "Road");
		Motor m4 = new Motor("Hunda", 1722, 157.8, "Dirt");
		
		c1.start();
		c2.start();
		c2.playingMusic("Metal");
		
		m3.start();
		m3.stop();
		m4.wheeli();
		m4.stop();
	}

}
