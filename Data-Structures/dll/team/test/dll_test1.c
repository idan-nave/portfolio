/*
  Name: Aya
  Project: Work Sheet 11 - Data Structures - DLL
  Reviewer: Sahar
  Date: 24/08/23
  Version: 1.0
*/

/******************************** Libraries  **********************************/
#include <stdio.h>  /*printf*/

#include "ws11_dll.h"

/******************************** Declerations  *******************************/
static void TestInsert();
static void DListInsertBefore_Test(dll_iter_t iter, void *data, dll_t *list);
static void TestPushFront();
static void DListPushFront_Test(dll_t *list, void *data);
static void TestPushEnd();
static void DListPushBack_Test(dll_t *list, void *data);

static void TestRemove();
static void DListRemove_Test(dll_iter_t to_remove, dll_iter_t returned_iter);
static void TestPopFront();
static void DListPopFront_Test(dll_t *list, dll_iter_t returned_iter);
static void TestPopBack();
static void DListPopBack_Test(dll_t *list, dll_iter_t returned_iter);

static void TestSize();
static void DListSize_Test(dll_t *list, size_t value);
static void TestIsEmpty();
static void DListIsEmpty_Test(dll_t *list, int value);

static void TestSameIter();
static void TestIteratorFunctions();
static void DListBegin_Test(dll_t *list, int is_same);
static void DListEnd_Test(dll_t *list, int is_same);
static void DListNext_Test(dll_iter_t iter, dll_iter_t expected_next, int is_same);
static void DListPrev_Test(dll_iter_t iter, dll_iter_t expected_prev, int is_same);

static void TestSetGetData();
static void DListGetData_Test(dll_iter_t iter, int value);
static void DListSetData_Test(dll_iter_t iter, void *data);

static void TestFind();
static int MatchFunc(const void *data, void *param);

static void TestForEach();
static int ActionFunc(void *data, void *param);

static void TestMultiFind();
static void DListMultiFind_Test(dll_iter_t from, dll_iter_t to, dll_match_t match_func,
                                void *param, dll_t *dest_list, size_t size_of_dest);

static void TestSplice();

/********************************* main ***************************************/
int main()
{
  printf("\n");
  TestInsert();
  TestPushFront();
  TestPushEnd();
  
  TestRemove();
  TestPopFront();
  TestPopBack();

  TestSize();
  TestIsEmpty();
  TestSetGetData();

  TestFind();
  TestForEach();
  TestMultiFind();
  TestSplice();

  TestSameIter();
  TestIteratorFunctions();

  printf("\n");
  return 0;
}

/******************************* Test Insert **********************************/
static void TestInsert()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;

  DListInsertBefore_Test(DListBegin(list), &data6, list);
  DListInsertBefore_Test(DListBegin(list), &data5, list);
  DListInsertBefore_Test(DListEnd(list), &data7, list);
  DListInsertBefore_Test(DListBegin(list), &data4, list);

  DListDestroy(list);

  printf("DListInsertBefore() Passed!\n");
}

static void DListInsertBefore_Test(dll_iter_t iter, void *data, dll_t *list)
{
  if(DListEnd(list) == DListInsertBefore(iter, data, list))
  {
    printf("Failed on DListInsertBefore()\n");
  }
}

/***************************** Test Push Front ********************************/
static void TestPushFront()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;

  DListPushFront_Test(list, &data6);
  DListPushFront_Test(list, &data5);
  DListPushFront_Test(list, &data7);
  DListPushFront_Test(list, &data4);

  DListDestroy(list);

  printf("DListPushFront() Passed!\n");
}

static void DListPushFront_Test(dll_t *list, void *data)
{
  if(DListEnd(list) == DListPushFront(list, data))
  {
    printf("Failed on DListPushFront()\n");
  }
}

/****************************** Test Push End *********************************/
static void TestPushEnd()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;

  DListPushBack_Test(list, &data6);
  DListPushBack_Test(list, &data5);
  DListPushBack_Test(list, &data7);
  DListPushBack_Test(list, &data4);

  DListDestroy(list);

  printf("DListPushBack() Passed!\n");
}

static void DListPushBack_Test(dll_t *list, void *data)
{
  if(DListEnd(list) == DListPushBack(list, data))
  {
    printf("Failed on DListPushBack()\n");
  }
}

