/*
  Name: Idan Nave
  Project: Work Sheet 6 - Data Structures - Singly Linked LIst
  Reviewer: Liel
  Date: 12/08/23
  Version: 1.0

  Project Overview: API for using a Singly Linked List. User is given an iterator
*/


#ifndef __ILRD_SLL_H__
#define __ILRD_SLL_H__

/******************************** Libraries  *******************************/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

typedef struct node node_t; /*decleration*/
typedef struct iter sll_iter_t; /*for client use*/
typedef struct sll sll_t;

typedef enum  {SUCCESS = 0, FAILURE} status_t;
typedef enum {FALSE = 0, TRUE} boolean_t;

typedef int (*sll_action_t)(void *data, void *param);
typedef int (*sll_match_t)(const void *data, void *param);

/*********************** S-list API Declerations  ****************************/

/*Function that inits an SLL.
  Arguments: None.
  Return value: pointer to SLL. On Error, returns NULL.
  Complexity: O(1). 
  Undefined B.: */
sll_t* SListCreate();

/*Function that destroys an SLL.
  Arguments: 'list' - List pointer.
  Return value: None.
  Complexity: O(n). 
  Undefined B.: NULL ptr of list */
void SListDestroy(sll_t *list);

/*Function that returns the number of current elements in the list.
  Arguments: 'list' - List pointer.
  Return value: Num of current valid elements in list.
  Complexity: O(n).
  Undefined B.: NULL pointer to SLL. */
size_t SListSize( sll_t *list);

/*Function that checks if SLL is empty.
  Arguments: 'list' - List pointer.
  Return value: EMPTY = TRUE, NOT_EMPTY = FALSE.
  Complexity: O(1).
  Undefined B.: NULL pointer to SLL. */
int SListIsEmpty(sll_t *list);

/*Function that retrieves the value of caller's iterator.
  Arguments: 'iter'- Iterator to the element which value is to be retrieved.
  Return value: data - void* pointer.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
void* SListGetData(sll_iter_t iter);

/*Function that sets the value of element caller's iterator.
  Arguments: 'iter'- Iterator to the element which value is to be set.
             'data' - data to be set as the element's new value.
  Return value: None.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
void SListSetData(sll_iter_t iter, void *data);

/*Function that inserts and sets an element before caller's iterator.
    If given iterator is SListEnd(), new element will replace ending element.
  Arguments: 'iter' - Iterator to the new element that will be next of the
                     inserted element, after the operation.
             'data' - the value to be set for the new inserted element.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
sll_iter_t SListInsertBefore(sll_iter_t iter, void* data);

/*Function that removes element iter.
  Arguments: 'iter' - Iterator to the element to-be removed.
  Return value: Iterator to element following the removed element. Passed iterator is invalidated.
  Complexity: O(1).
  Undefined B.: NULL Iterator */
sll_iter_t SListRemove(sll_iter_t iter);

/*Function that searches for data stored in elements of range
           'from' up to 'to', but not including 'to' iterator.
  Arguments: Search range indices ('from', 'to' iterator),
             'match_func' - User function & parameters.
  Return value: Iterator to the 1st found element.
                If the element is not found- returns 'to' iterator.
  Complexity: O(n).
  Undefined B.: NULL Iterators or Iterators for not-same SLL, NULL function.*/
sll_iter_t SListFind(sll_iter_t from_iter, sll_iter_t to_iter,  void* data, sll_match_t match_func, void* usr_param);

/*Function that peforms action on elements of range 
          'from' up to 'to', but not including 'to' iterator.
  Arguments: Search range indices ('from', 'to' iterator),
             'action_func' - User function & parameters.  
  Return value: Done all actions = SUCCESS, failed action (if any) = FAILURE.
  Complexity: O(n) * complexity of action_func.
  Undefined B.: NULL Iterators or Iterators for not-same SLL, NULL function.*/
int SListForEach(sll_iter_t from_iter, sll_iter_t to_iter, void* data, sll_action_t action_func, void* usr_param);

/********************* Iterator API Declerations  ****************************/

/*Function that checks if two iterators are the same. 
  Arguments: 'iter1', 'iter2' - Iterators to compare.
  Return value: same = SUCCESS, not same = FAILURE.
  Complexity: O(1).
  Undefined B.: NULL Iterators or Iterators for not-same SLL.*/
int SListIsSameIter(const sll_iter_t iter1, const sll_iter_t iter2);

/*Function that returns an iterator to the begining of the list.
  Arguments: 'list' - List pointer.
  Return value: SLL iterator to the first element of the list.
  Complexity: O(1).
  Undefined B.: NULL pointer to SLL. */
sll_iter_t SListBegin( sll_t *list);

/*Function that returns an iterator to the end of the list.
  Arguments: 'list' - List pointer.
  Return value: SLL iterator to the ending element of the list.
  Complexity: O(1).
  Undefined B.: NULL pointer to SLL. */
sll_iter_t SListEnd( sll_t *list);

/*Function that retrievs element following caller's iterator.
  Arguments: 'iter'- Iterator to SLL.
  Return value: Iter pointing at the element following caller's iterator.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
sll_iter_t SListNext(sll_iter_t iter);

/*Function that retrievs element preceeding caller's iterator.
  Arguments: 'iter'- Iterator to SLL.
  Return value: Iter pointing at the element following caller's iterator.
  Undefined B.: NULL Iterator. */
sll_iter_t SListPrev(sll_iter_t iter);

sll_t* SListAppend(sll_t *dest, sll_t *src);



/*****************************************************************************/

/*Iterator Definition - Not intended for user. Iterator struct is defined here because evaluation of type sll_iter_t is mandatory for header file */
struct iter
{
      node_t* node_ptr;
};

#endif /*(__ILRD_SLL_H__)*/