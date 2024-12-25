package files;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

public class StreamVsFileClass {
    public static void main(String[] args) {
        // Using BufferedReader (stream-based) for reading a file
        try (BufferedReader reader = new BufferedReader(new FileReader("largefile.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                // Process each line
            }
            System.out.println("BufferedReader was used for reading large file.");
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}
