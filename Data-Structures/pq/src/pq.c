/******************************************************************************/
/*
  Name: Idan Nave
  Project: PQ
  Reviewer: ??
  Date: 06/09/23
  Version: 1.0

  Overview: Implementation of an PQ Manager.
*/

/******************************** Libraries  **********************************/
#include <assert.h>             /* assert() */
#include <stdio.h>              /* perror */
#include <stdlib.h>             /* malloc(), free() */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */
#include <time.h>               /*time_t*/

#include "/home/idan/Documents/Dev/Git_WD/ds/sorted_list/include/sorted_list.h"
/*dll_status_t, dll_boolean_t*/
#include "/home/idan/Documents/Dev/Git_WD/ds/pq/include/pq.h"   

/********************************* Type Definitions **************************/

struct pq
{
  sorted_list_t *list;
};

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
pq_t* PQCreate(pq_compare_t cmp_func)
{
  pq_t* pq = NULL;
  assert(NULL != cmp_func);

  pq = (pq_t*)malloc(sizeof(pq_t));
  if(NULL == pq)
  {
    return NULL;
  }
  
  pq->list = SListCreate(cmp_func);
  if(NULL == pq->list)
  {
    return NULL;
  }

  return pq;
}

void PQDestroy(pq_t *pq)
{
  assert(NULL != pq);

  SListDestroy(pq->list);
  free(pq);
  pq = NULL;
}

size_t PQSize(const pq_t *pq)
{
  assert(NULL != pq);
  return SListSize(pq->list);
}

int PQIsEmpty(const pq_t *pq)
{
  assert(NULL != pq);
  return SListIsEmpty(pq->list);
}

void* PQPeek(const pq_t *pq)
{
  assert(NULL != pq);
  return SListGetData(SListBegin(pq->list));
}

int PQEnqueue(pq_t *pq, void* data)
{
  assert(NULL != pq);

  SListInsert(pq->list, data);
  return TRUE == SListIsSameIter(SListBegin(pq->list), SListEnd(pq->list));
}

void* PQDequeue(pq_t *pq)
{
  void* data = NULL;
  assert(NULL != pq);

  data = PQPeek(pq);
  SListPopFront(pq->list);
  return data;
}

void PQClear(pq_t *pq)
{
  assert(NULL != pq);
  while(TRUE != PQIsEmpty(pq))
  {
    PQDequeue(pq);    
  }
}

void* PQErase(pq_t *pq, pq_is_match_t match_func, void *params)
{
  sor_iter_t iter = {0};
  void* data = NULL;
  assert(NULL != pq);
  assert(NULL != match_func);
  iter = SlistFindIF
    (SListBegin(pq->list), SListEnd(pq->list), match_func, params);
  data = SListGetData(iter) ;

  SListRemove(iter);
  return data;
}