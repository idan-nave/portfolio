package files;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class BufferedIOExample {
    public static void main(String[] args) {
        // Write to a file using BufferedWriter
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("bufferedoutput.txt"))) {
            writer.write("Line 1: Java file handling is efficient.");
            writer.newLine();
            writer.write("Line 2: BufferedWriter improves performance.");
        } catch (IOException e) {
            System.out.println("Error writing to file: " + e.getMessage());
        }

        // Read from the file using BufferedReader
        try (BufferedReader reader = new BufferedReader(new FileReader("bufferedoutput.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.out.println("Error reading from file: " + e.getMessage());
        }
    }
}
