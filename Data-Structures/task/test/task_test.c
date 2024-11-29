/******************************************************************************/
/*
  Name: Idan Nave
  Project: Task
  Reviewer: Ahmad
  Date: 09/09/23
  Version: 1.0

  Overview: Implementation of an Task Tester.
*/

/******************************** Libraries  *********************************/
#include <assert.h>             /* assert() */
#include <stdio.h>              /* printf */
#include <stdlib.h>             /* malloc(), free() */
#include <stddef.h>             /* size_t, NULL */
#include <time.h>               /*time_t*/

#include "task.h"
/*typedef enum {FALSE = 0, TRUE} task_boolean_t;
typedef enum  {SUCCESS = 0, FAILURE} task_status_t;*/


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
/************************** Helper Functions Declerations ********************/
/*****************************************************************************/
    
static int Compare(const void *data1, const void *data2);
static int Match(const void* data, void* param);
static void CleanUp(void* param);
static int UnschedOp(void* param);
static int ReschedOp(void* param);
static time_t GiveAbsFutureTime(double sec_from_now);

/*****************************************************************************/
/**************************** Test Functions Declerations ********************/
/*****************************************************************************/

static void MainTestFunc(void);

static void TestTaskCreate(void);
static void TestTaskDestroy(void);
static void TestTaskExecute(void);
static void TestTaskGetTimeToExecute(void);
static void TestTaskGetUID(void);
static void TestTaskUpdateTimeToExecute(void);
static void TestTaskIsMatch(void);
static void TestTaskCompare(void);

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
	TestTaskCreate();
	TestTaskDestroy();
	TestTaskExecute();
	TestTaskGetTimeToExecute();
	TestTaskGetUID();
	TestTaskUpdateTimeToExecute();
	TestTaskIsMatch();
	TestTaskCompare();
}

/*****************************************************************************/
/**************************** Test Functions Definitions *********************/
/*****************************************************************************/

static void TestTaskCreate(void)
{
	int data = 100;
	time_t t1 = GiveAbsFutureTime(100);
	time_t t2 = GiveAbsFutureTime(200);

	int* alloc_var = (int*)malloc(sizeof(int));

	task_t *task = TaskCreate(t1, ReschedOp, NULL, NULL, NULL);
	task_t *task2 = TaskCreate(t2, UnschedOp, &data, CleanUp, (void*)alloc_var);
	REPORT(FALSE, TaskIsMatch(task, TaskGetUID(task2)), "TestTaskCreate()");

	printf("TestTaskCreate() tested\n");
	TaskDestroy(task);
	TaskDestroy(task2);
}

static void TestTaskDestroy(void)
{
	int data = 100;
	time_t t1 = GiveAbsFutureTime(100);
	task_t *task = TaskCreate(t1, UnschedOp, &data, CleanUp, NULL);

/*	TaskExecute(task);
*/	printf("TestTaskDestroy() tested\n");
	TaskDestroy(task);

}

static void TestTaskExecute(void)
{
	  int res = 100;
		int data = 100;
		int* add_date = &data;
		time_t t1 = GiveAbsFutureTime(100);
/*	  int res_struct = {0};
*/
		task_t *task = TaskCreate(t1, UnschedOp, add_date, NULL, NULL);
		res = TaskExecute(task);
		REPORT(FALSE, res, "TestTaskExecute()");
/*		REPORT(FALSE, res_struct.sched, "TestTaskCreate()");
*/		printf("TestTaskExecute() tested\n");
		TaskDestroy(task);
}

static void TestTaskGetTimeToExecute(void)
{
	time_t t1 = GiveAbsFutureTime(100);
	task_t *task = TaskCreate(t1, UnschedOp, NULL, CleanUp, NULL);
	REPORT(TaskGetTimeToExecute(task), t1, "TestTaskGetTimeToExecute()");

	printf("TestTaskGetTimeToExecute() tested\n");
	TaskDestroy(task);
}

static void TestTaskGetUID(void)
{
	time_t t1 = GiveAbsFutureTime(100);
	task_t *task = TaskCreate(t1, UnschedOp, NULL, CleanUp, NULL);
	task_t *task2 = TaskCreate(t1, UnschedOp, NULL, CleanUp, NULL);
	
	REPORT(TRUE, TaskIsMatch(task, TaskGetUID(task)), "TestTaskGetUID()");
	REPORT(FALSE, TaskIsMatch(task, TaskGetUID(task2)), "TestTaskGetUID()");

	printf("TestTaskGetUID() tested\n");
	TaskDestroy(task);
	TaskDestroy(task2);
}

static void TestTaskUpdateTimeToExecute(void)
{
	time_t t1 = GiveAbsFutureTime(100);
	time_t res_t = time(NULL);

	task_t *task = TaskCreate(t1, UnschedOp, NULL, CleanUp, NULL);
	res_t = (time_t)TaskUpdateTimeToExecute(task);

	REPORT(TaskGetTimeToExecute(task), t1+100, "TestTaskUpdateTimeToExecute()");

	printf("TestTaskUpdateTimeToExecute() tested\n");
	TaskDestroy(task);
}

static void TestTaskIsMatch(void)
{
	time_t t1 = GiveAbsFutureTime(100);
	task_t *task = TaskCreate(t1, UnschedOp, NULL, CleanUp, NULL);
	task_t *task2 = TaskCreate(t1, UnschedOp, NULL, CleanUp, NULL);
	
	REPORT(TRUE, TaskIsMatch(task, TaskGetUID(task)), "TestTaskIsMatch()");
	REPORT(FALSE, TaskIsMatch(task, TaskGetUID(task2)), "TestTaskIsMatch()");

	printf("TestTaskIsMatch() tested\n");
	TaskDestroy(task);
	TaskDestroy(task2);
}

static void TestTaskCompare(void)
{
	time_t t1 = GiveAbsFutureTime(100);
	time_t t2 = GiveAbsFutureTime(200);
	task_t *task = TaskCreate(t2, UnschedOp, NULL, CleanUp, NULL);
	task_t *task2 = TaskCreate(t1, UnschedOp, NULL, CleanUp, NULL);

  	REPORT(0, TaskCompare(task, task), "TestTaskCompare()");
  	REPORT(100, TaskCompare(task, task2), "TestTaskCompare()");

	printf("TestTaskCompare() tested\n");
	TaskDestroy(task);
	TaskDestroy(task2);
}

/*****************************************************************************/
/******************************* Tester Helper Functions  ********************/
/*****************************************************************************/

/* Function to match data & param */
static int Match(const void* data, void* param)
{
    return *((int*)data) == *((int*)param);
}

/* Function to compare data & param */
static int Compare(const void *data1, const void *data2)
{
	return (*((int*)data1) - *((int*)data2));
}

static void CleanUp(void* param)
{
		free(param);
		param = NULL;
}

static int UnschedOp(void* param)
{
	  printf("\tUnschedOp Func Does Nothing\n");
		return UNSCHEDULE;
}

static int ReschedOp(void* param)
{
	  printf("\tReschedOp Func Does Nothing\n");
		return RESCHEDULE;
}

/* Function to calculate a future time */
static time_t GiveAbsFutureTime(double sec_from_now)
{
    time_t currentTime = time(NULL);
    return currentTime + sec_from_now;
}