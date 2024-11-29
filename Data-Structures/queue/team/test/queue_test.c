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

void QueueSize_Test(queue_ty *queue, const char* str);
int PrintData(void* data, void* param);


/******************************** Definitions  ******************************/
int main()
{
  queue_ty *queue1 = QueueCreate();
  queue_ty *queue2 = QueueCreate();
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

  QueueAppend(queue1, queue2);

  myforeach(queue1, NULL, PrintData, NULL,"(After append)");
  QueueDestroy(queue1);

  return 0;
}

void QueueSize_Test(queue_ty *queue, const char* str)
{
  printf("size of the queue_ty %s: %ld\n", str, QueueGetSize(queue));
}

int PrintData(void* data, void* param)
{
    printf("%d ", *(int*)data);
    fflush(stdout);
    return SUCCESS;
}