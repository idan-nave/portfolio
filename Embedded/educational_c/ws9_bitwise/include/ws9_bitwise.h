/********************************** ws9_bitwise.h  ****************************/
/*
  Name: Idan Nave
  Project: Work Sheet #9 - BitWise
  Reviewer: Liel
  Date: 22/07/23
  Version: 1.0
*/
  
#ifndef __WS9_HEADER_H__
#define __WS9_HEADER_H__

/******************************** LIBRARIES  **********************************/

#include <stddef.h>  /*size_t*/

/******************************* DECLARATIONS *********************************/

/* 1.Function that multiplies x by 2^y */
long MultXByPow2(unsigned int x, unsigned int y);

/* Function to count number of set bits in unsigned int */
size_t CountOnes(unsigned int n);

/* 2.a.Function that receives unsigned int n,
• Returns 1 if n is a power of 2. Otherwise it returns ..
• Implement using a loop (in helper func). */
size_t IsPowerOf2Loop(unsigned int n);

/* 2.b.Function that receives unsigned int n,
• Returns 1 if n is a power of 2. Otherwise it returns ..
• Implement without a loop. */
size_t IsPowerOf2Simple(unsigned int n);

/* 3. A function that adds 1 to an int without using arithmetic operators.*/
int Add1ToIntBitWise(int n);

/*4. A function that receives an array of unsigned ints and only prints the ints that have exactly 3 bits on (set to 1).*/
size_t PrintOnly3SetBits(unsigned int *arr, size_t len);

/*5.a. ByteMirror - mirror 8 bits of byte
• Implement using a loop.*/
unsigned char ByteMirrorLoop(unsigned char byte);

/*5.b. ByteMirror - mirror 8 bits of byte
• Implement without a loop. */
unsigned char ByteMirrorMask(unsigned char byte);

/*6.a. • A function that receives an unsigned char and checks the 2nd and 6th bits. If they are both on, returns true.*/
int CheckBoth2And6(unsigned char ch);

/*6.b. • A function that receives an unsigned char and checks the 2nd and 6th bits. If at least one of them is on, returns true.*/
int CheckOneOf2And6(unsigned char ch);

/*6.c. • A function that receives an unsigned char, swaps between the 3rd and 5th bits, and returns the new number.*/
unsigned char Swap3rdAnd5thBits(unsigned char ch);

/*7. A function that receives an unsigned int and returns the closest (smaller) number that is divisible by 16 without a remainder.*/
unsigned int ClosestDivisibleBy16Bitwise(unsigned int num);
unsigned int ClosestDivisibleBy16Arth(unsigned int num);

/*8. Function to swap two variables without using a third variable */
void SwapWithoutThirdVariable(int *a, int *b);

/* 9.a. Function to count the number of set bits using a loop */
size_t CountSetBitsLoop(int n);

/* 9.b. Function to count the number of set bits without using a loop */
size_t CountSetBitsNoLoop(int n);

/*10.Function to print the binary representation of a float */
void PrintFloatBits(float num);



#endif /*(__WS9_HEADER_H__)*/
