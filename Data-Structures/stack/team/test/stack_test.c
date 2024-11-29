#include <stddef.h>/*size_t*/
#include <stdio.h>/*printf*/

#include "stack.h"

/**********************************define**************************************/

#define	SIZE_ARR 5
#define CAPACITY_TEST 100

/****************************forward decleratin********************************/

void TestStack();

/******************************************************************************/

int main()
{
	TestStack();
	return 0;
}

/******************************************************************************/

void TestStack()
{
	char res_char_arr[SIZE_ARR] = {99, 85, 35, 105, 74};
	int res_int_arr[SIZE_ARR] = {1059, 10254, 25454, 1457, -2544};
	double res_double_arr[SIZE_ARR] = {41412, 10254, 2514, 12157, -2544};
	
	stack_ty *my_stack_chars = StackCreate(CAPACITY_TEST,1);
	stack_ty *my_stack_ints = StackCreate(CAPACITY_TEST,4);
	stack_ty *my_stack_duobles = StackCreate(CAPACITY_TEST,8);
	int i = 0;
	char *res_ptr_char = NULL; 
	int *res_ptr_int = NULL; 
	double *res_ptr_double = NULL; 
	
	if(StackIsEmpty(my_stack_chars) != TRUE || 
	StackIsEmpty(my_stack_ints) != TRUE || 
	StackIsEmpty(my_stack_duobles) != TRUE)
	{
		printf("Test failed on StackIsEmpty \n");
	}
	
	while (i < SIZE_ARR)
	{
		StackPush(my_stack_chars, &res_char_arr[i]);
		StackPush(my_stack_ints, &res_int_arr[i]);
		StackPush(my_stack_duobles, &res_double_arr[i]);
		++i;
	}
	
	if(StackSize(my_stack_chars) != SIZE_ARR || 
	StackSize(my_stack_ints) != SIZE_ARR || 
	StackSize(my_stack_duobles) != SIZE_ARR)
	{
		printf("Test failed on StackSize \n");
	}
	
	if(StackCapacity(my_stack_chars) != CAPACITY_TEST || 
	StackCapacity(my_stack_ints) != CAPACITY_TEST || 
	StackCapacity(my_stack_duobles) != CAPACITY_TEST)
	{
		printf("Test failed on StackIsEmpty \n");
	}
	
	if(StackIsEmpty(my_stack_chars) != FALSE || 
	StackIsEmpty(my_stack_ints) != FALSE || 
	StackIsEmpty(my_stack_duobles) != FALSE)
	{
		printf("Test failed on StackIsEmpty \n");
	}
	
	i = SIZE_ARR -1;
	
	while (0 <= i)
	{
		res_ptr_char = (char*)StackPeek(my_stack_chars);
		
		if(*res_ptr_char != res_char_arr[i])
		{
			printf("Test failed on char %d and %d \n", res_char_arr[i], *res_ptr_char);
		}
		
		StackPop(my_stack_chars);
		--i;
	}
	
	i = SIZE_ARR -1;
	
	while (0 <= i)
	{
		res_ptr_int = (int*)StackPeek(my_stack_ints);
		
		if(*res_ptr_int != res_int_arr[i])
		{
			printf("Test failed on int %d and %d \n", res_int_arr[i], *res_ptr_int);
		}
		
		StackPop(my_stack_ints);
		--i;
	}
	
	i = SIZE_ARR -1;
	
	while (0 <= i)
	{
		res_ptr_double = (double*)StackPeek(my_stack_duobles);
		
		if(*res_ptr_double != res_double_arr[i])
		{
			printf("Test failed on double %f and %f \n", res_double_arr[i], *res_ptr_double);
		}
		
		StackPop(my_stack_duobles);
		--i;
	}
	
	if(StackIsEmpty(my_stack_chars) != TRUE || 
	StackIsEmpty(my_stack_ints) != TRUE || 
	StackIsEmpty(my_stack_duobles) != TRUE)
	{
		printf("Test failed on StackIsEmpty \n");
	}
	
	printf("Stack checked!\n");
	StackDestroy(my_stack_chars);
	StackDestroy(my_stack_duobles);
	StackDestroy(my_stack_ints);
}

