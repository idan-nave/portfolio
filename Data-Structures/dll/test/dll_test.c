/*
  Name: Idan Nave
  Project: Work Sheet 11 - Data Structures - Doubly Linked List
  Reviewer: ?
  Date: 22/08/23
  Version: 1.0
*/

/****************************** Libraries  **********************************/

#include <stdio.h> /*printf*/
#include "dll.h"

#define REPORT(expected, result, str) \
		{\
		    if (expected != result)\
		    {\
		    	printf("%s has failed\n", str);\
		    }\
		}

static void MainTestFunc(void);

	/* Function to match data & param */
static int Match(const void* data, void* param);
/* Function to manipulate data using param */
static int Add(void* data, void* param);

    /*Iterators Functions Tests*/
static void TestDListCreate(void);
static void TestDListSize(void);
static void TestDListIsEmpty(void);
static void TestDListGetData(void);
static void TestDListIsSameIter(void);

    /*Dlist Manipulating Tests*/
static void TestDListSetData(void);
static void TestDListInsertBefore(void);
static void TestDListRemove(void);
static void TestDListPushFront(void);
static void TestDListPushBack(void);
static void TestDListPopFront(void);
static void TestDListPopBack(void);
static void TestDListPrev(void);
static void TestDListNext(void);
static void TestDListEnd(void);
static void TestDListBegin(void);

    /*Dlist Traversing Tests*/
static void TestDListSplice(void);
static void TestDListFind(void);
static void TestDListForEach(void);
static void TestDListMultiFind(void);

/*****************************************************************************/
/*************************************** Main ********************************/
/*****************************************************************************/

int main()
{
	MainTestFunc();
	return 0;
}

static void MainTestFunc(void)
{  
    /*Dlist Allocating Tests*/
	TestDListCreate();

    /*Iterators Functions Tests*/
	TestDListSize();
	TestDListIsEmpty();
	TestDListIsSameIter();
	TestDListPrev();
	TestDListNext();
	TestDListEnd();
	TestDListBegin();
	TestDListGetData();

    /*Dlist Manipulating Tests*/	
	TestDListInsertBefore();
	TestDListSetData();
	TestDListRemove();
	TestDListPushFront();
	TestDListPushBack();
	TestDListPopFront();
	TestDListPopBack();

    /*Dlist Traversing Tests*/
	TestDListSplice();
	TestDListFind();
	TestDListForEach();
	TestDListMultiFind();
}

/*****************************************************************************/
/**************************** Test Functions Definitions *********************/
/*****************************************************************************/

static void TestDListCreate(void)
{
	dll_t *list = DListCreate();
	REPORT(1, DListIsEmpty(list), "TestDListCreate()");
	REPORT(0, DListSize(list), "TestDListCreate()");

	printf("TestDListCreate() tested\n");
	
	DListDestroy(list);
}

static void TestDListSize(void)
{
	dll_t *list = DListCreate();
	int x1 = 1;
	int x2 = 2;
	
	dll_iter_t my_itr2;
	REPORT(1, DListIsEmpty(list), "TestDListSize()");
	REPORT(0, DListSize(list), "TestDListSize()");
	
	my_itr2 = DListInsertBefore(DListBegin(list), &x1, list);
	DListInsertBefore(DListBegin(list), &x2, list);
	
	REPORT(2, DListSize(list), "TestDListSize()");
	
	DListRemove(my_itr2);
	
	REPORT(1, DListSize(list), "TestDListSize()");
	
	printf("TestDListCreate() tested\n");
	
	DListDestroy(list);
}

static void TestDListIsEmpty(void)
{
	dll_t *list = DListCreate();
	int x1 = 1;
	int x2 = 2;
	dll_iter_t my_itr1;
	dll_iter_t my_itr2;
	REPORT(1, DListIsEmpty(list), "TestDListIsEmpty()");
	REPORT(0, DListSize(list), "TestDListIsEmpty()");
	
	my_itr2 = DListInsertBefore(DListBegin(list), &x1, list);
	my_itr1 = DListInsertBefore(DListBegin(list), &x2, list);
	
	REPORT(0, DListIsEmpty(list), "TestDListIsEmpty()");
	
	DListRemove(my_itr2);
	
	REPORT(0, DListIsEmpty(list), "TestDListIsEmpty()");
	
	DListRemove(my_itr1);
	
	REPORT(1, DListIsEmpty(list), "TestDListIsEmpty()");

	printf("TestDListIsEmpty() tested\n");
	
	DListDestroy(list);
}

