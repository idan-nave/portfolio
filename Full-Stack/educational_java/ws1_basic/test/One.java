/********************************** Test_ws_x.java  ******************************/
/*
  Name: Idan Nave
  Project: Work Sheet #
  Reviewer: ???
  Date: 12.12.24
  Version: 1.0
*/

package test;

public class One {
  public static void main(String[] args) {
      Two number = new Two(); // Create an instance of Two
      System.out.println("One");
      int num = 20;
      
      number.print(num); // Use the print method of Two
      System.out.println("Sub: " + number.subNum(num)); // Use subNum method
  }
}