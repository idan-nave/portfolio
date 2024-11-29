/******************************************************************************/
/*
  Name: Idan Nave
  Project: FSA
  Reviewer: Aya
  Date: 13/09/23
  Version: 1.0

  Overview: Implementation of an FSA Manager.
*/

/******************************** Libraries  *********************************/

#include <stdio.h>              /* printf */
#include <stdlib.h>             /* malloc(), free() */
#include <stddef.h>             /* size_t, NULL */

#include "fsa.h"

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

static void MainTestFunc(void);

static void TestFSASuggestedSize(void);
static void TestFSAInit(void);
static void TestFSAAlloc(void);
static void TestFSAAlloc_SpecialCases(void);
static void TestFSAFree(void);
static void TestFSAFSACountFree(void);

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
	TestFSASuggestedSize();
	TestFSAInit();
	TestFSAAlloc();
	TestFSAAlloc_SpecialCases();
	TestFSAFree();
	TestFSAFSACountFree();
}

/*****************************************************************************/
/**************************** Test Functions Definitions *********************/
/*****************************************************************************/

static void TestFSASuggestedSize()
{
	size_t num_of_blocks = 4;
	size_t size_of_block = 10;
	size_t num_of_bytes_in_pool = FSASuggestedSize(size_of_block, num_of_blocks);

	REPORT(72, num_of_bytes_in_pool, "TestFSASuggestedSize()");

  	printf("TestFSASuggestedSize() tested\n");
}

static void TestFSAInit()
{
	fsa_t *fsa;
	void *pool = NULL;
	size_t num_of_blocks = 4;
	size_t size_of_block = 12;
	size_t num_of_free_blocks = 0;
	size_t num_of_bytes_in_pool = FSASuggestedSize(size_of_block, num_of_blocks);

	pool = malloc(num_of_bytes_in_pool);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}
	
	fsa = FSAInit(pool, size_of_block, num_of_bytes_in_pool);

	REPORT(pool, fsa, "TestFSAInit()");

	num_of_free_blocks = FSACountFree(fsa);
	REPORT(4, num_of_free_blocks, "TestFSAInit()");

  	free(pool);
  	pool = NULL;

  	printf("TestFSAInit() tested\n");
}

static void TestFSAAlloc()
{
	fsa_t *fsa;
	void *current_block = NULL;
	void *pool = NULL;
	size_t num_of_blocks = 4;
	size_t size_of_block = 12;
	size_t num_of_free_blocks = 0;
	size_t num_of_bytes_in_pool = FSASuggestedSize(size_of_block, num_of_blocks);

	pool = malloc(num_of_bytes_in_pool);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}
	
	fsa = FSAInit(pool, size_of_block, num_of_bytes_in_pool);
	current_block = FSAAlloc(fsa);
	REPORT((char*)fsa + 8, current_block, "TestFSAAlloc()");

	current_block = FSAAlloc(fsa);
	REPORT((char*)fsa + 8 + 16, current_block, "TestFSAAlloc()");

	num_of_free_blocks = FSACountFree(fsa);
	REPORT(2, num_of_free_blocks, "TestFSAAlloc()");

  	free(pool);
  	pool = NULL;

  	printf("TestFSAAlloc() tested\n");
}

static void TestFSAAlloc_SpecialCases()
{
	fsa_t *fsa;
	void *current_block = NULL;
	void *pool = NULL;
	size_t num_of_blocks = 4;
	size_t size_of_block = 12;
	size_t num_of_free_blocks = 0;
	size_t num_of_bytes_in_pool = FSASuggestedSize(size_of_block, num_of_blocks);

	pool = malloc(num_of_bytes_in_pool);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}
	
	fsa = FSAInit(pool, size_of_block, num_of_bytes_in_pool);
	/*printf("%ld\n", fsa);*/
	current_block = FSAAlloc(fsa);
	/*printf("%ld\n", current_block);*/
	current_block = FSAAlloc(fsa);
	/*printf("%ld\n", current_block);*/
	current_block = FSAAlloc(fsa);
	/*printf("%ld\n", current_block);*/
	current_block = FSAAlloc(fsa);
	/*printf("%ld\n", current_block);*/

	num_of_free_blocks = FSACountFree(fsa);
	REPORT(0, num_of_free_blocks, "TestFSAAlloc_SpecialCases() - countfree");

	current_block = FSAAlloc(fsa);
	/*printf("%x\n", *(char*)current_block);*/
	REPORT(NULL, current_block, "TestFSAAlloc_SpecialCases() - extra alloc");

  	free(pool);
  	pool = NULL;

  	printf("TestFSAAlloc_SpecialCases() tested\n");
}

static void TestFSAFree()
{
	fsa_t *fsa;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *pool = NULL;
	size_t num_of_blocks = 4;
	size_t size_of_block = 12;
	size_t num_of_free_blocks = 0;
	size_t num_of_bytes_in_pool = FSASuggestedSize(size_of_block, num_of_blocks);

	pool = malloc(num_of_bytes_in_pool);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}
	
	fsa = FSAInit(pool, size_of_block, num_of_bytes_in_pool);
	block1 = FSAAlloc(fsa);
	block2 = FSAAlloc(fsa);
	block3 = FSAAlloc(fsa);


	FSAFree(fsa, block1);

	num_of_free_blocks = FSACountFree(fsa);
	REPORT(2, num_of_free_blocks, "TestFSAFree()");

	block1 = FSAAlloc(fsa);
	REPORT((char*)fsa + 8 , block1, "TestFSAAlloc()");
	
  	free(pool);
  	pool = NULL;

  	printf("TestFSAFree() tested\n");
}

static void TestFSAFSACountFree()
{
	fsa_t *fsa;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *pool = NULL;
	size_t num_of_blocks = 4;
	size_t size_of_block = 12;
	size_t num_of_free_blocks = 0;
	size_t num_of_bytes_in_pool = FSASuggestedSize(size_of_block, num_of_blocks);

	pool = malloc(num_of_bytes_in_pool);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}
	
	fsa = FSAInit(pool, size_of_block, num_of_bytes_in_pool);
	num_of_free_blocks = FSACountFree(fsa);
	REPORT(4, num_of_free_blocks, "TestFSAFSACountFree()");

	block1 = FSAAlloc(fsa);
	num_of_free_blocks = FSACountFree(fsa);
	REPORT(3, num_of_free_blocks, "TestFSAFSACountFree()");
	block2 = FSAAlloc(fsa);
	num_of_free_blocks = FSACountFree(fsa);
	REPORT(2, num_of_free_blocks, "TestFSAFSACountFree()");
	block3 = FSAAlloc(fsa);
	num_of_free_blocks = FSACountFree(fsa);
	REPORT(1, num_of_free_blocks, "TestFSAFSACountFree()");


	FSAFree(fsa, block2);
	num_of_free_blocks = FSACountFree(fsa);
	REPORT(2, num_of_free_blocks, "TestFSAFSACountFree()");
	
  	free(pool);
  	pool = NULL;

  	printf("TestFSAFSACountFree() tested\n");
}