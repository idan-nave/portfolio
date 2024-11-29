/*Name: Dima
  Project: DS WS 12 - Sorted List
  Reviewer: ---
  Date: 24/08/23
  Version: 1.0

***********************************INCLUDE*************************************/
#include <stdio.h>  /*perror()*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc()*/
#include <assert.h> /*assert()*/
#include <string.h> /*memcpy()*/

#include "sorted_list.h"
#include "dll.h"
/****************************ENUMS/MACROS/DEFINES******************************/

/****************************TYPEDEFS AND STRUCTS******************************/
struct sorted_list 
{
	dll_ty *dlist;
	sorted_list_compare_func_t cmp_func;
};

typedef struct Params
{
	void *params;
	sorted_list_compare_func_t param_cmp_func;
}params_ty;

/*Wrapper Funcs*/
static int MatchFuncWrapper(const void* data, void* params);
/*Heler Funcs*/
static void PrintAll(sorted_list_t *test_slist);
static int IsEndElement(sorted_list_t *slist, sorted_list_iter_t iter);


/*============================================================================*/
/*===============================IMPLEMENTATION===============================*/
/*============================================================================*/


/*****************************CREATION FUNCS***********************************/
sorted_list_t* SListCreate(sorted_list_compare_func_t CompareFunc)
{
	/*Allocate memory for List struct, tail dummy and head dummy*/
	sorted_list_t *new_slist = NULL;
	
	new_slist = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	
	if(NULL == new_slist)
	{
		perror("Memory allocation for list failed");
		free(new_slist);
		new_slist = NULL;
		return NULL;
	}
	
	new_slist->dlist = DListCreate();
	new_slist->cmp_func = CompareFunc;
	
	
	return new_slist;
}

void SListDestroy(sorted_list_t *list)
{
	DListDestroy(list->dlist);
	free(list);
}

/*******************************BASE FUNCS*************************************/
size_t SListSize(const sorted_list_t *list)
{
	return DListSize(list->dlist);
}

int SListIsEmpty(sorted_list_t *list)
{
	return DListIsEmpty(list->dlist);
}

void* SListGetData(sorted_list_iter_t iter)
{
	return DListGetData(iter.internal_iter);
}

sorted_list_iter_t SListInsert(sorted_list_t *slist, void* data)
{
	sorted_list_iter_t iter = {0};
	
	iter.internal_iter = DListFind(DListBegin(slist->dlist), DListEnd(slist->dlist)
											   , (match_function_ty)slist->cmp_func, data);
											   
	iter.internal_iter = DListInsertBefore(iter.internal_iter, data, slist->dlist);
	
	return iter;
}

sorted_list_iter_t SListRemove(sorted_list_iter_t iter)
{
	iter.internal_iter = DListRemove(iter.internal_iter);
	return iter;
}
/********************************POP FUNCS*************************************/
sorted_list_iter_t SListPopFront(sorted_list_t *list)
{
	sorted_list_iter_t sl_iter = {0};
	assert(NULL != list);
	
	sl_iter.internal_iter = DListPopFront(list->dlist);
	return sl_iter;
}

sorted_list_iter_t SListPopBack(sorted_list_t *list)
{
	sorted_list_iter_t sl_iter = {0};
	assert(NULL != list);
	
	sl_iter.internal_iter = DListPopFront(list->dlist);;
	return sl_iter;
}
/*****************************SEARCH FUNCS*************************************/
sorted_list_iter_t SListFind
(sorted_list_iter_t from, sorted_list_iter_t to, void* params, sorted_list_t *list)
{
	sorted_list_iter_t sl_iter = {0};
	params_ty *parameters_struct = {0};

	parameters_struct = (params_ty *)malloc(sizeof(params_ty));
	
	parameters_struct->param_cmp_func = list->cmp_func;
	parameters_struct->params = params;
	
	sl_iter.internal_iter = DListFind(from.internal_iter ,to.internal_iter , MatchFuncWrapper, (void *)parameters_struct);
	
	free(parameters_struct);
	
	return sl_iter;
}

