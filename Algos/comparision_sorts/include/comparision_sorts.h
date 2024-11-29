/*
  Name: Idan Nave
  Project: Comparision sorts
  Reviewer: Uri
  Date: 26/09/23
  Version: 1.0
*/
/******************************** Definitions  ********************************/

#ifndef __ILRD_COMPARISION_SORTS__
#define __ILRD_COMPARISION_SORTS__

typedef enum {FALSE = 0, TRUE} comparision_sorts_boolean_ty;

/******************************** Libraries  **********************************/

#include <stddef.h>             /* size_t */

/******************************** API Functions *******************************/

void BubbleSort(int* arr, size_t arr_size);
void InsertionSort(int* arr, size_t arr_size);
void SelectionSort(int* arr, size_t arr_size);

#endif /*(__ILRD_COMPARISION_SORTS__)*/
