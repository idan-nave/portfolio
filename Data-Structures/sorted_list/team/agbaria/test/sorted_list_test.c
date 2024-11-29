/******************************************************************************/
/*
  Name:Agbaria Ahmad
  Project: Work Sheet 12 - Data Structures - Sorted List
  Reviewer: Uri
  Date: 27/08/23
  Version: 1.0
*/
/******************************************************************************/
#include <stdio.h>

#include "dll.h"
#include "sorted_list.h"

/***************************** user functions *********************************/

static int Multiply(void* data, void* param);
static int CmpFunc(const void* data, void* param);
static int IsDevideByParam(const void* data, void* param);

/******************************************************************************/

void testProgram(void);
static void SortedListCreate_test(void);
static void SortedListIsEmpty_test(void);
static void SortedListSize_test(void);
static void SortedListInsert_test(void);
static void SortedListGetData_test(void);
static void SortedListRemove_test(void);
static void SortedListPopFront_test(void);
static void SortedListPopBack_test(void);
static void SortedListNext_test(void);
static void SortedListPrev_test(void);
static void SortedListBegin_test(void);
static void SortedListEnd_test(void);
static void SortedListFind_test(void);
static void SortedListForEach_test(void);
static void SortedListFindIF_test(void);
static void SortedListMerge_test(void);

/******************************************************************************/

int main()
{
	testProgram();
	return 0;
}

/******************************************************************************/

void testProgram(void)
{
	SortedListCreate_test();
	SortedListIsEmpty_test();
	SortedListSize_test();
	SortedListInsert_test();
	SortedListGetData_test();
	SortedListRemove_test();
	SortedListPopFront_test();
	SortedListPopBack_test();
	SortedListNext_test();
	SortedListPrev_test();
	SortedListBegin_test();
	SortedListEnd_test();
	SortedListFind_test();
	SortedListForEach_test();
	SortedListFindIF_test();
	SortedListMerge_test();
	
}

/******************************************************************************/

static void SortedListCreate_test(void)
{
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	if(NULL != new_list)
	{
		printf("The function SortedListCreate() passed the test and checked with valgrind. \n");
	}
	else
	{
		printf("The function SortedListCreate() didn't pass the test. \n");
	}
	
	SortedListDestroy(new_list);
}
/******************************************************************************/
static void SortedListIsEmpty_test(void)
{
	sorted_list_t *empty_list = SortedListCreate(CmpFunc);
	sorted_list_t *filled_list = SortedListCreate(CmpFunc);
	int data = 1;
	
	SortedListInsert(filled_list, &data);
	
	if((FALSE == SortedListIsEmpty(filled_list)) &&
		   (TRUE == SortedListIsEmpty(empty_list)))
	{
		printf("The function SortedListIsEmpty() passed the test. \n");
	}
	else
	{
		printf("The function SortedListIsEmpty() didn't pass the test. \n");
	}
	
	SortedListDestroy(filled_list);
	SortedListDestroy(empty_list);
}

/******************************************************************************/
	
static void SortedListSize_test(void)
{
	int data = 1;
	size_t size_empty = 0;
	size_t size_after_insert = 0;
	size_t size_after_2insert = 0;
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	size_empty = SortedListSize(new_list);
	
	SortedListInsert(new_list, &data);
	size_after_insert = SortedListSize(new_list);
	
	SortedListInsert(new_list, &data);
	size_after_2insert = SortedListSize(new_list);
	
	
	if(0 != size_empty)
	{
		printf("The function SortedListSize() didn't pass the test.\n");
		return;
	}
	
	if(1 != size_after_insert)
	{
		printf("The function SortedListSize() didn't pass the test.\n");
		return;
	}
	
	if(2 != size_after_2insert)
	{
		printf("The function SortedListSize() didn't pass the test.\n");
		return;
	}
	
	printf("The function SortedListSize() passed the test. \n");
	
	SortedListDestroy(new_list);
}

/******************************************************************************/

static void SortedListInsert_test(void)
{
	size_t i = 0;
	int data[10] = {7,4,5,6,8,9,2,1,0,3};
	int check_data[10] = {0,1,2,3,4,5,6,7,8,9};
	int get_data = 0;
	size_t size_before_insert = 0;
	size_t size_after_insert = 0;
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	while(i < 10)
	{
		size_before_insert = SortedListSize(new_list);
		SortedListInsert(new_list, &data[i]);
		size_after_insert = SortedListSize(new_list);
		
		if(size_after_insert != ++size_before_insert) 
		{
			printf("The function SortedListInsert() didn't pass the test.\n");
		}
		++i;
	}
	
	i = 0;
	iter = SortedListBegin(new_list);
	
	while(!SortedListIsSameIter(SortedListEnd(new_list),iter))
	{
		if(*(int*)(SortedListGetData(iter)) != check_data[i])
		{
			printf("The function SortedListInsert() didn't sort the list in index = %ld \n",i);
			return;
		}
		iter = SortedListNext(iter);
		++i;
	}
	
	printf("The function SortedListInsert() passed the test. \n");
	
	SortedListDestroy(new_list);
}

