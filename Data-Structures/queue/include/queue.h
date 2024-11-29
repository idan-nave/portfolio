/*
  Name: HRD 32
  Project: Work Sheet 7 - Data Structures - Queue
  Reviewer: Liel
  Date: 16/08/23
  Version: 1.0
*/

#ifndef __ILRD_QUEUE_H__
#define __ILRD_QUEUE_H__

/******************************** Libraries  *******************************/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

typedef struct queue queue_t;

/*typedef enum  {SUCCESS = 1, FAILURE = 0} status_t;
typedef enum {TRUE = 1, FALSE = 0} boolean_t;*/

/*********************** Queue API Declerations  ****************************/

/*Function that inits the Queue struct
  Return value: pointer of type queue_t, if unsuccessful malloc(), returns NULL;
  Undefined B.: N.A */
queue_t* QueueCreate();

/*Function that destroys the Queue struct
  Arguments: Queue pointer
  Return value: N.A
  Undefined B.: NULL queue_t ptr */
void QueueDestroy(queue_t *queue);

/*Function that returns queue nodes count
  Arguments: Queue ptr
  Return value: node count
  Undefined B.: NULL queue_t ptr */
size_t QueueGetSize(const queue_t *queue);

/*Function that checks whether the queue is empty
  Arguments: Queue ptr
  Return value: EMPTY = 1, NOT_EMPTY = 0
  Undefined B.: NULL queue_t ptr */
int QueueIsEmpty(queue_t *queue);

/*Function that appends a node to the rear of the queue.
  Arguments: queue_t pointer, Data
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: NULL queue_t pointer */
int Enqueue(queue_t *queue, void* data);

/*Function that removes the front node from the queue
  Arguments: queue_t pointer
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: NULL queue_t pointer */
int Dequeue(queue_t *queue);

/*Function that retrieves the front node's value
  Arguments: queue_t pointer 
  Return value: void* data
  Undefined B.: NULL queue_t pointer */
void *QueuePeek(const queue_t *queue);

/*Function that appends all elements from src queue, in order, and appends 
 * them to the end of dest queue. The src queue is left empty.
  Arguments: 2 queues
  Return value: apended queue
  Undefined B.: NULL queue pointers */
queue_t *QueueAppend(queue_t *dest, queue_t *src);

#endif /*(__ILRD_QUEUE_H__)*/
























