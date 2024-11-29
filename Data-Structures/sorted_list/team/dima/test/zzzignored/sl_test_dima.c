/*Name: Dima
  Project: Work Sheet 6 - Data Structures - Circular buffer
  Reviewer: Dima
  Date: 20/08/2023
  Version: 1.0
*/
/******************************************************************************/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc()*/

#include "sl.h"

/****************************main test function********************************/
void TestProgram();

void PrintAll(dll_ty *list);
/*****************************user functions***********************************/

/*********************************** main *************************************/

int main()
{
	TestProgram();
	return 0;
}

/******************************************************************************/

void TestProgram()
{
	dll_ty *test_list = NULL;
	dll_iter_ty iter = NULL;
	
	printf("Hello\n");

	/*Create list and verify its empty*/
	test_list = DListCreate();
	printf("Is empty? %d \n",DListIsEmpty(test_list));
	/*Point iter to tail then insert abc*/
	iter = DListEnd(test_list);
	iter = DListInsertBefore(iter, "A", test_list);
	/*Test data of the new node and IsEmpty function*/
	printf("Data = %s \n",(char *)DListGetData(iter));
	printf("Is empty? %d \n",DListIsEmpty(test_list));
	/*Insert more data*/
	iter = DListInsertBefore(iter, "B", test_list);
	iter = DListInsertBefore(iter, "C", test_list);
	iter = DListInsertBefore(iter, "D", test_list);
	iter = DListInsertBefore(iter, "E", test_list);
	iter = DListInsertBefore(iter, "F", test_list);
	/*Go over each iter and print data
	  Test DListBegin(), DListEnd(), DListGetData(), DListNext()*/
	printf("\nPrint 1:\n");
	PrintAll(test_list);
	/*Go over each iter from ListEnd and print data
	  Test DListBegin(), DListEnd(), DListGetData(), DListNext()*/
	/*Test ListSize()*/
	printf("\nPrint 2:\n");
	iter = DListEnd(test_list); /*TODO: printing backwards failed*/
	while(DListEnd(test_list) != iter)
	{
		printf("Data = %s \n",(char *)DListGetData(iter));
		iter = DListPrev(iter);
	}
	printf("Number of elements: %ld\n", DListSize(test_list));
	
	/*Go to third element, then remove it and print the result
	  Test: DListRemove()*/
	iter = DListBegin(test_list);
	iter = DListNext(iter);
	iter = DListNext(iter);
	iter = DListRemove(iter);
	printf("\nPrint 3:\n");
	PrintAll(test_list);
	
}


void PrintAll(dll_ty *test_list)
{
	dll_iter_ty iter = DListBegin(test_list);
	while(DListEnd(test_list) != iter)
	{
		printf("Data = %s \n",(char *)DListGetData(iter));
		iter = DListNext(iter);
	}
}















