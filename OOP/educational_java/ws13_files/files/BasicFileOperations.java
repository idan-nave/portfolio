package files;

import java.io.File;
import java.io.IOException;

public class BasicFileOperations {
    public static void main(String[] args) {
        try {
            // Create a new file named testfile.txt
            File file = new File("testfile.txt");
            if (file.createNewFile()) {
                System.out.println("File created successfully: " + file.getName());
            } else {
                System.out.println("File already exists.");
            }

            // Get and print the absolute path
            System.out.println("Absolute Path: " + file.getAbsolutePath());
        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}
