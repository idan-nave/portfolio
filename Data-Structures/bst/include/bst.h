/*
  Name: Idan Nave (HRD32)
  Project: Binary Search Tree
  Reviewer: Aya
  Date: 30/09/2023
  Version: 1.0 - Publication
           1.1 - bst_incidence_ty, change of complexities.
           1.2 - key terminology (insert, prev, next, find).
           1.3 - BSTRemove return value in case of 'root' \ 'end' argument.
                 BSTFind- based on bst_compare_ty logics & bst_keycomp_ty.

  Project Overview: API for a Binary Search Tree.
                    An iterator (bst_iter_ty) is provided for tree traversal.
                    An invalid iterator is considered as the BST's root.
                    Key duplication is not supported.
*/

#ifndef __ILRD_BST_H__
#define __ILRD_BST_H__

/******************************** Libraries  ********************************/

#include <stddef.h> /*size_ty*/

/******************************** Definitions  ******************************/

typedef struct  bst bst_ty;
typedef struct  node node_ty;
typedef         node_ty* bst_iter_ty;

typedef enum {PARENT= 0, LEFT = 1, RIGHT = 2}     bst_incidence_ty;
typedef enum {SUCCESS = 0, FAILURE}               bst_status_ty;
typedef enum {FALSE = 0, TRUE}                    bst_boolean_ty;

typedef int (*bst_action_ty)(void* key, void* param);
typedef int (*bst_compare_ty)
            (const void* key_in_tree, const void* key_to_cmp, void* params);

/*********************** BST API Declerations  ****************************/


/*Function that creats a binary search tree.
  Arguments: 'cmp_func' - user's cmp func for the sake of tree ordering.
             'params' - cmp func parameters.
  Return value: pointer to the binary search tree.
                On Error- returns NULL.
  Complexity: O(1). 
  Undefined B.: NULL pointer to cmp_func, */
bst_ty *BSTCreate(bst_compare_ty cmp_func, void *params);

/*Function that destroys a binary search tree.
  Arguments: 'bst' - pointer to binary search tree.
  Return value: N.A.
  Complexity: O(n). 
  Undefined B.: NULL pointer to a binary search tree, */
void BSTDestroy(bst_ty* bst);

/*Function that inserts a new tree-element without disrupting the sorting.
  Arguments: 'bst' - pointer to a tree, 
             'key' - data to insert.
  Return value: Iterator to the inserted element.
                On Error, returns invalid Iterator.
  Complexity: O(n)-  (considering an unbalanced tree).
  Undefined B.: NULL pointer to tree, NULL pointer to data
                Duplication of already-existing key*/
bst_iter_ty BSTInsert(bst_ty* bst, void *key);

/*Function that removes an element of the tree without disrupting it's sorting.
  Removal by key operation is supported by passing in iter returned by BSTFind.
  Arguments: 'iter' - iterator to an element to be removed.
  Return value:  Iterator to element following the removed element.
                 Passed iterator is invalidated.
                 If iter points to 'root' - returns iter to 'root'.
  Complexity: O(log2(n)) as tree blancing is not kept, but possibly- O(1), 
  Undefined B.: Invalid iterator*/
bst_iter_ty BSTRemove(bst_iter_ty iter);

/*Function that retrieves the data from an element pointed by iterator.
  Arguments:  'iter' - iterator to an element of the tree.
  Return value: void pointer.
  Complexity: O(1).
  Undefined B.: Invalid iterator*/
void* BSTGetData(bst_iter_ty iter);

/*Function that checks if the tree is empty.
  Arguments: 'bst' - pointer to a tree, 
  Return value: if empty = TRUE, othewise = FALSE.
  Complexity: O(1).
  Undefined B.: NULL pointer to tree*/
int BSTIsEmpty(const bst_ty* bst);

/*Function that returns the number of current elements in the tree.
  Arguments: 'bst' - pointer to a tree, 
  Return value: Num of elements currently in tree.
  Complexity: O(n).
  Undefined B.: NULL pointer to list*/
size_t BSTSize(const bst_ty* bst);

/*Function that finds the lowest-level key element in the tree (least deep,
  first fit) that matches the provided key, based on bst_compare_ty logics.
  bst_compare_ty must return a bst_keycomp_ty value, relative to 'key_to_cmp'.
  Arguments: 'bst' -  pointer to tree.
             'key_to_find' - value to be found.
  Return value: iterator to the found element. If element is not found - 
                it will return an invalid iterator (comparable with IsSameIter).
  Complexity: O(log2(n)).
  Undefined B.: invalid to iterator, NULL pointer to data_to_find.
                bst_compare_ty that returns invalid result.     */
bst_iter_ty BSTFind(const bst_ty* bst, void* key_to_find);

/*Function that executes an action func for every element in the range 
  specified  by 'from' iterator (included) up to 'to' (not included).
   Arguments: tree range indices ('from', 'to' iterator),
             'action_func', 'params' - User function & parameters.
  Return value: SUCCESS, On Error = FAILURE.
  Complexity: ( O(m) * complexity of action func) , where (m) is the number
              of nodes between the "from" and "to" iterators in the BST.
  Undefined B.: invalid iterators, NULL pointer to action_func, 
                NULL pointer to params, NULL pointer to bst, 
                Iterators of not-same BST */ 
int BSTForEach(bst_iter_ty from, bst_iter_ty to, 
                            bst_action_ty action_func ,void* params);


/**************************** Iterators API ***********************************/

/*Function that returns an iter to the begining of the tree.
  Arguments: pointer to tree.
  Return value: an iterator of the first element in the tree.
  Complexity: O(log2(n)).
  Undefined B.: NULL pointer to tree. */
bst_iter_ty BSTBegin(const bst_ty* bst);

/*Function that returns a tree element, following the passed element
  (given the passed element is valid).
  Arguments: 'iter' - iterator to an element of the tree.
  Return value: iterator to the next element.
                If iter points to the 'end' element- iter is returned as is.
  Complexity: O(log2(n)).
  Undefined B.: invalid iterator */
bst_iter_ty BSTNext(bst_iter_ty iter);

/*Function that returns the a tree element, ahead (previous) of the passed
  element (given the passed element is valid).
  Arguments: 'iter' - iterator to an element of the tree.
  Return value: iterator to the previous element.
                If iter points to the 'begin' element- iter is returned as is.
  Complexity: O(log2(n)).
  Undefined B.: invalid iterator */
bst_iter_ty BSTPrev(bst_iter_ty iter);

/*Function that returns an iterator to the ending bst-element
  (as considered by user's compar function)
  Arguments: pointer to tree.
  Return value: an iterator of the end element of the tree.
  Complexity: O(log2(n)).
  Undefined B.:  NULL pointer to tree. */
bst_iter_ty BSTEnd(const bst_ty* bst);

/*Function that checks if given iterators are the same. 
  Arguments: two bst-iterators.
  Return value: if same = TRUE, othewise = FALSE.
  Complexity: O(1).
  Undefined B.: invalid iterators. */
int BSTIsSameIter(bst_iter_ty iter, bst_iter_ty iter_to_cmp);

#endif /*(__ILRD_BST_H__)*/