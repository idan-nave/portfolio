/******************************** ArrPtrs.c  **********************************/
/*Name: HRD 32
  Project: WS6 - Array Pointers
  Reviewer: Aya ?
  Date: 13.07.23
  Version: 1.0*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* For input validation */
#include <stddef.h>  		/* For size_t type*/
#include <stdlib.h> 		/* For memory allocation and deallocation */
#include <stdio.h>  		/* For standard input/output */

#include "ArrPtrs.h"	        /* APIs Header */

/******************** MATRIX API IMPLEMENTATIONS  ****************************/

/*Function that receives a matrix and calculates the sum of each row.*/
void GenAndPrintMatrixRowSums(const size_t rows, const size_t cols)
{  
    size_t i_print = 0;

    size_t** matrix;
    size_t* matrix_rows_sum = (size_t *)malloc(rows * sizeof(size_t));
    matrix = GenRandMatrix(rows, cols);
    PrintMatrix( (const size_t**)matrix, rows, cols);
   /* SumEachRow( (const size_t**)matrix, matrix_rows_sum, rows, cols);*/
    PrintArr(matrix_rows_sum, rows);
    FreeMat(matrix, rows);
    FreeArr(matrix_rows_sum);
}

/*Function that receives a matrix and calculates the sum of each row.*/
void SumEachRow(const size_t **mat, size_t *res, const size_t rows, const size_t cols)
{   
    /* initialize sum and indexes */
    size_t sum = 0;
    size_t i =0 , j = 0;
    while (i < (size_t)rows)
    { 
        /* initialize row sum and column index */
        j = 0; sum = 0;
        while (j < (size_t)cols)
        {
            sum += mat[i][j];
            *(res+i) = sum;
            /*printf("%u\n", *(res+i));*/
            ++j;
        }
        ++i;
     }
}

/*Function that displays Matrix elements */
void PrintMatrix(const size_t **mat, const size_t rows, const size_t cols)
{
   size_t i =0 , j = 0;
   printf("Two Dimensional array elements:\n");
   while (i < (size_t)rows)
   {  
         while (j < (size_t)cols)
         {
          /* prints column-element value each iteration */
           printf("%lu ", mat[i][j]);
           if(j == cols-1)
           {
              /* open next line for printing next row */
              printf("\n");
           }
           ++j;
         }
         ++i;
         j = 0;
   }
   printf("\n");
}

/*Function that displays array elements */
void PrintArr(const size_t *arr, const size_t len)
{
   size_t i =0;
   printf("One Dimensional array elements:\n");
   while (i < (size_t)len)
   {  
       /* prints element value each iteration */
      printf("%lu, ", *arr+i);
      ++i;
   }
   printf("\n\n");
}

/*Function that generates random Josephus game-Matrix */
size_t **GenJosephusMatrix(const size_t len)
{
    size_t i_alloc = 0;
    size_t **j_circle = (size_t **)malloc(len * sizeof(size_t*));
    for(; i_alloc < len; i_alloc++)
    {
      /* allocate 2 cells for each Josephus Soldier:
        #1 is for the soldier's index within the circle.
        #2 is for the next-alive soldier index.
      */
      j_circle[i_alloc] = (size_t *)malloc(2 * sizeof(size_t));
    }
    assert(j_circle);      /*validate successful allocation */
    
    /* Initialize the Josephus matrix:
        #1 col. for each soldiers holds his place index inside the circle.
        #2 col. for each solj_circlediers holds his place+1 index inside the circle,
        except for last that points back to zero place.
    */
    size_t i = 0;
    while (i < (size_t)len)
    {
        j_circle[i][0] = i;
        j_circle[i][1] = i + 1;
        ++i;
    }
    j_circle[i-1][1] = 0; /* last points to first */
    return (size_t**)j_circle;
}

/*Function that plays and prints Josephus game, returns last standing soldier index*/
size_t PlayJosephus(const size_t len)
{

   size_t** j_circle;
   j_circle = GenJosephusMatrix(len);
   printf("Josephus Circle on start:\n");
   PrintMatrix( (const size_t**)j_circle, len, 2);
    
   size_t nxt = j_circle[0][1];  /* first index points to the next
                                  soldier pointed by the 1st soldier */ 
   size_t i = 0;                 /* current index of pointing soldier*/ 
   /* as long as the last soldier standing does not
   point to himself as the next soldier */
   /*j_circle[nxt][1] != j_circle[nxt][0] OR  i != nxt*/
   while (j_circle[nxt][1] != j_circle[nxt][0])
   {  
          /* go to add pointed by nxt */
          j_circle[nxt][0] = 0;
          /* kill marked soldier */
          j_circle[i][1] = j_circle[nxt][1];
          /* update the killer finger */
          i = j_circle[i][1];
          /* update k */
          nxt = j_circle[i][1];
   }
   printf("Josephus Circle after playing:\n");
   PrintMatrix( (const size_t**)j_circle, len, 2);
   FreeMat((size_t**)j_circle,100);
   return i+1;
}

/*Function that generates a random matrix*/
size_t **GenRandMatrix(const size_t rows, const size_t cols)
{
    size_t i_alloc = 0;
    size_t **rnd_mat = (size_t **)malloc(rows * sizeof(size_t*));
    for(; i_alloc < rows; i_alloc++)
    {
      /* allocate new array for each row */
      rnd_mat[i_alloc] = (size_t *)malloc(cols * sizeof(size_t));
    }
    assert(rnd_mat);      /*validate successful allocation */
    
    size_t i = 0;
    size_t j = 0;
    while (i < (size_t)rows)
    {
            while (j < (size_t)cols)
            {
                rnd_mat[i][j] = rand()%10;
                ++j;
            }
        ++i;
       j = 0;
    }
    return (size_t**)rnd_mat;
}

/*Function that prints all C data-tyes sizes */
void PrintDataTypes()
{
    short int short_int;
    unsigned short int u_short_int;
    unsigned int u_int;
    int _int;
    long int long_int;
    unsigned long int u_long_int;
    long long int long_long_int;
    unsigned long long int u_long_long_int;
    signed char _char; 
    unsigned char u_char;
    float _float;
    double _double;
    long double long_double;

    printf("size of short int is %ld\n", sizeof(short_int));
    printf("size of unsigned short int is %ld\n", sizeof(u_short_int));
    printf("size of unsigned int is %ld\n", sizeof(u_int));
    printf("size of int is %ld\n", sizeof(_int));
    printf("size of long int is %ld\n", sizeof(long_int));
    printf("size of unsigned long int is %ld\n", sizeof(u_long_int));
    printf("size of long long int is %ld\n", sizeof(long_long_int));
    printf("size of unsigned long long int is %ld\n", sizeof(u_long_long_int));
    printf("size of signed char is %ld\n", sizeof(_char)); 
    printf("size of unsigned char is %ld\n", sizeof(u_char));
    printf("size of float is %ld\n", sizeof(_float));
    printf("size of double is %ld\n", sizeof(_double));
    printf("size of long double is %ld\n", sizeof(long_double));
    printf("size of void is %ld\n", sizeof(void));
}

/*Function that frees dynamic matrixs */
void FreeMat(size_t **mat, const size_t rows)
{
    size_t i_row = 0;
    for(; i_row < (size_t)rows; i_row++)
    {
      /* free inner array for each row */
      free(mat[i_row]);
      mat[i_row]=NULL;
    }
    free(mat);
    mat = NULL;
}

/*Function that frees dynamic arrays */
void FreeArr(size_t *arr)
{
    free(arr);
    arr = NULL;
}
