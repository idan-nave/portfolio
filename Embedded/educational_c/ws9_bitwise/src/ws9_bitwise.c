/********************************** ws9_bitwise.c  ****************************/
/*
  Name: HRD 32
  Project: Work Sheet #9 - BitWise
  Reviewer: Liel
  Date: 22/07/23
  Version: 1.0 - publish
           1.1 - fix TODOs
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* assert(), */
#include <stdio.h>  		/* FILEs, stderr, stdin, stdout, size_t */
#include <stdlib.h> 		/* malloc(), free() */

#include "ws9_bitwise.h" 

/****************************** Definitions  **********************************/

#define TRUE 1
#define BYTE_BITS 8 
#define NIBBLE_BITS 4

/********************************* Helper Functions ***************************/

/* Function to print the binary representation of an unsigned integer */
void PrintBinary(unsigned int num, size_t length);


/****************************** Implementations *******************************/

/* 1.Function that multiplies x by 2^y */
long MultXByPow2(unsigned int x, unsigned int y)
{
    /* effectively shifting y times is like multiplying by 2^y */
    return x << y; 
}

/* Function to count number of set bits in unsigned int */
size_t CountOnes(unsigned int n) /* 011101001 */
                                 /* 001110100 */
{
    /* Counter to store the number of set bits (1s) found */
    unsigned int count = 0;
    int mask1 = 1;  /* 00000001 */                
    /* Iterate through the bits of the input integer */
    while (0 != n)
    {
        /* Increment the count if the LSB is 0 */
        count += n & mask1; /* 011101001 */
                            /* 000000001 */
                            /* 000000001 */
        /* Shift the integer to the right to check the next bit */
        n >>= 1;
    }
    /* Return the total count of set bits (1s) */
    return count;
}

/* 2.a.Function that receives unsigned int n
• Returns 1 if n is a power of 2. Otherwise it returns 0
• Implement using a loop (in helper func). */
size_t IsPowerOf2Loop(unsigned int n)
{
    /* in case only Power > 0 is allowed: if set LSB - 1 is not valid*/
    if(n & 1) return 0;
    /* only 1 occurance of 1 is allowed for success */
    return (1 == CountOnes(n));
}

/* 2.b.Function that receives unsigned int n,
• Returns 1 if n is a power of 2. Otherwise it returns ..
• Implement without a loop. */       
size_t IsPowerOf2Simple(unsigned int n)
{
    /* if only 1 set-bit exist */
    return ((n != 0) && !(n & (n - 1)));
} 
/* The expression (n & (n - 1)) is a common technique used to clear
(unset) the rightmost set bit (binary 1) of a given positive integer n.                
              original         1010
              minus 1 num      1001
              after oper &     xxx0  set lsb to 0 */                  
                                                        
                                                            

/* 3. A function that adds 1 to an int without using arithmetic operators.*/
int Add1ToIntBitWise(int n)
{
    int mask1 = 1;  /* 00000001 */                
    /* Continue flipping bits until the least significant bit becomes 0 */
    while (0  != n & mask1)  /* or !!(n & mask) */
    {
        n ^= mask1;     /* Flip the current bit */
        mask1 <<= 1;    /* Shift the mask to consider the next bit */
    }

    n ^= mask1;         /* Flip the last remaining bit to add 1 */
    return n;
    /*
    
    Explanation:
    -For the positive number 10, its binary representation is 00001010.
    When we add 1 to it using the Add1ToIntBitWise function,
    it correctly becomes 11, which is 00001011 in binary.
    -For the negative number -64, its binary representation is
    11111111111111111111111111000000 (assuming 32-bit representation).
    When we add 1 to it using the Add1ToIntBitWise function,
    it correctly becomes -63, which is 11111111111111111111111111000001 in binary.
    As we can see, the function handles both positive and negative numbers
    correctly, and it can add 1 to them without using any arithmetic operators.
    */
}

