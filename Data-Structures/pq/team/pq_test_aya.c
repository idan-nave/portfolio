/******************************************************************************/
/*
  Name: Aya
  Project: Work Sheet 12 - Data Structures - pq
  Reviewer: 
  Date: 06/09/23
  Version: 1.0
  
  Overview: Implementation of a Priority Queue.
*/
/******************************** Libraries  **********************************/
#include <stdlib.h> /*malloc*/
#include <stdio.h>  /*printf*/

#include "sorted_list.h"
#include "pq.h"

/*****************************************************************************/
/********************************* Type Definitions **************************/
/*****************************************************************************/
    
#define REPORT(expected, result, str) \
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
static int Add(void* data, void* param);

/******************************************************************************/

static void MainTestFunc(void);

static void TestPQCreate(void);
static void TestPQSize(void);
static void TestPQIsEmpty(void);
static void TestPQPeak(void);
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
  TestPQPeak();
  TestPQEnqueue();
  TestPQDequeue();
  TestPQClear();
  TestPQErase();
}

/*****************************************************************************/
/**************************** Test Functions Definitions *********************/
/*****************************************************************************/

static void TestPQCreate()
{
  pq_t *pqueue = PQCreate(Compare);
  REPORT(1, PQIsEmpty(pqueue), "TestPQCreate()");
  REPORT(0, PQSize(pqueue), "TestPQCreate()");

  printf("TestPQCreate() tested\n");
  
  PQDestroy(pqueue);
}

static void TestPQSize()
{
  pq_t *pqueue = PQCreate(Compare);
  int x1 = 1;
  int x2 = 2;
  
  REPORT(1, PQIsEmpty(pqueue), "TestPQSize()");
  REPORT(0, PQSize(pqueue), "TestPQSize()");
  
  PQEnqueue(pqueue, &x1);
  PQEnqueue(pqueue, &x2);
  
  REPORT(2, PQSize(pqueue), "TestPQSize()");
  
  PQDequeue(pqueue);
  
  REPORT(1, PQSize(pqueue), "TestPQSize()");
  
  printf("TestPQSize() tested\n");
  
  PQDestroy(pqueue);
}

static void TestPQIsEmpty()
{
  pq_t *pqueue = PQCreate(Compare);
  int x1 = 1;
  int x2 = 2;
  
  REPORT(1, PQIsEmpty(pqueue), "TestPQIsEmpty()");
  REPORT(0, PQSize(pqueue), "TestPQIsEmpty()");
  
  PQEnqueue(pqueue, &x1);
  PQEnqueue(pqueue, &x2);
  
  REPORT(0, PQIsEmpty(pqueue), "TestPQIsEmpty()");
  
  PQDequeue(pqueue);
  
  REPORT(0, PQIsEmpty(pqueue), "TestPQIsEmpty()");
  
  PQDequeue(pqueue);
  
  REPORT(1, PQIsEmpty(pqueue), "TestPQIsEmpty()");

  printf("TestPQIsEmpty() tested\n");
  
  PQDestroy(pqueue);
}

static void TestPQPeak()
{
  pq_t *pqueue = PQCreate(Compare);
  int x1 = 1;
  int x2 = 2;
  int x3 = 3;

  PQEnqueue(pqueue, &x3);
  PQEnqueue(pqueue, &x1);
  PQEnqueue(pqueue, &x2);
  
  REPORT(x1, *((int*)PQPeak(pqueue)), "TestPQPeak()");

  PQDequeue(pqueue);
  
  REPORT(x2, *((int*)PQPeak(pqueue)), "TestPQPeak()");

  PQDequeue(pqueue);
  
  REPORT(x3, *((int*)PQPeak(pqueue)), "TestPQPeak()");
  
  printf("TestPQPeak() tested\n");
  
  PQDestroy(pqueue);
}

static void TestPQEnqueue()
{
  int arr[7] = {7,1,5,3,2,4,6};
  int arr_res[7] = {1,2,3,4,5,6,7};
  size_t i = 0;
  size_t size = 7;
  pq_t *pqueue = PQCreate(Compare);
  
  while (i < size)
  {
    PQEnqueue(pqueue, &(arr[i]));
    ++i;
  }

  i = 0;
  
  while (i < size)
  {
    REPORT(arr_res[i], *((int*)PQPeak(pqueue)), "TestPQEnqueue()");
    PQDequeue(pqueue);
    ++i;
  }
  
  printf("TestPQEnqueue() tested\n");
  
  PQDestroy(pqueue);
}

static void TestPQDequeue()
{
  int arr[7] = {7,1,5,3,2,4,6};
  int arr_res[7] = {1,2,3,4,5,6,7};
  size_t i = 0;
  size_t size = 7;
  pq_t *pqueue = PQCreate(Compare);
  
  while (i < size)
  {
    PQEnqueue(pqueue, &(arr[i]));      
    ++i;
  }
  
  i = 0;
  
  while (i < size)
  {
    REPORT(arr_res[i], *((int*)PQPeak(pqueue)), "TestPQDequeue()");
    PQDequeue(pqueue);
    ++i;
  }
  
  printf("TestPQDequeue() tested\n");
  
  PQDestroy(pqueue);
}

static void TestPQClear()
{
  pq_t *pqueue = PQCreate(Compare);
  int x1 = 1;
  int x2 = 2;
  int x3 = 3;

  PQEnqueue(pqueue, &x3);
  PQEnqueue(pqueue, &x1);
  PQEnqueue(pqueue, &x2);
  
  PQClear(pqueue);

  REPORT(1, PQIsEmpty(pqueue), "TestPQClear()");
  REPORT(0, PQSize(pqueue), "TestPQClear()");
  
  printf("TestPQClear() tested\n");
  
  PQDestroy(pqueue);
}

static void TestPQErase()
{
  int arr[7] = {7,1,5,3,2,4,6};
  size_t i = 0;
  size_t size = 7;
  pq_t *pqueue = PQCreate(Compare);
  
  while (i < size)
  {
    PQEnqueue(pqueue, &(arr[i]));      
    ++i;
  }
  
  i = 0;
  
  while (i < size)
  {
      REPORT((size - i), PQSize(pqueue), "TestPQErase()");
      PQDequeue(pqueue);
      ++i;
  }
  
  printf("TestPQErase() tested\n");
  
  PQDestroy(pqueue);

}

/*****************************************************************************/
/******************************* Tester Helper Functions  ********************/
/*****************************************************************************/

/* Function to manipulate data using param */
static int Add(void* data, void* param)
{
    if(NULL == data || NULL == param)
    {
            return FAILURE;
    }
    *((int*)data) += *((int*)param);
    return SUCCESS;
}

/* Function to match data & param */
/*
static int Match(const void* data, const void* param)
{
    return *((int*)data) == *((int*)param);
}
*/
/* Function to compare data & param */
static int Compare(const void *data1, const void *data2)
{
	return (*((int*)data1) - *((int*)data2));
}
