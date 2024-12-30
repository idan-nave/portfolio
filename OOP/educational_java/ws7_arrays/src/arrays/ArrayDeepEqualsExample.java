package arr_str_methods;

import java.util.Arrays;

public class ArrayDeepEqualsExample {
    public static void main(String[] args) {
        int[][] array1 = {{1, 2}, {3, 4}};
        int[][] array2 = {{1, 2}, {3, 4}};
        
        boolean result = Arrays.deepEquals(array1, array2);
        System.out.println("Are arrays deeply equal? " + result);
    }
}
