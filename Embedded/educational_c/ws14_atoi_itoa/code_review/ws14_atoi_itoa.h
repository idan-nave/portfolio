/***************************** ws14_atoi_itoa.h  *****************************/
/*
  Name: Idan Nave
  Project: Work Sheet 14 - atoi/itoa
  Reviewer: Aya
  Date: 07/08/23
  Version: 1.0
*/
/******************************* Definitions  ********************************/

#ifndef __WS14_ATOI_IOTA_H__
#define __WS14_ATOI_IOTA_H__

#define MAX_INT_DIGS 20	  /* Length of multi-type array */

/* FAIL TEST */
#define FAIL -1
#define PASS 0
#define TRUE 1
#define FALSE 0

/******************************* Libraries  **********************************/

#include <stddef.h>                                         /* size_t */

/********************** API Approved Functions - EXPOSED ********************/

/* Function to parse int into string */
int StringToInt(int *num, const char* int_str, size_t base);
/* Function to parse int into string */
int IntToString(int num, char* int_str, size_t base);
/*Function to Print Letters Appearing in Both Two Arrays but Not in the 3rd:*/
void PrintUniqueLettersInTwoOFThreeArrays();
/*Function to Check System Endianness */
int IsLittleEndian();

/*App Manager Function (called from Main)*/
int ExecuteApp();

#endif /*(__WS14_ATOI_IOTA_H__)*/
