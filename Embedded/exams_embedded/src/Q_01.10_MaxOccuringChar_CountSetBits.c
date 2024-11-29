#include <stdio.h>

/* Function to count number of set bits in unsigned int */
int countSetBits(long num)
{
    int count = 0;

    while (num != 0)
    {
        count++;
        num &= (num - 1);/* Clear the least significant set bit*/
    }

    return count;
}

/*Function to initialize the character count lookup table*/
static void initCharCount(int charCount[256])
{
    for (int i = 0; i < 256; i++)
    {
        charCount[i] = 0;
    }
}

/* Function to print max occurances of char on input zero */
void findMaxCharOccurrence(char inputChar)
{
    static int charCount[256];
    static int maxOccurrences = 0;
    static int currentOccurrences = 0;
    static int initialized = 0;

    if (!initialized)
    {
        /*Initialize the character count LUT only once*/
        initCharCount(charCount);
        initialized = 1;
    }

    if (inputChar == '0')
    {
        /*If '0' is pressed, print the maximum occurrences since the last '0'*/
        printf("Maximum occurrences since last '0': %d\n", maxOccurrences);

        /*Reset current occurrences for the next sequence*/
        currentOccurrences = 0;
    }
    else
    {
        /*If a different character is pressed, update the LUT*/
        charCount[(unsigned char)inputChar]++;

        /*Update current occurrences and check if it's greater than the previous maximum*/
        currentOccurrences = charCount[(unsigned char)inputChar];
        if (currentOccurrences > maxOccurrences)
        {
            maxOccurrences = currentOccurrences;
        }
    }
}

int main()
{
    /*Simulate a sequence of characters*/
    char sequence[] = "0aaaabbbbbbbb0";

    for (int i = 0; sequence[i] != '\0'; i++)
    {
        findMaxCharOccurrence(sequence[i]);
    }

    return 0;
}

/*int main()
{
    long num = 0b1100000101000; // Example binary number

    int bitCount = countSetBits(num);

    printf("Number of set bits: %d\n", bitCount);

    return 0;
}*/