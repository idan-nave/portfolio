/*
  Name: Idan Nave
  Project: Work Sheet 12 - Data Structures - Sorted List
  Reviewer: Agbaria
  Date: 27/08/23
  Version: 1.0
*/

/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <stdio.h>              /* perror */
#include <stdlib.h>             /* malloc(), free() */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */

#include "dll.h"
#include "sorted_list.h"

/*****************************************************************************/
/********************************* Type Definitions **************************/
/*****************************************************************************/

struct sorted_list
{
	dll_t *dlist;
	sorted_list_compare_t cmp_func;
};

typedef struct Params
{
	void *params;
	sorted_list_compare_t wrapped_cmp_func;
}params_t;

/*****************************************************************************/
/********************* Static Helper Functions Declerations ******************/
/*****************************************************************************/

/*Wrapper Funcs*/
static int MatchFuncWrapper(const void* from_data, void* params);
static int IsEndElement(sorted_list_t *slist, sor_iter_t iter);
/*Parser Funcs*/
sor_iter_t ToSrtIter (dll_iter_t to_parse);
dll_iter_t ToDllIter (sor_iter_t to_parse);
static int IsValidIter(sor_iter_t iter);

/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/

sorted_list_t* SListCreate(sorted_list_compare_t compare_func)
{
	sorted_list_t *list = NULL;
	
	assert(NULL != compare_func);

	list = (sorted_list_t*)malloc(sizeof(sorted_list_t));
	if(NULL == list)
	{
		return NULL;
	}
	
	list->dlist = DListCreate();
	list->cmp_func = compare_func;
	return list;
}

void SListDestroy(sorted_list_t *list)
{
	assert( NULL != list );

	/*destroy internal Dlist*/
	DListDestroy(list->dlist);
	free(list);
	list = NULL;
}

size_t SListSize(const sorted_list_t *list)
{
	assert( NULL != list );
	return DListSize(list->dlist);
}

int SListIsEmpty(sorted_list_t *list)
{
	assert( NULL != list );
	return DListIsEmpty(list->dlist);
}

void* SListGetData(sor_iter_t iter)
{
	/*assert(!IsValidIter(iter));*/
	return DListGetData(ToDllIter(iter));
}

sor_iter_t SListInsert(sorted_list_t *slist, void* data)
{
	sor_iter_t traverser = SListBegin(slist);
	sor_iter_t end = SListEnd(slist);
	
	assert( NULL != slist );

	while (FALSE == SListIsSameIter(end, traverser))
	{
		if(0 < slist->cmp_func(SListGetData(traverser), data))		
		/*traverser iter data is indeed greater than insertion request*/
		{
			traverser.internal_iter = 
				DListInsertBefore(ToDllIter(traverser), data, slist->dlist);
		 	return traverser;
		}
		traverser = SListNext(traverser);
	}
	traverser.internal_iter =
		DListInsertBefore(ToDllIter(traverser), data, slist->dlist);
	return traverser;
}

sor_iter_t SListRemove(sor_iter_t iter)
{
	/*assert(!IsValidIter(iter));*/
	iter.internal_iter = DListRemove(ToDllIter(iter));
	return iter;
}

sor_iter_t SListPopFront(sorted_list_t *list)
{
	sor_iter_t iter = {0};
	assert( NULL != list );

	iter.internal_iter = DListPopFront(list->dlist);
	#ifndef NDEBUG
	iter.list = list;
	#endif
	return iter;
}

sor_iter_t SListPopBack(sorted_list_t *list)
{
	sor_iter_t iter = {0};
	assert( NULL != list );

	iter.internal_iter = DListPopBack(list->dlist);
	#ifndef NDEBUG
	iter.list = list;
	#endif
	return iter;
}

/*****************************************************************************/
/****************** Sorted List Traversing - API Definitions  ****************/
/*****************************************************************************/

sor_iter_t SListFind
(sor_iter_t from, sor_iter_t to, void* params, sorted_list_t *list)
{
	sor_iter_t iter = {0};
	params_t *p_wrapper = {0};
	assert( NULL != list );
	/*assert(!IsValidIter(from));*/
	/*assert(!IsValidIter(to));*/

	p_wrapper = (params_t*)malloc(sizeof(params_t));
	
	p_wrapper->wrapped_cmp_func = list->cmp_func;
	p_wrapper->params = params;
	
	iter.internal_iter = DListFind(ToDllIter(from), ToDllIter(to), MatchFuncWrapper, (void *)p_wrapper);
	
	free(p_wrapper);
	return iter;
}

static int MatchFuncWrapper(const void* from_data, void* p_wrapper)
{
/*	printf("in Wrapper %d != %d\n", *((int*)from_data), 
				*((int*)(((params_t *)p_wrapper)->params)));*/
	return 0 == ((params_t *)p_wrapper)->wrapped_cmp_func
					(from_data, (((params_t *)p_wrapper)->params));
}

