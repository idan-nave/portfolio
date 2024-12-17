package src;

public class Vector {
    private double x, y, z;

    // Constructor to create a vector
    public Vector(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    // Getters for the vector components
    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getZ() {
        return z;
    }

    // Add another vector to this vector
    public Vector add(Vector other) {
        return new Vector(this.x + other.x, this.y + other.y, this.z + other.z);
    }

    // Subtract another vector from this vector
    public Vector subtract(Vector other) {
        return new Vector(this.x - other.x, this.y - other.y, this.z - other.z);
    }

    // Dot product of this vector and another vector
    public double dot(Vector other) {
        return this.x * other.x + this.y * other.y + this.z * other.z;
    }

    // Cross product of this vector and another vector
    public Vector cross(Vector other) {
        double cx = this.y * other.z - this.z * other.y;
        double cy = this.z * other.x - this.x * other.z;
        double cz = this.x * other.y - this.y * other.x;
        return new Vector(cx, cy, cz);
    }

    // Calculate the magnitude (length) of the vector
    public double magnitude() {
        return Math.sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector (make it unit length)
    public Vector normalize() {
        double mag = magnitude();
        if (mag == 0) {
            return new Vector(0, 0, 0);
        }
        return new Vector(x / mag, y / mag, z / mag);
    }

    // String representation of the vector
    @Override
    public String toString() {
        return "(" + x + ", " + y + ", " + z + ")";
    }
}
