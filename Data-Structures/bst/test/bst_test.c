/*
  Name: Idan Nave (HRD32)
  Project: Binary Search Tree
  Reviewer: Aya
  Date: 30/09/2023
  Version: 1.0
*/

#include "bst.h"
#include <stdio.h>

/**********************************define**************************************/
#define ARRAY_SIZE 7

#define REPORT(expected, result, str) \
		{\
		    if (expected != result)\
		    {\
		    	printf("%s has failed\n", str);\
		    }\
		}

/************************** forward decleration *******************************/

static int Compare(const void *a, const void *b, void *params);
static int Action(void *data, void *params);

static void TestFunc();

static void TestBSTCreate(void);
static void TestBSTDestroy(void);
static void TestBSTInsert(void);
static void TestBSTRemove(void);
static void TestBSTForEach(void);
static void TestBSTGetData(void);
static void TestBSTIsEmpty(void);
static void TestBSTSize(void);
static void TestBSTFind(void);
static void TestBSTBegin(void);
static void TestBSTNext(void);
static void TestBSTPrev(void);
static void TestBSTEnd(void);
static void TestBSTIsSameIter(void);

/******************************************************************************/

int main(void)
{
    TestFunc();
    return 0;
}

/******************************************************************************/

static void TestFunc()
{
    TestBSTCreate();
    /*TestBSTDestroy();*/
    TestBSTInsert();
    /*TestBSTRemove();*/
    TestBSTGetData();
    TestBSTIsEmpty();
    TestBSTSize();
   	TestBSTFind();
    TestBSTBegin();
    TestBSTNext();
    TestBSTPrev();
    TestBSTEnd();
    TestBSTIsSameIter();
    TestBSTForEach();
}


/******************************************************************************/

static void TestBSTCreate(void)
{
	bst_ty *bst = BSTCreate(Compare, NULL);
	BSTDestroy(bst);
	printf("TestBSTCreate() tested\n");
}

/******************************************************************************/

static void TestBSTDestroy(void)
{
	bst_ty *bst = BSTCreate(Compare, NULL);
	BSTDestroy(bst);
	printf("TestBSTDestroy() tested\n");
}

/******************************************************************************/

static void TestBSTInsert(void)
{
	int arr[ARRAY_SIZE] = {7, 1, 5, 3, 2, 4, 6};
	int arr_res[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7};
	bst_ty *bst = BSTCreate(Compare, NULL);
	bst_iter_ty my_itr;
	size_t i = 0;

	while (i < ARRAY_SIZE)
	{
		my_itr = BSTInsert(bst, &(arr[i]));
		++i;
	}

	my_itr = BSTBegin(bst);
	i = 0;

	while (i < ARRAY_SIZE)
	{
		REPORT(arr_res[i], *(int*)BSTGetData(my_itr), "TestBSTInsert()");
		my_itr = BSTNext(my_itr);
		++i;
	}

	BSTDestroy(bst);
	printf("TestBSTInsert() tested\n");
}

/******************************************************************************/

static void TestBSTRemove(void)
{
    int arr[ARRAY_SIZE] = {7, 1, 5, 3, 2, 4, 6};
    int arr_res[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7};
    bst_ty *bst = BSTCreate(Compare, NULL);
    bst_iter_ty my_itr;
    size_t i = 0;

    while (i < ARRAY_SIZE)
    {
        my_itr = BSTInsert(bst, &(arr[i]));
        ++i;
    }

    i = 0;
    while (i < ARRAY_SIZE - 1)
    {
        my_itr = BSTBegin(bst);
        REPORT(arr_res[i], *((int *)BSTGetData(my_itr)), "TestBSTRemove()");
        my_itr = BSTRemove(my_itr);        
        ++i;
    }

    BSTDestroy(bst);
    printf("TestBSTRemove() tested\n");
}

/******************************************************************************/

static void TestBSTForEach(void)
{
	int arr[ARRAY_SIZE] = {7, 1, 5, 3, 2, 4, 6};
	bst_ty *bst = BSTCreate(Compare, NULL);
	bst_iter_ty my_itr;
	size_t i = 0;
	int status = 0;
	while (i < ARRAY_SIZE)
	{
		my_itr = BSTInsert(bst, &(arr[i]));
		++i;
	}

	my_itr = BSTBegin(bst);
	status = BSTForEach(my_itr, BSTEnd(bst), Action, NULL);
	REPORT(SUCCESS, status, "TestBSTForEach()");

	BSTDestroy(bst);
	printf("TestBSTForEach() tested\n");
}