static void TestDListGetData(void)
{
	dll_t *list = DListCreate();
	int x1 = 1;
	int x2 = 2;
	dll_iter_t my_itr1;
	dll_iter_t my_itr2;
	
	my_itr2 = DListInsertBefore(DListBegin(list), &x1, list);
	my_itr1 = DListInsertBefore(DListBegin(list), &x2, list);
	
	REPORT(x1, *((int*)DListGetData(my_itr2)), "TestDListGetData()");
	
	REPORT(x2, *((int*)DListGetData(my_itr1)), "TestDListGetData()");
	
	REPORT(x2, *((int*)DListGetData(DListBegin(list))), "TestDListGetData()");

	printf("TestDListGetData() tested\n");
	
	DListDestroy(list);
}

static void TestDListSetData(void)
{
	dll_t *list = DListCreate();
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	dll_iter_t my_itr1;
	dll_iter_t my_itr2;
	
	my_itr2 = DListInsertBefore(DListBegin(list), &x1, list);
	my_itr1 = DListInsertBefore(DListBegin(list), &x2, list);
	
	DListSetData(my_itr2, &x3);
	DListSetData(my_itr1, &x4);
	
	REPORT(x3, *((int*)DListGetData(my_itr2)), "TestDListGetData()");
	
	REPORT(x4, *((int*)DListGetData(my_itr1)), "TestDListGetData()");
	
	REPORT(x4, *((int*)DListGetData(DListBegin(list))), "TestDListGetData()");

	printf("TestDListSetData() tested\n");
	
	DListDestroy(list);
}

static void TestDListInsertBefore(void)
{
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	int x6 = 6;
	int x7 = 7;
	dll_iter_t my_itr1;
	dll_iter_t my_itr2;
	dll_iter_t my_itr3;
	dll_iter_t my_itr4;
	dll_iter_t my_itr5;
	dll_iter_t my_itr;
	
	dll_t *list = DListCreate();
	
	my_itr = DListInsertBefore(DListBegin(list), &x1, list);
	my_itr1 = DListInsertBefore(my_itr, &x2, list);
	my_itr2 = DListInsertBefore(my_itr1, &x3, list);
	my_itr3 = DListInsertBefore(my_itr2, &x4, list);
	my_itr4 = DListInsertBefore(my_itr3, &x5, list);
	my_itr5 = DListInsertBefore(my_itr4, &x6, list);
	DListInsertBefore(my_itr5, &x7, list);
	
	REPORT(7, DListSize(list), "TestInsertBefore()");
	REPORT(0, DListIsEmpty(list), "TestInsertBefore()");
	
	printf("TestInsertBefore() tested\n");
	
	DListDestroy(list);
}

static void TestDListRemove(void)
{
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	int x6 = 6;
	int x7 = 7;
	size_t i = 0;
	size_t size = 0;
	dll_iter_t my_itr1;
	dll_iter_t my_itr2;
	dll_iter_t my_itr3;
	dll_iter_t my_itr4;
	dll_iter_t my_itr5;
	dll_iter_t my_itr;
	
	dll_t *list = DListCreate();
	
	my_itr = DListInsertBefore(DListBegin(list), &x1, list);
	my_itr1 = DListInsertBefore(my_itr, &x2, list);
	my_itr2 = DListInsertBefore(my_itr1, &x3, list);
	my_itr3 = DListInsertBefore(my_itr2, &x4, list);
	my_itr4 = DListInsertBefore(my_itr3, &x5, list);
	my_itr5 = DListInsertBefore(my_itr4, &x6, list);
	
	DListInsertBefore(my_itr5, &x7, list);
	
	size = DListSize(list);
	
	while (i < size)
	{
		REPORT((size - i), DListSize(list), "TestDListRemove()");
		DListRemove(DListBegin(list));
		++i;
	}
	
	printf("TestDListRemove() tested\n");
	
	DListDestroy(list);
}

