/*Name: Aya
  Project: Stack Implementation
  Reviewer: Idan
  Date: 10/08/2023
  Version: 1.0
*/
/******************************************************************************/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/

#include "stack.h"

struct stack
{
  size_t capacity;
  size_t size;
  size_t element_size;
  char *stack_arr;
};

/******************************************************************************/

stack_ty *StackCreate(size_t capacity, size_t element_size)
{
  stack_ty *initialized_stack = (stack_ty*)malloc(sizeof(stack_ty));
  if(NULL == initialized_stack)
  {
    return NULL;
  }

  initialized_stack->capacity = capacity;
  initialized_stack->size = 0;
  initialized_stack->element_size = element_size;

  initialized_stack->stack_arr = (char*)malloc(sizeof(char) * capacity * element_size);
  if(NULL == initialized_stack->stack_arr)
  {
    return NULL;
  }

  return initialized_stack;
}

/******************************************************************************/

void StackDestroy(stack_ty *stack)
{
  assert(stack);

  free(stack->stack_arr);
  stack->stack_arr = NULL;

  free(stack);
  stack = NULL;
}

/******************************************************************************/

void StackPop(stack_ty *stack)
{
  assert(stack);

  if(0 < stack->size)
  {
    --stack->size;
  }
}

/******************************************************************************/

void StackPush(stack_ty *stack, const void *data)
{
  assert(stack);

  if(stack->size < stack->capacity)
  {
    size_t index = 0;
    ++stack->size;
    index = stack->size * stack->element_size;
    memcpy(stack->stack_arr + index, data, stack->element_size);
  }
}

/******************************************************************************/

void *StackPeek(const stack_ty *stack)
{
  assert(stack);

  if(0 < stack->size)
  {
    size_t index = stack->size * stack->element_size;
    return (stack->stack_arr + index);
  }
  
  return (void*)0;
}

/******************************************************************************/

size_t StackSize(const stack_ty *stack)
{
  assert(stack);

  return stack->size;
}

/******************************************************************************/

int StackIsEmpty(const stack_ty *stack)
{
  assert(stack);

  return stack->size == 0 ? TRUE : FALSE;
}

/******************************************************************************/

size_t StackCapacity(const stack_ty *stack)
{
  assert(stack);

  return stack->capacity;
}