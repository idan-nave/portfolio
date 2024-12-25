package files;

import java.io.File;

public class FileClassMethods {
    public static void main(String[] args) {
        File dir = new File("exampleDir");

        // Create directory
        if (!dir.exists()) {
            if (dir.mkdir()) {
                System.out.println("Directory created: exampleDir");
            }
        }

        // Create file inside the directory
        File file = new File(dir, "exampleFile.txt");
        try {
            if (file.createNewFile()) {
                System.out.println("File created: exampleFile.txt inside exampleDir");
            }
        } catch (IOException e) {
            System.out.println("Error creating file: " + e.getMessage());
        }

        // Check if it's a directory or file
        if (dir.isDirectory()) {
            System.out.println("exampleDir is a directory.");
        }
        if (file.isFile()) {
            System.out.println("exampleFile.txt is a file.");
        }
    }
}
