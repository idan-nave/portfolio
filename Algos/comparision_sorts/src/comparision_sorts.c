/*
  Name: Idan Nave
  Project: Comparision sorts
  Reviewer: Uri
  Date: 26/09/23
  Version: 1.0
*/
/******************************** Libraries  **********************************/

#include <assert.h> 		/* assert() */
#include <stdio.h>  		/* printf */

#include "comparision_sorts.h" 		

/********************* Helper Functions Declerations **************************/

static void PrintArray(int *arr, size_t arr_size);
static void Swap(int *a, int *b);

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
/*Bubble sort is a sorting algorithm that compares two adjacent elements and swaps them until they are in the intended order. */
void BubbleSort(int* arr, size_t arr_size)
{
    size_t step = 0;
    size_t not_sorted = 1;

    assert(NULL != arr);
    assert(0 != arr_size);

    while ( not_sorted )
    {
        size_t i = 1;
        not_sorted = 0;
        for (; i < arr_size - step; ++i) 
        {
            if(arr[i-1] > arr[i])
            {
                Swap(&arr[i-1] , &arr[i]);
                ++not_sorted; /*if statement was entered, so keep sortin*/
            }
        }
        ++step;
        /*PrintArray(arr, arr_size);*/  /*only here for debug*/
    }
}

/* Insertion sort is a sorting algorithm that places an unsorted element at its suitable place in each stepation. */
void InsertionSort(int* arr, size_t arr_size)
{
    size_t key = 1;

    assert(NULL != arr);
    assert(0 != arr_size);

    for (; key < arr_size; ++key)
    {
        size_t i = key;
        int current = arr[key];

        /* Move elements of arr[0..key-1] that are greater than current
        to one position ahead of their current position*/
        while (i > 0 && arr[i - 1] > current)
        {
            arr[i] = arr[i - 1];
            --i;
        }
        /*PrintArray(arr, arr_size);*/ /*only here for debug*/
        arr[i] = current; /*Place current element at correct position*/
    }
}

/* Selection sort is a sorting algorithm that selects the smallest element from an unsorted list in each stepation and places that element at the beginning of the unsorted list. */
void SelectionSort(int* arr, size_t arr_size)
{
    size_t step = 0;

    assert(NULL != arr);
    assert(0 != arr_size);

    for (; step < arr_size - 1; ++step) 
    {
        size_t min_val_idx = step;
        size_t i = step + 1;
        for (; i < arr_size; ++i)
        {
            if(arr[i] < arr[min_val_idx])
            {
                min_val_idx = i;
            }
        }
        Swap(&arr[min_val_idx], &arr[step]);
        /*PrintArray(arr, arr_size);*/ /*only here for debug*/
    }
}

/******************************************************************************/
/********************* Helper Functions Definitions ***************************/
/******************************************************************************/

/*function to swap the the position of two elements*/
static void Swap(int* a, int* b)
{

    assert(NULL != a);
    assert(NULL != b);

    if (a != b) /*Ensure a and b are distinct memory locations*/
    {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
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