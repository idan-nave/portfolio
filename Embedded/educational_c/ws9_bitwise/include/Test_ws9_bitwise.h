/***************************** Test_ws9_bitwise.h  ****************************/
/*
  Name: Idan Nave
  Project: Work Sheet #9 - BitWise
  Reviewer: Liel
  Date: 22/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/

#ifndef __TST_WS9_HEADER_H__
#define __TST_WS9_HEADER_H__

#include <Test_ws9_bitwise.h>  /*Using size_t in header file*/

/******************************* DECLARATIONS *********************************/

/*Function Description*/

/* Test function to validate Test_MultXByPow2() */
int Test_MultXByPow2();
/* Test function to validate Test_MultXByPow2() */
int Test_CountOnes();
/* Test function to validate IsPowerOf2Loop() */
int Test_IsPowerOf2();
/* Test function to validate Add1ToIntBitWise() */
int Test_Add1ToIntBitWise();
/* Test function to validate PrintOnly3SetBits() */
int Test_PrintOnly3SetBits();
/* Test function to validate ByteMirrorLoop() & ByteMirrorSimple() */
int Test_ByteMirror();
/* Test function to validate CheckOneOf2And6 */
int Test_CheckBoth2And6();
/* Test function to validate CheckOneOf2And6 */
int Test_CheckOneOf2And6();
/* Test function to validate Swap3rdAnd5thBits */
int Test_Swap3rdAnd5thBits();
/* Test function to validate ClosestDivisibleBy16 */
int Test_ClosestDivisibleBy16Bitwise();
/* Function to test SwapWithoutThirdVariable */
void Test_SwapWithoutThirdVariable();
/* Test function to validate both CountSetBitsLoop and CountSetBitsNoLoop */
int Test_CountSetBits();
/* Function to test the PrintFloatBits function */
void TestPrintFloatBits();


/****************************** Auxiliary Functions ***************************/

/* Function to check if an integer is a power of 2 using arithmetic operations */
int IsPowerOf2Arth(int num);
/* Function to count ones using arithmetic operations */
size_t CountOnesArth(unsigned int num);

/****************************** User Input Functions **************************/

/* Function that prints a short manual from file */
void GreetUser();
/* Function that handles requests*/
size_t HandleMenuInput();
/* Function that receives user-input as option index accepts / ESC to exit
returns the input after validation, or 0 for exit*/
size_t GetMenuSelection(size_t range);
/* Function that prints current file contents to CLN*/
int FilePrint(const char *filename);

#endif /*(__TST_WS9_HEADER_H__)*/
