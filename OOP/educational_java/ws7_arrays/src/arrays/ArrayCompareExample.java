package arr_str_methods;

import java.util.Arrays;

public class ArrayCompareExample {
    public static void main(String[] args) {
        int[] array1 = {1, 2, 3};
        int[] array2 = {1, 2, 3};
        
        int result = Arrays.compare(array1, array2);
        System.out.println("Array comparison result: " + result);
    }
}
