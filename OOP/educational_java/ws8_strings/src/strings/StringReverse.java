package arr_str_methods;

public class StringReversal {

    // Method to reverse a string using StringBuilder
    public static String reverseStringWithBuilder(String str) {
        if (str == null) {
            return null; // Return null if the input string is null
        }

        StringBuilder reversedStr = new StringBuilder(str); // Create a StringBuilder from the input string
        return reversedStr.reverse().toString(); // Reverse the string and convert it back to a String
    }

    // Method to reverse a string character by character
    public static String reverseStringCharByChar(String str) {
        if (str == null) {
            return null; // Return null if the input string is null
        }

        char[] charArray = str.toCharArray(); // Convert string to a character array
        int left = 0; // Pointer to the start of the array
        int right = charArray.length - 1; // Pointer to the end of the array

        // Swap characters from both ends until the pointers meet
        while (left < right) {
            char temp = charArray[left];
            charArray[left] = charArray[right];
            charArray[right] = temp;
            left++;
            right--;
        }

        return new String(charArray); // Convert the character array back to a string
    }

    public static void main(String[] args) {
        String original = "Hello, World!";
        
        // Using StringBuilder
        String reversedWithBuilder = reverseStringWithBuilder(original);
        System.out.println("Reversed using StringBuilder: " + reversedWithBuilder);

        // Using character-by-character method
        String reversedCharByChar = reverseStringCharByChar(original);
        System.out.println("Reversed character by character: " + reversedCharByChar);
    }
}

