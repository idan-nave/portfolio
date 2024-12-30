package arrays;

public class MultidimensionalArray {
    public static void main(String[] args) {
        // Declare and initialize a 3x3 matrix
        int[][] matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        // Print the element in the first row and second column
        System.out.println("Element at first row, second column: " + matrix[0][1]);
    }
}
