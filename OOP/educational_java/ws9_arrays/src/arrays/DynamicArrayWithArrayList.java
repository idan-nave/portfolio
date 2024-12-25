package arrays;

import java.util.ArrayList;

public class DynamicArrayWithArrayList {
    public static void main(String[] args) {
        // Create an ArrayList and add three names
        ArrayList<String> names = new ArrayList<>();
        names.add("Alice");
        names.add("Bob");
        names.add("Charlie");

        // Update the second name to "David"
        names.set(1, "David");

        // Remove the last name
        names.remove(names.size() - 1);

        // Print the final list
        System.out.println("Final list of names: " + names);
    }
}
