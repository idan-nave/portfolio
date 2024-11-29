/*Name: Aya
  Project: DS WS 6 - SLL Exercise
  Reviewer: ---
  Date: 15/08/23
  Version: 1.0
*/
/**********************************INCLUDE*************************************/
#include <stddef.h> /*size_t*/
#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc*/
/****************************ENUMS/MACROS/DEFINES******************************/
#define NODE_ALLOC (node_ty *)malloc(sizeof(node_ty))

enum has_loop_ty {HASLOOP = 1, NOLOOP = 0};

/****************************TYPEDEFS AND STRUCTS******************************/
typedef struct node
{
	void *data;
	struct node *next;
}node_ty;

/*****************************FUNCTION DECLARATIONS****************************/
/*Reverses the order of a given SLL*/
node_ty *Flip(node_ty *head);

/*Tells whether a given SLL is looped*/
int HasLoop(node_ty *head);

/*Returns a pointer to a first node mutual to both SLLs, if any*/
node_ty *FindIntersection(node_ty *head_1, node_ty *head_2);

/*Helper Functions*/
/*function that creates list*/
node_ty* CreateList(int *data);
void push(node_ty** head_ref, void *new_data);
void PrintList(node_ty *head);

/********************************MAIN FUNCTION*********************************/

int main()
{
  int data_arr[4] = {1,2,3,4};
  int data1 = 6;
  node_ty *flip_list_test = CreateList(data_arr);
  node_ty *has_loop_list_test = CreateList(data_arr);
  node_ty *find_inter_section_list_1 = CreateList(data_arr);
  node_ty *find_inter_section_list_2 = find_inter_section_list_1->next->next;
  node_ty *find_inter_section_res = {0};

  /*Test Flip*/
  PrintList(flip_list_test);
  flip_list_test = Flip(flip_list_test);
  PrintList(flip_list_test);
  printf("\n");

  /*Test HasLoop*/
  has_loop_list_test->next->next->next->next = has_loop_list_test;
  if(HasLoop(has_loop_list_test))
  {
    printf("Loop found\n");
  }
  else
  {
    printf("No Loop\n");
  }
  printf("\n");
  

  /*Test FindIntersection*/
  push(&find_inter_section_list_2, &data1);
  PrintList(find_inter_section_list_1);
  PrintList(find_inter_section_list_2);
  find_inter_section_res = 
      FindIntersection(find_inter_section_list_1, find_inter_section_list_2);
  printf("first node mutual to both slists is: %d\n", *(int*)find_inter_section_res->data);


  return 0;
}

/*============================================================================*/
/*===============================IMPLEMENTATION===============================*/
/*============================================================================*/

node_ty *Flip(node_ty *head)
{
  node_ty *next_node = head->next;
  node_ty *prev_node = head;

  head->next = NULL;

  while(NULL != next_node)
  {
    head = next_node;
    next_node = next_node->next;
    head->next = prev_node;
    prev_node = head;
  }

  return head;
}

int HasLoop(node_ty *head)
{
  node_ty *slow_p = head; 
  node_ty *fast_p = head;
 
  while (slow_p && fast_p && fast_p->next) 
  {
    slow_p = slow_p->next;
    fast_p = fast_p->next->next;
    if (slow_p == fast_p) 
    {
        return HASLOOP;
    }
  }
  return NOLOOP;
}

node_ty *FindIntersection(node_ty *head_1, node_ty *head_2)
{
  size_t head_1_length = 0;
  size_t head_2_length = 0;
  node_ty *head_1_length_iterator = head_1;
  node_ty *head_2_length_iterator = head_2;
  node_ty *head_1_iterator = head_1;
  node_ty *head_2_iterator = head_2;

  /*calculate the length of each slist*/
  while (NULL != head_1_length_iterator)
  {
    head_1_length_iterator = head_1_length_iterator->next;
    ++head_1_length;
  }
  while (NULL != head_2_length_iterator)
  {
    head_2_length_iterator = head_2_length_iterator->next;
    ++head_2_length;
  }

  /*Move foward on the long slist until both slists are the same length*/
  if (head_1_length > head_2_length)
  {
    while (head_1_length != head_2_length)
    {
      head_1_iterator = head_1_iterator->next;
      --head_1_length;
    }
  }
  else
  {
    while (head_1_length != head_2_length)
    {
      head_2_iterator = head_2_iterator->next;
      --head_2_length;
    }
  }

  /*Move foward on both slists until the mutual node reached*/
  while (NULL != head_1_iterator)
  {
    if(head_1_iterator == head_2_iterator)
    {
      return head_1_iterator;
    }
    head_1_iterator = head_1_iterator->next;
    head_2_iterator = head_2_iterator->next;
  }


  return head_1_iterator;
}

/******************************HELPER FUNCTION*********************************/
node_ty* CreateList(int *data)
{
  node_ty* head = NULL;
  int i = 0;

  for(;4 > i; ++i)
  {
    push(&head, &data[i]);
  }

  return head;
}

void push(node_ty** head_ref, void *new_data)
{
    node_ty* new_node = (node_ty*)malloc(sizeof(node_ty));
 
    new_node->data = new_data;
 
    new_node->next = (*head_ref);
 
    (*head_ref) = new_node;
}

void PrintList(node_ty *head)
{
  node_ty *iterator = head;

  printf("List contents: ");
  while(NULL != iterator)
  {
    printf("%d ", *(int*)iterator->data);
    iterator = iterator->next;
  }

  printf("\n");
}





