package arr_str_methods;

import java.util.Arrays;

public class ArrayFillExample {
    public static void main(String[] args) {
        int[] array = new int[5];
        Arrays.fill(array, 7);
        System.out.println("Filled Array: " + Arrays.toString(array));
    }
}