sorted_list_iter_t SlistFindIF
(sorted_list_iter_t from, sorted_list_iter_t to, sorted_list_is_match_t conditional__func, void *params)
{
	while(FALSE == SListIsSameIter(from, to))
	{
		if(TRUE == conditional__func(DListGetData(from.internal_iter), params))
		{
			return(from);
		}
		from = SListNext(from);
	}
	return(from);
}
/*****************************LIST MANIPULATION FUNCS**************************/
int SListForEach
(sorted_list_iter_t from, sorted_list_iter_t to, sorted_list_action_t action_func, void* params)
{
	return DListForEach(from.internal_iter ,to.internal_iter ,action_func, params);
}

sorted_list_t* SlistMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sorted_list_iter_t dest_runner = SListBegin(dest_list);
	sorted_list_iter_t src_runner_from = SListBegin(src_list);
	sorted_list_iter_t src_runner_to = SListBegin(src_list);

	assert(NULL != dest_list);
	assert(NULL != src_list);
	
	/*while src not empty*/
	while(FALSE == SListIsEmpty(src_list))
	{
		/*src from = src to = src.begin*/
		src_runner_from = SListBegin(src_list);
		src_runner_to = SListBegin(src_list);
		
		/*while dest <= from*/
		while((FALSE == IsEndElement(dest_list, dest_runner)) &&
				(MORE_THEN != src_list->cmp_func((SListGetData(dest_runner)), SListGetData(src_runner_to))
				))	
		{
			/*++dest*/
			dest_runner = SListNext(dest_runner);
			/*if dest->next = NULL*/
			if(TRUE == IsEndElement(dest_list, dest_runner))
			{
				/*reached dest_end_flag = 1*/
				src_runner_to = SListEnd(src_list);
				DListSplice(src_runner_from.internal_iter,src_runner_to.internal_iter, dest_runner.internal_iter);
				return dest_list;
			}
		}
		
		/*while to <= dest && to != END*/
		while(MORE_THEN != src_list->cmp_func((SListGetData(src_runner_to)),SListGetData(dest_runner))
				&& (FALSE == IsEndElement(src_list, src_runner_to)))
		{
			/*++to*/
			src_runner_to = SListNext(src_runner_to);
		}
		/*splice src from-to => dest*/
		DListSplice(src_runner_from.internal_iter,src_runner_to.internal_iter, dest_runner.internal_iter);
		PrintAll(dest_list);
	}
	
	return dest_list;
}

/********************* Iterator API Declerations  ****************************/
int SListIsSameIter(sorted_list_iter_t iter, sorted_list_iter_t iter_to_compare)
{
	return DListIsSameIter(iter.internal_iter, iter_to_compare.internal_iter);
}

sorted_list_iter_t SListBegin(const sorted_list_t *list)
{
	sorted_list_iter_t sl_iter = {0};
	assert(NULL != list);
	
	sl_iter.internal_iter = DListBegin(list->dlist);
	return sl_iter;
}

sorted_list_iter_t SListEnd(const sorted_list_t *list)
{
	sorted_list_iter_t sl_iter = {0};
	assert(NULL != list);
	
	sl_iter.internal_iter = DListEnd(list->dlist);
	return sl_iter;
}

sorted_list_iter_t SListNext(sorted_list_iter_t iter)
{
	iter.internal_iter = DListNext(iter.internal_iter);
	return iter;
}

sorted_list_iter_t SListPrev(sorted_list_iter_t iter)
{
	iter.internal_iter = DListPrev(iter.internal_iter);
	return iter;
}

/********************************WRAPPER FUNCS*********************************/

static int MatchFuncWrapper(const void* from_data, void* params)
{
	int return_value = 0;

	return_value = ((params_ty *)params)->param_cmp_func
									(&from_data, &((params_ty *)params)->params);
									
	return (return_value==EQUAL)?TRUE:FALSE;
}

/*******************************HELPER FUNCS***********************************/
static void PrintAll(sorted_list_t *test_slist)
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

static int IsEndElement(sorted_list_t *slist, sorted_list_iter_t iter)
{
	if(1 == SListIsSameIter(iter, SListEnd(slist)))
	{
		return TRUE;
	}
	
	return FALSE;
}













