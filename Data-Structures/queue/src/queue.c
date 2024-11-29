/********************************** ws6_sll.c  ***************************/
/*
  Name: Idan Nave
  Project: Work Sheet 7 - Queue
  Reviewer: Uri
  Date: 16/08/23
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <stdio.h>              /* FILEs, stderr, stdin, stdout, perror */
#include <stdlib.h>             /* malloc(), free() */
#include <string.h>             /* string manipulation */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */
#include <stddef.h>             /* size_t, NULL */

#include "sll.h"    
#include "queue.h" 		

/*****************************************************************************/
/**************************** Type Definitions ************************/
/*****************************************************************************/
 
  /******************************** TypeDefs  *******************************/
/*Struct  */
struct queue
{
    sll_t* slist;
};

void myforeach(queue_t *queue, void* data, sll_action_t action_func, void* usr_param, const char* str);
/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/

/*Function that inits the Queue struct
  Return value: pointer of type queue_t, if unsuccessful malloc(), returns NULL;
  Undefined B.: N.A */
queue_t* QueueCreate()
{ 
    queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
    if(NULL == queue)
    {
      return (queue_t*)0;
    }

    queue->slist = SListCreate();
    if(NULL == queue->slist)
    {
      free(queue);
      queue = NULL;
      return (queue_t*)0;
    }
    return queue;
}
/*Function that destroys the Queue struct
  Arguments: Queue pointer
  Return value: N.A
  Undefined B.: NULL queue_t ptr */
void QueueDestroy(queue_t *queue)
{
    assert(NULL != queue);
    SListDestroy(queue->slist);
    free(queue);
    queue = NULL;
}

/*Function that returns queue nodes count
  Arguments: Queue ptr
  Return value: node count
  Undefined B.: NULL queue_t ptr */
size_t QueueGetSize(const queue_t* queue)
{
  assert(NULL != queue);
  return SListSize(queue->slist);
}

/*Function that checks whether the queue is empty
  Arguments: Queue ptr
  Return value: EMPTY = 1, NOT_EMPTY = 0
  Undefined B.: NULL queue_t ptr */
int QueueIsEmpty(queue_t *queue)
{
  assert(NULL != queue);
  return SListIsEmpty(queue->slist);
}
/*Function that appends a node to the rear of the queue.
  Arguments: queue_t pointer, Data
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: NULL queue_t pointer */
int Enqueue(queue_t *queue, void* data)
{                                     /*gives tail*/
    sll_iter_t iter = {0};
    assert(NULL != queue);
    iter = SListInsertBefore(SListEnd(queue->slist), data);
    if(NULL == iter.node_ptr)
    {
        return FAILURE;
    }
    return SUCCESS;
}

/*Function that removes the front node from the queue
  Arguments: queue_t pointer
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: NULL queue_t pointer */
int Dequeue(queue_t *queue)
{                                     /*gives tail*/
    sll_iter_t iter = {0};
    assert(NULL != queue);
    iter = SListRemove(SListBegin(queue->slist));/*gives head*/
    if(NULL == iter.node_ptr)
    {
        return FAILURE;
    }
    return SUCCESS;
}

/*Function that retrieves the front node's value
  Arguments: queue_t pointer 
  Return value: void* data
  Undefined B.: NULL queue_t pointer */
void *QueuePeek(const queue_t *queue)
{
    return SListGetData(SListBegin(queue->slist));/*gives head*/
}

/*Function that appends all elements from src queue, in order, and appends 
 * them to the end of dest queue. The src queue is left empty.
  Arguments: 2 queues
  Return value: apended queues and frees src
  Undefined B.: NULL queue pointers */

/*queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
  assert(NULL != dest);
  assert(NULL != src);

  SListMerge(dest->slist, src->slist);

  free(src->slist);
  free(src);
  return dest;
}*/

void myforeach(queue_t *queue, void* data, sll_action_t action_func, void* usr_param, const char* str)
{
  printf("List contents %s: ", str);
  SListForEach(SListBegin(queue->slist), SListEnd(queue->slist), data, action_func, usr_param);
  printf("\n");
}