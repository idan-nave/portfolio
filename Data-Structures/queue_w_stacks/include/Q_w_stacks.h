/*
  Name: Idan Nave
  Project: Quizz - Data Structures - Q With Stacks
  Reviewer: XXX
  Date: 12/08/23
  Version: 1.0

  Project Overview: API for using a Q With Stacks
*/

#ifndef __ILRD_Q_WITH_STACK_H__
#define __ILRD_Q_WITH_STACK_H__

/******************************** Libraries  *******************************/

#include <stddef.h> /*size_t*/
#include "stack.h"  

/******************************** Definitions  ******************************/

typedef struct Q_w_stacks queue_t;
#define NO_ERROR 0 

/*********************** Queue API Declarations ****************************/

/*Function that inits the Queue struct
  Return value: pointer of type queue_t, if unsuccessful malloc(), returns NULL;
  Undefined B.: N.A */
queue_t *QueueCreate(size_t stack_capacity, size_t element_size);

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
int Enqueue(queue_t *queue, const void *data);

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


#endif /*(__ILRD_Q_WITH_STACK_H__)*/
