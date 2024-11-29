/****************************** Test_ws6_sll.c  **************************/
/*
  Name: Idan Nave
  Project: Work Sheet 6 - Data Structures - Singly Linked LIst
  Reviewer: Agbaria
  Date: 12/08/23
  Version: 1.0
*/

/****************************** Libraries  **********************************/

#include <assert.h>               /* assert() */
#include <stdio.h>                /* perror */
#include <stdlib.h>               /* malloc(), free() */
#include <string.h>               /* string manipulation */
#include <errno.h>                /* errno global */
#include <stddef.h>               /* size_t, NULL */

#include "sll.h"  

#define NUM_OF_NODES 5    

/******************************* Definitions  ********************************/

/* Size Definition */


/*****************************************************************************/
/**************** Forward Declarations of Static Functions *******************/
/*****************************************************************************/
 
int ExecuteTestSequence();

  /****************************** Test Functions ****************************/

/* Function to validate sll-creation*/
static void SListGetInfo(sll_t *test_sll);
/* Function to validate data insrtion to list*/
static int TestSetData(sll_iter_t iter, void *data);
/* Function that inserts i index data in a row mum_of_inserts times*/
static void SListInsetInARow(sll_t *sll, size_t mum_of_inserts);
/* Function that removes mum_of_removes nodes starting from iter*/
static void SListRemoveInARow(sll_iter_t iter, size_t mum_of_removes);

int PrintData(void* data, void* param);

int MatchInt(const void* data, void* param);

void SListSize_Test(sll_t *list, const char* str);

void SListFind_Test(sll_t *list, void* data, sll_match_t match_func, void* usr_param);

void SListForEach_Test(sll_t *list, void* data, sll_action_t action_func, void* usr_param, const char* str);


/************************************* Main **********************************/

int main()
{  

    return ExecuteTestSequence();

}

/*****************************************************************************/
/*************** Tests Implementation - Functions Definitions ****************/
/*****************************************************************************/

  /**************** App Manager Function (called from Main) *****************/
 
int ExecuteTestSequence()
{ 

    /* init list */
    sll_t *test_sll = SListCreate();
    /* client iter for traversing the list */
    sll_iter_t tst_iter = SListEnd(test_sll);


    size_t data_to_set = 0;
/*    size_t* data_to_read = NULL;
*/
    printf("\n####### New List Was Created ########\n\n");
    SListGetInfo( test_sll );

    /* client iter points to the tail of the list, kee inserting from there */
    printf("\n####### Node-Insertion To List Tests: ########\n\n");
    SListInsetInARow(test_sll, NUM_OF_NODES);   
/*    TestInsertBefore(test_sll, &data_to_set );

*/    SListGetInfo( test_sll );

    printf("\n####### Node-Data Setting Test ########\n\n");
    data_to_set = 100;
    tst_iter = SListBegin(test_sll);
    TestSetData(tst_iter, (void*) &data_to_set);
    SListGetInfo( test_sll );

    printf("\n####### Node-Removing From List Tests: ########\n\n");
    tst_iter = SListBegin(test_sll);
    SListRemoveInARow(tst_iter, NUM_OF_NODES - 1);
    SListGetInfo( test_sll );

    printf("\n####### Destroying List Test: ########\n\n");
    SListDestroy(test_sll);
    SListGetInfo( test_sll );

    return 0;
}

  /****************************** Test Functions ****************************/

