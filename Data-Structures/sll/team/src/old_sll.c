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
#include <stdio.h>

#include "sll.h"

/******************************** Definitions  ********************************/

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
  sll_ty *list = (sll_ty*)malloc(sizeof(sll_ty));
  iter_ty head_iter = {0};
  iter_ty tail_iter = {0};

  head_iter.node_ptr = (node_ty*)malloc(sizeof(node_ty));
  tail_iter.node_ptr = (node_ty*)malloc(sizeof(node_ty));

  list->head = head_iter;
  list->tail = tail_iter;

  list->head.node_ptr->next = list->tail.node_ptr;
  list->tail.node_ptr->data = list;

  return list;
}

void SListDestroy(sll_ty *list)
{
  assert(NULL != list);

  free(list);
  list = NULL;
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
    ((sll_ty*)iter_new.node_ptr->data)->tail = iter_new;
  }

  return iter;
}

/*TODO: to test*/
void SListRemove(iter_ty iter)
{
  node_ty *to_remove = {0};

  assert(NULL != iter.node_ptr);

  /*Ensure there's a node after the current one*/
  if (NULL != iter.node_ptr->next)
  {
    to_remove = iter.node_ptr->next;
    /*Move data of the next node to the current one*/
    iter.node_ptr->data = to_remove->data;  
    /*Update the next pointer to skip the next node*/
    iter.node_ptr->next = to_remove->next;  
    /*Free the memory of the removed node*/
    free(to_remove);
  }
}

void *SListGetData(iter_ty iter)
{
  return iter.node_ptr->data;
}

void SListSetData(iter_ty iter, void* data)
{
  assert(NULL != data);

  iter.node_ptr->data = data;
}

/*TODO: to imp and test*/
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

  while (NULL != iter.node_ptr->next)
  {
    iter.node_ptr = iter.node_ptr->next;
    ++count;
  }

  --count;

  return count;
}

iter_ty SListFind(sll_ty *list, void* data, MatchFunc_ty match_func, void* usr_param)
{
  iter_ty iter = {0};

  assert(NULL != match_func);
  assert(NULL != list);

  iter = list->head;

  while (FALSE == SListIterIsEqual(iter, SListEnd(list)))
  {
    if (match_func(iter.node_ptr->data, data))
    {
        return iter;
    }
    iter = SListNext(iter);
  }

  return SListEnd(list); /*Return end iterator if not found*/
}

int SListForEach(iter_ty from_iter, iter_ty to_iter, void* data, ActionFunc_ty action_func, void* usr_param)
{
  iter_ty iter = {0};
  int i = 0;
  assert(NULL != action_func);

  iter = from_iter;

  printf("to_iterator: %d, from_iterator: %d\n", *(int*)SListGetData(to_iter), *(int*)SListGetData(from_iter));
  /*while (NULL != iter.node_ptr && FALSE == SListIterIsEqual(iter, to_iter))*/
  while (iter.node_ptr != to_iter.node_ptr)
  {
    printf("\t\t%dto_iterator: %p, from_iterator: %p\n",i, to_iter.node_ptr, iter.node_ptr);
    if (action_func(iter.node_ptr->data, usr_param) != SUCCESS)
    {
        return FAILURE; /*Stop iterating if the action fails*/
    }
    iter.node_ptr = iter.node_ptr->next;
    printf("\t\tthe next of from_iterator: %p\n", iter.node_ptr);
    fflush(stdout);
    ++i;
  }

  printf("SUCCESS");
  fflush(stdout);
  return SUCCESS;
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
  printf("%d\n", *(int*)(iter_nxt.node_ptr->data));
   fflush(stdout);
  return iter_nxt;
}