sor_iter_t SlistFindIF
(sor_iter_t from, sor_iter_t to, sorted_list_is_match_t conditional_func, void *params)
{
	/*assert(!IsValidIter(from));*/
	/*assert(!IsValidIter(to));*/
	assert(NULL != conditional_func);

	while(FALSE == SListIsSameIter(from, to))
	{
		if(0 < conditional_func(DListGetData(ToDllIter(from)),params))
		/*requested iter is indeed greater than current node of list*/
		{
			return(from);
		}
		from = SListNext(from);
	}
	return(from);
}

/*****************************************************************************/
/**************** Sorted List Manipulation - API Definitions  ****************/
/*****************************************************************************/

int SListForEach
(sor_iter_t from, sor_iter_t to, sorted_list_action_t action_func, void* params)
{
	/*assert(!IsValidIter(from));*/
	/*assert(!IsValidIter(to));*/
	assert(NULL != action_func);

	return DListForEach(ToDllIter(from), ToDllIter(to), action_func, params);
}

sorted_list_t* SlistMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sor_iter_t dest_runner = SListBegin(dest_list);
	sor_iter_t src_runner_from = SListBegin(src_list);
	sor_iter_t src_runner_to = SListBegin(src_list);

	assert(NULL != dest_list);
	assert(NULL != src_list);
	
	/*while src not empty*/
	while(FALSE == SListIsEmpty(src_list))
	{
		/*src from = src to = src.begin*/
		src_runner_from = SListBegin(src_list);
		src_runner_to = SListBegin(src_list);
		
		/*while dest <= from*/
		while
		(	(FALSE == IsEndElement(dest_list, dest_runner)) &&
				(0 > src_list->cmp_func
					((SListGetData(dest_runner)), SListGetData(src_runner_to))))
		{
			/*++dest*/
			dest_runner = SListNext(dest_runner);
			/*if dest->next = NULL*/
			if(TRUE == IsEndElement(dest_list, dest_runner))
			{
				/*reached dest_end_flag = 1*/
				src_runner_to = SListEnd(src_list);
				DListSplice(ToDllIter(src_runner_from),
										ToDllIter(src_runner_to),
										ToDllIter(dest_runner)   );
				return dest_list;
			}
		}
		
		/*while to <= dest && to != END*/
		while(	(FALSE == IsEndElement(src_list, src_runner_to)) &&
					(0 > src_list->cmp_func
					((SListGetData(src_runner_to)),SListGetData(dest_runner))))
		{
			/*++to*/
			src_runner_to = SListNext(src_runner_to);
		}
		/*splice src from-to => dest*/
				DListSplice(ToDllIter(src_runner_from),
										ToDllIter(src_runner_to),
										ToDllIter(dest_runner)   );
	}
	
	return dest_list;
}

/*****************************************************************************/
/********************* Iterator API Definitions  *****************************/
/*****************************************************************************/

int SListIsSameIter(sor_iter_t iter1, sor_iter_t iter2)
{
	/*assert(!IsValidIter(iter1));*/
	/*assert(!IsValidIter(iter2));*/

	return DListIsSameIter(ToDllIter(iter1), ToDllIter(iter2));
}

sor_iter_t SListBegin(const sorted_list_t *list)
{
	sor_iter_t iter = {0};
	assert( NULL != list );

	iter.internal_iter = DListBegin(list->dlist);
	#ifndef NDEBUG
	iter.list = (sorted_list_t*)list;
	#endif
	return iter;
}

sor_iter_t SListEnd(const sorted_list_t *list)
{
	sor_iter_t iter = {0};
	assert( NULL != list );

	iter.internal_iter = DListEnd(list->dlist);
	#ifndef NDEBUG
	iter.list = (sorted_list_t*)list;
	#endif
	return iter;
}

sor_iter_t SListNext(sor_iter_t iter)
{
	/*assert(!IsValidIter(iter));*/

	iter.internal_iter = DListNext(ToDllIter(iter));
	return iter;
}

sor_iter_t SListPrev(sor_iter_t iter)
{
	/*assert(!IsValidIter(iter));*/
	iter.internal_iter = DListPrev(ToDllIter(iter));
	return iter;
}

/*****************************************************************************/
/**************************** Helper Functions Definitions *******************/
/*****************************************************************************/

static int IsEndElement(sorted_list_t *slist, sor_iter_t iter)
{
	return SListIsSameIter(iter, SListEnd(slist));
}

static int IsValidIter(sor_iter_t iter)
{
	iter;
	return TRUE;
	/*( NULL != iter.list );*/
}

sor_iter_t ToSrtIter (dll_iter_t to_parse)
{
	sor_iter_t iter = {0};
	iter.internal_iter = to_parse;
	return iter;
}

dll_iter_t ToDllIter (sor_iter_t to_parse)
{
	return to_parse.internal_iter;
}