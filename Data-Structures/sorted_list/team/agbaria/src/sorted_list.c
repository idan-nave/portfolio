/******************************************************************************/
/*
  Name:Agbaria Ahmad
  Project: Work Sheet 12 - Data Structures - Sorted List
  Reviewer: Uri
  Date: 27/08/23
  Version: 1.0
*/
/******************************************************************************/
#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/
#include <stdio.h>

#include "dll.h"
#include "sorted_list.h"

/******************************************************************************/

struct sorted_list 
{
	sorted_list_compare_t cmp_func;
	dll_t *dlist;
};

typedef struct cast_cmp
{
	sorted_list_compare_t cmp_func;
	void *param;
}cast_cmp_t;

/********************************helper function*******************************/

static int IsBiger(const void *data , void *params);

static int IsMatch(const void *data , void *params);

/******************************************************************************/

sorted_list_t* SortedListCreate(sorted_list_compare_t CompareFunc)
{
	sorted_list_t *new_slist = (sorted_list_t*)malloc(sizeof(sorted_list_t));
	if(NULL == new_slist)
	{
		return NULL;
	}
	
	new_slist->dlist = DListCreate();
	if(NULL == new_slist->dlist)
	{
		return NULL;
	}
	
	new_slist->cmp_func = CompareFunc;
	
	return(new_slist);
}

/******************************************************************************/
void SortedListDestroy(sorted_list_t *slist)
{
	assert(NULL != slist);
	
	DListDestroy(slist->dlist);

	free(slist);
	slist = NULL;
}

/******************************************************************************/

size_t SortedListSize(const sorted_list_t *slist)
{
	assert(NULL != slist);
	
	return(DListSize(slist->dlist));
}

/******************************************************************************/

int SortedListIsEmpty(sorted_list_t *slist)
{
	assert(NULL != slist);
	
	return(DListIsEmpty(slist->dlist));
}

/******************************************************************************/

void* SortedListGetData(sorted_list_iter_t iter)
{
	return DListGetData(iter.internal_iter);
}

/******************************************************************************/

sorted_list_iter_t SortedListInsert(sorted_list_t *slist, void* data)
{
	cast_cmp_t *cast_struct = NULL;
	sorted_list_iter_t iter = {0};
	
	assert(NULL != slist);
	assert(NULL != data);
	
	cast_struct = (cast_cmp_t*)malloc(sizeof(cast_cmp_t));
	
	if(NULL == cast_struct)
	{
		iter.internal_iter = DListEnd(slist->dlist);
		return iter;
	}
	
	cast_struct->param = data;
	cast_struct->cmp_func = slist->cmp_func;
	
	dll_iter_t from_iter = DListBegin(slist->dlist);
	dll_iter_t to_iter = DListEnd(slist->dlist);
	
	iter.internal_iter = DListInsertBefore(DListFind(from_iter, to_iter,
						 &IsBiger, cast_struct),data,slist->dlist);
	#ifndef NDEBUG
	iter.list = slist;
	#endif
	 
	free(cast_struct);
	cast_struct = NULL;
	
	return iter;

}

/******************************************************************************/

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
	sorted_list_iter_t return_iter = {0};
	sorted_list_t *slist = iter.list;
	
	return_iter.internal_iter = DListRemove(iter.internal_iter);
	#ifndef NDEBUG
	return_iter.list = slist;
	#endif
	
	return return_iter;
}

/******************************************************************************/

sorted_list_iter_t SortedListPopFront(sorted_list_t *slist)
{
	sorted_list_iter_t iter = {0};

	assert(NULL != slist);
	
	iter.internal_iter = DListRemove(DListBegin(slist->dlist));
	#ifndef NDEBUG
	iter.list = slist;
	#endif
	
	return iter;
	
}

/******************************************************************************/

