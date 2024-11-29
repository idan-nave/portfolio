/*Name: Dima
  Project: DS WS 12 - Sorted List
  Reviewer: Sahar
  Date: 20/08/23
  Version: 1.0

***********************************INCLUDE*************************************/
#include <stdio.h>  /*perror()*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc()*/
#include <assert.h> /*assert()*/
#include <string.h> /*memcpy()*/

#include "sorted_list.h"

/****************************ENUMS/MACROS/DEFINES******************************/
dll_iter_ty NodeToIter(node_ty node);
/****************************TYPEDEFS AND STRUCTS******************************/

void DummyFunc();
int SortedListAction(void* data, void* param);
int SortedListCompare(const void* , void*);
int SortedListIsMatch(const void* , const void* );


/*Helper Funcs*/
void PrintAll(sorted_list_t *test_slist);
/*============================================================================*/
/*===============================IMPLEMENTATION===============================*/
/*============================================================================*/



int main()
{
	sorted_list_t *test_slist;
	sorted_list_t *src_slist;
	sorted_list_iter_t sl_iter = {0};
	sorted_list_iter_t sl_iter_finder = {0};
	int num_arr[13] = {20, 3, 16, -5, 66, 1, 11, 3, -7, 0,-7,-1,70};
	int num_to_add = 4;
	int find_if_num = 19;
	
	test_slist = SListCreate(SortedListCompare);
	src_slist = SListCreate(SortedListCompare);

	printf("Is empty? %d, Size of list: %ld\n", SListIsEmpty(test_slist), SListSize(test_slist));

	sl_iter = SListInsert(test_slist, &num_arr[0]);
	sl_iter = SListInsert(test_slist, &num_arr[1]);
	sl_iter = SListInsert(test_slist, &num_arr[2]);
	sl_iter = SListInsert(test_slist, &num_arr[3]);
	
	PrintAll(test_slist);
	printf("Finding \n");
	sl_iter_finder = SListFind(SListBegin(test_slist), SListEnd(test_slist), &num_arr[2], test_slist);
	printf("Data found: %d\n", *(int *)SListGetData(sl_iter_finder));
	
	printf("Finding \n");
	sl_iter_finder = SListFind(SListBegin(test_slist), SListEnd(test_slist), &num_arr[8], test_slist);
	printf("Data found: %p\n", SListGetData(sl_iter_finder));
	
	printf("Is empty? %d, Size of list: %ld\n", SListIsEmpty(test_slist), SListSize(test_slist));
	
	sl_iter = SListInsert(test_slist, &num_arr[4]);
	sl_iter = SListInsert(test_slist, &num_arr[5]);
	sl_iter = SListInsert(test_slist, &num_arr[6]);
	
	printf("SList for each:\n");
	PrintAll(test_slist);
	SListForEach(SListBegin(test_slist), SListEnd(test_slist), &SortedListAction, &num_to_add);
	PrintAll(test_slist);
	printf("SList Find if:\n");
	sl_iter = SlistFindIF(SListBegin(test_slist), SListEnd(test_slist), &SortedListIsMatch, &find_if_num);
	
	printf("	%d + 1 = %d\n", find_if_num, *(int *)SListGetData(sl_iter));
	
	sl_iter = SListInsert(src_slist, &num_arr[7]);
	sl_iter = SListInsert(src_slist, &num_arr[8]);
	sl_iter = SListInsert(src_slist, &num_arr[9]);
	sl_iter = SListInsert(src_slist, &num_arr[10]);
	sl_iter = SListInsert(src_slist, &num_arr[11]);
	sl_iter = SListInsert(src_slist, &num_arr[12]);
	
	printf("===================LAST TEST: MERGE!========================\n");
	printf("\n#####BEFORE#####\n\n");
	PrintAll(test_slist);
	PrintAll(src_slist);
	printf("\n#####MERGING#####\n\n");
	SlistMerge(test_slist, src_slist);
	printf("\n#####AFTER#####\n\n");
	PrintAll(test_slist);
	PrintAll(src_slist);
	
	SListDestroy(test_slist);
	SListDestroy(src_slist);
	
	return 0;
}






/******************************************************************************/
int SortedListAction(void* data, void* param)
{	
	printf("SL action Func Called data:VP1: %d VP2: %d\n",*((int*)data),*((int*)param));
	
	*(int *)data += *(int *)param;
	
	return 1;
}

int SortedListCompare(const void* vp1, void* vp2)
{
	/*printf("SL Compare Func Called VP1: %p, %d VP2: %p, %d\n",vp1,*((int*)vp1),vp2,*((int*)vp2));*/
	/*printf("######COMPARING: %d to: %d\n",*((int*)vp1), *((int*)vp2));*/
	
	if(*(int *)vp1 > *(int *)vp2)
	{
		return MORE_THEN;
	}
	if(*(int *)vp1 == *(int *)vp2)
	{
		return EQUAL;
	}
	return LESS_THEN;
	
}

int SortedListIsMatch(const void* vp1, const void* vp2)
{
	printf("SL IsMatch Func Called VP1: %d VP2: %d\n",*((int*)vp1),*((int*)vp2));
	if(*(int *)vp1 == *(int *)vp2 + 1)
	{
		return TRUE;
	}
	return FALSE;
}



/******************************************************************************/
void PrintAll(sorted_list_t *test_slist)
{
	sorted_list_iter_t sl_iter = {0};
	sl_iter = SListBegin(test_slist);
	
	printf("==========Printing all data========== \n");
	while(FALSE == SListIsSameIter(sl_iter, SListEnd(test_slist)))
	{
		printf("%d\n", *(int *)SListGetData(sl_iter));
		sl_iter = SListNext(sl_iter);
	}
}

