/*Name: sahar attia
  Project: Data Structures - Double Linked LIst
  Reviewer: Ahmad Agbariya
  Date: 31/07/2023
  Version: 1.0: published the program
  		*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <stdio.h>


#include "dll.h"

/**************************** Type Definitions ********************************/

struct node
{
  void *data;
  node_t *next;
  node_t *prev;
};

struct dll
{
  node_t head;
  node_t tail;
};

/**************************** Helper functions ********************************/

static node_t *CastItertoNode(dll_iter_t iter);
static dll_iter_t CastNodetoIter(node_t *node);
static node_t *CreateNewNode(node_t *next, node_t *prev, void *data);
static void SetNode(node_t *next, node_t *prev, node_t *dest);

/******************************************************************************/
/******************************* API Funcs ************************************/
/******************************************************************************/

dll_t *DListCreate(void)
{
	dll_t *list = (dll_t*)malloc(sizeof(dll_t));
	
	if(NULL == list)
	{
		return NULL;
	}
	
	SetNode(NULL, &(list->head), &(list->tail));
	SetNode(&(list->tail), NULL, &(list->head));
	
	return list;
}

/******************************************************************************/

void DListDestroy(dll_t *list)
{
	node_t* current = list->head.next; 
	
	assert(NULL != list);
	
    while (current->next != NULL)
    {
        node_t* next = current->next;
        free(current);
        current = NULL;
        current = next;
    }

    free(list);
    list = NULL;
}

/******************************************************************************/

size_t DListSize(const dll_t *list)
{
	size_t count = 0;
	node_t* node = NULL;
	assert(NULL != list);
		
	node = CastItertoNode(DListBegin(list));
	
	while (NULL != node->next)
	{
		++count;
		node = node->next;
	}
	
	return count;
}

/******************************************************************************/

int DListIsEmpty(dll_t *list)
{
	assert(NULL != list);
	
	if(NULL == list->head.next->next)
	{
		return TRUE;
	}
	
	return FALSE;
}

/******************************************************************************/

void *DListGetData(dll_iter_t iter)
{
	node_t *node = CastItertoNode(iter);
	assert(NULL != node);
	return node->data;
}

/******************************************************************************/

void DListSetData(dll_iter_t iter, const void *data)
{
	node_t *node = CastItertoNode(iter);
	assert(NULL != node);
	node->data = (void*)data;
}

/******************************************************************************/

dll_iter_t DListInsertBefore(dll_iter_t iter, void* data, dll_t *list)
{
	node_t *new_node = NULL;
	node_t *prev = NULL;
	node_t *node = CastItertoNode(iter);
	
	assert(NULL != node);
	assert(NULL != list);
	
	new_node = CreateNewNode(node, node->prev, data);
	
	if(NULL == new_node)
	{
		return DListEnd(list);
	}
	
	prev = node->prev;
	prev->next = new_node;
	iter->prev = new_node;
	
	return CastNodetoIter(new_node);
}

/******************************************************************************/

dll_iter_t DListRemove(dll_iter_t iter)
{
	node_t *next = NULL;
	node_t *prev = NULL;
	
	node_t *node = CastItertoNode(iter);
	
	assert(NULL != node->next);
	assert(NULL != node);
	
	next = node->next;
	prev = node->prev;
	
	SetNode(next->next, prev, next);
	SetNode(next, prev->prev, prev);
	
	free(node);
	iter = NULL;
	
	return CastNodetoIter(next); 
}

/******************************************************************************/

dll_iter_t DListPushFront(dll_t *list, void* data)
{
	assert(NULL != list);
	return DListInsertBefore(DListBegin(list), data, list);
}

/******************************************************************************/

dll_iter_t DListPushBack(dll_t *list, void* data)
{
	assert(NULL != list);
	return DListInsertBefore(DListEnd(list), data, list);
}

/******************************************************************************/

dll_iter_t DListPopFront(dll_t *list)
{
	assert(NULL != list);
	return DListRemove(DListBegin(list));
}

/******************************************************************************/

dll_iter_t DListPopBack(dll_t *list)
{
	node_t *node_end = NULL;
	assert(NULL != list);
	node_end = CastItertoNode(DListEnd(list));
	return DListPrev(DListRemove(CastNodetoIter(node_end->prev)));
}

/******************************************************************************/

