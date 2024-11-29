/********************************** ws6_sll.c  ***************************/
/*
  Name: Idan Nave
  Project: Work Sheet 6 - Data Structures - Singly Linked LIst
  Reviewer: Agbaria
  Date: 12/08/23
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <stddef.h>             /*size_t*/
#include <stdlib.h>             /*malloc*/
#include <assert.h>             /*assert*/
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */

#include "sll.h" 		

/*****************************************************************************/
/********************* Static Helper Functions Declerations ******************/
/*****************************************************************************/  
static node_t* CreateDummy();
static node_t* CreateNode();

/*****************************************************************************/
/*********************************** Type Definitions ************************/
/*****************************************************************************/

struct node
{
  void *data;
  node_t *next;
};

struct sll
{
  sll_iter_t head;
  sll_iter_t tail;
};

/*****************************************************************************/
/************************** API Functions Definitions ************************/
/*****************************************************************************/  
sll_t* SListCreate()
{
  node_t *dummy_node = CreateDummy();
  sll_t *list = (sll_t*)malloc(sizeof(sll_t));
  sll_iter_t dummy_iter = {0};

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

sll_iter_t SListInsertBefore(sll_iter_t iter, void* data)
{
  sll_iter_t iter_new = {0};
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

sll_iter_t SListRemove(sll_iter_t iter)
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

void *SListGetData(sll_iter_t iter)
{
  return iter.node_ptr->data;
}

void SListSetData(sll_iter_t iter, void* data)
{
  assert(NULL != data);
  iter.node_ptr->data = data;
}

int SListIsEmpty(sll_t *list)
{
  assert(NULL != list);

  if(0 == SListSize(list))
  {
    return TRUE;
  }

  return FALSE;
}

size_t SListSize(sll_t *list)
{
  size_t count = 0;
  sll_iter_t iter = {0};

  assert(NULL != list);

  iter = list->head;

  while (list != iter.node_ptr->data)
  {
    iter.node_ptr = iter.node_ptr->next;
    ++count;
  }

  return count;
}

sll_iter_t SListFind(sll_iter_t from_iter, sll_iter_t to_iter,  void* data, sll_match_t match_func, void* usr_param)
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

int SListForEach(sll_iter_t from_iter, sll_iter_t to_iter, void* data, sll_action_t action_func, void* usr_param)
{
  sll_iter_t iter = {0};

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
           
sll_t* SListAppend(sll_t *dest, sll_t *src)
{
  /*iter_t iter = {0};
  iter_t iter2 = SListNext(iter);

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

int SListIterIsEqual(sll_iter_t iter1, sll_iter_t iter2)
{
  if((iter1.node_ptr == iter2.node_ptr))
  {
    return TRUE;
  }

  return FALSE;
}

sll_iter_t SListBegin(sll_t *list)
{
  assert(NULL != list);

  return list->head;
}

sll_iter_t SListEnd(sll_t *list)
{
  assert(NULL != list);
  
  return list->tail;
}

sll_iter_t SListNext(sll_iter_t iter)
{
  sll_iter_t iter_nxt = {0};

  iter_nxt.node_ptr = iter.node_ptr->next;

  return iter_nxt;
}

/*****************************************************************************/
/*************** Static Helper Functions Definitions ******************/
/*****************************************************************************/

static node_t* CreateDummy()
{
  node_t* dummy_node = (node_t*)malloc(sizeof(node_t));

  if(NULL == dummy_node)
  {
    return NULL;
  }

  return dummy_node;
}

static node_t* CreateNode()
{
  node_t* node = (node_t*)malloc(sizeof(node_t));

  if(NULL == node)
  {
    return NULL;
  }

  return node;
}