/****************************** Test Remove ***********************************/
static void TestRemove()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;
  dll_iter_t iter = NULL;

  DListInsertBefore(DListBegin(list), &data6, list);
  DListInsertBefore(DListBegin(list), &data5, list);
  DListInsertBefore(DListEnd(list), &data7, list);
  DListInsertBefore(DListBegin(list), &data4, list);

  iter = DListNext(DListBegin(list));
  DListRemove_Test(DListBegin(list), iter);

  iter = DListEnd(list);
  DListRemove_Test(DListPrev(DListEnd(list)), iter);

  DListDestroy(list);

  printf("DListRemove() Passed!\n");
}

static void DListRemove_Test(dll_iter_t to_remove, dll_iter_t returned_iter)
{
  if(!DListIsSameIter(returned_iter, DListRemove(to_remove)))
  {
    printf("Failed on DListRemove()\n");
  }
}

/***************************** Test Pop Front *********************************/
static void TestPopFront()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;
  dll_iter_t iter = NULL;

  DListInsertBefore(DListBegin(list), &data6, list);
  DListInsertBefore(DListBegin(list), &data5, list);
  DListInsertBefore(DListEnd(list), &data7, list);
  DListInsertBefore(DListBegin(list), &data4, list);

  iter = DListNext(DListBegin(list));
  DListPopFront_Test(list, iter);

  iter = DListNext(DListBegin(list));
  DListPopFront_Test(list, iter);

  iter = DListNext(DListBegin(list));
  DListPopFront_Test(list, iter);

  DListDestroy(list);

  printf("DListPopFront() Passed!\n");
}

static void DListPopFront_Test(dll_t *list, dll_iter_t returned_iter)
{
  if(!DListIsSameIter(returned_iter, DListPopFront(list)))
  {
    printf("Failed on DListPopFront()\n");
  }
}

/****************************** Test Pop End **********************************/
static void TestPopBack()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;
  dll_iter_t iter = NULL;

  DListInsertBefore(DListBegin(list), &data6, list);
  DListInsertBefore(DListBegin(list), &data5, list);
  DListInsertBefore(DListEnd(list), &data7, list);
  DListInsertBefore(DListBegin(list), &data4, list);

  iter = DListEnd(list);
  DListPopBack_Test(list, iter);

  iter = DListEnd(list);
  DListPopBack_Test(list, iter);

  iter = DListEnd(list);
  DListPopBack_Test(list, iter);

  DListDestroy(list);

  printf("DListPopBack() Passed!\n");
}

static void DListPopBack_Test(dll_t *list, dll_iter_t returned_iter)
{
  if(!DListIsSameIter(returned_iter, DListPopBack(list)))
  {
    printf("Failed on DListPopFront()\n");
  }
}

/******************************* Test Size ************************************/
static void TestSize()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;

  /*empty list*/
  DListSize_Test(list, 0);

  /*After inserting 4 elements*/
  DListInsertBefore(DListBegin(list), &data6, list);
  DListInsertBefore(DListBegin(list), &data5, list);
  DListInsertBefore(DListEnd(list), &data7, list);
  DListInsertBefore(DListBegin(list), &data4, list);
  DListSize_Test(list, 4);

  /*After removing 1 element*/
  DListRemove(DListBegin(list));
  DListSize_Test(list, 3);

  DListDestroy(list);

  printf("DListSize() Passed!\n");
}

static void DListSize_Test(dll_t *list, size_t value)
{
  if(value != DListSize(list))
  {
    printf("Failed on DListSize()\n");
  }
}

/******************************* Test IsEmpty *********************************/
static void TestIsEmpty()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;

  /*empty list*/
  DListIsEmpty_Test(list, TRUE);

  /*After inserting 4 elements*/
  DListInsertBefore(DListBegin(list), &data6, list);
  DListInsertBefore(DListBegin(list), &data5, list);
  DListInsertBefore(DListEnd(list), &data7, list);
  DListInsertBefore(DListBegin(list), &data4, list);
  DListIsEmpty_Test(list, FALSE);

  /*After removing 1 element*/
  DListRemove(DListBegin(list));
  DListIsEmpty_Test(list, FALSE);

  /*After removing all the elements*/
  DListRemove(DListBegin(list));
  DListRemove(DListBegin(list));
  DListRemove(DListBegin(list));
  DListIsEmpty_Test(list, TRUE);

  DListDestroy(list);

  printf("DListIsEmpty() Passed!\n");
}

