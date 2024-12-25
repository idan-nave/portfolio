package src;

public class Main {
    public static void main(String[] args) {
        // Create points to define two sections
        Point p1 = new Point(0, 0, 0);
        Point p2 = new Point(2, 2, 2);
        Point p3 = new Point(1, 1, 1);
        Point p4 = new Point(3, 3, 3);

        // Create two sections from the points
        Section section1 = new Section(p1, p2);
        Section section2 = new Section(p3, p4);

        // Output the sections
        System.out.println("Section 1: " + section1);
        System.out.println("Section 2: " + section2);

        // Check if the two sections are parallel
        boolean isParallel = section1.isParallelTo(section2);
        System.out.println("Are the sections parallel? " + isParallel);

        // Check if the two sections intersect
        boolean doIntersect = section1.isIntersect(section2);
        System.out.println("Do the sections intersect? " + doIntersect);

        // If they intersect, output the intersection point
        if (doIntersect) {
            Point intersectPoint = section1.getIntersect(section2);
            System.out.println("Intersection point: " + intersectPoint);
        }

        // Move one of the sections and check again
        section1.move(1, 1, 1);
        System.out.println("Section 1 after moving: " + section1);
        doIntersect = section1.isIntersect(section2);
        System.out.println("Do the sections intersect after moving? " + doIntersect);
    }
}
