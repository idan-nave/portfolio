package streams;

import java.io.FileReader;
import java.io.IOException;

public class BasicFileReader {
    public static void main(String[] args) {
        try (FileReader reader = new FileReader("input.txt")) {
            int character;
            // Read character by character from the file
            while ((character = reader.read()) != -1) {
                System.out.print((char) character);  // Display each character
            }
        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}
