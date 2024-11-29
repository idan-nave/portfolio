/*
  Name: Aya
  Project: Work Sheet 6 - Data Structures - Singly Linked LIst
  Reviewer: ???
  Date: 14/08/23
  Version: 1.0
*/

/******************************** Libraries  **********************************/

#include <stddef.h> /*size_t*/
#include <stdio.h>  /*printf*/

#include "sll.h"

/******************************** Declerations  *******************************/

int PrintData(void* data, void* param);

int MatchInt(const void* data, void* param);

void SListSize_Test(sll_t *list, const char* str);

void SListFind_Test(sll_t *list, void* data, sll_match_t match_func, void* usr_param);

void SListForEach_Test(sll_t *list, void* data, sll_action_t action_func, void* usr_param, const char* str);


/******************************************************************************/
int main()
{
  sll_t *list1 = SListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;
  int find_data1 = 8;
  int find_data2 = 6;

  /*Test Insert*/
  SListSize_Test(list1, "");
  SListInsertBefore(SListBegin(list1), &data6);
  SListInsertBefore(SListBegin(list1), &data5);
  SListInsertBefore(SListEnd(list1), &data7);
  SListInsertBefore(SListBegin(list1), &data4);
  SListSize_Test(list1, "After Inserting 4 elements");
  printf("\n");

  /*Test SListForEach*/
/*  SListForEach_Test(list1, NULL, PrintData, NULL, "(Origin)");
*/  printf("\n\n");

  /*Test SListFind*/
/*  SListFind_Test(list1, &find_data1, MatchInt, NULL);
  SListFind_Test(list1, &find_data2, MatchInt, NULL);*/
  printf("\n");

  /*Test After Remove*/
  SListRemove(SListBegin(list1));
  SListSize_Test(list1, "After remove the head");
/*  SListForEach_Test(list1, NULL, PrintData, NULL,"(After remove the head)");
*/  printf("\n");

  SListDestroy(list1);
  return 0;
}

/******************************************************************************/
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

/*void SListForEach_Test
(sll_t *list, void* data, sll_action_t action_func, void* usr_param)
{
  printf("List contents %s: ", str);
  SListForEach(SListBegin(list), SListEnd(list), action_func, usr_param);
}

void SListFind_Test(sll_t *list, void* data, sll_match_t match_func)
{
  sll_iter_t found_iter =
    SListFind(SListBegin(list), SListEnd(list), match_func, data);
  if (SListIsSameIter(found_iter, SListEnd(list))) 
  {
      printf("Element %d not found.\n", *(int*)data);
  } 
  else 
  {
      printf("Element found: %d\n", *(int*)SListGetData(found_iter));
  }
}*/



