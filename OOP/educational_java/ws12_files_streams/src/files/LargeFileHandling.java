package files;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class LargeFileHandling {
    public static void main(String[] args) {
        int lineCount = 0;
        try (BufferedReader reader = new BufferedReader(new FileReader("largefile.txt"))) {
            @SuppressWarnings("unused")
            String line;
            while ((line = reader.readLine()) != null) {
                lineCount++;
            }
            System.out.println("Total lines in the file: " + lineCount);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}
