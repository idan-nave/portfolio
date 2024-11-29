/******************************************************************************/
/*
  Name: Idan Nave
  Project: PQ
  Reviewer: ??
  Date: 06/09/23
  Version: 1.0

  Overview: Implementation of an PQ Tester.
*/

/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <stdio.h>              /* perror */
#include <stdlib.h>             /* malloc(), free() */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */

#include "pq.h"   
typedef enum {FALSE = 0, TRUE} pq_boolean_t;
typedef enum  {SUCCESS = 0, FAILURE} pq_status_t;

/*****************************************************************************/
/********************************* Type Definitions **************************/
/*****************************************************************************/
    
#define REPORT(expected	, result, str) \
	{\
	    if (expected != result)\
	    {\
	    	printf("%s has failed\n", str);\
	    }\
	}
	
/*****************************************************************************/
/**************************** Test Functions Declerations ********************/
/*****************************************************************************/
    
static int Compare(const void *data1, const void *data2);
static int Match(const void* data, const void* param);

/******************************************************************************/

static void MainTestFunc(void);

static void TestPQCreate(void);
static void TestPQSize(void);
static void TestPQIsEmpty(void);
static void TestPQPeek(void);
static void TestPQEnqueue(void);
static void TestPQDequeue(void);
static void TestPQClear(void);
static void TestPQErase(void);

/*****************************************************************************/
/*************************************** Main ********************************/
/*****************************************************************************/

int main()
{
	MainTestFunc();
	return 0;
}

/******************************************************************************/

static void MainTestFunc(void)
{
	TestPQCreate();
	TestPQSize();
	TestPQIsEmpty();
	TestPQPeek();
	TestPQEnqueue();
	TestPQDequeue();
	TestPQClear();
	TestPQErase();
}

/*****************************************************************************/
/**************************** Test Functions Definitions *********************/
/*****************************************************************************/

static void TestPQCreate(void)
{
	pq_t *pq = PQCreate(Compare);
	REPORT(TRUE, PQIsEmpty(pq), "TestPQCreate()");
	REPORT(FALSE, PQSize(pq), "TestPQCreate()");

	printf("TestPQCreate() tested\n");
	
	PQDestroy(pq);
}

static void TestPQSize(void)
{
	pq_t *pq = PQCreate(Compare);
	int x1 = 1;
	int x2 = 2;
	
	REPORT(TRUE, PQIsEmpty(pq), "TestPQSize()");
	REPORT(FALSE, PQSize(pq), "TestPQSize()");
	
	PQEnqueue(pq, &x2);	PQEnqueue(pq, &x1);
	REPORT(2, PQSize(pq), "TestPQSize()");
	
	PQDequeue(pq);
	REPORT(1, PQSize(pq), "TestPQSize()");
	
	printf("TestPQSize() tested\n");
	
	PQDestroy(pq);
}

static void TestPQIsEmpty(void)
{
	pq_t *pq = PQCreate(Compare);
	int x1 = 1;
	int x2 = 2;

	REPORT(TRUE, PQIsEmpty(pq), "TestPQIsEmpty()");
	REPORT(FALSE, PQSize(pq), "TestPQIsEmpty()");
	
	PQEnqueue(pq, &x1);
	PQEnqueue(pq, &x2);
	REPORT(FALSE, PQIsEmpty(pq), "TestPQIsEmpty()");
	
	PQDequeue(pq);
	REPORT(FALSE, PQIsEmpty(pq), "TestPQIsEmpty()");
	
	PQDequeue(pq);
	
	REPORT(TRUE, PQIsEmpty(pq), "TestPQIsEmpty()");

	printf("TestPQIsEmpty() tested\n");
	PQDestroy(pq);
}

static void TestPQPeek(void)
{
	pq_t *pq = PQCreate(Compare);
	int x1 = 1;
	int x2 = 2;
	
	PQEnqueue(pq, &x1);
	REPORT(x1, *((int*)PQPeek(pq)), "TestPQPeek()");
	
	PQEnqueue(pq, &x2);
	REPORT(x1, *((int*)PQPeek(pq)), "TestPQPeek()");
	/*stays the same*/
	printf("TestPQPeek() tested\n");
	
	PQDestroy(pq);
}

static void TestPQEnqueue(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	int arr_res[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	pq_t *pq = PQCreate(Compare);
	
	while (i < size)
	{
		PQEnqueue(pq, &(arr[i]));
		++i;
	}
	
	i = 0;
	while (i < size)
	{
		REPORT(arr_res[i], *((int*)PQPeek(pq)), "TestPQEnqueue()");
		++i;
		PQDequeue(pq);
/*		printf("%d\n", *((int*)PQPeek(pq)));*/
	}
	
	printf("TestPQEnqueue() tested\n");
	PQDestroy(pq);
}

static void TestPQDequeue(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	size_t i = 0;
	size_t size = 7;
	pq_t *pq = PQCreate(Compare);
	
	while (i < size)
	{
		PQEnqueue(pq, &(arr[i]));
		++i;
	}
	
	i = 0;
	while (i < size)
	{
		REPORT((size - i), PQSize(pq), "TestPQDequeue()");
		PQDequeue(pq);
		++i;
	}
	
	printf("TestPQDequeue() tested\n");
	PQDestroy(pq);
}

static void TestPQClear(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	size_t i = 0;
	size_t size = 7;
	int x0 = 0;
	pq_t *pq = PQCreate(Compare);
	
	while (i < size)
	{
		PQEnqueue(pq, &(arr[i]));
		++i;
/*    printf("%d\n", *((int*)PQPeek(pq)));  
*/	}
	
	PQClear(pq);

	REPORT(0, PQSize(pq), "TestPQClear()");
		
	PQEnqueue(pq, &x0);
	REPORT(x0, *((int*)PQPeek(pq)), "TestPQClear()");

	printf("TestPQClear() tested\n");
	PQDestroy(pq);
}

static void TestPQErase(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	int arr_res[7] = {6,5,4,3,2,1,0}; 
	size_t i = 0;
	size_t size = 7;
	pq_t *pq = PQCreate(Compare);
	while (i < size)
	{
		PQEnqueue(pq, &(arr[i]));
		++i;
	}

	i = 0;
	while (i < size)
	{
		PQErase(pq, Match, &arr[i]);
		REPORT((size_t)arr_res[i], PQSize(pq), "TestPQErase()");
		++i;
/*    printf("%d\n", i);  fflush(stdout);
*/	}
	printf("TestPQErase() tested\n");
	PQDestroy(pq);}

/*****************************************************************************/
/******************************* Tester Helper Functions  ********************/
/*****************************************************************************/

/* Function to match data & param */
static int Match(const void* data, const void* param)
{
    return *((int*)data) == *((int*)param);
}

/* Function to compare data & param */
static int Compare(const void *data1, const void *data2)
{
	return (*((int*)data1) - *((int*)data2));
}
