/******************************** ArrPtrs.h  **********************************/
/*Name: HRD 32
  Project: WS6 - Array Pointers
  Reviewer: Aya ?
  Date: 13.07.23
  Version: 1.0*/
  
/******************************** LIBRARIES  **********************************/

#ifndef __ARRPRTS_H__
#define __ARRPRTS_H__

#include <stddef.h>  /*Using size_t in header file*/

/******************************* DECLERATIONS *********************************/

/*Function that prints all C data-tyes sizes */
void PrintDataTypes();

/************ Handle Arrays *********/
/*Function that frees dynamic matrixs */
void FreeMat(size_t **mat, const size_t rows);
/*Function that frees dynamic arrays */
void FreeArr(size_t *arr);
/*Function that displays array elements */
void PrintArr(const size_t *arr, const size_t len);
/*Function that displays Matrix elements */
void PrintMatrix(const size_t **mat, const size_t rows, const size_t cols);
/*Function that lowers all chars of given string */
char* ToLowerStr(char*str);

/************ Advanced Arrays *********/
/*Function that receives a matrix and calculates the sum of each row.*/
void SumEachRow(const size_t **mat, size_t *res, const size_t rows, const size_t cols);
/*Function that receives a matrix and calculates the sum of each row.*/
void GenAndPrintMatrixRowSums(const size_t rows, const size_t cols);
/*Function that generates a random matrix*/
size_t **GenRandMatrix(const size_t rows, const size_t cols);

/************ Games *********/
/*Function that generates random Josephus game-Matrix */
size_t **GenJosephusMatrix(const size_t len);
/*Function that plays and prints Josephus game, retuns last standing soldier index*/
size_t PlayJosephus(const size_t len);



/******************************************************************************/

#endif /*(__ARRPRTS_H__)*/
