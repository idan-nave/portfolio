/*
  Name: Idan Nave
  Project: Work Sheet #4 - Data Structures - Stack
  Reviewer: Dima
  Date: 12/08/23
  Version: 1.0 - publish
  		   1.1 - small convention fixes
*/

/******************************** Libraries  *********************************/

#include <assert.h> 	        /* assert() */
#include <stdio.h>  	       	/* FILEs, perror*/
#include <stdlib.h> 	      	/* malloc(), free() */
#include <string.h>             /* memcpy, string manipulation */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */

#include "stack.h" 	

#define STACK_META_OFFSET 3*sizeof(size_t)

/*****************************************************************************/
/**************************** Testing Data-structures ************************/
/*****************************************************************************/

  /******************************** TypeDefs  *******************************/

struct stack
{
    size_t capacity;
    size_t element_size;
    size_t size;
    char *stack_arr;
};

/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/

stack_t *StackCreate(size_t capacity, size_t element_size)
{
    /* init stack with one malloc, element 0 will remain out of use*/
    size_t stack_capacity = (sizeof(char)) * (capacity) * element_size;
    stack_t* new_stack = (stack_t*)malloc(sizeof(stack_t));

    /* validate successful malloc*/
    if(NULL== new_stack)
    {
        errno = ENOMEM;
        perror("Unsuccessful allocation of new stack");
        return NULL;
    }

    /* init stack fields*/
    new_stack->capacity = capacity;
    new_stack->element_size = element_size;
    new_stack->size = 0; /*element 0 is used as empty marker */
    /* stack array always points to bottom of stack_t data manager  */

    new_stack->stack_arr = (char*)malloc(sizeof(char) * capacity * element_size);
    if(NULL== new_stack->stack_arr)
    {
        free(new_stack);
        new_stack = NULL;
        errno = ENOMEM;
        perror("Unsuccessful allocation of new stack");
        return NULL;
    }

    return new_stack;
}

void StackDestroy(stack_t *stack)
{
    assert(NULL != stack);
    
    free(stack->stack_arr);
    stack->stack_arr = NULL;
    
    free(stack);
    stack = NULL;
}

int StackPop(stack_t *stack)
{
    assert(NULL != stack);
    /* nothing topop */
    if (0 == stack->size)
    {
        errno = EPERM;
        perror("no element left to pop");
        return FAILURE;
    }

    /* update size */
    --(stack->size);
    return SUCCESS; 
}

int StackPush(stack_t *stack, const void *data)
{
    size_t head_idx = 0;

    assert(NULL != stack);
    if (stack->size == stack->capacity)
    {
        errno = EPERM;
        perror("capacity overflow reached");
        return FAILURE;
    }

    /* update head size */  
    ++(stack->size); 
    /* calculate head offset */
    head_idx = (stack->size)*(stack->element_size);
    /* perform data write */
    memcpy( stack->stack_arr + head_idx, data ,stack->element_size);

    return SUCCESS; 
}

void *StackPeek(const stack_t *stack)
{
    size_t head_idx = 0;
    
    assert(NULL != stack);
    /* nothing to peek at */
    if (0 == stack->size)
    {
        return (void*)0;
    }
    /* calculate head offset */
    head_idx = (stack->size)*(stack->element_size);

    return  (void *)(stack->stack_arr + head_idx);
}

size_t StackSize(const stack_t *stack)
{
    assert(NULL != stack);
    return stack->size;
}

int StackIsEmpty(const stack_t *stack)
{
    assert(NULL != stack);
    return !(0 == StackSize(stack));
}

size_t StackCapacity(const stack_t *stack)
{
    return stack->capacity;
}