/******************************************************************************/
/*
  Name: Idan Nave
  Project: VSA
  Reviewer: Dima
  Date: 17/09/23
  Version: 1.0

  Overview: Implementation of an VSA Manager.
*/

/******************************** Libraries  *********************************/

#include <stdio.h>              /* printf */
#include <stdlib.h>             /* malloc(), free() */
#include <stddef.h>             /* size_t, NULL */

#include "vsa.h"

/*****************************************************************************/
/********************************* Type Definitions **************************/
/*****************************************************************************/
#define HDR_SIZE sizeof(size_t)

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

static void TestVSALargestChunkAvailable(void);
static void TestVSAInit(void);
static void TestVSAAlloc(void);
static void TestVSAFree(void);
static void TestVSAAlloc_SpecialCases(void);

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
	TestVSAInit();
	TestVSALargestChunkAvailable();
	TestVSAAlloc();
	TestVSAFree();
	TestVSAAlloc_SpecialCases();
}

/*****************************************************************************/
/**************************** Test Functions Definitions *********************/
/*****************************************************************************/

static void TestVSALargestChunkAvailable()
{
	vsa_t *vsa = NULL;
	void *pool = NULL;
	size_t pool_size = 102;

	pool = malloc(pool_size);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}

	vsa = VSAInit(pool, pool_size);
	REPORT(64, VSALargestChunkAvailable(vsa), "TestVSALargestChunkAvailable()");

	free(pool);
	pool = NULL;

  printf("TestVSALargestChunkAvailable() tested\n");
}

static void TestVSAInit()
{
	vsa_t *vsa = NULL;
	void *pool = NULL;
	size_t pool_size = 102;

	pool = malloc(pool_size);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}

	vsa = VSAInit(pool, pool_size);

	free(pool);
	pool = NULL;

	printf("TestVSAInit() tested\n");
}

static void TestVSAAlloc()
{
	vsa_t *vsa = NULL;
	void *chunk1 = NULL;
	void *chunk2 = NULL;
	void *chunk3 = NULL;
	void *pool = NULL;
	size_t pool_size = 102;

	pool = malloc(pool_size);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}
	
	vsa = VSAInit(pool, pool_size);
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

	chunk1 = VSAAlloc(vsa, 16);
	if ( NULL == chunk1 )
	{
		printf("\nmalloc request with 16B failed.\n");
	}	
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

	chunk2 = VSAAlloc(vsa, 24);
	if ( NULL == chunk2 )
	{
		printf("\nmalloc request with 24B failed.\n");
	}	
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

	chunk3 = VSAAlloc(vsa, 24);
	if ( NULL == chunk3 )
	{
		printf("\nmalloc request with 24B failed.\n");
	}	


	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

  	free(pool);
  	pool = NULL;

  	printf("TestVSAAlloc() tested\n");
}

static void TestVSAFree()
{
	vsa_t *vsa = NULL;
	void *chunk1 = NULL;
	void *chunk2 = NULL;
	void *chunk3 = NULL;
	void *pool = NULL;
	size_t pool_size = 160;

	pool = malloc(pool_size);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}
	
	vsa = VSAInit(pool, pool_size);
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

	chunk1 = VSAAlloc(vsa, 16);
	if ( NULL == chunk1 )
	{
		printf("\nmalloc request with 16B failed.\n");
	}	
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

	chunk2 = VSAAlloc(vsa, 24);
	if ( NULL == chunk2 )
	{
		printf("\nmalloc request with 24B failed.\n");
	}	
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

	chunk3 = VSAAlloc(vsa, 24);
	if ( NULL == chunk3 )
	{
		printf("\nmalloc request with 24B failed.\n");
	}	


	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

	VSAFree(chunk1);
	VSAFree(chunk2);
	VSAFree(chunk3);

	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));


  	free(pool);
  	pool = NULL;

  	printf("TestVSAFree() tested\n");
}