/******************************************************************************/

static void TestBSTGetData(void)
{
    int arr[1] = {42};
    bst_ty *bst = BSTCreate(Compare, NULL);
    bst_iter_ty my_itr = BSTInsert(bst, &arr[0]);
    REPORT((BSTGetData(my_itr) == &arr[0]), 1, "TestBSTGetData");
    BSTDestroy(bst);
    printf("TestBSTGetData() tested\n");
}

/******************************************************************************/

static void TestBSTIsEmpty(void)
{
    bst_ty *bst = BSTCreate(Compare, NULL);
    REPORT(BSTIsEmpty(bst), 1, "TestBSTIsEmpty");
    BSTDestroy(bst);
    printf("TestBSTIsEmpty() tested\n");
}

/******************************************************************************/

static void TestBSTSize(void)
{
    int arr[3] = {1, 2, 3};
    bst_ty *bst = BSTCreate(Compare, NULL);
    size_t i;
    for (i = 0; i < 3; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }
    REPORT(BSTSize(bst), 3, "TestBSTSize");
    BSTDestroy(bst);
    printf("TestBSTSize() tested\n");
}

/******************************************************************************/

static void TestBSTFind(void)
{
    int arr[1] = {42};
    bst_ty *bst = BSTCreate(Compare, NULL);
    bst_iter_ty my_itr = BSTInsert(bst, &arr[0]);
    bst_iter_ty found_itr = BSTFind(bst, &arr[0]);
    REPORT(BSTIsSameIter(my_itr, found_itr), 1, "TestBSTFind");
    BSTDestroy(bst);
    printf("TestBSTFind() tested\n");
}

/******************************************************************************/

static void TestBSTBegin(void)
{
    int arr[1] = {42};
    bst_ty *bst = BSTCreate(Compare, NULL);
    bst_iter_ty my_itr = BSTInsert(bst, &arr[0]);
    bst_iter_ty begin_itr = BSTBegin(bst);
    REPORT(BSTIsSameIter(my_itr, begin_itr), 1, "TestBSTBegin");
    BSTDestroy(bst);
    printf("TestBSTBegin() tested\n");
}

/******************************************************************************/

static void TestBSTNext(void)
{
    int arr[2] = {1, 2};
    bst_ty *bst = BSTCreate(Compare, NULL);
    bst_iter_ty first_itr = BSTInsert(bst, &arr[0]);
    bst_iter_ty second_itr = BSTInsert(bst, &arr[1]);
    bst_iter_ty next_itr = BSTNext(first_itr);
    REPORT(BSTIsSameIter(next_itr, second_itr), 1, "TestBSTNext");
    BSTDestroy(bst);
    printf("TestBSTNext() tested\n");
}

/******************************************************************************/

static void TestBSTPrev(void)
{
    int arr[2] = {1, 2};
    bst_ty *bst = BSTCreate(Compare, NULL);
    bst_iter_ty first_itr = BSTInsert(bst, &arr[0]);
    bst_iter_ty second_itr = BSTInsert(bst, &arr[1]);
    bst_iter_ty prev_itr = BSTPrev(second_itr);
    REPORT(BSTIsSameIter(prev_itr, first_itr), 1, "TestBSTPrev");
    BSTDestroy(bst);
    printf("TestBSTPrev() tested\n");
}

/******************************************************************************/

static void TestBSTEnd(void)
{
    bst_ty *bst = BSTCreate(Compare, NULL);
    bst_iter_ty end_itr = BSTEnd(bst);
    REPORT((end_itr == NULL), 1, "TestBSTEnd");
    BSTDestroy(bst);
    printf("TestBSTEnd() tested\n");
}

/******************************************************************************/

static void TestBSTIsSameIter(void)
{
    int arr[1] = {42};
    bst_ty *bst = BSTCreate(Compare, NULL);
    bst_iter_ty my_itr = BSTInsert(bst, &arr[0]);
    bst_iter_ty same_itr = BSTFind(bst, &arr[0]);
    REPORT(BSTIsSameIter(my_itr, same_itr), 1, "TestBSTIsSameIter");
    BSTDestroy(bst);
    printf("TestBSTIsSameIter() tested\n");
}

/*****************************************************************************/
/******************************* Tester Helper Functions  ********************/
/*****************************************************************************/

/******************************************************************************/

static int Compare(const void *a, const void *b, void *params)
{
	(void)params;
	return (*(int *)a - *(int *)b);
}

/******************************************************************************/

static int Action(void *data, void *params)
{
	(void)params;
	(void)data;
	return SUCCESS;
}