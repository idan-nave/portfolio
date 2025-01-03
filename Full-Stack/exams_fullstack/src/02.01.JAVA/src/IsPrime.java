package src;

public class IsPrime {
    public static void main(String[] args) {

        int[] testArr = {5, 10, 15, 56, 17};
        for (int i = 0; i < testArr.length; i++) {
            if (isPrime(testArr[i])) {
                System.out.println(testArr[i] + " YES");
            } else {
                System.out.println(testArr[i] + " NOT PRIME");
            }
        }
    }

    public static boolean isPrime(int number) {
        if (number <= 1) {
            return false; // testArr less than or equal to 1 are not prime
        }
        for (int i = 2; i <= Math.sqrt(number); i++) {
            if (number % i == 0) {
                return false; // found division
            }
        }
        return true; 
    }
}
