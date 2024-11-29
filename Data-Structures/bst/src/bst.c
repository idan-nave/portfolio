/*
  Name: Idan Nave (HRD32)
  Project: Binary Search Tree
  Reviewer: Aya
  Date: 30/09/2023
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <stdio.h>              /* perror */
#include <stdlib.h>             /* malloc(), free() */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */
#include <string.h>             /* memcpy */

#include "bst.h"

/*****************************************************************************/
/********************************* Type Definitions **************************/
/*****************************************************************************/

	/**************************** Value Macros  *****************************/

	#define NO_DIFF   	      	0
	#define NUM_OF_ADJACENTS 	3
	#define ADJ_LIST_SIZE 		( (NUM_OF_ADJACENTS) * (sizeof(void*)) )
	#define NODE_MAGIC          0xDEADC0DE

	/******************************* Op Macros  *****************************/

	#define FREE(node_to_free) \
	{\
    	free(node_to_free);\
    	node_to_free = NULL;\
	}

	#define SIGN_CHANGE(a, b) (((a) > 0 && (b) < 0) || ((a) < 0 && (b) > 0))

 	/******************************** Objects  ******************************/

	/*Struct for a node within BST */
	struct node
	{
		void *key;
		node_ty *adjacent[NUM_OF_ADJACENTS];
	};

	/*Struct manager for BST */
	struct bst
	{
		node_ty root;
		void *params;
		bst_compare_ty cmp_func;	
	};

/*****************************************************************************/
/********************* Static Helper Functions Declerations ******************/
/*****************************************************************************/

/**************************** Traversal Functions  ***************************/

static node_ty* GoDownMost (node_ty* node, bst_incidence_ty inc);
static node_ty* GoUpMost (node_ty* node, bst_incidence_ty inc);
static node_ty* GoUpToRoot (node_ty* node);
static node_ty* Left (node_ty* node);
static node_ty* Right (node_ty* node);
static node_ty* Parent (node_ty* node);

/********************** Node Properties Functions  ***************************/

static int IsLeaf (node_ty* node);
static int IsRoot (node_ty* node);
static int HasTwoChilds (node_ty* node);
static node_ty* HasOneChild (node_ty* node);
static int HasRightChild (node_ty* node);
static int HasLeftChild (node_ty* node);
static bst_incidence_ty WhichChild (node_ty* node);
static int IsRight (node_ty* node);
static int IsLeft (node_ty* node);

/************************ Node Manipulation Functions  ***********************/

/*Function to allocate & set a new node. On Error, returns NULL.*/
static node_ty* CreateNode (void *key);
static void LinkParentAndChild (node_ty* node, bst_incidence_ty descendant_inc);
static void CopyKey (node_ty* dest, node_ty* src);
static void SetAdjacency(node_ty* node, bst_incidence_ty inc, node_ty* set);
static void SetKey (node_ty* node, void* key);

/**************************** Parsing Macros  *****************************/
static node_ty* ToNode (bst_iter_ty to_parse);
static bst_iter_ty ToIter (node_ty* to_parse);
static node_ty* ToRoot (bst_ty* to_parse);
static bst_ty* ToBST (bst_iter_ty to_parse);

/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/

bst_ty *BSTCreate(bst_compare_ty cmp_func, void *params)
{    
    bst_ty* bst = (bst_ty*)malloc(sizeof(bst_ty));

	assert(NULL != cmp_func);

    /* validate successful malloc*/
    if(NULL == bst)
    {
        errno = ENOMEM;
        perror("Unsuccessful allocation of new bst");
    	return NULL;
    }
    
    /* init root */
	SetKey (ToRoot(bst), (void*)NODE_MAGIC);
	SetAdjacency(ToRoot(bst), PARENT, NULL);
	SetAdjacency(ToRoot(bst), LEFT, NULL);
	SetAdjacency(ToRoot(bst), RIGHT, NULL);

    /* init bst properties */
    bst->cmp_func = cmp_func;
    bst->params = params;

    return bst;
}

