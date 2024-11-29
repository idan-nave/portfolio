/*Name: HRD 32
  Project: Work Sheet 7 - Data Structures - Singly Linked LIst
  Reviewer: Liel
  Date: 16/08/23
  Version: 1.0
*******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

/*********************************Libraries************************************/

#include <stddef.h> /*size_t*/

/********************************Definitions***********************************/
typedef struct element_struct element_ty;
typedef struct queue_struct queue_ty;

/******************************API Declerations********************************/

/*Create a queue*/
queue_ty* QueueCreate();
/*Destroy a queue*/
void QueueDestroy(queue_ty *queue);
/*Count the number of elements in the queue*/
size_t QueueSize(queue_ty *queue);
/*Checks if the queue is empty*/
int QueueIsEmpty(queue_ty *queue);
/*Adds an element to back*/
void QueueEnqueue(queue_ty *queue, void *data);
/*Removes an element from front*/
void QueueDequeue(queue_ty *queue);
/*Retrieves the data from front element*/
void *QueuePeek(queue_ty *queue);
/*Change the data of first element*/
queue_ty *QueueAppend(queue_ty *queue_front, queue_ty *queue_back);


#endif /*(__QUEUE_H__)*/
