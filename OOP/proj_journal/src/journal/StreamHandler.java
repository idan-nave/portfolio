package journal;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;

public class StreamHandler {

    // Method to write to a file
    public static void writeToFile(String filePath, String[] lines) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
            for (String line : lines) {
                writer.write(line);
                writer.newLine(); // Add a newline after each line
            }
            System.out.println("Data written to " + filePath);
        } catch (IOException e) {
            System.out.println("Error writing to file: " + e.getMessage());
        }
    }

    // Method to replace a line in the file by index
    public static void replaceLineInFile(String filePath, int index, String newLine) {
        try {
            // Read all lines from the file
            List<String> lines = Files.readAllLines(Paths.get(filePath));

            // Check if the index is valid
            if (index >= 0 && index < lines.size()) {
                // Replace the line at the specified index
                lines.set(index, newLine);

                // Write the updated lines back to the file
                Files.write(Paths.get(filePath), lines);
                System.out.println("Line at index " + index + " replaced with: " + newLine);
            } else {
                System.out.println("Invalid index: " + index);
            }
        } catch (IOException e) {
            System.out.println("Error reading/writing the file: " + e.getMessage());
        }
    }

    // Method to delete a line in the file by index (removes the line)
    public static void deleteLineInFile(String filePath, int index) {
        try {
            // Read all lines from the file
            List<String> lines = Files.readAllLines(Paths.get(filePath));

            // Check if the index is valid
            if (index >= 0 && index < lines.size()) {
                // Remove the line at the specified index
                lines.remove(index);

                // Write the updated lines back to the file
                Files.write(Paths.get(filePath), lines);
                System.out.println("Line at index " + index + " has been deleted.");
            } else {
                System.out.println("Invalid index: " + index);
            }
        } catch (IOException e) {
            System.out.println("Error reading/writing the file: " + e.getMessage());
        }
    }

    // Method to read from a file
    public static void readFromFile(String filePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line); // Print each line from the file
            }
        } catch (IOException e) {
            System.out.println("Error reading from file: " + e.getMessage());
        }
    }

    // Method to read a specific line from a file by index
    public static String readLineInFile(String filePath, int lineIndex) {
        String line = null;
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            int currentLine = 0;
            // Iterate through the file to the desired line
            while ((line = reader.readLine()) != null) {
                if (currentLine == lineIndex) {
                    return line; // Return the line when the index matches
                }
                currentLine++;
            }
            // If the line index is out of bounds
            return "Line index out of bounds.";
        } catch (IOException e) {
            System.out.println("Error reading from file: " + e.getMessage());
            return null;
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
