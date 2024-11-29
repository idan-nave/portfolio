/*
  Name: Idan Nave
  Project: Quizz - Data Structures - MinStack
  Reviewer: XXX
  Date: 28/08/23
  Version: 1.0

  Project Overview: API for using a MinStack Data Structure.
*/

/******************************** Libraries  *********************************/

#include <assert.h> 	        /* assert() */
#include <stdio.h>  	       	/* FILEs, perror*/
#include <stdlib.h> 	      	/* malloc(), free() */
#include <string.h>             /* memcpy, string manipulation */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */
#include <limits.h>

#include "min_stack.h" 	
#include "stack.h"  

#define STACK_META_OFFSET 3*sizeof(size_t)

/*****************************************************************************/
/**************************** Testing Data-structures ************************/
/*****************************************************************************/

  /******************************** TypeDefs  *******************************/

struct min_stack
{
    /* Original stack */
    stack_t *original_stack;

    /* Stack to keep track of minimum values */
    stack_t *min_stack;
};

/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/
/* Function to create a new Min Stack */
min_stack_t *MinStackCreate(size_t capacity, size_t element_size)
{
    min_stack_t *min_stack = (min_stack_t *)malloc(sizeof(min_stack_t));
    if (!min_stack)
    {
        return NULL; /* Memory allocation failed */
    }

    min_stack->original_stack = StackCreate(capacity, element_size);
    if (!min_stack->original_stack)
    {
        free(min_stack);
        return NULL; /* Failed to create the original stack */
    }

    min_stack->min_stack = StackCreate(capacity, sizeof(int));
    if (!min_stack->min_stack)
    {
        StackDestroy(min_stack->original_stack);
        free(min_stack);
        return NULL; /* Failed to create the min stack */
    }

    return min_stack;
}

/* Function to destroy a Min Stack */
void MinStackDestroy(min_stack_t *min_stack)
{
    if (min_stack)
    {
        StackDestroy(min_stack->original_stack);
        StackDestroy(min_stack->min_stack);
        free(min_stack);
    }
}

/* Function to push an element onto the Min Stack */
int MinStackPush(min_stack_t *min_stack, int data)
{
    int push_status = 0;
    int current_min = 0;

    assert(NULL != min_stack);

    /* Push the element onto the original stack */
    push_status = StackPush(min_stack->original_stack, &data);
    if (push_status != SUCCESS) 
    {
        return push_status;
    }

    /* Update the min stack with the new minimum value */
    if (StackIsEmpty(min_stack->min_stack))
    {
        current_min = data;
    }
    else
    {
        int *min_ptr = StackPeek(min_stack->min_stack);
        current_min = *min_ptr;
        if (data < current_min) {
            current_min = data;
        }
    }
    StackPush(min_stack->min_stack, &current_min);

    return SUCCESS;
}

/* Function to pop an element from the Min Stack */
int MinStackPop(min_stack_t *min_stack)
{
    assert(NULL != min_stack);

    /* Pop the element from the original stack */
    if (StackSize(min_stack->original_stack) == 0)
    {
        return FAILURE; /* Stack is empty */
    }

    StackPop(min_stack->original_stack);
    StackPop(min_stack->min_stack);

    return SUCCESS;
}

/* Function to get the minimum value from the Min Stack */
int MinStackGetMin(const min_stack_t *min_stack)
{
    int *min_ptr = NULL;
    assert(NULL != min_stack);
    
    if (StackIsEmpty(min_stack->min_stack))
    {
        return INT_MAX; /* Invalid or empty stack */
    }

    min_ptr = StackPeek(min_stack->min_stack);
    return *min_ptr;
}