/*4. A function that receives an array of unsigned ints and only prints
the ints that have exactly 3 bits on (set to 1).*/
size_t PrintOnly3SetBits(unsigned int *arr, size_t len)
{ 
    size_t i = 0;
    size_t num_of_prints = 0; /* count num of prints */
    
    while(len > i)
    {  
      printf("\n");
      if (CountOnes(arr[i])  == 3)
      {
          PrintBinary(arr[i], 8);
          printf(" (%d) has 3 ones\n", arr[i]);
          ++num_of_prints;
      }
      ++i;
    }
    return num_of_prints;
}

/*5.a. ByteMirror - reverse the bits
• Implement using a loop., Ex:   10101011   MIRROR>   11010101 */
unsigned char ByteMirrorLoop(unsigned char byte)
{   
    int mir_i_left = 0;
    int mir_i_right = 0;
    int remain_shift = 0;
    /* new byte to hold the mirrored byte */
    unsigned char final_mirror = 0;

    size_t i = 0;         /* Runner on Byte*/                       /*00101101*/
    while (i < NIBBLE_BITS)
    {
        /* Extract the i-th bit from the least significant end */
        mir_i_left = (byte >> i) & 1;                               /*00000001*/
        mir_i_right = (byte >> (i + NIBBLE_BITS) ) & 1;             /*00000001*/
        
        /* Place the bit in the mirror at the mirrored position */

        final_mirror |= mir_i_left | mir_i_right;
        ++i;
    }
    return final_mirror;
}


/*5.b. ByteMirror - mirror 8 bits of byte
• Implement without a loop. */
unsigned char ByteMirrorMask(unsigned char byte)
{
    /* Swap the 4-bit nibbles using bit masking and shifting */
    byte = ((byte & 0xF0) >> 4) | ((byte & 0x0F) << 4);
    /* Swap the 2-bit groups using bit masking and shifting */
    byte = ((byte & 0xCC) >> 2) | ((byte & 0x33) << 2);
    /* Swap adjacent bits using bit masking and shifting */
    byte = ((byte & 0xAA) >> 1) | ((byte & 0x55) << 1);
    return byte;
}

/*6 Implement the following functions without using an if:*/

/*6.a. • A function that receives an unsigned char and checks 
the 2nd and 6th bits. If they are both on, returns true.*/
int CheckBoth2And6(unsigned char ch)
{
    /* Create masks for the 2nd (bit 1) and 6th (bit 5) bits */
    unsigned char mask2 = (1U << 1); /* 0000 0010 */
    unsigned char mask6 = (1U << 5); /* 0010 0000 */

    /* Check if both the 2nd and 6th bits are set */
    /* True: both 2nd and 6th bits are set */
    return (ch & mask2) && (ch & mask6); 
}

/*6.b. • A function that receives an unsigned char and checks
the 2nd and 6th bits. If at least one of them is on, returns true.*/
int CheckOneOf2And6(unsigned char ch)
{
    /* apply mask 0100 0100 to leave only bits 2 & 6 */
    unsigned char mask = ch & 0x44;

    /* check if at least one of the 2nd or 6th bits is set */
    return CountOnes(mask); /* True: at least one of the bits is set */
}

/*6.c. • A function that receives an unsigned char, 
        swaps between the 3rd and 5th bits, and returns the new number.*/
unsigned char Swap3rdAnd5thBits(unsigned char ch)
{
    /* Create masks for the 3rd (bit 2) and 5th (bit 4) bits */
    unsigned char mask3 = (1 << 2); /* 0000 0100 */
    unsigned char mask5 = (1 << 4); /* 0001 0000 */

    /* Extract the 3rd and 5th bits & shift them to be swapped*/
    unsigned char bit3 = (ch & mask3) >> 2;
    unsigned char bit5 = (ch & mask5) << 2;

    /* PURGE the 3rd and 5th bits in the original number */
    ch &= ~(mask3 | mask5);

    /* Place the extracted bits in the original number */
    ch |= (bit3 | bit5);

    return ch;
}

/*7.a. A function that receives an unsigned int and returns the closest (smaller) number that is divisible by 16 without a remainder.
• For example: 33 returns 32, 17 returns 16, 22 returns 16.*/
unsigned int ClosestDivisibleBy16Bitwise(unsigned int num)
{
    /* shift 4 time to validate the number is even dividable by 16 at all */
    return num & 0xfff0; /* return at least 16 by masking LSByte*/
}

