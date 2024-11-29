 C function that flips the order of words inside a string:

The `reverseWords` function first reverses the entire string to get "tneduts ma i". Then, it iterates through the string and reverses individual words to get the final reversed order of words: "student am i". The code includes a demonstration in the `main` function to showcase the usage of the `reverseWords` function.

#include <stdio.h>
#include <string.h>

void reverseWords(char *str) {
    int len = strlen(str);

    // Reverse the entire string
    for(int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }

    // Reverse individual words
    int start = 0;
    for (int i = 0; i <= len; i++)
    {
        if (str[i] == ' ' || str[i] == '\0')
        {
            int end = i - 1;
            while (start < end)
            {
                char temp = str[start];
                str[start] = str[end];
                str[end] = temp;
                start++;
                end--;
            }
            start = i + 1;
        }
    }
}

int main()
{
    char str[] = "i am student";
    printf("Original string: %s\n", str);

    reverseWords(str);

    printf("Reversed words: %s\n", str);

    return 0;
}
