
package calc;

import java.lang.Double; // Explicit import for Double

public class Calc {

  // Method for basic calc - a is first number (divided by), b is second.
  public static Double compute (Double a, char ch, Double b) {

    // Array of acceptable characters for basic arithmetic operations
    char[] acceptableChars = { '+', '-', '*', '/' };
    boolean validOp = false;

    // input validation - nums
    if (Double.isNaN(a) || Double.isNaN(b)) {
      return Double.NaN;
    }
    // input validation - char

    for (char operator : acceptableChars) {
      if (ch == operator) {
        validOp = true;
      }
    }
    if (!validOp) {
      return Double.NaN;
    }

    // Computation

    switch (ch) {
      case '+':
        return a + b;
      case '-':
        return a - b;
      case '*':
        return a * b;
      case '/':
        if (b == 0) {
          return Double.NaN;
        }
        return a / b;
      default:
        break;
    }

    return Double.NaN;
  }

    // Absolute number
  public static Double abs(Double a) {
    if (a < 0) {
      return a * -1;
    }
    return a;
  }
}