/*Name: sahar attia
  Project: Data Structures - Double Linked LIst
  Reviewer: ???
  Date: 31/07/2023
  Version: 1.0: published the program
  		*/
#include <stdlib.h>/*malloc*/

#include "dll.h"
#include "sorted_list.h"


/**************************** Type Definitions ********************************/

struct sorted_list
{
	dll_t *dlist;
	sorted_list_compare_t cmp_func;
};

/**************************** Helper functions ********************************/



/******************************************************************************/
/******************************* API Funcs ************************************/
/******************************************************************************/

sorted_list_t* SListCreate(sorted_list_compare_t CompareFunc)
{
	sorted_list_t *list = (sorted_list_t*)malloc(sizeof(sorted_list_t));
	
	if(NULL == list)
	{
		return NULL;
	}
	
	list->dlist = DListCreate();
	list->cmp_func = CompareFunc;
	return list;
}

/******************************************************************************/

void SListDestroy(sorted_list_t *list)
{
	DListDestroy(list->dlist);
	free(list);
	list = NULL;
}

/******************************************************************************/

size_t SListSize(const sorted_list_t *list)
{
	return DListSize(list->dlist);
}

/******************************************************************************/

int SListIsEmpty(sorted_list_t *list)
{
	return DListIsEmpty(list->dlist);
}

/******************************************************************************/

void* SListGetData(sorted_list_iter_t iter)
{
	return DListGetData(iter.internal_iter);
}

/******************************************************************************/
sorted_list_iter_t SListInsert(sorted_list_t *slist, void* data)
{
	sorted_list_iter_t begin = SListBegin(slist);
	sorted_list_iter_t end = SListEnd(slist);
	while (!SListIsSameIter(end, begin))
	{
		if(1 == slist->cmp_func(SListGetData(begin), data))		
		{
			begin.internal_iter = DListInsertBefore(begin.internal_iter, data,
		 	slist->dlist);
		 	return begin;
		}
		begin = SListNext(begin);
	}
	begin.internal_iter = DListInsertBefore(begin.internal_iter, data,
	 	slist->dlist);
	return begin;
}

/******************************************************************************/

sorted_list_iter_t SListRemove(sorted_list_iter_t iter)
{
	iter.internal_iter = DListRemove(iter.internal_iter);
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SListPopFront(sorted_list_t *list)
{
	sorted_list_iter_t iter = {0};
	iter.internal_iter = DListPopFront(list->dlist);
	#ifndef NDEBUG
	iter.list = list;
	#endif
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SListPopBack(sorted_list_t *list)
{
	sorted_list_iter_t iter = {0};
	iter.internal_iter = DListPopBack(list->dlist);
	#ifndef NDEBUG
	iter.list = list;
	#endif
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SListFind(sorted_list_iter_t from, sorted_list_iter_t to,
void* params, sorted_list_t *list)
{
	sorted_list_iter_t res = {0};
	res.internal_iter = DListFind(from.internal_iter, to.internal_iter, 
	list->cmp_func, params);
	#ifndef NDEBUG
	res.list = from.list;
	#endif
	return res; 
}

/******************************************************************************/

sorted_list_iter_t SlistFindIF(sorted_list_iter_t from, sorted_list_iter_t to,
sorted_list_is_match_t conditional_func, void *params)
{
	while (!SListIsSameIter(from, to))
	{
		if(TRUE == conditional_func(SListGetData(from), params))		
		{
			return from;
		}
		from = SListNext(from);
	}
	
	return from; 
}

/******************************************************************************/

int SListForEach(sorted_list_iter_t from, sorted_list_iter_t to,
 sorted_list_action_t action_func, void* params)
{
	return DListForEach(from.internal_iter, to.internal_iter, 
	action_func, params);
}

/******************************************************************************/

sorted_list_t* SlistMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
    sorted_list_iter_t iter_dest = SListBegin(dest_list);
    sorted_list_iter_t iter_src = SListBegin(src_list);
	sorted_list_iter_t where = SListBegin(src_list);
	sorted_list_iter_t next_src = {0};
	
    while (!SListIsSameIter(where, SListEnd(dest_list)))
    {
        where = SlistFindIF(iter_dest, SListEnd(dest_list), dest_list->cmp_func,
         SListGetData(iter_src));
        next_src = SListNext(iter_src);
		DListSplice(iter_src.internal_iter, next_src.internal_iter, where.internal_iter);
        iter_src = next_src;
    }

    return dest_list;
}

/******************************************************************************/

int SListIsSameIter(sorted_list_iter_t iter, sorted_list_iter_t iter_to_compare)
{
	return DListIsSameIter(iter.internal_iter, iter_to_compare.internal_iter);
}

/******************************************************************************/

sorted_list_iter_t SListBegin(const sorted_list_t *list)
{
	sorted_list_iter_t iter = {0};
	iter.internal_iter = DListBegin(list->dlist);
	#ifndef NDEBUG
	iter.list = (sorted_list_t*)list;
	#endif
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SListEnd(const sorted_list_t *list)
{
	sorted_list_iter_t iter = {0};
	iter.internal_iter = DListEnd(list->dlist);
	#ifndef NDEBUG
	iter.list = (sorted_list_t*)list;
	#endif
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SListNext(sorted_list_iter_t iter)
{
	iter.internal_iter = DListNext(iter.internal_iter);
	return iter;
}

/******************************************************************************/

sorted_list_iter_t SListPrev(sorted_list_iter_t iter)
{
	iter.internal_iter = DListPrev(iter.internal_iter);
	return iter;
}


