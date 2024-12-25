package oop;

class Vehicle {
    String brand;

    void start() {
        System.out.println(brand + " vehicle starting...");
    }

    void stop() {
        System.out.println(brand + " vehicle stopping...");
    }
}

class Car extends Vehicle {
    String model;

    void playMusic() {
        System.out.println("Playing music in the car.");
    }

    void details() {
        System.out.println("Car model: " + model);
    }
}

class Motorcycle extends Vehicle {
    int cc;

    void revEngine() {
        System.out.println("Revving the engine of the motorcycle!");
    }

    void details() {
        System.out.println("Motorcycle cc: " + cc);
    }
}

class Truck extends Vehicle {
    int capacity;

    void details() {
        System.out.println("Truck capacity: " + capacity + " tons");
    }
}

public class VehicleProject {
    public static void main(String[] args) {
        Vehicle car = new Car();
        car.brand = "Toyota";
        car.start();
        ((Car) car).model = "Corolla";
        ((Car) car).playMusic();
        car.stop();

        Vehicle motorcycle = new Motorcycle();
        motorcycle.brand = "Harley";
        motorcycle.start();
        ((Motorcycle) motorcycle).cc = 1200;
        ((Motorcycle) motorcycle).revEngine();
        motorcycle.stop();

        Vehicle truck = new Truck();
        truck.brand = "Ford";
        truck.start();
        ((Truck) truck).capacity = 10;
        ((Truck) truck).details();
        truck.stop();
    }
}
