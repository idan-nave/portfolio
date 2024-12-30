package streams;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class BufferedStreamsForEfficiency {
    public static void main(String[] args) {
        long startTime, endTime;

        try {
            // Without buffering (FileInputStream and FileOutputStream)
            startTime = System.nanoTime();
            try (FileInputStream inFile = new FileInputStream("largefile.txt");
                 FileOutputStream outFile = new FileOutputStream("copy_no_buffer.txt")) {
                int byteData;
                while ((byteData = inFile.read()) != -1) {
                    outFile.write(byteData);
                }
            }
            endTime = System.nanoTime();
            System.out.println("File copied without buffering. Time taken: " + (endTime - startTime) + " ns");

            // With buffering (BufferedInputStream and BufferedOutputStream)
            startTime = System.nanoTime();
            try (BufferedInputStream inFile = new BufferedInputStream(new FileInputStream("largefile.txt"));
                 BufferedOutputStream outFile = new BufferedOutputStream(new FileOutputStream("copy_with_buffer.txt"))) {
                int byteData;
                while ((byteData = inFile.read()) != -1) {
                    outFile.write(byteData);
                }
            }
            endTime = System.nanoTime();
            System.out.println("File copied with buffering. Time taken: " + (endTime - startTime) + " ns");
        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}
