package arr_str_methods;

import java.util.Arrays;

public class ArrayMismatchExample {
    public static void main(String[] args) {
        int[] array1 = {1, 2, 3};
        int[] array2 = {1, 3, 3};
        
        int result = Arrays.mismatch(array1, array2);
        System.out.println("First mismatch index: " + result);
    }
}
