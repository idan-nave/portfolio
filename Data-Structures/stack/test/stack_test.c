/*
  Name: Idan Nave
  Project: Work Sheet #4 - Data Structures - Stack
  Reviewer: Dima
  Date: 12/08/23
  Version: 1.0
*/

/**************** Libraries  *****************/

#include <stdio.h>                /*printf*/
#include <stdlib.h> 		      /* malloc(), free() */
#include <errno.h>                /* errno global */
#include <stddef.h>               /* size_t, NULL */

#include "stack.h" 		

/**************** Definitions  ****************/

/* Size Definition */
#define STACK_CAPACITY 5  
#define STACK_ELEM_SIZE 4  

/***************************************/
/******** Forward Declarations of Static Functions **********/
/***************************************/
 
int ExecuteTestSequence();

  /*************** Test Functions **************/

/* Function to validate stack-creation*/
static int Test_StackCreate(size_t capacity, size_t element_size);
/* Function to validate stack-deletion*/
static int Test_StackDestroy(stack_t *test_stack);
/* Function to pop a specified anpont of elements in a row*/
static int Test_StackPop(stack_t *test_stack, size_t num_of_pops);
/* Function to pushs a specified anpont of elements in a row*/
static int Test_StackPush(stack_t *test_stack, size_t num_of_pushs);
/* Function to validate data at head equals cmp_data*/
static void Test_StackPeek(const stack_t *test_stack);
/* Function to validate stack size equals cmp_data*/
static int Test_StackSize(const stack_t *test_stack, size_t cmp_size);
/* Function to validate stack-status fits cmp_st*/
static int Test_StackIsEmpty(const stack_t *test_stack, int cmp_st);

  /************* Helper Functions ************/

/* Generate and returns a random int in range [lower, upper] */
static int GenRandomInt(int lower, int upper);
/*App Manager Function (called from Main)*/
int ExecuteTestSequence();

/******************* Main *****************/

int main()
{   
   return ExecuteTestSequence();
}

/***************************************/
/******** Tests Implementation - Functions Definitions ********/
/***************************************/

  /******** App Manager Function (called from Main) *********/
 
int ExecuteTestSequence()
{ 
    stack_t *test_stack = NULL;
    stack_t *test_stack2 = NULL;
    /*You should not use a pointer that has been released already.*/
    errno = NO_ERROR;   

    printf("TESTING STACK CREATION:\n\n"); 
    /* test stack-creation function*/
    errno = Test_StackCreate(STACK_CAPACITY, STACK_ELEM_SIZE);
    /* now, it is possible to create & init a new stack */
    test_stack = StackCreate(STACK_CAPACITY, STACK_ELEM_SIZE);
    
    /* push max elements in a row & print tree to validate successful push */
    printf("PUSHING MAXIMUM ELEMENTS:\n\n"); 
    errno = Test_StackPush(test_stack, STACK_CAPACITY);

    /* try to push more elements than capacity allows */
    printf("PUSHING ONE MORE THAN MAXIMUM:\n\n"); 
/*    errno = Test_StackPush(test_stack, 1);
*/
    /* print stack status when stack is populated */
    printf("VIEWING STACK STATUS WHEN FULLY POPULATED:\n\n HEAD IS: "); 
    Test_StackPeek((const stack_t*)test_stack);
    errno = Test_StackSize((const stack_t*)test_stack, STACK_CAPACITY);
    errno = Test_StackIsEmpty((const stack_t*)test_stack, NOT_EMPTY);

    /* pop elements in a row & print tree to validate successful pop */
    printf("POPS ALL ELEMENTS:\n\n"); 
    errno = Test_StackPop(test_stack, STACK_CAPACITY );

    /* print stack status when stack is empty */
    printf("VIEWING STACK STATUS WHEN ALL EMPTY:\n\n"); 
    Test_StackPeek((const stack_t*)test_stack);
    errno = Test_StackSize((const stack_t*)test_stack, 0);
    errno = Test_StackIsEmpty((const stack_t*)test_stack, EMPTY);

    /* test destroying the stack while it is empty */
    printf("DESTROYING STACK:\n\n"); 
    errno = Test_StackDestroy(test_stack);

    /* create stack again */
    printf("RECREATING STACK:\n\n"); 
    test_stack2 = StackCreate(STACK_CAPACITY, STACK_ELEM_SIZE);
    /* try to push more elements than allowed */
    printf("PUSHING SINGLE ELEMENT:\n\n"); 
    errno = Test_StackPush(test_stack2, 1);
    /* try to pop more elements than allowed */
/*    printf("POPPING TWO ELEMENTS:\n\n"); 
    errno = Test_StackPop(test_stack2, 2);*/

    /* try to push again after pop was denied */
    printf("PUSHING ONE MORE SINGLE ELEMENT:\n\n"); 
/*    errno = Test_StackPush(test_stack2, 1);
*/    
    /* test destroying the stack while it is full */
    printf("DESTROYING STACK:\n\n"); 
    errno = Test_StackDestroy(test_stack2);

    return errno;
}

  /*************** Test Functions **************/

