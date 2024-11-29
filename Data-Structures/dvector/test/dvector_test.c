#include <stddef.h>/*size_t*/
#include <stdio.h>/*printf*/

#include "dvector.h"

/**********************************define**************************************/

#define	SIZE_ARR 5
#define CAPACITY_TEST 4

/****************************forward decleratin********************************/

void TestVector();

/******************************************************************************/

int main()
{
	TestVector();
	return 0;
}

/******************************************************************************/

void TestVector()
{
	char res_char_arr[SIZE_ARR] = {99, 85, 35, 105, 74};
	int res_int_arr[SIZE_ARR] = {1059, 10254, 25454, 1457, -2544};
	double res_double_arr[SIZE_ARR] = {41412, 10254, 2514, 12157, -2544};
	
	vector_t *my_vector_chars = VectorCreate(CAPACITY_TEST,1);
	vector_t *my_vector_ints = VectorCreate(CAPACITY_TEST,4);
	vector_t *my_vector_duobles = VectorCreate(CAPACITY_TEST,8);
	int i = 0;
	char *res_ptr_char = NULL; 
	int *res_ptr_int = NULL; 
	double *res_ptr_double = NULL; 
	
	if(VectorIsEmpty(my_vector_chars) != SUCCESS || 
	VectorIsEmpty(my_vector_ints) != SUCCESS || 
	VectorIsEmpty(my_vector_duobles) != SUCCESS)
	{
		printf("Test failed on VectorIsEmpty \n");
	}
	
	while (i < SIZE_ARR)
	{
		if(FAILURE == VectorPushBack(my_vector_chars, &res_char_arr[i]))
		{
			printf("failed on chars i = %d\n", i);
		}
		if(FAILURE == VectorPushBack(my_vector_ints, &res_int_arr[i]))
		{
			printf("failed on ints i = %d\n", i);
		}
		if(FAILURE == VectorPushBack(my_vector_duobles, &res_double_arr[i]))
		{
			printf("failed on double i = %d\n", i);
		}
		++i;
	}
	
	if(VectorSize(my_vector_chars) != SIZE_ARR || 
	VectorSize(my_vector_ints) != SIZE_ARR || 
	VectorSize(my_vector_duobles) != SIZE_ARR)
	{
		
		printf("Test failed on VectorSize \n");
	}
	
	if(VectorCapacity(my_vector_chars) != 6 || 
	VectorCapacity(my_vector_ints) != 6 || 
	VectorCapacity(my_vector_duobles) != 6)
	{
		printf("%ld\n",VectorCapacity(my_vector_chars));
		printf("%ld\n",VectorCapacity(my_vector_ints));
		printf("%ld\n",VectorCapacity(my_vector_duobles));
		printf("Test failed on VectorCapacity \n");
	}
	
	if(VectorIsEmpty(my_vector_chars) != FAILURE || 
	VectorIsEmpty(my_vector_ints) != FAILURE || 
	VectorIsEmpty(my_vector_duobles) != FAILURE)
	{
		printf("Test failed on VectorIsEmpty \n");
	}
	
	i = SIZE_ARR -1;
	
	while (0 <= i)
	{
		res_ptr_char = (char*)VGetAccessToElement(my_vector_chars, i);

		if(*res_ptr_char != res_char_arr[i])
		{
			printf("Test failed on char %d and %d \n", res_char_arr[i], *res_ptr_char);
		}
		VectorPopBack(my_vector_chars);
		--i;
	}
	
	i = SIZE_ARR -1;
	
	while (0 <= i)
	{
		res_ptr_int = (int*)VGetAccessToElement(my_vector_ints, i);
		
		if(*res_ptr_int != res_int_arr[i])
		{
			printf("Test failed on int %d and %d \n", res_int_arr[i], *res_ptr_int);
		}
		
		VectorPopBack(my_vector_ints);
		--i;
	}
	
	i = SIZE_ARR -1;
	
	while (0 <= i)
	{
		res_ptr_double = (double*)VGetAccessToElement(my_vector_duobles, i);
		
		if(*res_ptr_double != res_double_arr[i])
		{
			printf("Test failed on double %f and %f i = %d \n", res_double_arr[i], *res_ptr_double, i);
		}
		
		VectorPopBack(my_vector_duobles);
		--i;
	}
	
	if(VectorIsEmpty(my_vector_chars) != SUCCESS || 
	VectorIsEmpty(my_vector_ints) != SUCCESS || 
	VectorIsEmpty(my_vector_duobles) != SUCCESS)
	{
		printf("Test failed on VectorIsEmpty \n");
	}
	
	printf("Vector checked!\n");
	VectorDestroy(my_vector_chars);
	printf("char destroyed\n");
	VectorDestroy(my_vector_ints);
	printf("int destroyed\n");
	VectorDestroy(my_vector_duobles);
	printf("double destroyed\n");
}

