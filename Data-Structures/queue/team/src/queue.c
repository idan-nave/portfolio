/*
  Name: Aya
  Project: Work Sheet 7 - Data Structures - Queue
  Reviewer: Idan
  Date: 16/08/23
  Version: 1.0
*/

/******************************** Libraries  *******************************/

#include "queue.h"
#include "sll.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void myforeach(queue_ty *queue, void* data, ActionFunc_ty action_func, void* usr_param, const char* str);
/******************************** Definitions  ******************************/

struct queue
{
  sll_ty *slist;
};

/*********************** Queue API Declerations  ****************************/
queue_ty* QueueCreate()
{
  queue_ty *queue = (queue_ty*)malloc(sizeof(queue_ty));
  if(NULL == queue)
  {
    return (queue_ty*)0;
  }

  queue->slist = SListCreate();
  if(NULL == queue->slist)
  {
    free(queue);
    queue = NULL;
    return (queue_ty*)0;
  }

  return queue;
}

void QueueDestroy(queue_ty *queue)
{
  assert(NULL != queue);

  SListDestroy(queue->slist);

  free(queue);
  queue = NULL;

  return;
}

size_t QueueGetSize(const queue_ty *queue)
{
  assert(NULL != queue);

  return SListCount(queue->slist);
}

int QueueIsEmpty(queue_ty *queue)
{
  assert(NULL != queue);

  return SListIsEmpty(queue->slist);
}

int Enqueue(queue_ty *queue, void* data)
{
  assert(NULL != queue);

  if(NULL == SListInsertBefore(SListEnd(queue->slist), data).node_ptr)
  {
    return FAILURE;
  }

  return SUCCESS;
}

void Dequeue(queue_ty *queue)
{
  assert(NULL != queue);

  SListRemove(SListBegin(queue->slist));

  return;
}

void *QueuePeek(const queue_ty *queue)
{
  assert(NULL != queue);

  return SListGetData(SListBegin(queue->slist));
}

void QueueAppend(queue_ty *dest, queue_ty *src)
{
  iter_ty iter = SListEnd(dest->slist);

  SListSetNext(iter, SListBegin(src->slist));
  SListSetTail(dest->slist, src->slist);
  SListSetData(SListEnd(dest->slist), SListGetData(SListEnd(src->slist)));
  SListRemove(iter);

  /*iter = SListEnd(dest->slist);*/
  
  free(src->slist);
  src->slist = NULL;
  free(src);
  src = NULL;
  return;
}


void myforeach(queue_ty *queue, void* data, ActionFunc_ty action_func, void* usr_param, const char* str)
{
  printf("List contents %s: ", str);
  SListForEach(SListBegin(queue->slist), SListEnd(queue->slist), data, action_func, usr_param);
  printf("\n");
}