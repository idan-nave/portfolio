/*
  Name: Idan Nave
  Project: Linear Sorts
  Reviewer: Sahar
  Date: 28/09/2023
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <stdio.h>              /* printf */
#include <stdlib.h>             /* malloc(), free() */
#include <stddef.h>             /* size_t, NULL */
#include <time.h>               /* clock() */

#include "linear_sorts.h"    

/********************************* Type Definitions **************************/
    
#define ARR_SIZE 10000    
#define ELEM_RANGE 10000    
#define EQUAL 0    
#define DISABLE_PRINTS TRUE    
#define TIME_FACTOR 1    
#define TIME_UNIT "sec"    
#define RAND_NEG_NUMS TRUE    

#define REPORT(expected , result, str) \
  {\
      if (expected != result)\
      {\
        printf("%s has failed\n", str);\
      }\
  }
  
/*********************** Helper Functions Declerations ***********************/

static void QsortIntArray(int* arr, int size);
static int  CompareIntArrays(int arr1[], int arr2[], int size);
static int  CompareInts(const void *a, const void *b);
static void InitArrayWithRandomNumbers(int* arr, int size);
static void CopyIntArray(int destination[], int source[], int size);
static void PrintArray(int *arr, size_t arr_size);

/**************************** Test Functions Declerations ********************/

static void MainTestFunc(void);

static void TestCountingSort(void);
static void TestRadixSort(void);

/*****************************************************************************/
/*************************************** Main ********************************/
/*****************************************************************************/

int main()
{
  srand(time(NULL));
  MainTestFunc();
  return 0;
}

static void MainTestFunc(void)
{
  TestCountingSort();
  TestRadixSort();
}

/*****************************************************************************/
/**************************** Test Functions Definitions *********************/
/*****************************************************************************/

static void TestCountingSort()
{
    int tested_arr[ARR_SIZE];
    int q_sorted_arr[ARR_SIZE];
    double q_elapsed_time = 0;
    double t_elapsed_time = 0;
    clock_t q_start_time = 0;
    clock_t t_start_time = 0;

    InitArrayWithRandomNumbers(tested_arr, ARR_SIZE);
    if (TRUE != DISABLE_PRINTS)
    {   
        printf("\n\n####### Testing CountingSort() ########\n");
        printf("Tested Array:\n");PrintArray(tested_arr, ARR_SIZE);
    }

    CopyIntArray(q_sorted_arr, tested_arr, ARR_SIZE);

    q_start_time = clock();
    QsortIntArray(q_sorted_arr, ARR_SIZE);
    q_elapsed_time = (double)(clock() - q_start_time) / CLOCKS_PER_SEC;

    t_start_time = clock();
    CountingSort(tested_arr, ARR_SIZE);   
    t_elapsed_time = (double)(clock() - t_start_time) / CLOCKS_PER_SEC;

    if (FALSE == CompareIntArrays(q_sorted_arr, tested_arr, ARR_SIZE))
    {
            printf("TestCountingSort() FAILED\n");
    }

    printf("Qsort is done in %f %s\n", q_elapsed_time*TIME_FACTOR, TIME_UNIT);
    printf("CountingSort is done in %f %s\n", t_elapsed_time*TIME_FACTOR, TIME_UNIT);
    printf("TestCountingSort() tested\n");
}

static void TestRadixSort()
{
    int tested_arr[ARR_SIZE];
    int q_sorted_arr[ARR_SIZE];
    double q_elapsed_time = 0;
    double t_elapsed_time = 0;
    clock_t q_start_time = 0;
    clock_t t_start_time = 0;

    InitArrayWithRandomNumbers(tested_arr, ARR_SIZE);
    if (TRUE != DISABLE_PRINTS)
    {   
        printf("\n\n####### Testing RadixSort() ########\n");
        printf("Tested Array:\n");PrintArray(tested_arr, ARR_SIZE);
    }
    CopyIntArray(q_sorted_arr, tested_arr, ARR_SIZE);

    q_start_time = clock();
    QsortIntArray(q_sorted_arr, ARR_SIZE);
    q_elapsed_time = (double)(clock() - q_start_time) / CLOCKS_PER_SEC;

    t_start_time = clock();
    RadixSort(tested_arr, ARR_SIZE);   
    t_elapsed_time = (double)(clock() - t_start_time) / CLOCKS_PER_SEC;

    if (FALSE == CompareIntArrays(q_sorted_arr, tested_arr, ARR_SIZE))
    {
            printf("TestRadixSort() FAILED\n");
    }

    printf("Qsort is done in %f %s\n", q_elapsed_time*TIME_FACTOR, TIME_UNIT);
    printf("RadixSort is done in %f %s\n", t_elapsed_time*TIME_FACTOR, TIME_UNIT);
    printf("TestRadixSort() tested\n");
}

/*Static function to sort an integer array*/
static void QsortIntArray(int* arr, int size)
{
    qsort(arr, size, sizeof(int), CompareInts);
}

static int CompareIntArrays(int arr1[], int arr2[], int size)
{
    int i = 0;
    for (; i < size; i++)
    {
        if (EQUAL != CompareInts(arr1 + i, arr2 + i))
        {
            return FALSE; /*Elements at position i are not equal*/
        }
    }
    return TRUE; /*All elements are equal*/
}

/*Comparison function for qsort*/
static int CompareInts(const void *a, const void *b)
{
    int intA = *((int*)a);
    int intB = *((int*)b);

    if (intA < intB) return -1;
    if (intA > intB) return 1;
    return EQUAL;
}

static void InitArrayWithRandomNumbers(int* arr, int size)
{
    int i = 0;
    /*Seed the random number generator with the current time*/
    srand(time(NULL));

    /*Fill the array with random numbers*/
    for (; i < size; i++)
    {
        int neg_range = 0;
        if (TRUE == RAND_NEG_NUMS)
        {
            neg_range = (-1) * (rand() % ELEM_RANGE);
        }
        arr[i] = rand() % ELEM_RANGE + neg_range;
    }
}

/*Static function to copy an array*/
static void CopyIntArray(int destination[], int source[], int size)
{
    int i = 0;
    for (; i < size; i++)
    {
        destination[i] = source[i];
    }
}

static void PrintArray(int *arr, size_t arr_size)
{
    size_t i = 0;
    for (; i < arr_size; ++i)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");
}