static void DListIsEmpty_Test(dll_t *list, int value)
{
  if(value != DListIsEmpty(list))
  {
    printf("Failed on DListIsEmpty()\n");
  }
}


/********************** Test Set Data and Get Data ****************************/
static void TestSetGetData()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;
  int data9 = 9;

  DListInsertBefore(DListBegin(list), &data6, list);
  DListInsertBefore(DListBegin(list), &data5, list);
  DListInsertBefore(DListEnd(list), &data7, list);
  DListInsertBefore(DListBegin(list), &data4, list);

  DListGetData_Test(DListBegin(list), data4);
  DListSetData_Test(DListBegin(list), &data9);

  DListDestroy(list);

  printf("DListGetData() Passed!\nDListSetData() Passed!\n");
}

static void DListGetData_Test(dll_iter_t iter, int value)
{
  if(value != *(int*)DListGetData(iter))
  {
    printf("Failed on DListGetData()\n");
  }
}

static void DListSetData_Test(dll_iter_t iter, void *data)
{
  DListSetData(iter, data);
  if(data != DListGetData(iter))
  {
    printf("Failed on DListSetData()\n");
  }
}

/******************************* Test Find ************************************/
static void TestFind()
{
    dll_t *list = DListCreate();
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int search_data = 2;
    dll_iter_t from = NULL;
    dll_iter_t to = NULL;
    dll_iter_t result = NULL;

    DListInsertBefore(DListBegin(list), &data4, list);
    DListInsertBefore(DListBegin(list), &data3, list);
    DListInsertBefore(DListEnd(list), &data2, list);
    DListInsertBefore(DListBegin(list), &data1, list);

    from = DListBegin(list);
    to = DListEnd(list);
    result = DListFind(from, to, MatchFunc, &search_data);

    if (!DListIsSameIter(result, to) && DListIsSameIter(result, DListPrev(to)))
    {
        printf("DListFind() Passed!\n");
    }
    else
    {
        printf("Failed on DListFind()\n");
    }

    DListDestroy(list);
}

static int MatchFunc(const void *data, void *param)
{
    return (*(int *)data == *(int *)param);
}

/****************************** Test ForEach **********************************/
static void TestForEach()
{
    dll_t *list = DListCreate();
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    dll_iter_t from =NULL;
    dll_iter_t to = NULL;
    int param = 10;
    int result = 0;

    DListInsertBefore(DListBegin(list), &data4, list);
    DListInsertBefore(DListBegin(list), &data3, list);
    DListInsertBefore(DListEnd(list), &data2, list);
    DListInsertBefore(DListBegin(list), &data1, list);

    from = DListBegin(list);
    to = DListEnd(list);
    param = 10;
    result = DListForEach(from, to, ActionFunc, &param);
    
    DListDestroy(list);
    
    if (result == SUCCESS)
    {
        printf("DListForEach() Passed!\n");
    }
    else
    {
        printf("Failed on DListForEach()\n");
    }

    
}

static int ActionFunc(void *data, void *param)
{
    *(int*)data += *(int*)param;
    return SUCCESS;
}

/***************************** Test MultiFind *********************************/
static void TestMultiFind()
{
    dll_t *list = DListCreate();
    dll_t *dest_list = DListCreate();
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int search_data = 2;
    dll_iter_t from = NULL;
    dll_iter_t to = NULL;

    DListInsertBefore(DListBegin(list), &data4, list);
    DListInsertBefore(DListBegin(list), &data3, list);
    DListInsertBefore(DListEnd(list), &data2, list);
    DListInsertBefore(DListBegin(list), &data1, list);

    from = DListBegin(list);
    to = DListEnd(list);
    DListMultiFind_Test(from, to, MatchFunc, &search_data, dest_list, 1);

    DListDestroy(list);
    DListDestroy(dest_list);

    printf("DListMultiFind() Passed!\n");
}

static void DListMultiFind_Test(dll_iter_t from, dll_iter_t to, dll_match_t match_func,
                                void *param, dll_t *dest_list, size_t size_of_dest)
{
    dll_iter_t iter_begin = NULL;
    dll_iter_t iter_end = NULL;

    DListMultiFind(from, to, match_func, param, dest_list);
    iter_begin = DListBegin(dest_list);
    iter_end = DListEnd(dest_list);

    if(size_of_dest != DListSize(dest_list))
    {
      printf("Failed on DListMultiFind()\n");
    }

    while(FALSE == DListIsSameIter(iter_begin, iter_end))
    {
      if(*(int*)param != *(int*)DListGetData(iter_begin))
      {
        printf("Failed on DListMultiFind()\n");
      }

      iter_begin = DListNext(iter_begin);
    }
}

