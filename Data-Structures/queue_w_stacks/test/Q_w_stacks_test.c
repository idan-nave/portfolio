/*
  Name: Idan Nave
  Project: Quizz - Data Structures - Q With Stacks
  Reviewer: XXX
  Date: 12/08/23
  Version: 1.0

  Project Overview: API for using a Q With Stacks
*/

/**************** Libraries  *****************/

#include <stdio.h>                /*printf*/
#include <stdlib.h>               /* malloc(), free() */
#include <errno.h>                /* errno global */
#include <stddef.h>               /* size_t, NULL */

#include "Q_w_stacks.h"  

/**************** Definitions  ****************/

int main()
{
    queue_t *queue = QueueCreate(100, sizeof(int));

    int data = 42;

    Enqueue(queue, &data);  /*Enqueue an element*/
    Dequeue(queue);         /*Dequeue an element*/

    QueueDestroy(queue);

    return 0;
}