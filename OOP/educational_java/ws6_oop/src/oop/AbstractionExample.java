package oop;

abstract class Animal {
    abstract void makeSound();
    abstract void move();
}

class Bird extends Animal {
    void makeSound() {
        System.out.println("Chirp");
    }
    void move() {
        System.out.println("Fly");
    }
}

class Fish extends Animal {
    void makeSound() {
        System.out.println("Blub");
    }
    void move() {
        System.out.println("Swim");
    }
}

public class AbstractionExample {
    public static void main(String[] args) {
        Animal bird = new Bird();
        bird.makeSound();
        bird.move();

        Animal fish = new Fish();
        fish.makeSound();
        fish.move();
    }
}
