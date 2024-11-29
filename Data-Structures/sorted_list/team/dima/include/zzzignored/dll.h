/*Name: HRD32
  Project: Work Sheet 8 - Data Structures - Doubly Linked List
  Reviewer: HRD32
  Date: 22/08/23
  Version: 1.0 
*/

#ifndef __DLL_H__
#define __DLL_H__

/******************************** Libraries  *******************************/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

typedef struct node node_ty; /*decleration*/
typedef struct iter iter_ty; /*for client use*/
typedef struct dll dll_ty;

typedef enum {SUCCESS = 1, FAILURE = 0} status_ty;
typedef enum {EMPTY = 1, NOT_EMPTY = 0} op_res_ty;

typedef int (*ActionFunc_ty)(void* data, void* user_data, void* param);
typedef int (*MatchFunc_ty)(const void* node_data,const void* comparison_data, void* param);

/*********************** S-list API Declerations  ****************************/

/*Function that inits the DLL struct
  Return value: pointer of type dll_ty, if unsuccessful malloc(), returns NULL;
  Undefined B.: N.A */
dll_ty* DllCreate();

/*Function that destroys the DLL struct
  Arguments: List pointer
  Return value: N.A
  Undefined B.: NULL dll_ty ptr */
void DllDestroy(dll_ty* list);

/*Function that inserts and sets a node before the indice specified by iter_ty.
  Arguments: Iterator, Data
  Return value: next-place iterator
  Undefined B.: inexistent node specified by iter */
iter_ty DllInsertBefore(iter_ty iter, void* data);

/*Function that removes a node before the indice specified by iter_ty.
  Arguments: Iterator
  Return value: next-place iterator
  Undefined B.: inexistent node specified by iter */
iter_ty DllRemove(iter_ty iter);

/*Function that retrieves a value stired in a node
  Arguments: Iterator 
  before the indice specified by iter_ty.
  Return value: data
  Undefined B.: inexistent node specified by iter */
void* DllGetData(iter_ty iter);

/*Function that sets a node specified by iter_ty.
  Arguments: Iterator, Data
  Return value: N.A
  Undefined B.: inexistent node specified by iter */
void DllSetData(iter_ty iter, void* data);

/*Function that checks list population status
  Arguments: List ptr
  Return value: EMPTY = 1, NOT_EMPTY = 0
  Undefined B.: NULL dll_ty ptr */
int DllIsEmpty(dll_ty *list);

/*Function that returns list nodes count
  Arguments: List ptr
  Return value: node count
  Undefined B.: NULL dll_ty ptr */
size_t DllSize(dll_ty *list);

/*Function that retrieves node data
  Arguments: user function & parameters
  Return value: Iterator
  Undefined B.: NULL dll_ty ptr, NULL function */
iter_ty DllFind(iter_ty from_iter, iter_ty to_iter,  void* data, 
					MatchFunc_ty match_func,void* usr_param);

/*Function that manipulates node data
  Arguments: user function & parameters
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: NULL dll_ty ptr, NULL function */
int DllForEach(iter_ty from_iter, iter_ty to_iter, void* data, 
					ActionFunc_ty action_func, void* usr_param);                

/********************* Iterator API Declerations  ****************************/

/*Function that checks if two iterators belong to the same list
  Arguments: 2 client iterators
  Return value: SUCCESS = 1, FAILURE = 0
  Undefined B.: NULL iter_ty ptrs */
int DllIterIsEqual(iter_ty iter1, iter_ty iter2);

/*Function that returns an iter to the begining of the list
  Arguments: list
  Return value: iterator
  Undefined B.: NULL dll_ty ptr */
iter_ty DllBegin(dll_ty *list);

/*Function that returns an iter to the end of the list
  Arguments: list
  Return value: iterator
  Undefined B.: NULL dll_ty ptr */
iter_ty DllEnd(dll_ty *list);

/*Function that returns an iter pointing to the next node of node pinted by the input iterator.
  Arguments: iterator
  Return value: iterator
  Undefined B.: NULL iter_ty ptr */
iter_ty DllNext(iter_ty iter);

/*Function that returns an iter pointing to the next node of node pinted by the input iterator.
  Arguments: iterator
  Return value: iterator
  Undefined B.: NULL iter_ty ptr */
iter_ty DllPrev(iter_ty iter);

iter_ty PushFront(dll_ty *list);
iter_ty PushBack(dll_ty *list);
iter_ty PopFront(dll_ty *list);
iter_ty PopBack(dll_ty *list);
iter_ty DllMultiFind(iter_ty from_iter, iter_ty to_iter,  void* data[], size_t element_num, 
					MatchFunc_ty match_func,void* usr_param);
void Splice(dll_ty *list, size_t cut_from, size_t cut_to, );
					
					

Size (O(n))
IsEmpty V
Begin V
End V
Next V 
Prev V
GetData V
IsSameIter V
Insert V
Remove
PushFront
PushBack
PopFront
PopBack
ForEach
Find V
MultiFind - finds many elements in given list
Splice - Cuts & pastes sequential elements in a given range to a given position in the list

/*Iterator Definition - Not intended for user. Iterator struct is defined here because evaluation of type iter_ty is mandatory for header file */
struct iter
{
      node_ty* node_ptr;
      #ifndef NDEBUG
      #define DEBUG_ONLY(x) x
      #else 
      #define DEBUG_ONLY(x) 

      # endif
};

#endif /*(__DLL_H__)*/
