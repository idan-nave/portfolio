/********************************** Test_ws_x.java  ******************************/
/*
  Name: Idan Nave
  Project: Work Sheet #
  Reviewer: ???
  Date: 12.12.24
  Version: 1.0
*/

package test;

public class Two {
  public void print(int num) {
      System.out.println();
      System.out.print(num);
      System.out.print(addNum(num));
      System.out.println("___________");
  }

  private int addNum(int num) {
      if (num > 10) {
          return (num + 15);
      } else {
          return (num + 10);
      }
  }

  public int subNum(int num) {
      if (num > 10) {
          return (num - 15);
      } else {
          return (num - 10);
      }
  }
}