void BSTDestroy(bst_ty *bst)
{
	bst_iter_ty trav = {0};
	bst_incidence_ty route = RIGHT;
	node_ty* node = NULL;

	assert( NULL != bst);

    trav = BSTBegin(bst);
    node = ToNode(trav);

	while (FALSE == BSTIsEmpty (bst))
	{
		if (TRUE == IsLeaf(trav))
		{
			FREE(node);
		  	trav = Parent(trav);
			node = ToNode(trav);
		}
		else
		{
			FlipRoute (route);
			node = GoDownMost(trav, route);
		}
	}
	FREE(bst);
}

bst_iter_ty BSTInsert(bst_ty* bst, void *key)
{
	bst_iter_ty trav = {0};
	bst_iter_ty trav_parent = {0};
	bst_iter_ty res_iter = {0};
	node_ty* inserted = NULL;
	node_ty* res_node = NULL;
	void* trav_key = NULL;
	int res = 0;
	int last_direction = LEFT;

	assert(NULL != bst);
	assert(NULL != key);

	/* create & validate successful malloc*/
	inserted = CreateNode(key);
    if(NULL == bst)
    {
        errno = ENOMEM;
        perror("Unsuccessful allocation of new bst");
    	return NULL;
    }

    if ( BSTIsEmpty(bst) )
	{
		SetAdjacency(ToRoot(bst), LEFT, inserted);
		SetAdjacency(inserted, PARENT, ToRoot(bst));
		return ToIter(inserted);
	}
	
	trav = ToIter(ToRoot((bst_ty*)bst));

	while (NULL != trav)
	{
		trav_parent = Parent(trav);
    	trav_key = BSTGetData(trav);
		res = bst->cmp_func(trav_key, key, bst->params);
		if (NO_DIFF < res) /*GREATER*/
		{
			trav = Left(trav);
			last_direction = LEFT;
		}
		else if (NO_DIFF > res) /*LESSER*/
		{
			trav = Right(trav);
			last_direction = RIGHT;
		}
	}

	SetAdjacency(inserted, PARENT, ToNode(trav_parent));
	SetAdjacency(ToNode(trav_parent), last_direction, inserted);
	
	return ToIter(inserted);
}

bst_iter_ty BSTRemove(bst_iter_ty iter)
{
	node_ty* to_rmv = NULL;

	assert(NULL != to_rmv);

    /*preperation of related nodes for return exp.*/
	to_rmv 	= ToNode(iter);
	parent	= Parent(to_rmv); 

	if (TRUE == IsLeaf(to_rmv)) /*leaf node*/
	{
		SetAdjacency(Parent(to_rmv), WhichChild(to_rmv), NULL);
	}

	if (NULL!= HasOneChild(to_rmv)) /*has one child*/
	{
		LinkParentAndChild (to_rmv, WhichChild(to_rmv));
	}

	if (TRUE == HasTwoChild(to_rmv)) /*has two childs*/
    {
		to_rmv = Left(to_rmv);
		to_rmv = GoDownMost(to_rmv, RIGHT);
		SetAdjacency(Parent(to_rmv), WhichChild(to_rmv), NULL);
		CopyKey (ToNode(iter), to_rmv);
	}
	FREE(to_rmv);
}

void* BSTGetData(bst_iter_ty iter)
{
	node_ty* node = ToNode(iter);

	assert(NULL != node);

	return node->key;
}

size_t BSTSize(const bst_ty* bst)
{
	size_t size = 0;
	bst_iter_ty trav =  NULL;
	node_ty* node = NULL;

	assert(NULL != bst);

	if(TRUE == BSTIsEmpty(bst))
	{
		return 0;
	}

    trav = BSTBegin(bst);

	while (FALSE == BSTIsSameIter(trav, BSTEnd(bst)))
	{
		trav = BSTNext(trav);
	  	++size;
	}
	return size;
}

