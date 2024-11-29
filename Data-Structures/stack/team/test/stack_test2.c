/*Name: Aya
  Project: Stack Implementation
  Reviewer: Idan
  Date: 10/08/2023
  Version: 1.0
*/
/******************************************************************************/
#include <stdio.h> /*printf*/

#include "stack.h"

int RunProg();

void StackPushInt_test(stack_t *stack, const void *data, size_t index);
void StackPushChr_test(stack_t *stack, const void *data, size_t index);
void StackPushDouble_test(stack_t *stack, const void *data, size_t index);

void StackPopInt_test(stack_t *stack);
void StackPopChr_test(stack_t *stack);
void StackPopDouble_test(stack_t *stack);

/******************************************************************************/

int main()
{
  return RunProg();
}

/******************************************************************************/

int RunProg()
{
  stack_t *my_new_stack = StackCreate(100,23);
  int data1[] = {4,5,7};
  char data2[] = {'A','G'};
  double data3[] = {7.5,6.6};

  char str[5] = "hell";
  size_t i = 0;

  printf("\nCreate stack\n");
  printf("\tsize: %ld\n", StackSize(my_new_stack)); 
  printf("\tIsEmpty: %s\n", StackIsEmpty(my_new_stack) == 0 ? "FALSE" : "TRUE"); 
  printf("\tcapacity: %ld\n", StackCapacity(my_new_stack));

  for(i = 0; 3 > i; ++i)
  {
    StackPushInt_test(my_new_stack, &data1[i], i);
  }

  for(i = 0; 2 > i; ++i)
  {
    StackPushChr_test(my_new_stack, &data2[i], i);
  }

  for(i = 0; 2> i; ++i)
  {
    StackPushDouble_test(my_new_stack, &data3[i], i);
  }

  StackPopDouble_test(my_new_stack);


  StackPush(my_new_stack, str);
  printf("\tstack head: %s\n", (char*)StackPeek(my_new_stack));
  printf("\tsize: %ld\n", StackSize(my_new_stack)); 
  printf("\tIsEmpty: %s\n", StackIsEmpty(my_new_stack) == 0 ? "FALSE" : "TRUE");


  StackDestroy(my_new_stack);
  printf("\nDestroy the stack\n");
  return 0;

}

/******************************test Push**************************************/

void StackPushInt_test(stack_t *stack, const void *data, size_t index)
{
  StackPush(stack, data);
  printf("\n%ld int Push to stack\n", index);
  printf("\tstack head: %d\n", *(int*)StackPeek(stack));
  printf("\tsize: %ld\n", StackSize(stack)); 
  printf("\tIsEmpty: %s\n", StackIsEmpty(stack) == 0 ? "FALSE" : "TRUE"); 
}

void StackPushChr_test(stack_t *stack, const void *data, size_t index)
{
  StackPush(stack, data);
  printf("\n%ld char Push to stack\n", index);
  printf("\tstack head: %c\n", *(char*)StackPeek(stack));
  printf("\tsize: %ld\n", StackSize(stack)); 
  printf("\tIsEmpty: %s\n", StackIsEmpty(stack) == 0 ? "FALSE" : "TRUE"); 
}

void StackPushDouble_test(stack_t *stack, const void *data, size_t index)
{
  StackPush(stack, data);
  printf("\n%ld double Push to stack\n", index);
  printf("\tstack head: %f\n", *(double*)StackPeek(stack));
  printf("\tsize: %ld\n", StackSize(stack)); 
  printf("\tIsEmpty: %s\n", StackIsEmpty(stack) == 0 ? "FALSE" : "TRUE"); 
}

/****************************test Pop*************************************/

void StackPopInt_test(stack_t *stack)
{
  StackPop(stack);
  printf("\nPop from stack\n");
  printf("\tstack head: %d\n", *(int*)StackPeek(stack));
  printf("\tsize: %ld\n", StackSize(stack)); 
  printf("\tIsEmpty: %s\n", StackIsEmpty(stack) == 0 ? "FALSE" : "TRUE"); 
}

void StackPopChr_test(stack_t *stack)
{
  StackPop(stack);
  printf("\nPop from stack\n");
  printf("\tstack head: %c\n", *(char*)StackPeek(stack));
  printf("\tsize: %ld\n", StackSize(stack)); 
  printf("\tIsEmpty: %s\n", StackIsEmpty(stack) == 0 ? "FALSE" : "TRUE"); 
}

void StackPopDouble_test(stack_t *stack)
{
  StackPop(stack);
  printf("\nPop from stack\n");
  printf("\tstack head: %f\n", *(double*)StackPeek(stack));
  printf("\tsize: %ld\n", StackSize(stack)); 
  printf("\tIsEmpty: %s\n", StackIsEmpty(stack) == 0 ? "FALSE" : "TRUE"); 
}