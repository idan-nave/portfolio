package streams;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class AppendedContent {
    public static void main(String[] args) {
        // Read from input file and write to output file
        try (BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
                BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"))) {

            String line;
            while ((line = reader.readLine()) != null) {
                writer.write(line);
                writer.newLine();
            }

            // Append a custom message using the append method of BufferedWriter
            writer.write("This is appended content");
            writer.newLine();

            // Append the message using FileWriter's append functionality
            try (FileWriter fileWriter = new FileWriter("output.txt", true)) {
                fileWriter.append("Appended via FileWriter's append method.");
                fileWriter.append(System.lineSeparator()); // Ensure line break
            }
            
            System.out.println("File copied and appended successfully.");
        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}
