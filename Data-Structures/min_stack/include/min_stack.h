/*
  Name: Idan Nave
  Project: Quizz - Data Structures - MinStack
  Reviewer: XXX
  Date: 28/08/23
  Version: 1.0

  Project Overview: API for using a MinStack Data Structure.
*/

#ifndef __ILRD_MIN_STACK_H__
#define __ILRD_MIN_STACK_H__

/******************************** Libraries  *******************************/

#include <stddef.h> /*size_t*/
#include "stack.h"  

/******************************** Definitions  ******************************/

typedef struct min_stack min_stack_t;
/*typedef enum 
  {SUCCESS = 0, FAILURE = 1, EMPTY = 0, NOT_EMPTY = 1} min_stack_status_t;
#define NO_ERROR 0 */

/****************************************************************************/

/*Function to create a new Min Stack 
  Arguments: capacity of the stack, element size.
  Return value: pointer to the created stack struct
  Complexity: O(1). 
  Undefined B.: element_size = 0, capacity = 0 */
min_stack_t *MinStackCreate(size_t capacity, size_t element_size);

/*Function to destroy a Min Stack 
  Arguments: pointer to the stack struct.
  Return value: void.
  Complexity: O(1). 
  Undefined B.: NULL ptr of stack */
/* Function to destroy a Min Stack */
void MinStackDestroy(min_stack_t *min_stack);

/*Function to pop an element from the Min Stack
  Arguments: pointer to the stack struct.
  Return value: SUCCESS / FAILURE
  Complexity: O(1). 
  Undefined B.: NULL ptr of stack */
int MinStackPop(min_stack_t *min_stack);

/* Function to push an element onto the Min Stack
  Arguments: pointer to the stack struct, data to be added.
  Return value: SUCCESS / FAILURE
  Complexity: O(1). 
  Undefined B.: size of data > element_size, NULL ptr of stack */
int MinStackPush(min_stack_t *min_stack, int data);

/*Function to get the minimum value from the Min Stack
  Arguments: pointer to the stack struct.
  Return value: void* that represent the data.
  Complexity: O(1). 
  Undefined B.: NULL ptr of stack */
int MinStackGetMin(const min_stack_t *min_stack);

#endif /*(__ILRD_MIN_STACK_H__)*/
