/******************************************************************************/
/*
  Name: Sahar Attia
  Project: Data Structures - DLL
  Reviewer: Ahmad Agbariya
  Date: 22/08/23
  Version: 1.0
*/

#ifndef __DLL_H__
#define __DLL_H__

/******************************** Libraries  **********************************/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

typedef struct node node_t;
typedef node_t* dll_iter_t;
typedef struct dll dll_t;

typedef enum  {SUCCESS = 0, FAILURE} status_ty;
typedef enum {FALSE = 0, TRUE} boolean_ty;

typedef int (*DLLActionFunc_t)(void* data, void* param);
typedef int (*DLLMatchFunc_t)(const void* list_data, void* params);

/*********************** D-list API Declerations  ****************************/

/*
Description:
		Function that creates the list.
		
Arguments: 
		None.
		
Return value:
		pointer to the list. On Error: return NULL.
		
Complexity:
		O(1). 
  
Undefined B.:
		 None
*/
dll_t *DListCreate(void);

/*
Description:
		Function that destroys the list .
		
Arguments:
		list - pointer to the list.
		
Return value:
		None.
  
Complexity:
		O(n). 

Undefined B.:
		NULL pointer to list.
*/

void DListDestroy(dll_t *list);

/*
Description:
		Function that returns the number of elements in the list.

Arguments:
		list - pointer to the list.

Return value:
		Number of elements in the list.
		
Complexity:
		O(n).
		
Undefined B.:
		NULL pointer to list. 
*/
		
size_t DListSize(const dll_t *list);

/*
Description:
		Function that checks if the list is empty.
		
Arguments:
		List - pointer to the list.
		
Return value:
		TRUE if list is empty, FALSE if list isnt empty.
		
Complexity:
		O(1).
		
Undefined B.:
		NULL pointer to list. 
*/

int DListIsEmpty(dll_t *list);

/*
Description:
		Function that returns the value of the iterator given.

Arguments:
		iter - it is iterator to element.

Return value:
		the data of element.
		
Complexity:
		O(1).
		
Undefined B.:
		invalid iterator or tail iterator.
*/

void *DListGetData(dll_iter_t iter);

/*
Description:
		Function that sets the value of of data stored in iterator.

Arguments:
		iter - iterator to element to be set.
        data - data to be set..

Return value:
		None.

Complexity:
		O(1).

Undefined B.:
		invalid iterator or iterator recieved from DListEnd().
*/

void DListSetData(dll_iter_t iter, const void *data);

/*
Description:
		Function that inserts and sets an element before iterator given.
		If iterator is End then the new element will be set at the end of the list
		if iterator is Begin then the new element will be set at the beginning of 
		the list

Arguments:
		iter - the new element will be stored before 'iter'.
        data - contains the value of the new element.
        dlist - is the list of the iterator given

Return value:
		iterator that was inserted.
        On Error: invalid iterator.

Complexity:
		O(1).

Undefined B.:
		invalid iterator or iterator recieved from DListEnd().
		NULL pointer to list.
*/
		
dll_iter_t DListInsertBefore(dll_iter_t iter, void* data, dll_t *dlist);

/*
Description:
		Function that removes element iter from the list.

Arguments:
		iter - element to be removed

Return value:
		Iterator to Element after the removal, On Error: returns invalid iterator.

Complexity:
		O(1).

Undefined B.:
		invalid iterator or end iterator. 
*/

dll_iter_t DListRemove(dll_iter_t iter);

/*
Description:
		Function that inserts and sets an element at the beginning of the list.

Arguments:
		list - pointer to the list.
        data - contains the value of the new element.

Return value:
		Iterator to the beginning of the list.
        On Error: return invalid iterator. 

Complexity:
		O(1).
		
Undefined B.: 
		NULL pointer to list. 
*/

dll_iter_t DListPushFront(dll_t *list, void *data);

/*
Description:
		Function that inserts and sets an element at the end of the list.
		
Arguments: 
		list - pointer to the list.
        data - contains the value of the new element.
        
Return value: 
		Iterator to the end of the list.
        On Error: return returns invalid iterator. 
        
Complexity: 
		O(1).
  
Undefined B.: 
		NULL pointer to list.
*/

dll_iter_t DListPushBack(dll_t *list, void* data);

/*
Description: 
		Function that removes the first element of the list.

Arguments: 
		list - pointer to the list.

Return value:
		Iterator to the beginning of the list.
     	On Error: return invalid iterator. 

Complexity:
		O(1).

Undefined B.:
		NULL pointer to list.
*/

dll_iter_t DListPopFront(dll_t *list);

