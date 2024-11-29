/*
  Name: Idan Nave
  Project: Work Sheet 11 - Data Structures - Doubly Linked List
  Reviewer: Amit
  Date: 22/08/23
  Version: 1.0

  Project Overview: API for using a Doubly Linked List.. User is given an iterator
*/

#ifndef __ILRD_DLL_H__
#define __ILRD_DLL_H__

/******************************** Libraries  *******************************/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

typedef struct dll dll_t;
typedef struct node node_t;
typedef node_t* dll_iter_t;

typedef enum  {SUCCESS = 0, FAILURE} dll_status_t;
typedef enum {FALSE = 0, TRUE} dll_boolean_t;

typedef int (*dll_action_t)(void* data, void* param);
typedef int (*dll_match_t)(const void* list_data, void* param);

/*********************** D-list API Declerations  ****************************/

/*Function that creates a DLL.
  Arguments: None.
  Return value: pointer to DLL. On Error, returns NULL.
  Complexity: O(1). 
  Undefined B.: */
dll_t* DListCreate(void);

/*Function that destroys a DLL.
  Arguments: 'list' - List pointer.
  Return value: None.
  Complexity: O(n). 
  Undefined B.: NULL ptr of list */
void DListDestroy(dll_t *list);

/*Function that returns the number of current elements in the list.
  Arguments: 'list' - List pointer.
  Return value: Num of current valid elements in list.
  Complexity: O(n).
  Undefined B.: NULL pointer to DLL. */
size_t DListSize(const dll_t *list);

/*Function that checks if DLL is empty.
  Arguments: 'list' - List pointer.
  Return value: if empty = TRUE, othewise = FALSE.
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
int DListIsEmpty(dll_t *list);

/*Function that retrieves the value of caller's iterator.
  Arguments: 'iter'- Iterator to the element which value is to be retrieved.
  Return value: data - void* pointer.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
void* DListGetData(dll_iter_t iter);

/*Function that sets the value of element caller's iterator.
  Arguments: 'iter'- Iterator to the element which value is to be set.
             'data' - data to be set as the element's new value.
  Return value: None.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
void DListSetData(dll_iter_t iter, const void *data);

/*Function that inserts and sets an element before caller's iterator.
    If given iterator is DListEnd(), new element will replace ending element.
  Arguments: 'iter' - Iterator to the new element that will be next of the
                     inserted element, after the operation.
             'data' - the value to be set for the new inserted element.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
dll_iter_t DListInsertBefore(dll_iter_t iter, void* data, dll_t *dlist);

/*Function that removes element iter.
  Arguments: 'iter' - Iterator to the element to-be removed.
  Return value: Iterator to element following the removed element. Passed iterator is invalidated.
  Complexity: O(1).
  Undefined B.: NULL Iterator */
dll_iter_t DListRemove(dll_iter_t iter);

/*Function that inserts and sets the head element of the list.
  Arguments: 'list' - List pointer.
             'data' - data to be set as the value of the new element.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.  
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
dll_iter_t DListPushFront(dll_t *list, void* data);

/*Function that inserts and sets a new ending element of the list.
  Arguments: 'list' - List pointer.
             'data' - data to be set as the value of the new element.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
dll_iter_t DListPushBack(dll_t *list, void* data);

/*Function that removes the head element of the list.
  Arguments: 'list' - List pointer.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
  dll_iter_t DListPopFront(dll_t *list);

/*Function that removes the ending element of the list.
  Arguments: 'list' - List pointer.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.  
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
  dll_iter_t DListPopBack(dll_t *list);

/*Function that searches for data stored in elements of range
           'from' up to 'to', but not including 'to' iterator.
  Arguments: Search range indices ('from', 'to' iterator),
             'match_func' - User function & parameters.
  Return value: Iterator to the 1st found element.
                If the element is not found- returns 'to' iterator.
  Complexity: O(n).
  Undefined B.: NULL Iterators or Iterators for not-same DLL, NULL function.*/
dll_iter_t DListFind
    (dll_iter_t from, dll_iter_t to, dll_match_t match_func,
     void* param);

/*Function that searches & retrieves the elements from range 
          'from' up to 'to', but not including 'to' iterator.
  Arguments: Search range indices ('from', 'to' iterator),
             'match_func' - User function & parameters.
             'dest_list' - DLL pointer to store found elements.
  Complexity: O(n) * complexity of match_func.
  Return value: found any = SUCCESS, not-found any = FAILURE.
  Undefined B.: NULL Iterators or Iterators for not-same DLL, NULL function.*/
int DListMultiFind
    (dll_iter_t from, dll_iter_t to, dll_match_t match_func,
    void *param, dll_t *dest_list);

/*Function that peforms action on elements of range 
          'from' up to 'to', but not including 'to' iterator.
  Arguments: Search range indices ('from', 'to' iterator),
             'action_func' - User function & parameters.  
  Return value: Done all actions = SUCCESS, failed action (if any) = FAILURE.
  Complexity: O(n) * complexity of action_func.
  Undefined B.: NULL Iterators or Iterators for not-same DLL, NULL function.*/
int DListForEach
    (dll_iter_t from, dll_iter_t to, dll_action_t action_func,
    void* param);

/* Function that relocates consecutive elements defined to by caller,
            to exist before element 'new_i'. passed iterator is invalidated.
  Arguments: Search range indices ('from', 'to' iterator),
             'action_func' - User function & parameters.
             'new_i' - Iterator marking relocation.
  Return value: None, On Error, DLL is unchanged.
  Complexity: O(1).
  Undefined B.: NULL Iterators or Iterators for not-same DLL.*/
void DListSplice (dll_iter_t from, dll_iter_t to, dll_iter_t where);

/********************* Iterator API Declerations  ****************************/

/*Function that checks if two iterators are the same. 
  Arguments: 'iter1', 'iter2' - Iterators to compare.
  Return value: same = SUCCESS, not same = FAILURE.
  Complexity: O(1).
  Undefined B.: NULL Iterators or Iterators for not-same DLL.*/
int DListIsSameIter(const dll_iter_t iter1, const dll_iter_t iter2);

/*Function that returns an iterator to the begining of the list.
  Arguments: 'list' - List pointer.
  Return value: DLL iterator to the first element of the list.
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
dll_iter_t DListBegin(const dll_t *list);

/*Function that returns an iterator to the end of the list.
  Arguments: 'list' - List pointer.
  Return value: DLL iterator to the ending element of the list.
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
dll_iter_t DListEnd(const dll_t *list);

/*Function that retrievs element following caller's iterator.
  Arguments: 'iter'- Iterator to DLL.
  Return value: Iter pointing at the element following caller's iterator.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
dll_iter_t DListNext(dll_iter_t iter);

/*Function that retrievs element preceeding caller's iterator.
  Arguments: 'iter'- Iterator to DLL.
  Return value: Iter pointing at the element following caller's iterator.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
dll_iter_t DListPrev(dll_iter_t iter);

/*****************************************************************************/

#endif /*(__ILRD_DLL_H__)*/

