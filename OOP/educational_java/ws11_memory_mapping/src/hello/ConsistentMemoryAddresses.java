package hello;

import java.util.HashMap;
import java.util.Map;

public class ConsistentMemoryAddresses {

    // A simple object to hold some data
    static class MyObject {
        int id;
        String name;

        // Constructor
        MyObject(int id, String name) {
            this.id = id;
            this.name = name;
        }

        @Override
        public String toString() {
            return "MyObject{id=" + id + ", name='" + name + "'}";
        }
    }

    public static void main(String[] args) {
        // Use a Map to simulate object storage
        Map<Integer, MyObject> objectsMap = new HashMap<>();

        // Add objects with the same data across both runs
        MyObject obj1 = new MyObject(1, "FirstObject");
        MyObject obj2 = new MyObject(2, "SecondObject");
        MyObject obj3 = new MyObject(3, "ThirdObject");

        // Store them in the map
        objectsMap.put(obj1.id, obj1);
        objectsMap.put(obj2.id, obj2);
        objectsMap.put(obj3.id, obj3);

        // Print the objects and their "memory addresses" (simulated by their hash code)
        for (MyObject obj : objectsMap.values()) {
            System.out.println("Object: " + obj);
            // Use identityHashCode to simulate "real" memory address (identity-based hash)
            int address = System.identityHashCode(obj);
            System.out.println("Simulated Memory Address (HashCode): " + address);
        }
        while (true)
        {
        }
    }

}
