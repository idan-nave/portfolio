/*
  Name: Aya
  Project: Work Sheet 6 - Data Structures - Singly Linked LIst
  Reviewer: ???
  Date: 14/08/23
  Version: 1.0
*/

/******************************** Libraries  **********************************/

#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "sll.h"

/******************************** Definitions  ********************************/
static node_ty* CreateDummy();

struct node
{
  void *data;
  node_ty *next;
};

struct sll
{
  iter_ty head;
  iter_ty tail;
};

/*********************** S-list API Declerations  *****************************/
  
sll_ty* SListCreate()
{
  node_ty *dummy_node = CreateDummy();
  sll_ty *list = (sll_ty*)malloc(sizeof(sll_ty));
  iter_ty dummy_iter = {0};

  if(NULL == list)
  {
    free(dummy_node);
    dummy_node = NULL;
    return (sll_ty*)0;
  }

  dummy_node->data = list;
  dummy_node->next = NULL;
  
  dummy_iter.node_ptr = dummy_node;

  list->head = dummy_iter;
  list->tail = dummy_iter;

  return list;
}

void SListDestroy(sll_ty *list)
{
  node_ty* current = list->head.node_ptr->next; 

  assert(NULL != list);

  while (current != NULL)
  {
      node_ty* next = current->next;
      free(current);
      current = next;
  }

  free(list->head.node_ptr); 
  free(list);
}

iter_ty SListInsertBefore(iter_ty iter, void* data)
{
  iter_ty iter_new = {0};
  iter_new.node_ptr = (node_ty*)malloc(sizeof(node_ty));

  iter_new.node_ptr->data = iter.node_ptr->data;
  iter_new.node_ptr->next = iter.node_ptr->next;
  iter.node_ptr->data = data;
  iter.node_ptr->next = iter_new.node_ptr;
  
  if(NULL == iter_new.node_ptr->next)
  {
    ((sll_ty*)iter_new.node_ptr->data)->tail.node_ptr = iter_new.node_ptr;
  }

  return iter;
}

iter_ty SListRemove(iter_ty iter)
{
  node_ty *to_remove = {0};

  assert(NULL != iter.node_ptr);

  if (NULL != iter.node_ptr->next)
  {
    to_remove = iter.node_ptr->next;
    iter.node_ptr->data = to_remove->data;  
    iter.node_ptr->next = to_remove->next;  
    free(to_remove);
  }

  if(NULL == iter.node_ptr->next)
  {
    ((sll_ty*)iter.node_ptr->data)->tail = iter;
  }
  
  return iter;
}

void *SListGetData(iter_ty iter)
{
  return iter.node_ptr->data;
}

void SListSetData(iter_ty iter, void* data)
{
  assert(NULL != data);

  iter.node_ptr->data = data;

  return;
}

void SListSetNext(iter_ty iter1, iter_ty iter2)
{
  iter1.node_ptr->next = iter2.node_ptr;

  return;
}

void SListSetTail(sll_ty *dest, sll_ty *src)
{
  dest->tail = src->tail;

  return;
}

int SListIsEmpty(sll_ty *list)
{
  assert(NULL != list);

  if(0 == SListCount(list))
  {
    return EMPTY;
  }

  return NOT_EMPTY;
}

size_t SListCount(sll_ty *list)
{
  size_t count = 0;
  iter_ty iter = {0};

  assert(NULL != list);

  iter = list->head;

  while (list != iter.node_ptr->data)
  {
    iter.node_ptr = iter.node_ptr->next;
    ++count;
  }

  return count;
}

iter_ty SListFind(iter_ty from_iter, iter_ty to_iter,  void* data, MatchFunc_ty match_func, void* usr_param)
{
  assert(NULL != match_func);

  while (FALSE == SListIterIsEqual(from_iter, to_iter))
  {
    if (match_func(from_iter.node_ptr->data, data))
    {
        return from_iter;
    }

    from_iter = SListNext(from_iter);
  }

  return to_iter; /*Return end iterator if not found*/
}

int SListForEach(iter_ty from_iter, iter_ty to_iter, void* data, ActionFunc_ty action_func, void* usr_param)
{
  iter_ty iter = {0};

  assert(NULL != action_func);

  iter = from_iter;

  while (FALSE == SListIterIsEqual(iter, to_iter))
  {
    if (action_func(iter.node_ptr->data, usr_param) != SUCCESS)
    {
        return FAILURE; /*Stop iterating if the action fails*/
    }
    
    iter.node_ptr = iter.node_ptr->next;
  }

  return SUCCESS;
}

sll_ty* SListAppend(sll_ty *dest, sll_ty *src)
{
  /*iter_ty iter = {0};
  iter_ty iter2 = SListNext(iter);

  assert(NULL != dest);
  assert(NULL != src);

  iter = SListEnd(dest->slist);
  iter2.node_ptr = CreateNode();
  iter2.node_ptr = SListBegin(src->slist).node_ptr;
  SListRemove(iter);*/

  dest->tail = src->head;

  return dest;
}
           

/********************* Iterator API Declerations  *****************************/

int SListIterIsEqual(iter_ty iter1, iter_ty iter2)
{
  if((iter1.node_ptr == iter2.node_ptr))
  {
    return TRUE;
  }

  return FALSE;
}

iter_ty SListBegin(sll_ty *list)
{
  assert(NULL != list);

  return list->head;
}

iter_ty SListEnd(sll_ty *list)
{
  assert(NULL != list);
  
  return list->tail;
}

iter_ty SListNext(iter_ty iter)
{
  iter_ty iter_nxt = {0};

  iter_nxt.node_ptr = iter.node_ptr->next;

  return iter_nxt;
}

/**************************** Helper Functions  *******************************/
static node_ty* CreateDummy()
{
  node_ty* dummy_node = (node_ty*)malloc(sizeof(node_ty));

  if(NULL == dummy_node)
  {
    return (node_ty*)0;
  }

  return dummy_node;
}