/******************************************************************************/

static void SortedListGetData_test(void)
{
	int data = 1234;
	int get_data = 0;
	
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	iter = SortedListInsert(new_list, &data);
	
	get_data = *(int*)(SortedListGetData(iter));
	
	if(data != get_data)
	{
		printf("The function SortedListGetData() didn't pass the test.\n");
		return;
	}
	
	printf("The function SortedListGetData() passed the test. \n");
	
	SortedListDestroy(new_list);
}

/******************************************************************************/

static void SortedListRemove_test(void)
{
	int data_1 = 1;
	int data_2 = 2;
	size_t size_before_remove = 0;
	size_t size_after_remove = 0;
	
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	iter = SortedListInsert(new_list, &data_1);
	iter = SortedListInsert(new_list, &data_2);
	
	size_before_remove = SortedListSize(new_list);
	SortedListRemove(iter);
	size_after_remove = SortedListSize(new_list);
	
	if(size_before_remove == (++size_after_remove))
	{
		printf("The function SortedListRemove() passed the test. \n");
	}
	else
	{
		printf("The function SortedListRemove() didn't pass the test. \n");
	}
	
	SortedListDestroy(new_list);
}

/******************************************************************************/

static void SortedListPopFront_test(void)
{
	size_t i = 0;
	int data[10] = {0,1,2,3,4,5,6,7,8,9};
	int check_data[10] = {0,1,2,3,4,5,6,7,8,9};
	int get_data = 0;
	size_t size_before_popfront = 0;
	size_t size_after_popfront = 0;
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	while(i < 10)
	{
		SortedListInsert(new_list, &data[i]);
		++i;
	}
	
	i = 0;
	while(!SortedListIsSameIter(SortedListEnd(new_list),SortedListBegin(new_list)))
	{
		get_data = *(int*)(SortedListGetData(SortedListBegin(new_list)));
		
		if(get_data != check_data[i])
		{
			printf("The function SortedListPopFront() didn't pass the test.\n");
			return;
		}
		size_before_popfront = SortedListSize(new_list);
		SortedListPopFront(new_list);
		size_after_popfront = SortedListSize(new_list);
		
		if(size_before_popfront != ++size_after_popfront) 
		{
			printf("The function SortedListPopFront() didn't pass the test.\n");
			return;
		}
		++i;
	}
	printf("The function SortedListPopFront() passed the test.\n");
	
	SortedListDestroy(new_list);
}

/******************************************************************************/

static void SortedListPopBack_test(void)
{
	size_t i = 0;
	int data[10] = {0,1,2,3,4,5,6,7,8,9};
	int check_data[10] = {0,1,2,3,4,5,6,7,8,9};
	int get_data = 0;
	size_t size_before_popback = 0;
	size_t size_after_popback = 0;
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	while(i < 10)
	{
		SortedListInsert(new_list, &data[i]);
		++i;
	}
	
	i = 9;
	while(!SortedListIsSameIter(SortedListEnd(new_list),SortedListBegin(new_list)))
	{
		get_data = *(int*)(SortedListGetData(SortedListPrev(SortedListEnd(new_list))));
		
		if(get_data != check_data[i])
		{
			printf("The function SortedListPopFront() didn't pass the test.\n");
			return;
		}
		size_before_popback = SortedListSize(new_list);
		SortedListPopBack(new_list);
		size_after_popback = SortedListSize(new_list);
		
		if(size_before_popback != ++size_after_popback) 
		{
			printf("The function SortedListPopBack() didn't pass the test.\n");
			return;
		}
		--i;
	}
	printf("The function SortedListPopBack() passed the test.\n");
	
	SortedListDestroy(new_list);
}

/******************************************************************************/

