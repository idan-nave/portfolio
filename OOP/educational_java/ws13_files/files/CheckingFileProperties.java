package files;

import java.io.File;

public class CheckingFileProperties {
    public static void main(String[] args) {
        File file = new File("testfile.txt");

        // Check if the file exists
        if (file.exists()) {
            // Check if it's a file or directory
            if (file.isFile()) {
                System.out.println("testfile.txt is a file.");
            } else if (file.isDirectory()) {
                System.out.println("testfile.txt is a directory.");
            }
        } else {
            System.out.println("testfile.txt does not exist.");
        }
    }
}