sorted_list_iter_t SortedListPopBack(sorted_list_t *slist)
{
	sorted_list_iter_t iter = {0};
	
	assert(NULL != slist);
	
	iter.internal_iter = DListRemove(DListPrev(DListEnd(slist->dlist)));
	#ifndef NDEBUG
	iter.list = slist;
	#endif
	
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SortedListFind
(sorted_list_iter_t from, sorted_list_iter_t to, void* params,
 sorted_list_t *slist)
{
	sorted_list_iter_t iter= {0};
	cast_cmp_t *cast_struct = NULL;
	
	assert(from.list == to.list);
	assert(NULL != slist);
	
	cast_struct = (cast_cmp_t*)malloc(sizeof(cast_cmp_t));
	if(NULL == cast_struct)
	{
		iter.internal_iter = DListEnd(slist->dlist);
		#ifndef NDEBUG
		iter.list = slist;
		#endif
		
		return iter;
	}
	
	cast_struct->param = params;
	cast_struct->cmp_func = slist->cmp_func;
	
	iter.internal_iter = DListFind(from.internal_iter, to.internal_iter,
	 &IsMatch, cast_struct);
	#ifndef NDEBUG
	iter.list = slist;
	#endif
	 
	free(cast_struct);
	cast_struct = NULL;
	
	return iter;
}
/******************************************************************************/

int SortedListForEach
(sorted_list_iter_t from, sorted_list_iter_t to,
 sorted_list_action_t action_func, void* params)
{
	assert(from.list == to.list);
	assert(NULL != action_func);
	
	return DListForEach (from.internal_iter, to.internal_iter, action_func,
						 params);
}

/******************************************************************************/

sorted_list_iter_t SortedListFindIF
(sorted_list_iter_t from, sorted_list_iter_t to,
	 sorted_list_is_match_t conditional_func, void *params)
 {
 	assert(NULL != conditional_func);
 	assert(from.list == to.list);
 	
 	while(!SortedListIsSameIter(from,to))
 	{
 		if(conditional_func(SortedListGetData(from), params))
 		{
 			return from;
 		}
 		
 		from = SortedListNext(from);
 	}
 	return from;
 }
 

/******************************************************************************/

sorted_list_t* SortedListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	cast_cmp_t *cast_struct = NULL;
	void *from_data = NULL;
	void *where_data = NULL;
	sorted_list_iter_t where_iter = {0};
	sorted_list_iter_t from_iter = {0};
	sorted_list_iter_t to_iter = {0};
	
	assert(NULL != dest_list);
	assert(NULL != src_list);
	
	cast_struct = (cast_cmp_t*)malloc(sizeof(cast_cmp_t));
	
	if(NULL == cast_struct)
	{
		return NULL;
	}
	
	from_iter = SortedListBegin(src_list);
	
	while(!SortedListIsSameIter(from_iter, SortedListEnd(src_list)))
	{
		from_data = SortedListGetData(from_iter);
		cast_struct->param = from_data;
		cast_struct->cmp_func = dest_list->cmp_func;
		
		where_iter.internal_iter = 
		DListFind(SortedListBegin(dest_list).internal_iter, 
		SortedListEnd(dest_list).internal_iter, &IsBiger, cast_struct);

		where_data = SortedListGetData(where_iter);
		cast_struct->param = where_data;
		cast_struct->cmp_func = src_list->cmp_func;
		
		to_iter.internal_iter = 
		DListFind(SortedListNext(from_iter).internal_iter, 
		SortedListEnd(src_list).internal_iter, &IsBiger, cast_struct);
		
		DListSplice(from_iter.internal_iter, to_iter.internal_iter,
		where_iter.internal_iter);
		
		from_iter = to_iter;
	}
	
	free(cast_struct);
	cast_struct = NULL;
	
	return dest_list;
}
	

/********************* Iterator API Implementation  ***************************/

int SortedListIsSameIter(sorted_list_iter_t iter,
	 sorted_list_iter_t iter_to_compare)
{
	return (DListIsSameIter(iter.internal_iter, iter_to_compare.internal_iter));
}


/******************************************************************************/
sorted_list_iter_t SortedListBegin(const sorted_list_t *slist)
{
	sorted_list_iter_t iter= {0};
	
	assert(NULL != slist);
	
	iter.internal_iter = DListBegin(slist->dlist);
	#ifndef NDEBUG
	iter.list = (sorted_list_t*)slist;
	#endif
	
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SortedListEnd(const sorted_list_t *slist)
{
	sorted_list_iter_t iter= {0};
	
	assert(NULL != slist);
	
	iter.internal_iter = DListEnd(slist->dlist);
	#ifndef NDEBUG
	iter.list = (sorted_list_t*)slist;
	#endif
	
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	iter.internal_iter = DListNext(iter.internal_iter);
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	iter.internal_iter = DListPrev(iter.internal_iter);	
	return iter;
}

/******************************************************************************/

static int IsBiger(const void *data , void *params)
{
	sorted_list_compare_t CompareFunc = NULL;
	cast_cmp_t *cast_struct = NULL;
	
	cast_struct = (cast_cmp_t*)params;
	CompareFunc = cast_struct->cmp_func;
	params = cast_struct->param;
	
	if(0 < (CompareFunc(data,params)))
	{	
		return TRUE;
	}
	return FALSE;
}

static int IsMatch(const void *data , void *params)
{
	sorted_list_compare_t CompareFunc = NULL;
	cast_cmp_t *cast_struct = NULL;
	
	cast_struct = (cast_cmp_t*)params;
	CompareFunc = cast_struct->cmp_func;
	params = cast_struct->param;
	
	if(0 == (CompareFunc(data,params)))
	{	
		return TRUE;
	}
	return FALSE;
}















