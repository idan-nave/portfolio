#include <stdio.h>/*printf*/

#include "sorted_list.h"

/******************************************************************************/

#define ErrorMsg(expected, result, str) \
		{\
		    if (expected != result)\
		    {\
		    	printf("%s has failed\n", str);\
		    }\
		}
		
/******************************************************************************/
static int Compare(const void *data1, void *data2);
static int Add(void* data, void* param);

/******************************************************************************/

static void MainTestFunc(void);

static void TestSListCreate(void);
static void TestSListSize(void);
static void TestSListIsEmpty(void);
static void TestSListGetData(void);
static void TestSListInsert(void);
static void TestSListRemove(void);
static void TestSListPopFront(void);
static void TestSListPopBack(void);
static void TestSListPrev(void);
static void TestSListEnd(void);
static void TestSListNext(void);
static void TestSListIsSameIter(void);
static void TestSListFind(void);
static void TestSListFindIf(void);
static void TestSListForEach(void);
static void TestSListSlistMerge(void);

/******************************************************************************/
/*
int main()
{
	
	return 0;
}
*/

/******************************************************************************/


int main()
{
	MainTestFunc();
	return 0;
}

/******************************************************************************/

static void MainTestFunc(void)
{
	TestSListCreate();
	TestSListSize();
	TestSListIsEmpty();
	TestSListGetData();
	TestSListInsert();
	TestSListRemove();
	TestSListPopFront();
	TestSListPopBack();
	TestSListPrev();
	TestSListEnd();
	TestSListNext();
	TestSListIsSameIter();
	TestSListFind();
	/*TestSListFindIf();*/
	TestSListForEach();
	TestSListSlistMerge();
}

/******************************************************************************/

