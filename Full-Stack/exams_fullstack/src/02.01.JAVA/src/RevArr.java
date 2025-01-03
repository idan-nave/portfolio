package src;

public class RevArr {

  public static int[] revArr(int[] arr) {

      int[] rev = new int[arr.length];
      for (int i = 0; i < arr.length; i++) {
          rev[i] = arr[arr.length - 1 - i];
      }
      return rev;
  }

  public static void main(String[] args) {
      int[] arr = {1, 2, 3, 4};
      int[] revArr = revArr(arr);

      for (int num : arr) {
          System.out.print(num + " ");
      }

      System.out.println("\nrev arr: ");
      for (int num : revArr) {
          System.out.print(num + " ");
      }
  }
}
