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
static node_t* CreateDummy();
static node_t* CreateNode();

struct node
{
  void *data;
  node_t *next;
};

struct sll
{
  iter_t head;
  iter_t tail;
};

/*********************** S-list API Declerations  *****************************/
  
sll_t* SListCreate()
{
  node_t *dummy_node = CreateDummy();
  sll_t *list = (sll_t*)malloc(sizeof(sll_t));
  iter_t dummy_iter = {0};

  if(NULL == list)
  {
    free(dummy_node);
    return (sll_t*)0;
  }

  dummy_node->data = list;
  dummy_node->next = NULL;
  
  dummy_iter.node_ptr = dummy_node;

  list->head = dummy_iter;
  list->tail = dummy_iter;

  return list;
}

void SListDestroy(sll_t *list)
{
  node_t* current = list->head.node_ptr->next; 

  assert(NULL != list);

  while (current != NULL)
  {
      node_t* next = current->next;
      free(current);
      current = next;
  }

  free(list->head.node_ptr); 
  free(list);
}

iter_t SListInsertBefore(iter_t iter, void* data)
{
  iter_t iter_new = {0};
  iter_new.node_ptr = (node_t*)malloc(sizeof(node_t));

  iter_new.node_ptr->data = iter.node_ptr->data;
  iter_new.node_ptr->next = iter.node_ptr->next;
  iter.node_ptr->data = data;
  iter.node_ptr->next = iter_new.node_ptr;
  
  if(NULL == iter_new.node_ptr->next)
  {
    ((sll_t*)iter_new.node_ptr->data)->tail.node_ptr = iter_new.node_ptr;
  }

  return iter;
}

iter_t SListRemove(iter_t iter)
{
  node_t *to_remove = {0};

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
    ((sll_t*)iter.node_ptr->data)->tail = iter;
  }
  
  return iter;
}

void *SListGetData(iter_t iter)
{
  return iter.node_ptr->data;
}

void SListSetData(iter_t iter, void* data)
{
  assert(NULL != data);

  iter.node_ptr->data = data;

  return;
}

int SListIsEmpty(sll_t *list)
{
  assert(NULL != list);

  if(0 == SListCount(list))
  {
    return EMPTY;
  }

  return NOT_EMPTY;
}

size_t SListCount(sll_t *list)
{
  size_t count = 0;
  iter_t iter = {0};

  assert(NULL != list);

  iter = list->head;

  while (list != iter.node_ptr->data)
  {
    iter.node_ptr = iter.node_ptr->next;
    ++count;
  }

  return count;
}

iter_t SListFind(iter_t from_iter, iter_t to_iter,  void* data, MatchFunc_t match_func, void* usr_param)
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

int SListForEach(iter_t from_iter, iter_t to_iter, void* data, ActionFunc_t action_func, void* usr_param)
{
  iter_t iter = {0};

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
           

/********************* Iterator API Declerations  *****************************/

int SListIterIsEqual(iter_t iter1, iter_t iter2)
{
  if((iter1.node_ptr == iter2.node_ptr))
  {
    return TRUE;
  }

  return FALSE;
}

iter_t SListBegin(sll_t *list)
{
  assert(NULL != list);

  return list->head;
}

iter_t SListEnd(sll_t *list)
{
  assert(NULL != list);
  
  return list->tail;
}

iter_t SListNext(iter_t iter)
{
  iter_t iter_nxt = {0};

  iter_nxt.node_ptr = iter.node_ptr->next;

  return iter_nxt;
}

/**************************** Helper Functions  *******************************/
static node_t* CreateDummy()
{
  node_t* dummy_node = (node_t*)malloc(sizeof(node_t));

  if(NULL == dummy_node)
  {
    return (node_t*)0;
  }

  return dummy_node;
}

static node_t* CreateNode()
{
  node_t* node = (node_t*)malloc(sizeof(node_t));

  if(NULL == node)
  {
    return (node_t*)0;
  }

  return node;
}