static void TestSListCreate(void)
{
	sorted_list_t *list = SListCreate(Compare);
	ErrorMsg(1, SListIsEmpty(list), "TestSListCreate()");
	ErrorMsg(0, SListSize(list), "TestSListCreate()");

	printf("TestSListCreate() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/
	
static void TestSListSize(void)
{
	sorted_list_t *list = SListCreate(Compare);
	int x1 = 1;
	int x2 = 2;
	
	sorted_list_iter_t my_itr2;
	ErrorMsg(1, SListIsEmpty(list), "TestSListSize()");
	ErrorMsg(0, SListSize(list), "TestSListSize()");
	
	my_itr2 = SListInsert(list, &x1);
	SListInsert(list, &x2);
	
	ErrorMsg(2, SListSize(list), "TestSListSize()");
	
	SListRemove(my_itr2);
	
	ErrorMsg(1, SListSize(list), "TestSListSize()");
	
	printf("TestSListSize() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/
	
static void TestSListIsEmpty(void)
{
	sorted_list_t *list = SListCreate(Compare);
	int x1 = 1;
	int x2 = 2;
	sorted_list_iter_t my_itr1;
	sorted_list_iter_t my_itr2;
	
	ErrorMsg(1, SListIsEmpty(list), "TestSListIsEmpty()");
	ErrorMsg(0, SListSize(list), "TestSListIsEmpty()");
	
	my_itr2 = SListInsert(list, &x1);
	my_itr1 = SListInsert(list, &x2);
	
	ErrorMsg(0, SListIsEmpty(list), "TestSListIsEmpty()");
	
	SListRemove(my_itr2);
	
	ErrorMsg(0, SListIsEmpty(list), "TestSListIsEmpty()");
	
	SListRemove(my_itr1);
	
	ErrorMsg(1, SListIsEmpty(list), "TestSListIsEmpty()");

	printf("TestSListIsEmpty() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/
	
static void TestSListGetData(void)
{
	sorted_list_t *list = SListCreate(Compare);
	int x1 = 1;
	int x2 = 2;
	sorted_list_iter_t my_itr1;
	sorted_list_iter_t my_itr2;
	
	my_itr2 = SListInsert(list, &x1);
	my_itr1 = SListInsert(list, &x2);
	
	ErrorMsg(x1, *((int*)SListGetData(my_itr2)), "TestSListGetData()");
	
	ErrorMsg(x2, *((int*)SListGetData(my_itr1)), "TestSListGetData()");
	
	ErrorMsg(x1, *((int*)SListGetData(SListBegin(list))), "TestSListGetData()");

	printf("TestSListGetData() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/

static void TestSListInsert(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	int arr_res[7] = {1,2,3,4,5,6,7};
	sorted_list_iter_t my_itr;
	size_t i = 0;
	size_t size = 7;
	sorted_list_t *list = SListCreate(Compare);
	
	while (i < size)
	{
		my_itr = SListInsert(list, &(arr[i]));
		++i;
	}
	
	my_itr = SListBegin(list);
	i = 0;
	
	while (i < size)
	{
		ErrorMsg(arr_res[i], *((int*)SListGetData(my_itr)), "TestSListInsert()");
		my_itr = SListNext(my_itr);
		++i;
	}
	
	printf("TestSListInsert() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/
	
static void TestSListRemove(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	size_t i = 0;
	size_t size = 7;
	
	sorted_list_t *list = SListCreate(Compare);
	
	while (i < size)
	{
		SListInsert(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	
	while (i < size)
	{
		ErrorMsg((size - i), SListSize(list), "TestSListRemove()");
		SListRemove(SListBegin(list));
		++i;
	}
	
	printf("TestSListRemove() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/
	
static void TestSListPopFront(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	int arr_res[7] = {1,2,3,4,5,6,7};
	sorted_list_iter_t my_itr;
	size_t i = 0;
	size_t size = 7;
	sorted_list_t *list = SListCreate(Compare);
	
	while (i < size)
	{
		my_itr = SListInsert(list, &(arr[i]));
		++i;
	}
	
	my_itr = SListBegin(list);
	i = 1;
	
	while (i < size)
	{
		my_itr = SListPopFront(list);
		ErrorMsg(arr_res[i], *((int*)SListGetData(my_itr)), "TestSListPopFront()");
		++i;
	}
	
	printf("TestSListPopFront() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/
	
static void TestSListPopBack(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	int arr_res[7] = {7,6,5,4,3,2,1};
	sorted_list_iter_t my_itr;
	size_t i = 0;
	size_t size = 7;
	sorted_list_t *list = SListCreate(Compare);
	
	while (i < size)
	{
		my_itr = SListInsert(list, &(arr[i]));
		++i;
	}
	
	my_itr = SListBegin(list);
	i = 1;
	
	while (i < size)
	{
		my_itr = SListPopBack(list);
		ErrorMsg(arr_res[i], *((int*)SListGetData(my_itr)), "TestSListPopBack()");
		++i;
	}
	
	printf("TestSListPopBack() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/

static void TestSListEnd(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	sorted_list_iter_t my_itr;
	size_t i = 0;
	size_t size = 7;
	sorted_list_t *list = SListCreate(Compare);
	
	while (i < size)
	{
		my_itr = SListInsert(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = SListPrev(SListEnd(list));
	
	while (i < size)
	{
		int res = *((int*)SListGetData(SListPrev(SListEnd(list))));
		ErrorMsg(res, *((int*)SListGetData(my_itr)), "TestSListEnd()");
		my_itr = SListPopBack(list);
		++i;
	}
	
	printf("TestSListEnd() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/
	
static void TestSListPrev(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	sorted_list_iter_t my_itr;
	size_t i = 0;
	size_t size = 7;
	sorted_list_t *list = SListCreate(Compare);
	
	while (i < size)
	{
		my_itr = SListInsert(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = SListPrev(SListEnd(list));
	
	while (i < size)
	{
		int res = *((int*)SListGetData(SListPrev(SListEnd(list))));
		ErrorMsg(res, *((int*)SListGetData(my_itr)), "TestSListPrev()");
		my_itr = SListPopBack(list);
		++i;
	}
	
	printf("TestSListPrev() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/
	
static void TestSListNext(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	int arr_res[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	sorted_list_iter_t my_itr;
	sorted_list_t *list = SListCreate(Compare);
	
	while (i < size)
	{
		my_itr = SListInsert(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = SListBegin(list);
	
	while (i < size)
	{
		ErrorMsg(arr_res[i], *((int*)SListGetData(my_itr)),
		 "TestSListNext()");
		my_itr = SListNext(my_itr);
		++i;
	}
	
	printf("TestSListNext() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/
	
static void TestSListIsSameIter(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	size_t i = 0;
	size_t size = 7;
	sorted_list_iter_t my_itr;
	sorted_list_iter_t my_itr2;
	sorted_list_t *list = SListCreate(Compare);
	
	while (i < size)
	{
		my_itr = SListInsert(list, &(arr[i]));
		++i;
	}
	
	i = 0;
	my_itr = SListBegin(list);
	my_itr2 =  SListPrev(SListEnd(list));
	
	while (i < size)
	{
		if(i == (size - 1) && FALSE == SListIsSameIter(my_itr2, my_itr))
		{
			printf("there was a problem with TestSListIsSameIter()\n");
		}
		
		if(i != (size - 1) && TRUE == SListIsSameIter(my_itr2, my_itr))
		{
			printf("there was a problem with TestSListIsSameIter()\n");
		}
		
		my_itr = SListNext(my_itr);
		++i;
	}
	
	printf("TestSListIsSameIter() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/

static void TestSListFind(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	int arr_res[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	sorted_list_iter_t my_itr;
	sorted_list_iter_t my_itr2;
	sorted_list_iter_t my_iter_res;
	
	sorted_list_t *list = SListCreate(Compare);
	
	my_itr = SListBegin(list);
	my_itr2 =  SListPrev(SListEnd(list));
	
	while (i < size)
	{
		my_itr = SListInsert(list, &(arr[i]));
		++i;
	}
	my_itr = SListBegin(list);
	my_iter_res = SListFind(my_itr, my_itr2, &(arr_res[3]), list);
	ErrorMsg(arr_res[3], *((int*)SListGetData(my_iter_res)), "TestSListFind()");
	
	my_iter_res = SListFind(my_itr, my_itr2, &(arr_res[5]), list);
	ErrorMsg(arr_res[5], *((int*)SListGetData(my_iter_res)), "TestSListFind()");
	
	printf("TestSListFind() tested\n");
	
	SListDestroy(list);
}

/******************************************************************************/

static void TestSListForEach(void)
{
	int arr[7] = {7,1,5,3,2,4,6};
	int arr_res[7] = {1,2,3,4,5,6,7};
	size_t i = 0;
	size_t size = 7;
	int to_add = 7;
	sorted_list_iter_t my_itr;
	sorted_list_iter_t my_itr2;
	
	sorted_list_t *list = SListCreate(Compare);
	
	my_itr = SListBegin(list);
	my_itr2 =  SListPrev(SListEnd(list));
	
	while (i < size)
	{
		my_itr = SListInsert(list, &(arr[i]));
		++i;
	}
	
	my_itr = SListBegin(list);
	my_itr2 =  SListEnd(list);
	
	SListForEach(my_itr, my_itr2, Add, &to_add);
	
	i = 0;
	my_itr = SListBegin(list);
	while (i < size)
	{
		ErrorMsg(*((int*)SListGetData(my_itr)), arr_res[i] +to_add,
		 "TestSListForEach()");
		my_itr = SListNext(my_itr);
		++i;
	}
	
	SListDestroy(list);
	
	printf("TestSListForEach() tested\n");
}

/******************************************************************************/

static void TestSListSlistMerge(void)
{
	int x = 4;
	int x1 = 7;
	int x2 = 1;
	int x3 = 3;
	int x4 = 5;
	int x5 = 9;
	int x6 = 2;
	size_t i = 0;
	int arr_res[7] = {1,2,3,4,5,7,9};
	sorted_list_iter_t begin = {0};
	sorted_list_iter_t res = {0};
	sorted_list_iter_t end = {0};
	sorted_list_t *list_dest = SListCreate(Compare);
	sorted_list_t *list_src = SListCreate(Compare);
	
	begin = SListBegin(list_dest);
	res = SListInsert(list_dest, &x);
	res = SListInsert(list_dest, &x2);
	res = SListInsert(list_dest, &x1);
	
	
	res = SListInsert(list_src, &x3);
	res = SListInsert(list_src, &x4);
	res = SListInsert(list_src, &x5);
	res = SListInsert(list_src, &x6);
	list_dest = SlistMerge(list_dest, list_src);
	
	res = SListBegin(list_dest);
	
	while(7 > i)
	{
		ErrorMsg(*((int*)SListGetData(res)), arr_res[i], "TestSListSlistMerge()");
		res = SListNext(res);
		++i;
	}	
	
	SListDestroy(list_dest);
	SListDestroy(list_src);
	printf("TestSListSlistMerge() tested\n");
}

/******************************************************************************/
/*TestSListFindIf();*/

static int Add(void* data, void* param)
{
	*((int*)data) += *((int*)param);
	
	return SUCCESS;
	
}

static int Compare(const void *data1, void *data2)
{
	if(*((int*)data1) > *((int*)data2))
	{
		return 1;
	}
	
	if(*((int*)data1) < *((int*)data2))
	{
		return -1;
	}
	
	return 0;
}

