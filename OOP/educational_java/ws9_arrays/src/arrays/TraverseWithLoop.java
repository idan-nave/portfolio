package arrays;

public class TraverseWithLoop {
    public static void main(String[] args) {
        // Declare and initialize the one-dimensional array
        int[] numbers = {5, 10, 15};

        // Use a for loop to print all elements
        System.out.println("Elements of the array:");
        for (int i = 0; i < numbers.length; i++) {
            System.out.println("numbers[" + i + "]: " + numbers[i]);
        }
    }
}