dll_iter_t DListEnd(const dll_t *list)
{
	node_t *tail = NULL;
	
	assert(NULL != list);
	
	tail = &((dll_t*)list)->tail;
	return CastNodetoIter(tail);
}

/******************************************************************************/

void DListSplice(dll_iter_t from, dll_iter_t to, dll_iter_t where)
{

	node_t *node_from = CastItertoNode(from);
	node_t *node_to = CastItertoNode(to);
	node_t *node_where = CastItertoNode(where);
	
	node_t *from_prev = node_from->prev;
	node_t *to_prev = node_to->prev;
	node_t *where_prev = node_where->prev;
	
	assert(NULL != node_from);
	assert(NULL != node_to);
	assert(NULL != node_where);
	
	to_prev->next = node_where;
	from_prev->next = node_to;
	node_to->prev = from_prev;
	node_where->prev = to_prev;
	node_from->prev = where_prev;
	where_prev->next = node_from;
}

/******************************************************************************/

int DListForEach
(dll_iter_t from, dll_iter_t to, DLLActionFunc_t action_func, void* params)
{
	node_t *node_from = CastItertoNode(from);
	node_t *node_to = CastItertoNode(to);
	
	assert(NULL != node_from);
	assert(NULL != node_to);
	assert(NULL != action_func);
	
	while (node_from != node_to)
	{
		if(SUCCESS != action_func(node_from->data, params))		
		{
			return FAILURE;
		}
		
		node_from = node_from->next;
	}
	
	return SUCCESS;	
}

/******************************************************************************/

int DListMultiFind(dll_iter_t from, dll_iter_t to, DLLMatchFunc_t match_func,
	void *param, dll_t *dest_list)
{
	node_t *node_from = CastItertoNode(from);
	node_t *node_to = CastItertoNode(to);
	
	assert(NULL != node_from);
	assert(NULL != node_to);
	assert(NULL != match_func);
	
	while (node_from != node_to)
	{
		if(SUCCESS == match_func(node_from->data, param))		
		{
			DListPushFront(dest_list,node_from->data);
		}
		node_from = node_from->next;
	}
		
	return SUCCESS;
}

/******************************************************************************/

dll_iter_t DListFind
(dll_iter_t from, dll_iter_t to, DLLMatchFunc_t match_func, void* params)
{
	node_t *node_from = CastItertoNode(from);
	node_t *node_to = CastItertoNode(to);
	
	assert(NULL != node_from);
	assert(NULL != node_to);
	assert(NULL != match_func);
	
	while (node_from != node_to)
	{
		if(SUCCESS == match_func(node_from->data, params))		
		{
			return CastNodetoIter(node_from);
		}
		node_from = node_from->next;
	}
		
	return CastNodetoIter(node_from);
}

/******************************************************************************/

dll_iter_t DListBegin(const dll_t *list)
{
	dll_iter_t head = NULL;
	
	assert(NULL != list);
	
	head = CastNodetoIter(list->head.next);
	return head;
}

/******************************************************************************/

dll_iter_t DListNext(dll_iter_t iter)
{
	node_t *node = CastItertoNode(iter);
	
	assert(NULL != node);
	
	return node->next;
}

/******************************************************************************/

dll_iter_t DListPrev(dll_iter_t iter)
{
	node_t *node = CastItertoNode(iter);
	
	assert(NULL != node);
	
	return node->prev;
}

/******************************************************************************/

int DListIsSameIter(dll_iter_t iter1, dll_iter_t iter2)
{
	node_t *node1 = CastItertoNode(iter1);
	node_t *node2 = CastItertoNode(iter2);
	
	assert(NULL != node1);
	assert(NULL != node2);
	
	return node1 == node2;
}

/******************************************************************************/
/******************************* Helper function ******************************/
/******************************************************************************/

static node_t *CastItertoNode(dll_iter_t iter)
{
	return (node_t*)iter;
}

/******************************************************************************/

static dll_iter_t CastNodetoIter(node_t *node)
{
	return (dll_iter_t)node;
}

/******************************************************************************/

static node_t *CreateNewNode(node_t *next, node_t *prev, void *data)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));

    if(NULL == new_node)
    {
        return NULL;
    }
    new_node->data = data;
    SetNode(next, prev, new_node);

    return new_node;
}

/******************************************************************************/

static void SetNode(node_t *next, node_t *prev, node_t *dest)
{
	dest->next = next;
	dest->prev = prev;
}