/********************************* Test Splice *********************************/
static void TestSplice()
{
    dll_t *list1 = DListCreate();
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    int data6 = 6;
    int data7 = 7;
    int data8 = 8;
    dll_iter_t from = NULL;
    dll_iter_t to = NULL;
    dll_iter_t where = NULL;
    dll_iter_t where_prev = NULL;

    DListInsertBefore(DListBegin(list1), &data8, list1);
    DListInsertBefore(DListBegin(list1), &data7, list1);
    DListInsertBefore(DListBegin(list1), &data6, list1);
    DListInsertBefore(DListBegin(list1), &data5, list1);
    DListInsertBefore(DListBegin(list1), &data4, list1);
    DListInsertBefore(DListBegin(list1), &data3, list1);
    DListInsertBefore(DListBegin(list1), &data2, list1);
    DListInsertBefore(DListBegin(list1), &data1, list1);

    from = DListPrev(DListPrev(DListPrev(DListPrev(DListEnd(list1)))));
    to = DListPrev(DListPrev(DListEnd(list1)));
    where = DListNext(DListBegin(list1));
    where_prev = DListPrev(where);

    DListSplice(from, to, where);

    if(DListIsSameIter(DListNext(where_prev), from) && 
       DListIsSameIter(DListPrev(where), to))
    {
        printf("DListSplice() Passed!\n");
    }
    else
    {
        printf("Failed on DListSplice()\n");
    }

    DListDestroy(list1);
}

/****************************** Test IsSameIter *******************************/
static void TestSameIter()
{
  dll_t *list = DListCreate();
  int data4 = 4;
  int data5 = 5;
  int data6 = 6;
  int data7 = 7;

  DListInsertBefore(DListBegin(list), &data6, list);
  DListInsertBefore(DListBegin(list), &data5, list);
  DListInsertBefore(DListEnd(list), &data7, list);
  DListInsertBefore(DListBegin(list), &data4, list);

  if(FALSE == DListIsSameIter(DListBegin(list), DListBegin(list)))
  {
    printf("Failed on DListIsSameIter()\n");
  }
  if(TRUE == DListIsSameIter(DListBegin(list), DListEnd(list)))
  {
    printf("Failed on DListIsSameIter()\n");
  }

  DListDestroy(list);

  printf("DListIsSameIter() Passed!\n");
}

/******************************** Test Iterator Functions ************************/
static void TestIteratorFunctions()
{
    dll_t *list = DListCreate();
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    DListInsertBefore(DListBegin(list), &data3, list);
    DListInsertBefore(DListBegin(list), &data2, list);
    DListInsertBefore(DListBegin(list), &data1, list);

    DListBegin_Test(list, TRUE);
    DListEnd_Test(list, TRUE);

    DListNext_Test(DListBegin(list), DListBegin(list), FALSE);
    DListNext_Test(DListPrev(DListEnd(list)), DListEnd(list), TRUE);

    DListPrev_Test(DListEnd(list), DListEnd(list), FALSE);
    DListPrev_Test(DListBegin(list), DListBegin(list), FALSE);

    DListDestroy(list);
    
    printf("Iterator Function Tests Passed!\n");
}

/******************************** Test Helper Functions **************************/

static void DListBegin_Test(dll_t *list, int is_same)
{
    if (is_same != DListIsSameIter(DListBegin(list), DListBegin(list)))
    {
        printf("Failed on DListBegin_Test()\n");
    }
}

static void DListEnd_Test(dll_t *list, int is_same)
{
    if (is_same != DListIsSameIter(DListEnd(list), DListEnd(list)))
    {
        printf("Failed on DListEnd_Test()\n");
    }
}

static void DListNext_Test(dll_iter_t iter, dll_iter_t expected_next, int is_same)
{
    if (is_same != DListIsSameIter(DListNext(iter), expected_next))
    {
        printf("Failed on DListNext_Test()\n");
    }
}

static void DListPrev_Test(dll_iter_t iter, dll_iter_t expected_prev, int is_same)
{
    if (is_same != DListIsSameIter(DListPrev(iter), expected_prev))
    {
        printf("Failed on DListPrev_Test()\n");
    }
}