/*
  Name: Idan Nave
  Project: Work Sheet 11 - Data Structures - Doubly Linked List
  Reviewer: Uri
  Date: 22/08/23
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <stdio.h>              /* perror */
#include <stdlib.h>             /* malloc(), free() */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */

#include "dll.h"

/*****************************************************************************/
/********************************* Type Definitions **************************/
/*****************************************************************************/

  /******************************** TypeDefs  ******************************/

/*Struct for a node within DLL */
struct node
{
	node_t *next;
	node_t *prev;
	void *data;
};

/*Struct manager for dll */
struct dll
{
	node_t head;
	node_t tail;
};

/*****************************************************************************/
/********************* Static Helper Functions Declerations ******************/
/*****************************************************************************/

node_t* ToNode (dll_iter_t to_parse);
dll_iter_t ToIter (node_t* to_parse);

/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/

dll_t* DListCreate()
{    
    dll_t* new_dll = (dll_t*)malloc(sizeof(dll_t));

    /* validate successful malloc*/
    if(NULL == new_dll)
    {
        errno = ENOMEM;
        perror("Unsuccessful allocation of new dll");
    	return NULL; /*as agreed in API*/
    }
    
    /* assign constant dummies */
    new_dll->head.next = &(new_dll->tail);
    new_dll->head.prev = NULL;
    new_dll->head.data = (void*)0;
    new_dll->tail.prev = &(new_dll->head);
    new_dll->tail.next = NULL;
    new_dll->tail.data = (void*)0;
    return new_dll;
}

void DListDestroy(dll_t *list)
{
	dll_iter_t traverser =  NULL;
	dll_iter_t temp_nxt = NULL;

	assert(NULL != list);
	traverser = DListBegin( list );

	while (traverser->next != NULL)
	{
		/*store next priorto freeing */
		temp_nxt = DListNext(traverser); 
		DListRemove(traverser);
		traverser = temp_nxt;
	}
	free(list);
}

dll_iter_t DListRemove(dll_iter_t iter)
{
	node_t* prv_link = NULL;
	node_t* nxt_link = NULL;

	assert(NULL != ToNode(iter));

	prv_link = DListPrev(iter);
	nxt_link = DListNext(iter);
	/* perform re-linkig */
	prv_link->next = iter->next;
  	nxt_link->prev = iter->prev;
  	
  	/* detach requested node */
  	free(ToNode(iter));
  	return nxt_link;
}

dll_iter_t DListInsertBefore(dll_iter_t iter, void* data, dll_t *dlist)
{
	node_t* inserted = NULL;
	node_t *node_tmp = NULL;

	assert(NULL != ToNode(iter));
	assert( NULL != dlist );

    inserted = (node_t*)malloc(sizeof(node_t));
    if(NULL == inserted)
    {
        errno = ENOMEM;
        perror("Unsuccessful allocation of new node");
    	return ToIter(&dlist->tail); /*as agreed in API*/
    }

  	/* assign data & links to new allocated node */
    inserted->data = data;
	inserted->next = iter;
  	inserted->prev = iter->prev;
  	/* temp is needed to update next of previos node
  	to point to the new allocared iter */
  	node_tmp = iter->prev;
  	node_tmp->next = inserted;
	iter->prev = inserted;

  	return ToIter(inserted);
}

void* DListGetData(dll_iter_t iter)
{
	assert(NULL != ToNode(iter));
	return iter->data;
}

void DListSetData(dll_iter_t iter, const void *data)
{
	assert(NULL != ToNode(iter));
	iter->data = (void *)data;
}

size_t DListSize(const dll_t *list)
{
	size_t size = 0;
	dll_iter_t traverser =  NULL;
	assert(NULL != list);

    traverser = DListBegin(list);
    /* stay one after tail, to prevent segmentation fault */

	while (traverser->next !=NULL)
	{
		traverser = DListNext( traverser );
	  	++size;
	}
	return size;
}

/*****************************************************************************/
/******************** DLL Traversing - API Definitions  **********************/
/*****************************************************************************/

