/*
  Name: Idan Nave
  Project: Linear Sorts
  Reviewer: Sahar
  Date: 28/09/2023
  Version: 1.0
*/
/******************************** Libraries  **********************************/

#include <assert.h>         /* assert() */
#include <stdio.h>          /* printf() */
#include <stdlib.h>         /* abs() */
#include <limits.h>         /* INT_MIN, INT_MAX */

#include "linear_sorts.h" 		

/******************************** Definitions  ********************************/

#define BASE10 10
#define MOD10(val, magnitude) ( ( (val) / (magnitude) ) % BASE10 )

/********************* Helper Functions Declerations **************************/

static int RadixCountingSort(int* arr, size_t arr_size, size_t radix);
static void GetMinMax(int *arr, size_t arr_size, int *max, int *min);
static size_t GetRadix(int num);
static void PrintArray(int *arr, size_t arr_size);

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
/*
Counting Sort is a stable sorting algorithm, meaning that the relative order of equal elements is preserved in the sorted output.
It works by counting the number of occurrences of each distinct integer keyue in the input array and using that information to key each element in its correct sorted position.
Counting Sort assumes that the input consists of integers within a known range (usually within a small range) because it creates a "counting array" of that size.
It has a time complexity of O(n + k), where n is the number of elements to be sorted, and k is the range of input keyues. Counting Sort can be very efficient when k is much smaller than n.
*/
int CountingSort(int* arr, size_t arr_size)
{
    int* count_arr = NULL;
    int* sorted_arr = NULL;
    size_t i = 0;
    int max_elem = arr[0];
    int min_elem = arr[0];
    int offset = 0;
    size_t counting_range = 0;
    int curr_val = 0;
    size_t place_idx = 0;

    assert(NULL != arr);
    assert(0 != arr_size);

    GetMinMax(arr, arr_size, &max_elem, &min_elem);
    /*special cases optimization*/
    if(1 == arr_size || (min_elem == max_elem))
    {
        /*arr contains a single value(s) and is considered sorted*/
        return SUCCESS;
    }

    /*allocating a zeroed output sorted array*/
    sorted_arr = (int*)calloc(arr_size, sizeof(int));
    if (NULL == sorted_arr)
    {
        return FAILIURE;
    }
 
    /*counting arr size definition*/
    offset = (0 - min_elem);
    counting_range = (size_t)(max_elem - min_elem + 1); 

    /*counting arr allocation, initialized with zeroes*/
    count_arr = (int*)calloc(counting_range, sizeof(int));
    if (NULL == count_arr)
    {
        free(sorted_arr);
        sorted_arr = NULL;
        return FAILIURE;
    }

    /*populating counting array with num of instances of elements in arr*/
    i = 0;
    for (; i < arr_size; ++i) 
    {
         ++count_arr[ arr[i] + offset];
    }

    /*adjusting the counting array for idx accumulation*/
    i = 1;
    for (; i < counting_range; ++i) 
    {
        count_arr[i] += count_arr[i-1];
    }

    /*Find the index of each element of the original array in count array*/ 
    i = arr_size ;
    for(; 0 < i; --i)
    {
        curr_val = arr[i-1];
        place_idx = count_arr[curr_val + offset] - 1;
        sorted_arr[place_idx] = curr_val;
        --count_arr[curr_val + offset]; /*in case of val multiplication*/
    }

    i = 0;
    for (; i < arr_size; ++i) 
    {
        arr[i] = sorted_arr[i];
    }

    /* Free allocated memory */
    free(sorted_arr);
    sorted_arr = NULL;
    free(count_arr);
    count_arr = NULL;

    return SUCCESS;
}

