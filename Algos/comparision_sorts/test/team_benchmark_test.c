/*******************************************************************************
  Name: Dima
  Project: Sorting Algorithms
  Reviewer: ---
  Date: 26/09/23
  Version: 1.0
*******************************************************************************/

#include <stdlib.h> /*rand(), qsort()*/
#include <stdio.h>
#include <time.h> /*clock()*/

#include "comparision_sorts.h"

/******************************DEFINES AND ENUMS*******************************/

#define ARR_SIZE 10000
/****************************FUNCTION DECLARATIONS*****************************/

void TestAll();

void BubbleTimeTest();
void SelectionTimeTest();
void InsertionTimeTest();


int CmpFunc(const void *num1, const void *num2);
/************************************* ****************************************/
/********************************** TESTS *************************************/
/************************************* ****************************************/

int main()
{
	TestAll();
	
	BubbleTimeTest();
	SelectionTimeTest();
	InsertionTimeTest();


	return 0;
}

void TestAll()
{
	int bubbl_arr[ARR_SIZE] = {0};
	int selct_arr[ARR_SIZE] = {0};
	int insrt_arr[ARR_SIZE] = {0};
	size_t size = ARR_SIZE;
	
	size_t i = 0;
	int rand_num = 0;
	
	for(i=0; i<ARR_SIZE; ++i)
	{
		rand_num = rand()%5000;
		
		bubbl_arr[i] = rand_num;
		selct_arr[i] = rand_num;
		insrt_arr[i] = rand_num;
	}
	
	
	BubbleSort(bubbl_arr, size);
	SelectionSort(selct_arr, size);
	InsertionSort(insrt_arr, size);
	
	for(i=0; i<ARR_SIZE; ++i)
	{
		if(bubbl_arr[i] != selct_arr[i])
		{
			printf("Test FAILED at iter %ld \n", i);
			return;
		}
		
		if(bubbl_arr[i] != insrt_arr[i])
		{
			printf("Test FAILED at iter %ld \n", i);
			return;
		}
		
		if(insrt_arr[i] != selct_arr[i])
		{
			printf("Test FAILED at iter %ld \n", i);
			return;
		}
	}
	
	printf("Test success. \n\n\n");
}


/******************************************************************************/

void BubbleTimeTest()
{
	int bubbl_arr[ARR_SIZE] = {0};
	int qsort_arr[ARR_SIZE] = {0};
	size_t size = ARR_SIZE;
	
	size_t i = 0;
	int rand_num = 0;
	
	clock_t time_start = 0;
	clock_t time_end = 0;
	double bubble_time = 0;
	double qsort_time = 0;
	
	for(i=0; i<ARR_SIZE; ++i)
	{
		rand_num = rand()%5000;
		
		bubbl_arr[i] = rand_num;
		qsort_arr[i] = rand_num;
	}
	
	time_start = clock();
	BubbleSort(bubbl_arr, size);
	time_end = clock();
	bubble_time = difftime(time_end, time_start);
	
	/*printf("Bubble sort time = %f\n", bubble_time);*/
	
	time_start = clock();
	qsort(qsort_arr, ARR_SIZE, sizeof(int), CmpFunc);
	time_end = clock();
	qsort_time = difftime(time_end, time_start);
	
	/*printf("Qsort time = %f\n", qsort_time);*/
	
	printf("Bubble sort Benchmark: %f%% \n", (qsort_time/bubble_time)*100 );
}


void SelectionTimeTest()
{
	int selct_arr[ARR_SIZE] = {0};
	int qsort_arr[ARR_SIZE] = {0};
	size_t size = ARR_SIZE;
	
	size_t i = 0;
	int rand_num = 0;
	
	clock_t time_start = 0;
	clock_t time_end = 0;
	double selection_time = 0;
	double qsort_time = 0;
	
	for(i=0; i<ARR_SIZE; ++i)
	{
		rand_num = rand()%5000;

		selct_arr[i] = rand_num;
	}
	
	time_start = clock();
	SelectionSort(selct_arr, size);
	time_end = clock();
	selection_time = difftime(time_end, time_start);
	
	/*printf("Selection sort time = %f\n", selection_time);*/
	
	time_start = clock();
	qsort(qsort_arr, ARR_SIZE, sizeof(int), CmpFunc);
	time_end = clock();
	qsort_time = difftime(time_end, time_start);
	
	/*printf("Qsort time = %f\n", qsort_time);*/
	
	printf("Selection sort benchmark: %f%% \n", (qsort_time/selection_time)*100 );
}


void InsertionTimeTest()
{
	int insrt_arr[ARR_SIZE] = {0};
	int qsort_arr[ARR_SIZE] = {0};
	size_t size = ARR_SIZE;
	
	size_t i = 0;
	int rand_num = 0;
	
	clock_t time_start = 0;
	clock_t time_end = 0;
	double insertion_time = 0;
	double qsort_time = 0;
	
	for(i=0; i<ARR_SIZE; ++i)
	{
		rand_num = rand()%5000;
		
		insrt_arr[i] = rand_num;
		qsort_arr[i] = rand_num;
	}
	
	time_start = clock();
	InsertionSort(insrt_arr, size);
	time_end = clock();
	insertion_time = difftime(time_end, time_start);
	
	/*printf("Insertion time = %f\n", insertion_time);*/
	
	
	time_start = clock();
	qsort(qsort_arr, ARR_SIZE, sizeof(int), CmpFunc);
	time_end = clock();
	qsort_time = difftime(time_end, time_start);
	
	/*printf("Qsort time = %f\n", qsort_time);*/
	
	printf("Insertion sort benchmark: %f%% \n", (qsort_time/insertion_time)*100 );
}




/******************************************************************************/

int CmpFunc(const void *num1, const void *num2)
{
	return (*(int *)num1 < *(int *)num2)?-1: 1;
	
}