static void SortedListNext_test(void)
{
	size_t i = 0;
	int data[10] = {0,1,2,3,4,5,6,7,8,9};
	int check_data[10] = {0,1,2,3,4,5,6,7,8,9};
	int get_data = 0;
	
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	while(i < 10)
	{
		SortedListInsert(new_list, &data[i]);
		++i;
	}
	
	iter = SortedListBegin(new_list);
	i = 0;
	
	while(!SortedListIsSameIter(SortedListEnd(new_list),SortedListNext(iter)))
	{
		get_data = *(int*)(SortedListGetData(iter));
		
		if(get_data != check_data[i])
		{
			printf("The function SortedListNext() didn't pass the test.\n");
			return;
		}
		
		++i;
		iter = SortedListNext(iter);
		
	}
	printf("The function SortedListNext() passed the test.\n");
	
	SortedListDestroy(new_list);
}

/******************************************************************************/

static void SortedListPrev_test(void)
{
	size_t i = 0;
	int data[10] = {0,1,2,3,4,5,6,7,8,9};
	int check_data[10] = {0,1,2,3,4,5,6,7,8,9};
	int get_data = 0;
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	while(i < 10)
	{
		SortedListInsert(new_list, &data[i]);
		++i;
	}
	
	iter = SortedListPrev(SortedListEnd(new_list));
	i = 9;
	
	while(!SortedListIsSameIter(SortedListBegin(new_list),SortedListPrev(iter)))
	{
		get_data = *(int*)(SortedListGetData(iter));
		
		if(get_data != check_data[i])
		{
			printf("The function SortedListPrev() didn't pass the test.\n");
			return;
		}
		
		--i;
		iter = SortedListPrev(iter);
		
	}
	printf("The function SortedListPrev() passed the test.\n");
	
	SortedListDestroy(new_list);
}

/******************************************************************************/

static void SortedListIsSameIter_test(void)
{
	int data = 5;
	sorted_list_iter_t iter = {0};
	sorted_list_iter_t iter_2 = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	SortedListInsert(new_list, &data);
	iter = SortedListPrev(SortedListEnd(new_list));
	iter_2 = SortedListBegin(new_list);
	
	if(!SortedListIsSameIter(SortedListBegin(new_list),SortedListPrev(iter)))
	{
		printf("The function SortedListIsSameIter() didn't pass the test.\n");
		return;
	}
	
	if(!SortedListIsSameIter(SortedListEnd(new_list),SortedListNext(iter_2)))
	{
		printf("The function SortedListIsSameIter() didn't pass the test.\n");
		return;
	}
	
	printf("The function SortedListIsSameIter() passed the test.\n");
	
	SortedListDestroy(new_list);
}

/******************************************************************************/
static void SortedListBegin_test(void)
{
	size_t i = 0;
	int get_data = 0;
	int data[10] = {0,1,2,3,4,5,6,7,8,9};
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	while(i < 10)
	{
		SortedListInsert(new_list, &data[i]);
		++i;
	}
	
	iter = SortedListBegin(new_list);
	get_data = *(int*)(SortedListGetData(iter));
	
	if(data[0] == get_data)
	{
		printf("The function SortedListBegin() passed the test. \n");
	}
	else
	{
		printf("The function SortedListBegin() didn't pass the test. \n");
	}
	
	SortedListDestroy(new_list);
	
}
/******************************************************************************/

static void SortedListEnd_test(void)
{
	int data = 5;
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	iter = SortedListInsert(new_list, &data);
	
	if(SortedListIsSameIter(SortedListEnd(new_list),SortedListNext(iter)))
	{
		printf("The function SortedListEnd() passed the test. \n");
	}
	else
	{
		printf("The function SortedListEnd() didn't pass the test. \n");
	}
	
	SortedListDestroy(new_list);
	
}
/******************************************************************************/

static void SortedListFind_test(void)
{
	size_t i = 0;
	int data_to_find = 7;
	int get_data = 0;
	int data[10] = {0,1,2,3,4,5,6,7,8,9};
	int check_data[11] = {0,1,2,3,4,5,6,7,8,9,10};
	sorted_list_iter_t from_iter = {0};
	sorted_list_iter_t to_iter = {0};
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	while(i < 10)
	{
		SortedListInsert(new_list, &data[i]);
		++i;
	}
	
	from_iter = SortedListBegin(new_list);
	to_iter = SortedListEnd(new_list);
	
	iter = SortedListBegin(new_list);
	i = 0;
	
	while(10 > i)
	{
		iter = SortedListFind(from_iter, to_iter, &data[i], new_list);
		get_data = *(int*)(SortedListGetData(iter));
		
		if(get_data != check_data[i])
		{
			printf("The function SortedListFind() didn't pass the test.\n");
			return;
		}
		++i;
	}
	
	iter = SortedListFind(from_iter, to_iter, &check_data[i], new_list);

	if(!SortedListIsSameIter(SortedListEnd(new_list),iter))
	{
		printf("The function SortedListFind() didn't pass the test.\n");
		return;
	}
	
	printf("The function SortedListFind() passed the test.\n");
	
	SortedListDestroy(new_list);
	
}

