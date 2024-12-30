package arr_str_methods;

import java.util.Arrays;

public class ArrayCopyExample {
    public static void main(String[] args) {
        int[] originalArray = {1, 2, 3};
        int[] newArray = Arrays.copyOf(originalArray, 5);
        System.out.println("Copied Array: " + Arrays.toString(newArray));
    }
}
