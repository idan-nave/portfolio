/*
  Project: Quizz - Data Structures - Q With Stacks
  Reviewer: XXX
  Date: 12/08/23
  Version: 1.0

  Project Overview: API for using a Q With Stacks
*/

/******************************** Libraries  *********************************/

#include <assert.h> 	        /* assert() */
#include <stdio.h>  	       	/* FILEs, perror*/
#include <stdlib.h> 	      	/* malloc(), free() */
#include <string.h>             /* memcpy, string manipulation */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */
#include <limits.h>

#include "Q_w_stacks.h" 	
#include "stack.h"  

/*****************************************************************************/
/**************************** Testing Data-structures ************************/
/*****************************************************************************/

  /******************************** TypeDefs  *******************************/

struct Q_w_stacks
{
    stack_t *stack1; /* For enqueue operations  */
    stack_t *stack2; /* For dequeue operations */
};

/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/

queue_t *QueueCreate(size_t stack_capacity, size_t element_size)
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    if (!queue) 
    {
        return NULL;
    }

    queue->stack1 = StackCreate(stack_capacity, element_size);
    queue->stack2 = StackCreate(stack_capacity, element_size);

    if (!queue->stack1 || !queue->stack2)
    {
        free(queue->stack1);
        free(queue->stack2);
        free(queue);
        return NULL;
    }

    return queue;
}

void QueueDestroy(queue_t *queue) {
    if (queue)
    {
        StackDestroy(queue->stack1);
        StackDestroy(queue->stack2);
        free(queue);
    }
}

size_t QueueGetSize(const queue_t *queue)
{
    return queue ? StackSize(queue->stack1) + StackSize(queue->stack2) : 0;
}

int QueueIsEmpty(queue_t *queue)
{
    return QueueGetSize(queue) == 0;
}

int Enqueue(queue_t *queue, const void *data)
{
    assert(NULL != queue);

    return StackPush(queue->stack1, data);
}

int Dequeue(queue_t *queue)
{
    assert(NULL != queue);

    if (StackIsEmpty(queue->stack2))
    {
        while (!StackIsEmpty(queue->stack1))
        {
            void *element = StackPeek(queue->stack1);
            StackPop(queue->stack1);
            StackPush(queue->stack2, element);
        }
    }

    return StackPop(queue->stack2);
}

void *QueuePeek(const queue_t *queue)
{
    assert(NULL != queue);

    if (StackIsEmpty(queue->stack2))
    {
        while (!StackIsEmpty(queue->stack1))
        {
            void *element = StackPeek(queue->stack1);
            StackPop(queue->stack1);
            StackPush(queue->stack2, element);
        }
    }

    return StackPeek(queue->stack2);
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
    assert(NULL != dest);
    assert(NULL != src);

    while (!StackIsEmpty(src->stack1))
    {
        void *element = StackPeek(src->stack1);
        StackPop(src->stack1);
        StackPush(dest->stack1, element);
    }

    return dest;
}