/*****************************************************************************/
/******************** BST Traversing - API Definitions  **********************/
/*****************************************************************************/

bst_iter_ty BSTFind(const bst_ty* bst, void* key_to_find)
{
	void* trav_key = NULL;
	bst_iter_ty trav = {0};
	int res = NO_DIFF;

	assert(NULL != bst);
	assert(NULL != key_to_find);

	trav = ToIter(ToRoot((bst_ty*)bst));
    trav_key = BSTGetData(trav);

	while (NULL != trav)
	{
		res = bst->cmp_func(trav_key, key_to_find, bst->params);
		if (NO_DIFF < res) /*GREATER*/
		{
			trav = Left(trav);
		}
		else if (NO_DIFF > res) /*LESSER*/
		{
			trav = Right(trav);
		}
		else
		{
			return trav;
		}
    	trav_key = BSTGetData(trav);
	}
	return BSTEnd(bst); /*NOT FOUND*/
}

int BSTForEach(bst_iter_ty from, bst_iter_ty to, 
                            bst_action_ty action_func ,void* params)
{
	bst_iter_ty trav = from;

	assert(NULL != ToNode(from));
	assert(NULL != ToNode(to));
	assert(NULL != action_func);

	while (FALSE == BSTIsSameIter(trav, to))
	{
	  	if (FAILURE == action_func( BSTGetData(trav), params))
	  	{
	  		return FAILURE;
	  	}
	  	trav = BSTNext(trav);
	}
	return SUCCESS;
}

/*****************************************************************************/
/********************* Iterator API Definitions  *****************************/
/*****************************************************************************/

bst_iter_ty BSTBegin(const bst_ty* bst)
{
	node_ty* root = NULL;

	assert(NULL != (bst_ty*)bst);
	
	root = ToRoot((bst_ty*)bst);
	return ToIter( GoDownMost(root, LEFT) );
}

bst_iter_ty BSTEnd(const bst_ty *bst)
{
	assert(NULL != (bst_ty*)bst);

	return ToIter(ToRoot((bst_ty*)bst));
}

bst_iter_ty BSTNext(bst_iter_ty iter)
{
	
	node_ty* trav = ToNode(iter);

	assert(NULL != trav);

    /*find min of right sub-tree*/
    if(HasRightChild(trav))
    {
		trav = Right(trav);
		trav = GoDownMost(trav, LEFT);
    }
    else /*if IsRight or left leaf*/
    {
    	while(IsRight(trav))
		{
			trav = Parent(trav);
		}
		trav = Parent(trav);
    }
	return ToIter(trav);
}

bst_iter_ty BSTPrev(bst_iter_ty iter)
{
	
	node_ty* trav = ToNode(iter);

	assert(NULL != trav);

    /*find max of left sub-tree*/
    if(HasLeftChild(trav))
    {
		trav = Left(trav);
		trav = GoDownMost(trav, RIGHT);
    }
    else /*if IsLeft or right leaf*/
    {
    	while(IsLeft(trav))
		{
			trav = Parent(trav);
		}
		trav = Parent(trav);
    }
	return ToIter(trav);
}

int BSTIsSameIter(bst_iter_ty iter, bst_iter_ty iter_to_cmp)
{
	node_ty* node1 = ToNode(iter);
	node_ty* node2 = ToNode(iter_to_cmp);

	assert(NULL != node1);
	assert(NULL != node2);

	if (node1 == node2)
	{
		return TRUE;
	}
	return FALSE;
}

int BSTIsEmpty(const bst_ty* bst)
{
	assert( NULL != bst);

 	return (NULL == Left(ToRoot((bst_ty*)bst)));
}

/*****************************************************************************/
/**************************** Helper Functions Definitions *******************/
/*****************************************************************************/

/**************************** Traversal Functions  ***************************/