/******************************************************************************/
static void SortedListForEach_test(void)
{
	size_t i = 0;
	int multiply_num = 2;
	int get_data = 0;
	int data[10] = {0,1,2,3,4,5,6,7,8,9};
	int data_2[10] = {0,2,4,6,8,10,12,14,16,18};
	sorted_list_iter_t from_iter = {0};
	sorted_list_iter_t to_iter = {0};
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	while(i < 10)
	{
		SortedListInsert(new_list, &data[i]);
		++i;
	}
	
	from_iter = SortedListBegin(new_list);
	to_iter = SortedListEnd(new_list);
	SortedListForEach(from_iter, to_iter, Multiply, &multiply_num);

	iter = SortedListBegin(new_list);
	i = 0;
	
	while(!SortedListIsSameIter(SortedListEnd(new_list),iter))
	{
		get_data = *(int*)(SortedListGetData(iter));
		if((data_2[i]) != get_data)
		{
			printf("The function SortedListForEach() didn't pass the test\n");
			return;
		}
		
		++i;
		iter = SortedListNext(iter);
		
	}
	printf("The function SortedListForEach() passed the test. \n");
	
	SortedListDestroy(new_list);
	
}

/******************************************************************************/
static void SortedListFindIF_test(void)
{
	size_t i = 0;
	int get_data = 0;
	int param = 6;
	int data[9] = {1,2,3,4,5,6,7,8,9};
	sorted_list_iter_t from_iter = {0};
	sorted_list_iter_t to_iter = {0};
	sorted_list_iter_t iter = {0};
	sorted_list_t *new_list = SortedListCreate(CmpFunc);
	
	while(i < 9)
	{
		SortedListInsert(new_list, &data[i]);
		++i;
	}
	
	from_iter = SortedListBegin(new_list);
	to_iter = SortedListEnd(new_list);
	
	iter = SortedListFindIF(from_iter, to_iter, IsDevideByParam, &param);
	get_data = *(int*)(SortedListGetData(iter));
	
	if(get_data == param)
	{
		printf("The function SortedListFindIF() passed the test. \n");
	}
	else
	{
		printf("The function SortedListFindIF() didn't pass the test\n");
	}
	
	SortedListDestroy(new_list);
	
}

/******************************************************************************/

static void SortedListMerge_test(void)
{
	size_t i = 0;
	int get_data = 0;
	int data[5] = {0,2,4,6,8};
	int data_2[5] = {1,3,5,7,9};
	int after_merge[10] = {0,1,2,3,4,5,6,7,8,9};
	sorted_list_iter_t iter = {0};
	sorted_list_t *src_list = SortedListCreate(CmpFunc);
	sorted_list_t *dest_list = SortedListCreate(CmpFunc);
	
	while(i < 5)
	{
		SortedListInsert(src_list, &data[i]);
		SortedListInsert(dest_list, &data_2[i]);
		++i;
	}
	
	SortedListMerge(dest_list,src_list);

	iter = SortedListBegin(dest_list);
	i = 0;
	
	while(!SortedListIsSameIter(SortedListEnd(dest_list),iter))
	{
		get_data = *(int*)(SortedListGetData(iter));
		if((after_merge[i]) != get_data)
		{
			printf("The function SortedListMerge() didn't pass the test\n");
			return;
		}
		
		++i;
		iter = SortedListNext(iter);
		
	}
	printf("The function SortedListMerge() passed the test. \n");
	
	SortedListDestroy(dest_list);
	SortedListDestroy(src_list);
}

/******************************************************************************/

static int IsDevideByParam(const void* data, void* param)
{
 	if(((*(int*)data) % (*(int*)param)) == 0)
 	{
 		return TRUE;
 	}
	return FALSE;
}

/******************************************************************************/
static int Multiply(void* data, void* param)
{
 	*(int*)data = (*(int*)data)*(*(int*)param);
	return (SUCCESS);
}

/******************************************************************************/

static int CmpFunc(const void* data, void* param)
{
	return(*(int*)data - *(int*)param);
}

/******************************************************************************/

/*
static int MatchFunc(const void* data, void* param)
{
	if(*(int*)data > *(int*)param)
	{	
		return TRUE;
	}
	return FALSE;
}*/