dll_iter_t DListFind
  (dll_iter_t from, dll_iter_t to, dll_match_t match_func, void* param)
{
	assert(NULL != ToNode(from));
	assert(NULL != ToNode(to));
	assert( NULL != match_func);

	while (FALSE == DListIsSameIter(from, to) )
	{
	  	if (TRUE == match_func( DListGetData(from) , param ))
	  	{
	  		return from;
	  	}
	  	from = DListNext(from);
	}
	return to;
}

int DListMultiFind (dll_iter_t from, dll_iter_t to,
					dll_match_t match_func, void *param, dll_t *dest_list)
{
	int is_found = FALSE;
	assert(NULL != ToNode(from));
	assert(NULL != ToNode(to));
	assert( NULL != match_func);
	assert( NULL != dest_list);

	while (FALSE == DListIsSameIter(from, to) )
	{
/*		printf("%d\n", *((int*)DListGetData(from)));
*/	  	is_found = match_func( DListGetData(from) , param );
	  	if (TRUE == is_found)
	  	{
			DListPushFront(dest_list, DListGetData(from));
	  	}
	  	from = DListNext(from);
	}
	return is_found;
}

int DListForEach(dll_iter_t from, dll_iter_t to, 
				dll_action_t action_func, void* param)
{
	assert(NULL != ToNode(from));
	assert(NULL != ToNode(to));
	assert( NULL != action_func);

	while (FALSE == DListIsSameIter(from, to) )
	{
	  	if (FAILURE == action_func( DListGetData(from), param))
	  	{
	  		return FAILURE;
	  	}
	  	from = DListNext(from);
	}
	return SUCCESS;
}

void DListSplice (dll_iter_t from, dll_iter_t to, dll_iter_t where)
{
	node_t *node_from = ToNode(from);
	node_t *node_to = ToNode(to);
	node_t *node_where = ToNode(where);
	
	node_t *from_prev = node_from->prev;
	node_t *to_prev = node_to->prev;
	node_t *where_prev = node_where->prev;

	assert(NULL != ToNode(node_from));
	assert(NULL != ToNode(node_to));
	assert(NULL != ToNode(node_where));

	to_prev->next = node_where;
	from_prev->next = node_to;
	node_to->prev = from_prev;
	node_where->prev = to_prev;
	node_from->prev = where_prev;
	where_prev->next = node_from;
}

/*****************************************************************************/
/********************* Begin & End API Definitions  **************************/
/*****************************************************************************/

dll_iter_t DListPushFront(dll_t *list, void* data)
{
	assert( NULL != list);
	return DListInsertBefore(DListBegin( list), data, list);
}

dll_iter_t DListPushBack(dll_t *list, void* data)
{
	assert( NULL != list);
	return DListInsertBefore(DListEnd(list), data, list);
}

dll_iter_t DListPopFront(dll_t *list)
{
	assert( NULL != list);
	return DListRemove(DListBegin( list));
}

dll_iter_t DListPopBack(dll_t *list)
{
	assert( NULL != list);
	return DListPrev((DListRemove(DListPrev(DListEnd(list)))));
}

/*****************************************************************************/
/********************* Iterator API Definitions  *****************************/
/*****************************************************************************/

int DListIsEmpty(dll_t *list)
{
	assert( NULL != list);
 	return list->head.next->next == NULL;
}

dll_iter_t DListBegin(const dll_t *list)
{
	assert( NULL != list);
    return ToIter(list->head.next);
}

dll_iter_t DListEnd(const dll_t *list)
{
	assert( NULL != list);
    return (dll_iter_t)&(list->tail);
}

dll_iter_t DListNext(dll_iter_t iter)
{
    return ToIter(iter->next);
}

dll_iter_t DListPrev(dll_iter_t iter)
{
	assert(NULL != ToNode(iter));
    return ToIter(iter->prev);
}

int DListIsSameIter(const dll_iter_t iter1, const dll_iter_t iter2)
{
	assert(NULL != ToNode(iter1));
	assert(NULL != ToNode(iter2));

    return iter1 == iter2; 
	/*Compare the memory addresses of the node_t "inside" iters*/
}

/*****************************************************************************/
/**************************** Helper Functions Definitions *******************/
/*****************************************************************************/

node_t* ToNode (dll_iter_t to_parse)
{
	return (node_t*)to_parse;
}

dll_iter_t ToIter (node_t* to_parse)
{
	return (dll_iter_t)to_parse;
}