/*
  Name: Idan Nave
  Project: MinStack
  Reviewer: XXX
  Date: 28/08/23
  Version: 1.0
*/

/**************** Libraries  *****************/

#include <stdio.h>                /*printf*/
#include <stdlib.h>               /* malloc(), free() */
#include <errno.h>                /* errno global */
#include <stddef.h>               /* size_t, NULL */

#include "min_stack.h"  

/**************** Definitions  ****************/

/* Size Definition */
#define STACK_CAPACITY 10  
#define STACK_ELEM_SIZE 1  


/*
the min_stack_t structure is used to maintain both the 
original stack and the min stack. The MinStackPush function 
updates the min stack whenever a new element is pushed onto 
the original stack, and the MinStackPop function ensures 
that the corresponding element is popped from both stacks.
The MinStackGetMin function provides access to the current 
minimum value in O(1) time complexity.
*/

int main()
{
    min_stack_t *min_stack = MinStackCreate(100, sizeof(int));
    if (!min_stack)
    {
        printf("Failed to create Min Stack.\n");
        return 1;
    }

    MinStackPush(min_stack, 3);
    /*MinStackPush(min_stack, 5);
    MinStackPush(min_stack, 2);
    MinStackPush(min_stack, 1);

    printf("Minimum value: %d\n", MinStackGetMin(min_stack));

    MinStackPop(min_stack);
    printf("Minimum value: %d\n", MinStackGetMin(min_stack));

    MinStackDestroy(min_stack);*/

    return 0;
}
/*Should print 1*/
/*Should print 2*/