/*
Radix Sort is a non-comparative integer sorting algorithm that works by sorting digits of numbers from the least significant digit (LSD) to the most significant digit (MSD) or vice versa.
It is particularly suitable for sorting integers with a fixed number of digits or integers represented in base-n positional numeral systems.
Radix Sort can be implemented in two variants: LSD Radix Sort and MSD Radix Sort. LSD Radix Sort sorts the numbers from rightmost digit to leftmost digit, while MSD Radix Sort works in the opposite direction.
The time complexity of Radix Sort is O(nk), where n is the number of elements and k is the number of digits in the maximum number. It is typically faster than comparison-based sorting algorithms for large datasets or when the numbers have many digits.
*/
int RadixSort(int* arr, size_t arr_size)
{
    int max_elem = arr[0];
    int min_elem = arr[0];
    size_t radix = 0;
    size_t magnitude = 1;
    int status = SUCCESS;
    size_t i = 0;

    assert(NULL != arr);

    GetMinMax(arr, arr_size, &max_elem, &min_elem);
    /*offset whole arr to disregard negative nums*/
    i = 0 ;
    for(; arr_size > i; ++i)
    {
        arr[i] += abs(min_elem);
    }

    /*special cases optimization*/
    if(1 == arr_size || (min_elem == max_elem))
    {
        /*arr contains a single value(s) and is considered sorted*/
        return SUCCESS;
    }

    radix = GetRadix(max_elem);
    i = 0 ;
    for(; (i < radix + 1) && (SUCCESS == status); ++i)
    {
        /*because of the offset to positive values- loop will run up to radix+1 in case the offsetting had raised some of the members' radix*/
        status = RadixCountingSort(arr, arr_size, magnitude);
        magnitude *= BASE10;
    }

    /*offset whole arr back to origins*/
    i = 0 ;
    for(; arr_size > i; ++i)
    {
        arr[i] -= abs(min_elem);
    }

    return status;
}

/******************************************************************************/
/********************* Helper Functions Definitions ***************************/
/******************************************************************************/

/*A custom Counting-Sort function for sorting an array based on a given radix*/
static int RadixCountingSort(int* arr, size_t arr_size, size_t radix)
{
    int count_arr[BASE10] = {0}; /*counting array for base 10*/
    int* sorted_arr = NULL;
    size_t i = 0;
    int max_elem = INT_MIN;
    int min_elem = INT_MAX;
    int curr_val = 0;
    size_t place_idx = 0;

    assert(NULL != arr);
    assert(0 != arr_size);

    GetMinMax(arr, arr_size, &max_elem, &min_elem);
    /*special cases optimization*/
    if(1 == arr_size || (min_elem == max_elem))
    {
        /*arr contains single value(s) and is considered sorted*/
        return SUCCESS;
    }

    /*allocating a zeroed output sorted array*/
    sorted_arr = (int*)calloc(arr_size, sizeof(int));
    if (NULL == sorted_arr)
    {
        return FAILIURE;
    }

    /*populating counting array with num of instances of elements in arr*/
    i = 0;
    for (; i < arr_size; ++i) 
    {
        ++count_arr[ MOD10(arr[i], radix) ];
    }

    /*adjusting the counting array for idx accumulation*/
    i = 1;
    for (; i < BASE10; ++i) 
    {
        count_arr[i] += count_arr[i-1];
    }
    
    /*Find the index of each element of the original array in count array*/ 
    i = arr_size ;
    for(; 0 < i; --i)
    {
        curr_val = arr[i-1];
        place_idx = count_arr[ MOD10(curr_val, radix) ] - 1;
        sorted_arr[place_idx] = curr_val;
        --count_arr[ MOD10(curr_val, radix) ]; /*in case of val multiplication*/
    }

    i = 0;
    for (; i < arr_size; ++i) 
    {
        arr[i] = sorted_arr[i];
    }

    /* Free allocated memory */
    free(sorted_arr);
    sorted_arr = NULL;

    return SUCCESS;
}

/*Function to get the largest and smallest elements from an array*/
static void GetMinMax(int *arr, size_t arr_size, int *max, int *min)
{
    size_t i = 1;

    assert(NULL != arr);
    assert(NULL != max);
    assert(NULL != min);
    assert(0 != arr_size);

    *max = arr[0];
    *min = arr[0];

    for (; i < arr_size; i++)
    {
        if (arr[i] > *max)
        {
            *max = arr[i];
        }
        else if (arr[i] < *min)
        {
            *min = arr[i];
        }
    }
}

static size_t GetRadix(int num)
{
    size_t radix = 0;

    if (0 == num)
    {
        return 1;
    }

    while (0 != num) 
    {
        num /= 10;
        ++radix;
    }

    return radix;
}

static void PrintArray(int *arr, size_t arr_size)
{
    size_t i = 0;

    assert(NULL != arr);
    assert(0 != arr_size);

    for (; i < arr_size; ++i)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");
}