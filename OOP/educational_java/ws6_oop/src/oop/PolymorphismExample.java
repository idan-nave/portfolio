package oop;

class Calculator {
    // Method overloading
    public int add(int a, int b) {
        return a + b;
    }

    public double add(double a, double b) {
        return a + b;
    }

    public int add(int a) {
        return a * 2;
    }

    public static void main(String[] args) {
        Calculator calc = new Calculator();
        System.out.println("Sum of 5 and 10 (int): " + calc.add(5, 10));
        System.out.println("Sum of 5.5 and 10.5 (double): " + calc.add(5.5, 10.5));
        System.out.println("Double of 5 (int): " + calc.add(5));
    }
}
    // Method overiding

abstract class Shape {
    abstract void draw();
}

class Circle extends Shape {
    void draw() {
        System.out.println("Drawing a Circle");
    }
}

class Square extends Shape {
    void draw() {
        System.out.println("Drawing a Square");
    }
}

public class PolymorphismExample {
    public static void main(String[] args) {
        Shape shape1 = new Circle();
        shape1.draw();

        Shape shape2 = new Square();
        shape2.draw();
    }
}
