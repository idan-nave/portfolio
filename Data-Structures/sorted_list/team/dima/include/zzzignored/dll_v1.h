/******************************************************************************/
/*
  Name: Aya
  Project: Work Sheet 8 - Data Structures - DLL
  Reviewer: ???
  Date: 22/08/23
  Version: 1.0
*/

#ifndef __DLL_H__
#define __DLL_H__

/******************************** Libraries  **********************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

typedef struct node node_ty;
typedef node_ty* dll_iter_ty;
typedef struct dll dll_ty;

typedef enum  {SUCCESS = 1, FAILURE = 0} status_ty;
typedef enum {EMPTY = 1, NOT_EMPTY = 0} op_res_ty;
typedef enum {TRUE = 1, FALSE = 0} boolean_ty;

typedef int (*DLLActionFunc_ty)(void* data, void* param);
typedef int (*DLLMatchFunc_ty)(const void* list_data, void* params);

/*********************** D-list API Declerations  ****************************/

/*Function that inits the DLL struct
  Arguments: None.
  Return value: pointer of type dll_ty, if unsuccessful malloc(), returns NULL;
  Complexity: O(1). 
  Undefined B.: */
dll_ty *DListCreate(void);

/*Function that destroys the DLL struct
  Arguments: List pointer.
  Return value: None.
  Complexity: O(n). 
  Undefined B.: */
void DListDestroy(dll_ty *list);

/*Function that returns list size.
  Arguments: List ptr.
  Return value: Num of elements in list.
  Complexity: O(n).
  Undefined B.: NULL dll_ty ptr */
size_t DListSize(const dll_ty *list);

/*Function that checks if list is empty.
  Arguments: List ptr.
  Return value: EMPTY = 1, NOT_EMPTY = 0.
  Complexity: O(1).
  Undefined B.: NULL dll_ty ptr.*/
int DListIsEmpty(dll_ty *list);

/*Function that retrieves a value stored in a node
  Arguments: Iterator. 
  before the indice specified by dll_iter_ty.
  Return value: data
  Complexity: O(1).
  Undefined B.: inexistent node specified by iter */
void *DListGetData(dll_iter_ty iter);

void *DListSetData(dll_iter_ty iter);

/*Function that inserts and sets a node before the indice specified by iter_ty.
  Arguments: Iterator, Data
  Return value: SUCCESS = 'regular' iterator, FAILURE = tail_iterator.
  Complexity: O(1).
  Undefined B.: inexistent node specified by iter */
dll_iter_ty DListInsertBefore(dll_iter_ty iter, void* data);

/*Function that removes a node before the indice specified by dll_iter_ty.
  Arguments: Iterator
  Return value: iterator to next node.
  Complexity: O(1).
  Undefined B.: inexistent node specified by iter */
dll_iter_ty DListRemove(dll_iter_ty iter);

/*Function that inserts and sets a node at the head of the list.
  Arguments: Iterator, Data
  Return value: SUCCESS = 'regular' iterator, FAIL = tail iterator.
  Complexity: O(1).
  Undefined B.: inexistent node specified by iter */
dll_iter_ty DListPushFront(dll_ty *list, void* data);

/*Function that inserts and sets a node at the tail of the list.
  Arguments: Iterator, Data
  Return value: SUCCESS = 'regular' iterator, FAIL = tail iterator.
  Complexity: O(1).
  Undefined B.: inexistent node specified by iter */
dll_iter_ty DListPushBack(dll_ty *list, void* data);

/*Function that removes a node from the head of the list.
  Arguments: Iterator
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: inexistent node specified by iter */
dll_iter_ty DListPopFront(dll_ty *list);

/*Function that removes a node from the tail of the list.
  Arguments: Iterator
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: inexistent node specified by iter */
dll_iter_ty DListPopBack(dll_ty *list);

/*Function that retrieves node data - the search DOES NOT INCLUDE to!
  Arguments: user function & parameters
  Return value: Iterator
  Complexity: O(n).
  Undefined B.: NULL sll_ty ptr, NULL function */
dll_iter_ty DListFind
(dll_iter_ty from, dll_iter_ty to, DLLMatchFunc_ty match_func, void* params);

/*Function that manipulates node data - the action is NOT PERFORMED on 'to'!
  Arguments: user function & parameters
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: NULL sll_ty ptr, NULL function */
int DListForEach
(dll_iter_ty from, dll_iter_ty to, DLLActionFunc_ty action_func, void* params);

/* Finds all elements in the DLL which match param. Search DOES NOT INCLUDE 'to'!
   Arguments: from and to iters, match function, param - value to be found.
     dest_list - a place to store all elments with matching value searched.
   Return value: int, 'telling' the user if found any element/s or none. 
   */
int DListMultiFind(dll_iter_ty from, dll_iter_ty to, DLLMatchFunc_ty match_func,
	void *param, dll_ty *dest_list);

/* 'Moves' a few consecutive members in the list to another location inside
	the list. (Cut-Paste).
	Arguments: dll_iter_ty from, to, rak_where_beemet.
	Complexity: O(1).
	Undefined B.: iterators do not 'belong' to the correct list. */
void DListSplice(dll_iter_ty from, dll_iter_ty to, dll_iter_ty rak_where_beemet);

/********************* Iterator API Declerations  ****************************/

/*Function that checks if two iterators belong to the same list
  Arguments: 2 client iterators
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: NULL dll_iter_ty ptrs */
int DListIsSameIter(dll_iter_ty iter1, dll_iter_ty iter2);

/*Function that returns an iter to the begining of the list
  Arguments: list
  Return value: iterator
  Undefined B.: NULL dll_ty ptr */
dll_iter_ty DListBegin(dll_ty *list);

/*Function that returns an iter to the end of the list
  Arguments: list
  Return value: iterator
  Undefined B.: NULL dll_ty ptr */
dll_iter_ty DListEnd(dll_ty *list);

/*Function that returns an iter pointing to the next node of node pointed by the input iterator.
  Arguments: iterator
  Return value: iterator
  Undefined B.: NULL dll_iter_ty ptr */
dll_iter_ty DListNext(dll_iter_ty iter);

/*Function that returns an iter pointing to the prev node of node pointed by the input iterator.
  Arguments: iterator
  Return value: iterator
  Undefined B.: NULL dll_iter_ty ptr */
dll_iter_ty DListPrev(dll_iter_ty iter);

/******************************************************************************/

/*Dont look here stupid - user descretion is advised*/



#endif /*(__DLL_H__)*/



/*source file
struct node
{
  void *data;
  node_ty *next;
  node_ty *prev;
};

struct dll
{
  node_ty head;
  node_ty tail;
};*/
