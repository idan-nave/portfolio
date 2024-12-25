package streams;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCopyingUsingByteStreams {
    public static void main(String[] args) {
        try (FileInputStream inFile = new FileInputStream("source.txt");
             FileOutputStream outFile = new FileOutputStream("destination.txt")) {
            
            int byteData;
            // Copy content byte by byte
            while ((byteData = inFile.read()) != -1) {
                outFile.write(byteData);
            }
            System.out.println("File copied successfully.");
        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}
