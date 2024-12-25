package src;

import java.util.ArrayList;

public class Section {
    private Point _p1;
    private Point _p2;
    private ArrayList<Point> _points = new ArrayList<>();

    // Default constructor
    public Section() {
        _p1 = new Point();
        _p2 = new Point(_p1.getX() + 1, _p1.getY() + 1, _p1.getZ() + 1);
        _points.add(_p1);
        _points.add(_p2);
    }

    // Parameterized constructor
    public Section(Point p1, Point p2) {
        this._p1 = p1;
        this._p2 = p2;
        _points.add(_p1);
        _points.add(_p2);
    }

    // Getter for points
    public ArrayList<Point> getPoints() {
        return _points;
    }

    // Move the section by delta
    public void move(double deltaX, double deltaY, double deltaZ) {
        this._p1.move(deltaX, deltaY, deltaZ);
        this._p2.move(deltaX, deltaY, deltaZ);
    }

    // Length of the section
    public double length() {
        return this._p1.distance(this._p2);
    }

    // Method to check if two sections intersect
    public boolean isIntersect(Section obj) {
        Vector dir1 = _p1.toVector(_p2);  // Direction vector of this section
        Vector dir2 = obj._p1.toVector(obj._p2);  // Direction vector of the other section
        Vector diff = obj._p1.toVector(_p1);  // Difference between the start points

        double denom = dir1.cross(dir2).magnitude();
        if (denom == 0) {
            return false;  // Sections are parallel or collinear
        }

        double t1 = diff.cross(dir2).magnitude() / denom;
        double t2 = diff.cross(dir1).magnitude() / denom;

        return t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1; // Intersection occurs within the segment bounds
    }

    // Get the intersection point of two sections
    public Point getIntersect(Section obj) {
        if (!this.isIntersect(obj)) {
            return null;  // No intersection
        }

        Vector dir1 = _p1.toVector(_p2);  // Direction vector of this section
        Vector dir2 = obj._p1.toVector(obj._p2);  // Direction vector of the other section
        Vector diff = obj._p1.toVector(_p1);  // Difference between the start points

        double denom = dir1.cross(dir2).magnitude();
        if (denom == 0) {
            return null;  // No intersection point if parallel
        }

        double t1 = diff.cross(dir2).magnitude() / denom;

        // Calculate the intersection point using t1 and the parametric equation of the first section
        double intersectX = _p1.getX() + t1 * dir1.getX();
        double intersectY = _p1.getY() + t1 * dir1.getY();
        double intersectZ = _p1.getZ() + t1 * dir1.getZ();

        return new Point(intersectX, intersectY, intersectZ);
    }
}
