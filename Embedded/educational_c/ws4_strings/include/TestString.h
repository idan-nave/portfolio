/*************************** TestStrings.h META  ******************************/
/*Name: HRD 32
  Project: String Function Re-implementation
  Reviewer: Liel
  Date: 04/07/2023
  Version: 1.0*/
  
/******************************** LIBRARIES  **********************************/
#ifndef __TESTSTRING_H__
#define __TESTSTRING_H__

#include <stddef.h>  /*Using size_t in header file*/


/******************************* DECLERATIONS *********************************/

/* String Function Testing Overview:
 * -------------------------------
 * Testing functions to validate various string functions.
 * Each function focuses on one specific string function.
 * Test cases cover normal, edge, and special cases.
 * Compare expected results against actual results.
 * Return number of failed tests or 0 for all pass.
 */

int TestStrLen();
int TestStrCpy();
int TestStrnCpy();
int TestStrCmp();
int TestStrnCmp();
int TestStrCaseCmp();
int TestStrChr();
int TestStrDup();
int TestStrCat();
int TestStrnCat();
int TestStrStr();
int TestStrSpn();
 

#endif
