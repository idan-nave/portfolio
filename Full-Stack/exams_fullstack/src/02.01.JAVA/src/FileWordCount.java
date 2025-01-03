package src;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileWordCount {
  public static void main(String[] args) {
    countWordsFile();
  }

  public static void countWordsFile() {
    // MAKE SURE THE WORDS IN THE FILE ARE SEPERATED BY ONE SPACE ONLY, OTHERWISE
    // EACH EXTRA SPACE IS COUNTED AS A WORD TOO
    try (BufferedReader reader = new BufferedReader(new FileReader("input.txt"))) {
      String line;
      int words = 0;
      while ((line = reader.readLine()) != null) {
        System.out.println(line);
        words += line.split(" ").length;
      }
      System.out.println("Count of words is: " + words);
    } catch (IOException e) {
      System.out.println("Error reading from file: " + e.getMessage());
    }
  }
}