import java.util.Arrays;

public class MaxFinder {

    // Method to find the maximum number in an array using Arrays.stream
    public static int findMaxUsingStream(int[] arr) {
        if (arr == null || arr.length == 0) {
            throw new IllegalArgumentException("Array must not be empty");
        }

        // Find the maximum element using the stream API
        return Arrays.stream(arr)
                     .max()
                     .orElseThrow(() -> new IllegalArgumentException("Array is empty")); // Optional: Throw exception if no max found
    }

    // Method to find the maximum number in an array using traditional loop
    public static int findMax(int[] arr) {
        if (arr == null || arr.length == 0) {
            throw new IllegalArgumentException("Array must not be empty");
        }

        int max = arr[0]; // Assume the first element is the largest
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i]; // Update max if a larger number is found
            }
        }
        return max;
    }

    public static void main(String[] args) {
        int[] numbers = {3, 5, 7, 2, 8, 1};

        // Using traditional method
        int largest = findMax(numbers);
        System.out.println("The largest number (traditional method) is: " + largest);

        // Using the Arrays.stream method
        int largestUsingStream = findMaxUsingStream(numbers);
        System.out.println("The largest number (stream method) is: " + largestUsingStream);
    }
}