/* Function to validate stack-creation*/
static int Test_StackCreate(size_t capacity, size_t element_size)
{
    stack_t *new_stack = NULL;

    errno = NO_ERROR;
    new_stack = StackCreate(capacity, element_size);
    printf("Top element after creation is: %s\n\n",(char*)StackPeek(new_stack)); 

    if (StackCapacity(new_stack) != capacity)
    {
        errno = EFAULT;
        perror("capacity init failed");
        return errno;
    }
    if (StackSize(new_stack) != 0)
    {
        errno = EFAULT;
        perror("curr_size init failed");
        return errno;
    }
/*    if (new_stack->stack_arr == NULL)
    {
        errno = EFAULT;
        perror("stack_arr init failed");
        return errno;
    }*/
    printf("#####Stack Creation Success#####\n\n");

    StackDestroy(new_stack);
    return errno;
}

/* Function to validate stack-deletion*/
static int Test_StackDestroy(stack_t *test_stack)
{
    printf("#####Test_StackDestroy#####\n\n");
    errno = NO_ERROR;
    StackDestroy(test_stack);

    printf("#####Stack Destroy #####\n\n");
    return errno;
}

/* Function to pop a specified anpont of elements in a row*/
static int Test_StackPop(stack_t *test_stack, size_t num_of_pops)
{
    size_t i = 0; 
    int catch_err = 0; 

    printf("#####Test_StackPop#####\n\n");
    errno = NO_ERROR;

    /* pop elements in a row */
    while (i < num_of_pops)
    {
        catch_err = StackPop(test_stack);
        if(FAILURE != catch_err)  
        {  
            printf("After POP #%ld out of %ld:\n\n:", i+1, num_of_pops);
            Test_StackPeek( (const stack_t*)test_stack );
        }
        else printf("\n\nError Catched Successfully\n\n");
        ++i;
    }
    return errno;
}

/* Function to pushs a specified anpont of elements in a row*/
static int Test_StackPush(stack_t *test_stack, size_t num_of_pushs)
{
    size_t i = 0; 
    int rnd_data_to_push = 0;
    int catch_err = 0; 
    
    printf("#####Test_StackPush#####\n\n");
    errno = NO_ERROR;

    /* push 'num_of_pushs' elements in a row */
    while (i < num_of_pushs)
    {   
        rnd_data_to_push = GenRandomInt(1,100);
        catch_err = StackPush(test_stack, &rnd_data_to_push);
        if(FAILURE != catch_err)  
        {  
            /* printing operation */
            printf("After PUSH #%ld out of %ld:\t with data: %d\n\n",
            i+1, num_of_pushs, rnd_data_to_push);
            Test_StackPeek(test_stack);
        }
        else printf("\n\nError Catched Successfully\n\n");
        ++i;
    }

    return errno;
}

/* Function to validate stack size equals cmp_data*/
static int Test_StackSize(const stack_t *test_stack, size_t cmp_size)
{
    size_t stack_size = StackSize(test_stack);

    printf("#####Test_StackSize#####\n\n");
    errno = NO_ERROR;

    printf("Stack Size is: %ld, expected %ld:\n\n", stack_size , cmp_size); 
    
    if (stack_size != cmp_size)
    {
        errno = EFAULT;
        perror("Stack Size Fail");
        return errno;
    }
    return SUCCESS;
}

/* Function to validate stack-status fits cmp_st*/
static int Test_StackIsEmpty(const stack_t *test_stack, int cmp_st)
{
    int stack_st = StackIsEmpty(test_stack);

    printf("#####Test_StackIsEmpty#####\n\n");
    errno = NO_ERROR;

    printf("Stack Status is: %d, expected %d:\n\n", stack_st , cmp_st); 
    if (stack_st != cmp_st)
    {
        errno = EFAULT;
        perror("Stack Status Fail");
        return errno;
    }
    return SUCCESS;
}

/* Function to validate peek funcionality*/
static void Test_StackPeek(const stack_t* test_stack)
{
    printf("Elem. #%ld " ,StackSize(test_stack));
    if(NULL == StackPeek(test_stack))
    {
        printf("is Empty\n\n");
        return;
    }
    printf("Add. %p: " ,StackPeek(test_stack));
    printf("stores data: %d\n\n",*( (int*)(StackPeek(test_stack)) ) );
}

/***************************************/
/*********** Static Helper-Functions Definitions *********/
/***************************************/

/* Generate and returns a random float in range [lower, upper] */
static int GenRandomInt(int lower, int upper)
{
  return ((upper - lower)* ((float)rand() / RAND_MAX)) + lower;
}