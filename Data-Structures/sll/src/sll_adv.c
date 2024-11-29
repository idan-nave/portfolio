/********************************** ws6_sll.c  ***************************/
/*
  Name: Idan Nave
  Project: Work Sheet 6 - Data Structures - Singly Linked LIst
  Reviewer: ???
  Date: 12/08/23
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <stdio.h>              /* FILEs, stderr, stdin, stdout, perror */
#include <stdlib.h>             /* malloc(), free() */
#include <string.h>             /* string manipulation */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */

/*****************************************************************************/
/**************************** Type Definitions ************************/
/*****************************************************************************/
 
typedef struct node node_ty; /*decleration*/

  /******************************** TypeDefs  *******************************/
/*Struct for a node within lls */
struct node
{
    void* data;
    node_ty* next;
};


/*****************************************************************************/
/*************************** Extra Exercises *********************************/
/*****************************************************************************/

/* Reverses the order of a given slist. */ 
node_ty* Flip(node_ty *head)
{
    node_ty *iter = head;
    node_ty *prv_ptr = NULL;
    node_ty *next_ptr = NULL;;

    while(NULL != iter->next)
    {
        next_ptr = iter->next;
        iter->next = prv_ptr;
        prv_ptr = iter ; /*update iter field*/
        iter = next_ptr;
   }
   iter->next = prv_ptr;
   return(iter);
}

/* Prints a list starting rom head */ 
void PrintList(node_ty *head, size_t num_of_nodes)
{ 
    size_t i = 0;
    node_ty *next_ptr = head;;
    printf("list is:\n");
    while(i < num_of_nodes)
    {
        printf("\tnode %ld is %ld\n", i+1, *((size_t*)(next_ptr->data)));
        next_ptr = next_ptr->next;
        ++i;
    }

}

/* Tells whether a given slist has loop. returns index of loop ot -1 */
int HasLoop(const node_ty *head)
{
    size_t i = 0;
    node_ty *fast_ptr1 = (node_ty*)head;
    node_ty *fast_ptr2 = (node_ty*)head;
    node_ty *slow_ptr = (node_ty*)head;
    node_ty *prv_ptr = (node_ty*)head;

    /* for loops up to 2 nodes in size*/ 
    if(head == head->next) return 1;
    else if(head->next->next == head) return 2;

    /* for loops starting from 3 nodes in size*/ 
    while(NULL != fast_ptr1 || NULL != fast_ptr2 || NULL != slow_ptr)
    {
        fast_ptr1 = fast_ptr1->next->next->next;
        fast_ptr2 = fast_ptr2->next->next;
        slow_ptr = slow_ptr->next;

        /* Recheck iterators initialization */ 
        if(NULL != fast_ptr1 || NULL != fast_ptr2 || NULL != slow_ptr)
        {
            return -1;
        }

        if ( fast_ptr1 == slow_ptr )
        {
          return i + 1;
        }
        if ( fast_ptr2 == slow_ptr )
        {
          return i + 1;
        }
        ++i;
    }

    return -1;
}

/* Returns a pointer to a first node mutual to both lists- if not found, NULL*/ 
node_ty *FindIntersection (node_ty *head1, node_ty *head2)
{

  size_t len1 = 0;
  size_t len2 = 0;
  size_t jump = 0;
  size_t i = 0;
  node_ty *iter1 = {0};
  node_ty *iter2 = {0};
  node_ty *iter_big = {0};
  node_ty *iter_small = {0};
  node_ty *dummy = NULL;

  assert(NULL != head1);
  assert(NULL != head2);
  
  iter1 = head1;
  iter2 = head2;
  iter_big = head1;
  iter_small = head2;
  
  while(NULL != iter1)
  {
    iter1 = iter1->next;
    ++len1;
  }
  
  while(NULL != iter2)
  {
    iter2 = iter2->next;
    ++len2;
  }
  
  if(len1 > len2)
  {
    jump = len1 - len2;
    iter_big = head1;
    iter_small = head2;
  }
  else if (len2 > len1)
  {
    jump = len2-len1;
    iter_big = head2;
    iter_small = head1;
  }
  
  /* offset the iter of bigger list*/ 
  while(i < jump)
  {
    iter_big = iter_big->next;
    ++i;
  }

  /* compare iterators after offset*/ 
  while(NULL != iter_big)
  {
      if(iter_big == iter_small)
      {
        return iter_big;
      }
      iter_big = iter_big->next;
      iter_small = iter_small->next;
  }
  return iter_big;
}