static void TestDListPushFront(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_t *list = DListCreate();
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		REPORT(*((int*)DListGetData(DListBegin(list))), 
		*((int*)DListGetData(my_itr)), "TestDListPushFront()");
		++i;
	}
	
	printf("TestDListPushFront() tested\n");
	
	DListDestroy(list);
}

static void TestDListPushBack(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_t *list = DListCreate();
	
	while (i < size)
	{
		my_itr = DListPushBack(list, &(arr[i]));
		REPORT(*((int*)DListGetData(DListPrev(DListEnd(list)))), 
		*((int*)DListGetData(my_itr)), "TestDListPushBack()");
		++i;
	}
	
	printf("TestDListPushBack() tested\n");
	
	DListDestroy(list);
}

static void TestDListPopFront(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_t *list = DListCreate();
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	
	while (i < size)
	{
		int res = *((int*)DListGetData(DListBegin(list)));
		REPORT(res, *((int*)DListGetData(my_itr)), "TestDListPopFront()");
		my_itr = DListPopFront(list);
		++i;
	}
	
	printf("TestDListPopFront() tested\n");
	
	DListDestroy(list);
}

static void TestDListPopBack(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_t *list = DListCreate();
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = DListPrev(DListEnd(list));
	
	while (i < size)
	{
		int res = *((int*)DListGetData(DListPrev(DListEnd(list))));
		REPORT(res, *((int*)DListGetData(my_itr)), "TestDListPopBack()");
		my_itr = DListPopBack(list);
		++i;
	}
	
	printf("TestDListPopBack() tested\n");
	
	DListDestroy(list);
}

static void TestDListEnd(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_t *list = DListCreate();
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = DListPrev(DListEnd(list));
	
	while (i < size)
	{
		int res = *((int*)DListGetData(DListPrev(DListEnd(list))));
		REPORT(res, *((int*)DListGetData(my_itr)), "TestDListEnd()");
		my_itr = DListPopBack(list);
		++i;
	}
	
	printf("TestDListEnd() tested\n");
	
	DListDestroy(list);
}

static void TestDListBegin(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_t *list = DListCreate();
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = DListBegin(list);
	
	while (i < size)
	{
		int res = *((int*)DListGetData(DListBegin(list)));
		REPORT(res, *((int*)DListGetData(my_itr)), "TestDListBegin()");
		my_itr = DListPopFront(list);
		++i;
	}
	
	printf("TestDListBegin() tested\n");
	
	DListDestroy(list);
}

static void TestDListPrev(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_t *list = DListCreate();
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = DListPrev(DListEnd(list));
	
	while (i < size)
	{
		int res = *((int*)DListGetData(DListPrev(DListEnd(list))));
		REPORT(res, *((int*)DListGetData(my_itr)), "TestDListPrev()");
		my_itr = DListPopBack(list);
		++i;
	}
	
	printf("TestDListPrev() tested\n");
	
	DListDestroy(list);
}

static void TestDListNext(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_t *list = DListCreate();
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = DListBegin(list);
	
	while (i < size)
	{
		REPORT(arr[size-i-1], *((int*)DListGetData(my_itr)),
		 "TestDListPrev()");
		my_itr = DListNext(my_itr);
		++i;
	}
	
	printf("TestDListNext() tested\n");
	
	DListDestroy(list);
}

static void TestDListIsSameIter(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_iter_t my_itr2;
	dll_t *list = DListCreate();
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = DListBegin(list);
	my_itr2 =  DListPrev(DListEnd(list));
	
	while (i < size)
	{
		if(i == (size - 1) && FALSE == DListIsSameIter(my_itr2, my_itr))
		{
			printf("there was a problem with TestDListIsSameIter()\n");
		}
		
		if(i != (size - 1) && TRUE == DListIsSameIter(my_itr2, my_itr))
		{
			printf("there was a problem with TestDListIsSameIter()\n");
		}
		
		my_itr = DListNext(my_itr);
		++i;
	}
	
	printf("TestDListIsSameIter() tested\n");
	
	DListDestroy(list);
}