/*7.b. A function that receives an unsigned int and returns the 
closest (smaller) number that is divisible by 16 without a remainder.*/
unsigned int ClosestDivisibleBy16Arth(unsigned int num)
{
    /* Calculate the remainder when dividing by 16 */
    unsigned int remainder = num % 16;
    /* Calculate the closest smaller number divisible by 16 */
    unsigned int closestDivisible = num - remainder;
    return closestDivisible;
}

/*8. A function that swaps 2 variables without using a third variable
Will it always work? Why?*/
/* Function to swap two variables without using a third variable */
void SwapWithoutThirdVariable(int *a, int *b)
{
    /*checks if a and b are different addresses to avoid issues
    when trying to swap a variable with itself. */
    if (a != b)
    {
        /* Perform bitwise XOR swap */
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

/*9. A function that counts the number of set bits in an integer.
/* 9.a. Function to count the number of set bits using a loop */
size_t CountSetBitsLoop(int n)
{
    return CountOnes(n);
}

/* 9.b. Function to count the number of set bits without using a loop */
size_t CountSetBitsNoLoop(int n)
{
    /* Counting set bits in each pair of bits (2 consecutive bits). */
    n = n - ((n >> 1) & 0x55555555);

    /* Counting set bits in each nibble (4 bits). */
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);

    /* Counting set bits in each byte (8 bits). */
    n = (n + (n >> 4)) & 0x0F0F0F0F;

    /* Counting set bits in each 16-bit word (16 bits). */
    n = n + (n >> 8);

    /* Counting set bits in each 32-bit word (32 bits). */
    n = n + (n >> 16);

    /* Return the final count, which is the number of set bits in the original 
       integer 'n'. Mask to retain the 6 least significant bits 
       (count cannot exceed 32 bits). */
    return n & 0x0000003F; 
}

/* Function to print the binary representation of a float */
void PrintFloatBits(float num)
{
    unsigned int* ptr = (unsigned int*)&num;

    /* Extract the integer representation of the float */
    unsigned int value = *ptr;

    /* Print the binary representation */
    size_t bit_count = sizeof(float) * 8;
    size_t i = 0;
    while (i < bit_count)
    {
        /* Extract the bit at position (bit_count - 1 - i) and print it */
        printf("%d", (value >> (bit_count - 1 - i)) & 1);

        /* Move to the next bit towards the LSB */
        i++;
    }
    printf("\n");
}

/****************************** Helper Functions ***************************/

/* Function to print the binary representation starting from LSB unsigned int */
void PrintBinary(unsigned int num, size_t data_length)
{
    /* Check if the specified length is valid */
    size_t bit_count = sizeof(unsigned int) * 8;

    if (data_length > bit_count)
    {
        printf("Invalid length specified.\n");
        return;
    }

    /* Print the binary representation of the specified
    number of bits starting from LSB */
    int i = data_length - 1; /* Start from the least significant bit */

    while (i >= 0)
    {
        /* Extract the bit at position i and print it */
        printf("%d", (num >> i) & 1);

        /* Move to the next bit towards the most significant bit (MSB) */
        --i;
    }
}

/********************************** WHEN TO USE XOR ***************************/
/*
Simmilars = 0, Strangers = 1;

XOR (exclusive OR) is a fundamental bitwise operation that is used to manipulate individual bits within an integer or other binary data. It has several important properties that make it useful in various scenarios:

Flipping bits: XORing a bit with 1 will flip the bit (0 becomes 1, and 1 becomes 0). This property is often used to toggle specific bits in an integer.

Clearing bits: XORing a bit with 0 will leave the bit unchanged. If you XOR an integer with a bitmask where all the bits are 0 except for the bit you want to clear (which is set to 1), it will effectively clear the specified bit.

Extracting differences: XOR can be used to find the differences between two integers. XORing two integers with the same value will result in 0 for all common bits and non-zero for differing bits.

Swapping variables without a temporary variable: XOR can be used to swap the values of two variables without the need for a temporary variable. This technique is known as the XOR swap algorithm.
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
*/
