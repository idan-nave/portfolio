package oop;

class Vehicle {
    void start() {
        System.out.println("Vehicle starting...");
    }

    void stop() {
        System.out.println("Vehicle stopping...");
    }
}

class Car extends Vehicle {
    void playMusic() {
        System.out.println("Playing music in the car.");
    }
}

class Motorcycle extends Vehicle {
    void revEngine() {
        System.out.println("Revving the motorcycle engine!");
    }
}

public class InheritanceExample {
    public static void main(String[] args) {
        Vehicle car = new Car();
        car.start();
        ((Car) car).playMusic();
        car.stop();

        Vehicle motorcycle = new Motorcycle();
        motorcycle.start();
        ((Motorcycle) motorcycle).revEngine();
        motorcycle.stop();
    }
}