static void TestDListSplice(void)
{
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	int x6 = 6;
	int x7 = 7;
	dll_iter_t my_itr1;
	dll_iter_t my_itr2;
	dll_iter_t my_itr3;
	dll_iter_t my_itr4;
	dll_iter_t my_itr5;
	dll_iter_t my_itr;
	dll_t *list = DListCreate();
	my_itr = DListInsertBefore(DListBegin(list), &x1, list);
	my_itr1 = DListInsertBefore(my_itr, &x2, list);
	my_itr2 = DListInsertBefore(my_itr1, &x3, list);
	my_itr3 = DListInsertBefore(my_itr2, &x4, list);
	my_itr4 = DListInsertBefore(my_itr3, &x5, list);
	my_itr5 = DListInsertBefore(my_itr4, &x6, list);
	DListInsertBefore(my_itr5, &x7, list);
	
	DListSplice(DListBegin(list), my_itr3, my_itr1);
	my_itr = DListBegin(list);

	REPORT(x4, *((int*)DListGetData(my_itr)), "TestDListSplice()");
	
	my_itr = DListNext(my_itr);
	
	REPORT(x3, *((int*)DListGetData(my_itr)), "TestDListSplice()");
	
	my_itr = DListNext(my_itr);
	
	REPORT(x7, *((int*)DListGetData(my_itr)), "TestDListSplice()");
	
	my_itr = DListNext(my_itr);
	
	REPORT(x6, *((int*)DListGetData(my_itr)), "TestDListSplice()");
	
	my_itr = DListNext(my_itr);
	
	REPORT(x5, *((int*)DListGetData(my_itr)), "TestDListSplice()");
	
	printf("TestDListSplice() tested\n");
	
	DListDestroy(list);
}

static void TestDListFind(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_iter_t my_itr2;
	dll_iter_t my_iter_res;
	
	dll_t *list = DListCreate();
	
	my_itr = DListBegin(list);
	my_itr2 =  DListPrev(DListEnd(list));
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	my_itr = DListBegin(list);
	my_iter_res = DListFind(my_itr, my_itr2, Match, &(arr[3]));
	
	REPORT(arr[3], *((int*)DListGetData(my_iter_res)), "TestDListFind()");
	
	my_iter_res = DListFind(my_itr, my_itr2, Match, &(arr[5]));
	
	REPORT(arr[5], *((int*)DListGetData(my_iter_res)), "TestDListFind()");
	
	printf("TestDListFind() tested\n");
	
	DListDestroy(list);
}

static void TestDListForEach(void)
{
	int arr[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	int to_add = 7;
	dll_iter_t my_itr;
	dll_iter_t my_itr2;
	
	dll_t *list = DListCreate();
	
	my_itr = DListBegin(list);
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	
	my_itr = DListBegin(list);
	my_itr2 =  DListPrev(DListEnd(list));
	
	DListForEach(my_itr, my_itr2, Add, &to_add);
	
	i = 0;
	my_itr = DListBegin(list);
	while (i < size)
	{
		REPORT(*((int*)DListGetData(my_itr)), arr[size - i - 1],
		 "TestDListForEach()");
		my_itr = DListNext(my_itr);
		++i;
	}
	
	printf("TestDListForEach() tested\n");
	
	DListDestroy(list);
}

static void TestDListMultiFind(void)
{
	int arr[7] = {7,2,3,7,5,6,7};
	size_t i = 0;
	size_t size = 7;
	dll_iter_t my_itr;
	dll_iter_t my_itr2;
	
	dll_t *list = DListCreate();
	dll_t *list_res = DListCreate();
	
	my_itr = DListBegin(list);
	
	while (i < size)
	{
		my_itr = DListPushFront(list, &(arr[i]));
		++i;
	}
	
	my_itr = DListBegin(list);
	my_itr2 =  DListEnd(list);
	
	DListMultiFind(my_itr, my_itr2, Match, &(arr[0]), list_res);
	
	REPORT(3, DListSize(list_res), "TestDListMultiFind()");
	
	printf("TestDListMultiFind() tested\n");
	
	DListDestroy(list);
	DListDestroy(list_res);
}

/*****************************************************************************/
/******************************* Tester Helper Functions  ********************/
/*****************************************************************************/

/* Function to match data & param */
static int Match(const void* data, void* param)
{
    return *((int*)data) == *((int*)param);
}

/* Function to manipulate data using param */
static int Add(void* data, void* param)
{
    *((int*)data) += *((int*)param);
    return SUCCESS;
}