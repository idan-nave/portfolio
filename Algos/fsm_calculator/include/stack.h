/*
  Project: Work Sheet #4 - Data Structures - Stack
  Reviewer: Dima
  Date: 12/08/23
  Version: 1.0

  Project Overview: API for using a Stack Data Structure.
*/

#ifndef __ILRD_STACK_H__
#define __ILRD_STACK_H__

/******************************** Libraries  *******************************/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

typedef enum 
  {SUCCESS = 0, FAILURE = 1, EMPTY = 0, NOT_EMPTY = 1} stack_status_t;
typedef struct stack stack_t;
#define NO_ERROR 0 

/****************************************************************************/

/*Function that inits the stack struct
  Arguments: capacity of the stack, element size.
  Return value: pointer to the created stack struct
  Complexity: O(1). 
  Undefined B.: element_size = 0, capacity = 0 */
stack_t *StackCreate(size_t capacity, size_t element_size);

/*Function that deletes the stack struct
  Arguments: pointer to the stack struct.
  Return value: void.
  Complexity: O(1). 
  Undefined B.: NULL ptr of stack */
void StackDestroy(stack_t *stack);

/*Function that removes the head of the stack struct
  Arguments: pointer to the stack struct.
  Return value: SUCCESS / FAILURE
  Complexity: O(1). 
  Undefined B.: NULL ptr of stack */
int StackPop(stack_t *stack);

/*Function that adds data to the head of the stack struct
  Arguments: pointer to the stack struct, data to be added.
  Return value: SUCCESS / FAILURE
  Complexity: O(1). 
  Undefined B.: size of data > element_size, NULL ptr of stack */
int StackPush(stack_t *stack, const void *data);

/*Function that gets the data of the head of the stack struct
  Arguments: pointer to the stack struct.
  Return value: void* that represent the data.
  Complexity: O(1). 
  Undefined B.: NULL ptr of stack */
void *StackPeek(const stack_t *stack);

/*Function that returns the size of the stack struct
  Arguments: pointer to the stack struct.
  Return value: size of the stack struct.
  Complexity: O(1). 
  Undefined B.: NULL ptr of stack */
size_t StackSize(const stack_t *stack);

/*Function that checks if the stack struct is empty
  Arguments: pointer to the stack struct.
  Return value: EMPTY = 0, NOT_EMPTY = 1
  Complexity: O(1). 
  Undefined B.: NULL ptr of stack */
int StackIsEmpty(const stack_t *stack);

/*Function that returns the capacity of the stack struct
  Arguments: pointer to the stack struct.
  Return value: capacity of the stack struct.
  Complexity: O(1). 
  Undefined B.: NULL ptr of stack */
size_t StackCapacity(const stack_t *stack);

#endif /*(__ILRD_STACK_H__)*/