/*Function to return a node at the end of a consucutive traversal (down) in the same direction 'inc', starting at a given node of the tree.
Undefined B.: invalid bst_incidence_ty (which isn't any of RIGHT or LEFT)*/
static node_ty* GoDownMost (node_ty* node, bst_incidence_ty inc)
{
	node_ty* trav = node;
	
	/*user can call this func with an invalid bst_incidence_ty argument:*/
	assert(PARENT != inc);
	assert(NULL != node);

	while(NULL != trav->adjacent[inc])
	{
		trav = trav->adjacent[inc];
	}
	return trav;
}

/*Function to return a node at the end of a consucutive traversal (up) in the same direction 'inc', starting at a given node of the tree.
If node is NULL, NULL is returned as is.
Undefined B.: invalid bst_incidence_ty (which isn't any of RIGHT or LEFT)*/
static node_ty* GoUpMost (node_ty* node, bst_incidence_ty inc)
{
	node_ty* trav = node;

	/*user can call this func with an invalid bst_incidence_ty argument:*/

	assert(PARENT != inc);
	assert(NULL != node);

	if (LEFT == inc)
	{
		inc = RIGHT;
	}
	else if(RIGHT == inc)
	{
		inc = LEFT;
	}

	while(inc == WhichChild(trav))
	{
		trav = Parent(trav);
	}
	return trav;
}

/*Function to return a tree root by a given node of the same tree.*/
static node_ty* GoUpToRoot (node_ty* node)
{
	node_ty* trav = node;

	assert(NULL != node);

	while(NULL != Parent(trav))
	{
		trav = Parent(trav);
	}
	return trav;
}

/*Function to return a node's left descendant node. may return NULL*/
static node_ty* Left (node_ty* node)
{
	node_ty* trav_l = node;

	assert(NULL != node);

	return trav_l->adjacent[LEFT];
}

/*Function to return a node's right descendant node. may return NULL*/
static node_ty* Right (node_ty* node)
{
	node_ty* trav_r = node;

	assert(NULL != node);

	return trav_r->adjacent[RIGHT];
}

/*Function to return a node's parent node.
  If encounterd at root node or requested root's 'parent' - returns root node*/
static node_ty* Parent (node_ty* node)
{
	node_ty* trav = node;

	assert(NULL != node);
	
	if (NODE_MAGIC == (size_t)trav		/*MEANING NODE IS ACTUALLY ROOT*/
		 || NODE_MAGIC == (size_t)(trav->adjacent[PARENT]))
	{
		return trav;		/*DO NOT ALLOW TRAVERSING UP*/
	}

	return trav->adjacent[PARENT];
}

/********************** Node Properties Functions  ***************************/

/*Function to return whether a node is a tree-leaf.*/
static int IsLeaf (node_ty* node)
{
	assert(NULL != node);

	if (NULL == Left(node) && NULL == Right(node))
	{
		return TRUE;
	}
	return FALSE;
}

/*Function to return whether a node is a tree-root.*/
static int IsRoot (node_ty* node)
{
	assert(NULL != node);

	if (NODE_MAGIC == *((int*)BSTGetData(Parent(node))))
	{
		return TRUE;
	}

	return FALSE;
}

/*Function to return whether a node is a parent to two children nodes.*/
static int HasTwoChilds (node_ty* node)
{
		
	assert(NULL != node);

	if (HasRightChild(node) && HasLeftChild(node))
	{
		return TRUE;
	}
	return FALSE;
}

/*Function to return a node's single child adjacency. if none- returns root.*/
static node_ty* HasOneChild (node_ty* node)
{
	assert(NULL != node);

	if (FALSE == HasTwoChilds(node) && FALSE == IsLeaf(node))
	{
		if (NULL != Left(node))
		{
			return Left(node);
		}
		return Right(node);
	}
	return NULL; /*return invalid node*/
}

/*Function to cheack whether a node has a right child*/
static int HasRightChild (node_ty* node)
{
	assert(NULL != node);

	if (NULL != Right(node))
	{
		return TRUE;
	}
	return FALSE;
}

