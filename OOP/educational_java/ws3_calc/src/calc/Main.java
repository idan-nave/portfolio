
package calc;

import java.util.Scanner; //input
import java.lang.Double; // type Double

public class Main {
  public static void main(String[] args) {

    Double a = 0.0;
    Double b = 0.0;
    char op = ' ';
    String opInput;
    // Enter first num, operator, next num
    System.out.println("Enter first num, operator, next num");
    Scanner scan = new Scanner(System.in);

    while (true) {
      try {
        a = scan.nextDouble();
        opInput = scan.next();
        b = scan.nextDouble();
        op = opInput.charAt(0);

        System.out.println("Calculating...");
        if (Double.isNaN(Calc.compute(a, op, b)))
          System.out.println("Bad Input / Syntax Error, Try again!");
        else {

          System.out.println("Result is : " + Calc.compute(a, op, b));
          System.out.println("Enter Next Argument!");
        }
      } catch (Exception e) {
        System.out.println(e.getMessage());
      } finally {
        scan.close();

      }
    }

  }
}