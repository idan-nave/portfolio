package streams;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class StreamTypesExample {
    public static void main(String[] args) {
        // Reading and writing binary file using byte streams
        try (FileInputStream inFile = new FileInputStream("binaryfile.dat");
             FileOutputStream outFile = new FileOutputStream("copy_binaryfile.dat")) {
            int byteData;
            while ((byteData = inFile.read()) != -1) {
                outFile.write(byteData);
            }
            System.out.println("Binary file copied successfully.");
        } catch (IOException e) {
            System.out.println("Error handling binary file: " + e.getMessage());
        }

        // Reading and writing text file using character streams
        try (FileReader inFile = new FileReader("textfile.txt");
             FileWriter outFile = new FileWriter("copy_textfile.txt")) {
            int charData;
            while ((charData = inFile.read()) != -1) {
                outFile.write(charData);
            }
            System.out.println("Text file copied successfully.");
        } catch (IOException e) {
            System.out.println("Error handling text file: " + e.getMessage());
        }
    }
}
