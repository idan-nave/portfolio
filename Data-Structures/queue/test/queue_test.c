/****************************** Test_ws6_sll.c  **************************/
/*
  Name: Idan Nave
  Project: Work Sheet 6 - Data Structures - Singly Linked LIst
  Reviewer: ???
  Date: 12/08/23
  Version: 1.0
*/

/******************************** Libraries  **********************************/

#include <assert.h>               /* assert() */
#include <stdio.h>                /* FILEs, stderr, stdin, stdout, perror */
#include <stdlib.h>               /* malloc(), free() */
#include <string.h>               /* string manipulation */
#include <errno.h>                /* errno global */
#include <ctype.h>                /* isalpha, isdigit, isspace */
#include <stddef.h>               /* size_t, NULL */

#include "sll.h"    
#include "queue.h"           

/******************************* Definitions  ********************************/

/* Size Definition */

/*****************************************************************************/
/**************************** App's Data-structures **************************/
/*****************************************************************************/

  /******************************** TypeDefs  *******************************/
struct queue
{
    sll_t* slist;
};

/*****************************************************************************/
/**************** Forward Declarations of Static Functions *******************/
/*****************************************************************************/
void QueueSize_Test(queue_t *queue, const char* str);
int PrintData(void* data, void* param);


/******************************** Definitions  ******************************/
int main()
{
  queue_t *queue1 = QueueCreate();
  queue_t *queue2 = QueueCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;

  int data4_queue2 = 33;
  int data5_queue2 = 23;
  int data6_queue2 = 1;
  int data7_queue2 = 9;

  Enqueue(queue2, &data6_queue2);
  Enqueue(queue2, &data5_queue2);
  Enqueue(queue2, &data7_queue2);
  Enqueue(queue2, &data4_queue2);

  /*Test Insert*/
  QueueSize_Test(queue1, "");
  Enqueue(queue1, &data6);
  Enqueue(queue1, &data5);
  Enqueue(queue1, &data7);
  Enqueue(queue1, &data4);
  QueueSize_Test(queue1, "After Inserting 4 elements");
  printf("\n");

  myforeach(queue1, NULL, PrintData, NULL, "of queue1");
  myforeach(queue2, NULL, PrintData, NULL,"of queue2");

  Dequeue(queue1);
  QueueSize_Test(queue1, "After remove the head");
  myforeach(queue1, NULL, PrintData, NULL,"(After remove the head)");

/*  queue1 = QueueAppend(queue1, queue2);
*/
  myforeach(queue1, NULL, PrintData, NULL,"(After append)");
  QueueDestroy(queue1);
  return 0;
}

void QueueSize_Test(queue_t *queue, const char* str)
{
  printf("size of the queue_t %s: %ld\n", str, QueueGetSize(queue));
}

int PrintData(void* data, void* param)
{
    printf("%d ", *(int*)data);
    fflush(stdout);
    return SUCCESS;
}