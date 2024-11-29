/*
  Name: Idan Nave
  Project: Linear Sorts
  Reviewer: Sahar
  Date: 28/09/2023
  Version: 1.0
*/
/******************************** Definitions  ********************************/

#ifndef __ILRD_LINEAR_SORTS__
#define __ILRD_LINEAR_SORTS__

typedef enum {FALSE = 0, TRUE} linear_sorts_boolean_ty;
typedef enum {SUCCESS = 1, FAILIURE} linear_sorts_status_ty;

/******************************** Libraries  **********************************/

#include <stddef.h>                                         /* size_t */

/******************************** API Functions *******************************/

int CountingSort(int* arr, size_t arr_size);
int RadixSort(int* arr, size_t arr_size);

#endif /*(__ILRD_LINEAR_SORTS__)*/