/* Function to validate sll-creation*/
static void SListGetInfo(sll_t *test_sll)
{    
    /* create pointers to parse data given by iterator functions */
    size_t* head_def_data = NULL;
    size_t* tail_def_data = NULL;
    size_t* head_def_next = NULL;
    size_t* tail_def_next = NULL;
    size_t node_count = 0;

    /* retrieve created list head & tail iterators */
    sll_iter_t head_tester = SListEnd(test_sll);
    sll_iter_t tail_tester  = SListBegin(test_sll);
    node_count = SListSize(test_sll);

    printf("\n#Displaying list %p containing %ld nodes:\n#",
        test_sll, node_count);
/*    SListForEach_Test(test_sll, NULL, PrintData, NULL, "");
    printf("\n\n");*/
    /* print head data after list creation (NULL or &List) */
    
    head_def_data =  (size_t*)(SListGetData( head_tester )) ;
    if(NULL == head_def_data)
    {
        errno = ENOMEM;
        perror("Data stored in Tail's data is NULL, Bad Init\n");
    }
    else printf("Data stored in Tail's data is: 0x%zx\n",
        (size_t)head_def_data);

    tail_def_data =  (size_t*)(SListGetData( tail_tester )) ;
    if(NULL == head_def_data)
    {
        errno = ENOMEM;
        perror("Data stored in Head's data is NULL, Bad Init\n");
    }
    else printf("Data stored in Head's data is: 0x%zx\n",
        (size_t)head_def_data);

    /* retrieve next-adds of nodes pointed by head & tail  */

    head_def_next =  (size_t*)(  (SListNext( head_tester ).node_ptr) );
    if(NULL == head_def_next)
    {
        printf("Address stored in Tail's next is NULL\n");
    }
    else printf("Address stored in Tail's next: 0x%zx\n",
        (size_t)head_def_next);

    tail_def_next =  (size_t*)( (SListNext( tail_tester ).node_ptr) ) ;
    if(NULL == tail_def_next)
    {
        printf("Address stored in Tail's next is NULL\n");
    }
    else printf("Address stored in Tail's next: 0x%zx\n",
        (size_t)tail_def_next);
  
    /* check list population status */
    if(TRUE == SListIsEmpty(test_sll))
    {
        printf("List is currently Empty\n");
    }
    else printf("List is not Empty\n");
}

/* Function that inserts i index data in a row mum_of_inserts times*/
static void SListInsetInARow(sll_t *sll, size_t mum_of_inserts)
{
    size_t i = 0;
    
    /* insert multiple by calling insert-before function */
    while (i < mum_of_inserts)
    { 
        SListInsertBefore(SListBegin(sll), &i);
        ++i;
    }
}

/* Function to validate data setting of n existing node in a list*/
static int TestSetData(sll_iter_t iter, void *data)
{
    
    size_t data_to_set = *((size_t*)data);
    size_t* data_to_read = (size_t*)(SListGetData( iter )) ;

    printf("\tSetting node %p: [old]%ld > [new]%ld\n", (SListNext( iter ).node_ptr), data_to_read, data_to_set);

    SListSetData(iter, data);

    data_to_read =  (size_t*)(SListGetData( iter )) ;
    printf("\t\t\t\t\t\tRead Back: %ld \n", *data_to_read);
}

/* Function that removes mum_of_removes nodes starting from iter*/
static void SListRemoveInARow(sll_iter_t iter, size_t mum_of_removes)
{
    size_t i = 0;
    
    /* insert multiple by calling remove function */
    while (i < mum_of_removes)
    {
        iter = SListRemove(iter);
        ++i;
    }
}

/* Function to validate Match Operation*/
static int Test_Match(sll_iter_t iter, void *data)
{
/*   sll_match_t(void* node_data, void* data, void* param)
*/}

/*****************************************************************************/
/************** Static User-Imitating Functions Definitions ******************/
/*****************************************************************************/

/*typedef int (*sll_match_t)(const void* data, void* param);*/
static int Match(void* node_data, void* data, void* param)
{
    param;
    if( ( *(size_t*)data ) == ( *(size_t*)node_data ))
    {
        return SUCCESS;
    }
    return FAILURE;
}

/*typedef int (*sll_action_t)(void* data, void* param);*/
static int Add(void* data, void* param)
{
    
    if( ( *(size_t*)data ) == ( *(size_t*)param ))
    {
        return SUCCESS;
    }
    return FAILURE;
}

int PrintData(void* data, void* param)
{
    printf("%d ", *(int*)data);
    fflush(stdout);
    return SUCCESS;
}

int MatchInt(const void* data, void* param)
{
    return (*(int*)data == *(int*)param);
}

void SListSize_Test(sll_t *list, const char* str)
{
  printf("size of the list %s: %ld\n", str, SListSize(list));
}

void SListForEach_Test(sll_t *list, void* data, sll_action_t action_func, void* usr_param, const char* str)
{
  printf("List contents %s: ", str);
  SListForEach(SListBegin(list), SListEnd(list), data, action_func, usr_param);
}

void SListFind_Test(sll_t *list, void* data, sll_match_t match_func, void* usr_param)
{
  sll_iter_t found_iter = SListFind(SListBegin(list), SListEnd(list), data, match_func, usr_param);
  if (SListIterIsEqual(found_iter, SListEnd(list))) 
  {
      printf("Element %d not found.\n", *(int*)data);
  } 
  else 
  {
      printf("Element found: %d\n", *((int*)SListGetData(found_iter)));
  }
}