static void TestVSAAlloc_SpecialCases()
{
	vsa_t *vsa = NULL;
	void *chunk1 = NULL;
	void *chunk2 = NULL;
	void *chunk3 = NULL;
	void *pool = NULL;
	size_t pool_size = 150;

	pool = malloc(pool_size);
	if ( NULL == pool )
	{
		printf("\nmalloc failed, aborting run.\n");
		return;
	}
	
	vsa = VSAInit(pool, pool_size);
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

/******************************************************************************/
	/*PERFORM 2 INITIAL ALLOC REQUSTS*/
/******************************************************************************/
	printf("\t\t\t\t\t\tmalloc request with 15B(>>16B):\n");
	chunk1 = VSAAlloc(vsa, 15);
	if ( NULL == chunk1 )
	{
		printf("\nmalloc request with 15B(>>16B) failed.\n");
	}	
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

	printf("\t\t\t\t\t\tmalloc request with 25B(>>32B):\n");
	chunk2 = VSAAlloc(vsa, 25);
	if ( NULL == chunk2 )
	{
		printf("\nmalloc request with 25B(>>32B) failed.\n");
	}	
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

	printf("\t\t\t\t\t\tmalloc request with 33B(>>40B):\n");
	chunk3 = VSAAlloc(vsa, 33);
	if ( NULL == chunk3 )
	{
		printf("\nmalloc request with 33B(>>40B) failed INTENTIALLY.\n");
	}	

/******************************************************************************/
	/*LAST REQUEST FAILED, SO FIRST, FREE chunk1 & RE-REQUST*/
/******************************************************************************/
	printf("\t\t\t\t\t\tfree request of chunk1: 15B(>>16B):\n");
	VSAFree(chunk1);
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));
	printf("\t\t\t\t\t\tmalloc request with 33B(>>40B):\n");
	chunk3 = VSAAlloc(vsa, 33);
	if ( NULL == chunk3 )
	{
		printf("\nmalloc request with 25B(>>32B) failed INTENTIALLY.\n");
	}

/******************************************************************************/
	/*REQUEST FAILED AGAIN, BECAUSE chunk1 DID NOT PROVIDE
		CONTAGIOUS SPACE OVER chunk2. 
		SO LETS RE-ALLOC chunk1 llike before:
		chunk1 = VSAAlloc(vsa, 15)*/
/******************************************************************************/
	printf("\t\t\t\t\t\tmalloc request with 15B(>>16B):\n");
	chunk1 = VSAAlloc(vsa, 15);
	if ( NULL == chunk1 )
	{
		printf("\nmalloc request with 15B(>>16B) failed.\n");
	}
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

/******************************************************************************/
		/*NOW LETS FREE chunk2: WHICH SHOULD ALLOW CONTAGIOUS AVAILABLE SPACE 
		OVER chunk2 & Already available space = 
		32B (given by chnk2, at least) + 32B (already avail) = 64B (at least)
		& RE-REQUST:*/
/******************************************************************************/
	printf("\t\t\t\t\t\tfree request of chunk2: 25B(>>32B):\n");
	VSAFree(chunk2);
	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));
	printf("\t\t\t\t\t\tmalloc request with 33B(>>40B):\n");
	chunk3 = VSAAlloc(vsa, 33);
	if ( NULL == chunk3 )
	{
		printf("\nmalloc request with 25B(>>32B) failed.\n");
	}	

	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

/******************************************************************************/
/*SUCCESSFUL3 ALLOC for chunk3, shuld leave 64B - 40B = 24B free*/
/******************************************************************************/
	printf("\t\t\t\t\t\tfree request of chunk3: 33B(>>40B):\n");
	VSAFree(chunk3);

	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));

/******************************************************************************/
/*CLEAR POOL FINALLY & VALIDATE NO LEAKS: ALIGNED(112B) = 96B*/
/******************************************************************************/
	VSAFree(chunk1);

	printf("\t\t\t\t\t\tLargest Chunk Available: %ldB \n", VSALargestChunkAvailable(vsa));
	
	REPORT(112, VSALargestChunkAvailable(vsa), "TestVSAAlloc_SpecialCases()");

  	free(pool);
  	pool = NULL;

  	printf("TestVSAAlloc_SpecialCases() tested\n");
}