/************************************* Main **********************************/
void TestFlip()
{   
    node_ty* node1 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* node2 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* node3 = (node_ty*)(malloc(sizeof(node_ty)));

    size_t data1 = 1;
    size_t data2 = 2;
    size_t data3 = 3;

    node1->next = node2;
    node1->data = (void*)&data1;

    node2->next = node3;
    node2->data = (void*)&data2;

    node3->next = NULL;
    node3->data = (void*)&data3;

    PrintList(node1, 3);
    node1 = Flip(node1);
    PrintList(node1, 3);
}

int TestHasLoop()
{   
    node_ty* node1 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* node2 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* node3 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* node4 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* node5 = (node_ty*)(malloc(sizeof(node_ty)));

    int res = -1;
    size_t data1 = 1;
    size_t data2 = 2;
    size_t data3 = 3;
    size_t data4 = 4;
    size_t data5 = 5;


    /* Full Circular Loop*/
    node1->next = node2;
    node1->data = (void*)&data1;
    node2->next = node3;
    node2->data = (void*)&data2;
    node3->next = node4;
    node3->data = (void*)&data3;
    node4->next = node5;
    node4->data = (void*)&data4;
    node5->next = node1;
    node5->data = (void*)&data5;

    PrintList(node1, 6);
    res = HasLoop(node1);
    if(res > 0)
    {
      printf("loop found in node %d:\n", res);
    }
    else
    {
      printf("no loop found:\n");
    }

    /* Partial Circular Loop*/
    node4->next = node1;
    node5->next = NULL;
    PrintList(node1, 6);
    res = HasLoop(node1);
    if(res > 0)
    {
      printf("loop found in node %d:\n", res);
    }
    else
    {
      printf("no loop found:\n");
    }

    /*  No Loop*/
    node4->next = node5;
    node5->next = NULL;
    PrintList(node1, 3);
    res = HasLoop(node1);
    if(res > 0)
    {
      printf("loop found in node %d:\n", res);
    }
    else
    {
      printf("no loop found:\n");
    }
}

int TestFindIntersection()
{   
    node_ty* A1 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* A2 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* A3 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* A4 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* A5 = (node_ty*)(malloc(sizeof(node_ty)));

    node_ty* B1 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* B2 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* B3 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* B4 = (node_ty*)(malloc(sizeof(node_ty)));
    node_ty* B5 = (node_ty*)(malloc(sizeof(node_ty)));

    node_ty *res_node = NULL;

    size_t Adata1 = 101;
    size_t Adata2 = 102;
    size_t Adata3 = 103;
    size_t Adata4 = 104;
    size_t Adata5 = 105;

    size_t Bdata1 = 201;
    size_t Bdata2 = 202;
    size_t Bdata3 = 203;
    size_t Bdata4 = 204;
    size_t Bdata5 = 205;

    /* Init 2 lists */
    A1->next = A2;                        B1->next = B2;
    A1->data = (void*)&Adata1;            B1->data = (void*)&Bdata1;
    A2->next = A3;                        B2->next = B3;
    A2->data = (void*)&Adata2;            B2->data = (void*)&Bdata2;
    A3->next = A4;                        B3->next = B4;
    A3->data = (void*)&Adata3;            B3->data = (void*)&Bdata3;
    A4->next = A5;            /*inersect*/B4->next = A3;
    A4->data = (void*)&Adata4;            B4->data = (void*)&Bdata4;
    A5->next = NULL;
    A5->data = (void*)&Adata5;

    PrintList(A1, 5);
    PrintList(B1, 7);
    res_node = FindIntersection(A1, B1);

    if(NULL == res_node)
    {
      printf("no intersection found in given lists\n");
    }
    else
    {
      printf("found intersection in node: %ld\n",*((size_t*)(res_node->data)));
    }

}

int main()
{   
    /*TestFlip();*/
    /*TestHasLoop();*/
    TestFindIntersection();
}