/*
Description:
		Function that removes the ending element of the list.

Arguments:
		list - pointer to the list.

Return value:
		Iterator to the end of the list.
        On Error: return invalid iterator.   

Complexity:
		O(1).

Undefined B.:
		NULL pointer to list. 
*/

dll_iter_t DListPopBack(dll_t *list);

/*
Description:
		Function that searches through out the list for the first element that 
		matches data with pram given, start the search from iterator from and 
		ends the search at iterator to, not include.

Arguments: 
		from is where the search will start,
		to is where the search endes, not includes to. 
  		match_func is user function for comparation.

Return value:
		Iterator of the 1st element found is range.
        if there was no match in range returns to iterator.

Complexity:
		O(n).
		
Undefined B.:
		invalid iterator or end iterator, iterators from a different list, 
		NULL function.
*/

dll_iter_t DListFind
(dll_iter_t from, dll_iter_t to, DLLMatchFunc_t match_func, void* params);

/*
Description:
		Function that preform action through out the list, start the the action
		from iterator from and ends	the action at iterator to, not include.

Arguments:
		from is where the search will start,
		to is where the search endes, not includes to. 
  		action_func is user function for action to preform.  

Return value:
		if function failed at any of the elements will return FAILURE and not do 
		the next ones, else it will return SUCCESS.

Complexity:
		O(n) * O(action_func)

Undefined B.:
		invalid iterator or end iterator, iterators from a different list, 
		NULL function.
*/

int DListForEach
(dll_iter_t from, dll_iter_t to, DLLActionFunc_t action_func, void* params);

/*
Description:
		Function that searches through out the list for all elements that 
		matches data with pram given, start the search from iterator from and 
		ends the search at iterator to, not include.

Arguments: 
		from is where the search will start,
		to is where the search endes, not includes to. 
  		match_func is user function for comparation.
  		destenation list to add the founded elements

Return value:
		if function failed at any of the elements will return FAILURE else it 
		will return SUCCESS.

Complexity:
		O(n).
		
Undefined B.:
		invalid iterator or end iterator, iterators from a different list, 
		NULL function, NULL pointer to list.
*/

int DListMultiFind(dll_iter_t from, dll_iter_t to, DLLMatchFunc_t match_func,
	void *param, dll_t *dest_list);

/* 
Description: 
		Function that relocates all elements between from and to not include to,
        to be before element where.
        
Arguments: 
		from is where the search will start,
		to is where the search endes, not includes to. 
		where iteretor marks where elements will move

Return value: 
		None, On Error: will not change. 
		
Complexity:
		O(1).
		
Undefined B.:
		invalid iterator or end iterator, or Iterators not from the same list.
*/

void DListSplice(dll_iter_t from, dll_iter_t to, dll_iter_t where);

/********************* Iterator API Declerations  ****************************/

/*
Description:
		Function that checks whether two iterators are the same. 

Arguments: iter1, iter2 Iterators to be compared.

Return value:
		TRUE if equal, false otherwise.

Complexity: 
		O(1).

Undefined B.:
		invalid iterator or end iterator, or Iterators not from the same list.
*/
int DListIsSameIter(dll_iter_t iter1, dll_iter_t iter2);

/*
Description:
		Function that returns the first element of the list.
  
Arguments:
		'list' - pointer to list.
	
Return value:
		iterator of the first element of the list.
		
Complexity:
		O(1).

Undefined B.:
		NULL pointer to list or a pointer mot initialized by DListCreate(). 
*/
dll_iter_t DListBegin(const dll_t *list);

/*
Description: 
		Function that returns an iterator to the end of the list.

Arguments: 
		'list' - pointer to list.

Return value: 
		iterator to last element of the list.

Complexity: 
		O(1).

Undefined B.:
		NULL pointer to list or a pointer mot initialized by DListCreate(). 
*/
dll_iter_t DListEnd(const dll_t *list);

/*
Description: 
		Function that returns the next element to iterator.

Arguments:
		'iter'- Iterator of the element previous to the element returned.

Return value: 
		Iterator of the next element in the list.

Complexity: 
		O(1).

Undefined B.: 
		invalid iterator or end iterator, or Iterators not from the same 
		list.
*/
dll_iter_t DListNext(dll_iter_t iter);

/*
Description: 
		Function that returns the previous element to iterator.

Arguments:
		'iter'- Iterator of the element next to the element returned.

Return value: 
		Iterator of the previous element in the list.

Complexity: 
		O(1).

Undefined B.: 
		invalid iterator or end iterator or Iterators not from the same 
		list.
*/
dll_iter_t DListPrev(dll_iter_t iter);

/******************************************************************************/

#endif /*(__DLL_H__)*/