/*Function to cheack whether a node has a left child*/
static int HasLeftChild (node_ty* node)
{
	assert(NULL != node);

	if (NULL != Left(node))
	{
		return TRUE;
	}
	return FALSE;
}

/*Function to return a node's relative adjacency to it's parent node
  On Error- returns PARENT*/
static bst_incidence_ty WhichChild (node_ty* node)
{
	node_ty* parent = NULL;

	assert(NULL != node);

	parent = Parent(node);

	if (node == Left(parent))
	{
		return LEFT;
	}

	if (node == Right(parent))
	{
		return RIGHT;
	}

	return PARENT; /*INVALID ITER*/
}
/*Function to cheack whether a node has a right child*/
static int IsRight (node_ty* node)
{
	assert(NULL != node);

	if (RIGHT == WhichChild(node))
	{
		return TRUE;
	}
	return FALSE;
}

/*Function to cheack whether a node has a left child*/
static int IsLeft (node_ty* node)
{
	assert(NULL != node);

	if (LEFT == WhichChild(node))
	{
		return TRUE;
	}
	return FALSE;
}

/*Function to return the opposite of a given route*/
static int FlipRoute (bst_incidence_ty route_to_flip)
{
	assert(PARENT != route_to_flip);

		if (RIGHT == route)
		{
			route = LEFT;
		}
		else
		{
			route = RIGHT;
		}
}

/************************ Node Manipulation Functions  ***********************/

/*Function to allocate & set a new node. On Error, returns NULL.*/
static node_ty* CreateNode (void *key)
{
    node_ty* new = (node_ty*)malloc(sizeof(node_ty));

	assert(NULL != key);

    /* validate successful malloc*/
    if(NULL == new)
    {
        errno = ENOMEM;
        perror("Unsuccessful allocation of new bst");
    	return NULL;
    }

	SetKey (new, key);
	SetAdjacency(new, PARENT, NULL);
	SetAdjacency(new, LEFT, NULL);
	SetAdjacency(new, RIGHT, NULL);

	return new;
}

/*Function to set a node's parent-adjacency to point to the node's descendant.
Undefined B.: invalid bst_incidence_ty (which isn't any of RIGHT or LEFT)*/
static void LinkParentAndChild (node_ty* node, bst_incidence_ty descendant_inc)
{
	assert(NULL != node);
	assert(PARENT != descendant_inc);

	SetAdjacency(Parent(node),WhichChild(node), node->adjacent[descendant_inc]);
	SetAdjacency(node->adjacent[descendant_inc], PARENT, Parent(node));
}

/*Function to copy a node's key from 'src' to node 'dest' by num of 'bytes'*/
static void CopyKey (node_ty* dest, node_ty* src)
{
	assert(NULL != src);
	assert(NULL != dest);
	assert(NULL != src->key);

	dest->key =  src->key;
}

/*Function to set a node's adjacency list.
Undefined B.: invalid bst_incidence_ty (which isn't any of RIGHT/LEFT/PARENT)*/
static void SetAdjacency(node_ty* node, bst_incidence_ty inc, node_ty* set)
{
	assert(NULL != node);  /*set can be NULL*/

	node->adjacent[inc] = set;
}

/*Function to set a node's key*/
static void SetKey (node_ty* node, void* key)
{
	assert(NULL != node);

	node->key = key;
}

/**************************** Parsing Macros  *****************************/

static node_ty* ToNode (bst_iter_ty to_parse)
{
	return (node_ty*)to_parse;
}

static bst_iter_ty ToIter (node_ty* to_parse)
{
	return (bst_iter_ty)to_parse;
}

static node_ty* ToRoot (bst_ty* to_parse)
{
	return (node_ty*)(&to_parse->root);
}

static bst_ty* ToBST (bst_iter_ty to_parse)
{
	return (bst_ty*)(to_parse);
}