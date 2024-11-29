/*
  Name: Idan Nave
  Project: Work Sheet 12 - Data Structures - Sorted List
  Reviewer: Agbaria
  Date: 27/08/23
  Version: 1.0
  Project Overview: API for using a Sorted list. User is given an iterator for traversing of the list.
*/

#ifndef __ILRD_SORTED_LIST_H__
#define __ILRD_SORTED_LIST_H__

/******************************** Libraries  *********************************/

#include <stddef.h> /*size_t*/
#include "/home/idan/Documents/Dev/Git_WD/ds/dll/include/dll.h"
/*dll_status_t, dll_boolean_t*/

/******************************** Definitions  ******************************/

typedef struct sorted_list sorted_list_t;
typedef struct sorted_list_iter sor_iter_t;

/*typedef enum {FALSE = 0, TRUE} sor_boolean_t;*/
typedef int (*sorted_list_action_t)(void* data, void* param);
typedef int (*sorted_list_is_match_t)(const void* , const void* );

/*Returns difference 1st param - 2nd param*/
typedef int (*sorted_list_compare_t)(const void* , const void* );

/************************ definitions in the document *************************/

/* invalid iterator =  SlistEnd() */
/* undefined behaviors: iterators that do not 'belong' to the same list */

/*********************** D-list API Declerations  ****************************/

/*Function that creates a list.
  Arguments: None.
  Return value: pointer to DLL. On Error, returns NULL.
  Complexity: O(1). 
  Undefined B.: NULL pointer to compare_func*/
sorted_list_t* SListCreate(sorted_list_compare_t compare_func);

/*Function that destroys a list.
  Arguments: user comarision logic.
  Return value: None.
  Complexity: O(n). 
  Undefined B.: NULL ptr of list */
void SListDestroy(sorted_list_t *list);

/*Function that returns the number of current elements in the list.
  Arguments: 'list' - List pointer.
  Return value: Num of current valid elements in list.
  Complexity: O(n).
  Undefined B.: NULL pointer to DLL. */
size_t SListSize(const sorted_list_t *list);

/*Function that checks if DLL is empty.
  Arguments: 'list' - List pointer.
  Return value: if empty = TRUE, othewise = FALSE.
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
int SListIsEmpty(sorted_list_t *list);

/*Function that retrieves the value of caller's iterator.
  Arguments: 'iter'- Iterator to the element which value is to be retrieved.
  Return value: data - void* pointer.
  Complexity: O(1).
  Undefined B.: NULL Ierator. */
void* SListGetData(sor_iter_t iter);

/*Function that inserts an element to the list without disrupting the sorting.
  Arguments: 'slist' - pointer to list,
             'data' - data to be set as the element's new value.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.  Complexity: O(n).
  Undefined B.: NULL pointer to data, NULL pointer to list*/
sor_iter_t SListInsert(sorted_list_t *slist, void* data);

/*Function that removes element iter.
  Arguments: 'iter' - Iterator to the element to-be removed.
  Return value: Iterator to element following the removed element. Passed iterator is invalidated.
  Complexity: O(1).
  Undefined B.: NULL Iterator */
sor_iter_t SListRemove(sor_iter_t iter);

/*Function that removes the head element of the list.
  Arguments: 'list' - List pointer.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
sor_iter_t SListPopFront(sorted_list_t *list);

/*Function that removes the ending element of the list.
  Arguments: 'list' - List pointer.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.  
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
sor_iter_t SListPopBack(sorted_list_t *list);

/*Function that searches for data stored in elements of range
           'from' up to 'to', but not including 'to' iterator.
  Arguments: Search range indices ('from', 'to' iterator),
             'match_func' - User function & parameters.
  Return value: Iterator to the 1st found element.
                If the element is not found- returns 'to' iterator.
  Complexity: O(n).
  Undefined B.: NULL Iterators or Iterators for not-same DLL, NULL function.*/
sor_iter_t SListFind
(sor_iter_t from, sor_iter_t to, void* params, sorted_list_t *list);

/*Function that searches & retrieves the elements from range 
          'from' up to 'to', but not including 'to' iterator.
  Arguments: Search range indices ('from', 'to' iterator),
             'match_func' - User function & parameters.
             'dest_list' - DLL pointer to store found elements.
  Return value: found any = SUCCESS, not-found any = FAILURE.
  Complexity: O(n) * complexity of action_func.
  Undefined B.: NULL Iterators or Iterators for not-same DLL, NULL function.*/int SListForEach
(sor_iter_t from, sor_iter_t to, sorted_list_action_t action_func, void* params);

/*Function that searches elements from range 
          'from' up to 'to', but not including 'to' iterator.
  Arguments: Search range indices ('from', 'to' iterator),
             'match_func' - User function & parameters.
             'dest_list' - DLL pointer to store found elements.
  Complexity: O(n) * complexity of match_func.
  Return value: Iterator to the 1st found element.
                If the element is not found- returns 'to' iterator.
  Undefined B.: NULL Iterators or Iterators for not-same DLL, NULL function.*/
sor_iter_t SlistFindIF
(sor_iter_t from, sor_iter_t to, sorted_list_is_match_t conditional_func, void *params);


/*Function that merges src list into the dest_list in an ordered approach.
  Arguments: 2 pointers to list.
  Return value: None, On Error, DLL is unchanged.
  Complexity: O(n*m).
  Undefined B.: NULL pointers to list*/
sorted_list_t* SlistMerge(sorted_list_t *dest_list, sorted_list_t *src_list);

/********************* Iterator API Declerations  ****************************/

/*Function that checks if two iterators are the same. 
  Arguments: 'iter1', 'iter2' - Iterators to compare.
  Return value: same = SUCCESS, not same = FAILURE.
  Complexity: O(1).
  Undefined B.: NULL Iterators or Iterators for not-same DLL.*/
int SListIsSameIter(sor_iter_t iter1, sor_iter_t iter2);

/*Function that returns an iterator to the begining of the list.
  Arguments: 'list' - List pointer.
  Return value: DLL iterator to the first element of the list.
  Complexity: O(1).
  Undefined B.: NULL pointer to DLL. */
sor_iter_t SListBegin(const sorted_list_t *list);

/*Function that retrievs element following caller's iterator.
  Arguments: 'iter'- Iterator to DLL.
  Return value: Iter pointing at the element following caller's iterator.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
sor_iter_t SListEnd(const sorted_list_t *list);

/*Function that receives an element in the list, and returns the following element.
   Arguments: an iterator from a list.
   Return value: iterator to the next element.
   Complexity: O(1).
   Undefined B.: invalid iterator */
sor_iter_t SListNext(sor_iter_t iter);

/*Function that retrievs element preceeding caller's iterator.
  Arguments: 'iter'- Iterator to DLL.
  Return value: Iter pointing at the element following caller's iterator.
  Complexity: O(1).
  Undefined B.: NULL Iterator. */
sor_iter_t SListPrev(sor_iter_t iter);

/******************************************************************************/

struct sorted_list_iter
{
	dll_iter_t internal_iter;
	#ifndef NDEBUG
	sorted_list_t *list;
	#endif
};

#endif /*(__ILRD_SORTED_LIST_H__)*/


