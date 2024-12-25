package arr_str_methods;

import java.util.Arrays;

public class ArraySortExample {
    public static void main(String[] args) {
        int[] intArray = {3, 1, 2};
        char[] charArray = {'b', 'a', 'c'};

        Arrays.sort(intArray);
        Arrays.sort(charArray);

        System.out.println("Sorted Integer Array: " + Arrays.toString(intArray));
        System.out.println("Sorted Character Array: " + Arrays.toString(charArray));
    }
}
