package files;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class ByCharcterIOExample {
    public static void main(String[] args) {
        // Write to a file using FileWriter (without buffering)
        try (FileWriter writer = new FileWriter("output.txt")) {
            writer.write("Line 1: Java file handling is efficient.\n");
            writer.write("Line 2: FileWriter writes character data.");
        } catch (IOException e) {
            System.out.println("Error writing to file: " + e.getMessage());
        }

        // Read from the file using FileReader (without buffering)
        try (FileReader reader = new FileReader("output.txt")) {
            int character;
            while ((character = reader.read()) != -1) {
                System.out.print((char) character);  // Print character by character
            }
        } catch (IOException e) {
            System.out.println("Error reading from file: " + e.getMessage());
        }
    }
}
