package journal;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Streamer {

    // Method to write to a file
    public static void writeToFile(String fileName, String[] lines) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            for (String line : lines) {
                writer.write(line);
                writer.newLine(); // Add a newline after each line
            }
            System.out.println("Data written to " + fileName);
        } catch (IOException e) {
            System.out.println("Error writing to file: " + e.getMessage());
        }
    }

    // Method to read from a file
    public static void readFromFile(String fileName) {
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line); // Print each line from the file
            }
        } catch (IOException e) {
            System.out.println("Error reading from file: " + e.getMessage());
        }
    }

    // Serialize a single file by writing its content to a file
    public static void serializeFile(String filePath, String outputFile) throws IOException {
        // Read the content of the file
        byte[] fileContent = Files.readAllBytes(Paths.get(filePath));
        
        // Write the content to the output file
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(outputFile))) {
            oos.writeObject(fileContent);
            System.out.println("File serialized successfully: " + outputFile);
        }
    }

    // Deserialize a single file from the serialized format
    public static void deserializeFile(String inputFile, String outputPath) throws IOException, ClassNotFoundException {
        // Read the serialized content
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(inputFile))) {
            byte[] fileContent = (byte[]) ois.readObject();
            
            // Write the content back to the original file path
            Files.write(Paths.get(outputPath), fileContent);
            System.out.println("File deserialized successfully to: " + outputPath);
        }
    }

    public static void main(String[] args) {
        // Example data to write to the file
        String[] lines = {
            "Line 1: Java file handling is efficient.",
            "Line 2: BufferedWriter improves performance."
        };
        
        // Write data to the file
        writeToFile("bufferedoutput.txt", lines);

        // Read data from the file
        readFromFile("bufferedoutput.txt");
    }
}
