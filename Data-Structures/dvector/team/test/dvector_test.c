/*Name: Aya
  Project: Dynamic Vector Implementation
  Reviewer: ???
  Date: 10/08/2023
  Version: 1.0
*/
/******************************************************************************/
#include <stdio.h> /*printf*/

#include "dvector.h"

int RunProg();

void VectorPushInt_test(vector_ty *vector, const void *data, size_t index);
void VectorPushChr_test(vector_ty *vector, const void *data, size_t index);
void VectorPushDouble_test(vector_ty *vector, const void *data, size_t index);

void VectorPopInt_test(vector_ty *vector, size_t index);
void VectorPopChr_test(vector_ty *vector, size_t index);
void VectorPopDouble_test(vector_ty *vector, size_t index);

/******************************************************************************/

int main()
{
  return RunProg();
}

/******************************************************************************/

int RunProg()
{
  vector_ty *my_new_vector = VectorCreate(4,23);
  int data1[] = {4,5,7};
  char data2[] = {'A','G'};
  double data3[] = {7.5,6.6};

  char str[5] = "hell";
  size_t i = 0;
  size_t j = 0;

  printf("\nCreate vector\n");
  printf("\tsize: %ld\n", VectorSize(my_new_vector)); 
  printf("\tIsEmpty: %s\n", VectorIsEmpty(my_new_vector) == 0 ? "FALSE" : "TRUE"); 
  printf("\tcapacity: %ld\n", VectorCapacity(my_new_vector));

  for(i = 0; 3 > i; ++i)
  {
    VectorPushInt_test(my_new_vector, &data1[i], j);
    ++j;
  }

  for(i = 0; 2 > i; ++i)
  {
    VectorPushChr_test(my_new_vector, &data2[i], j);
    ++j;
  }

  for(i = 0; 2> i; ++i)
  {
    VectorPushDouble_test(my_new_vector, &data3[i], j);
    ++j;
  }

  VectorPushBack(my_new_vector, str);
  printf("\nString Push to vector\n");
  printf("\tVector head: %s\n", (char*)VGetAccessToElement(my_new_vector, j));
  printf("\tsize: %ld\n", VectorSize(my_new_vector)); 
  printf("\tIsEmpty: %s\n", VectorIsEmpty(my_new_vector) == 0 ? "FALSE" : "TRUE");

  VectorPopDouble_test(my_new_vector,j-1);


  

  VectorDestroy(my_new_vector);
  printf("\nDestroy the vector\n");
  return 0;

}

/******************************test Push**************************************/

void VectorPushInt_test(vector_ty *vector, const void *data, size_t index)
{
  VectorPushBack(vector, data);
  printf("\n%ld int Push to vector\n", index);
  printf("\tvector head: %d\n", *(int*)VGetAccessToElement(vector, index));
  printf("\tsize: %ld\n", VectorSize(vector)); 
  printf("\tIsEmpty: %s\n", VectorIsEmpty(vector) == 0 ? "FALSE" : "TRUE"); 
}

void VectorPushChr_test(vector_ty *vector, const void *data, size_t index)
{
  VectorPushBack(vector, data);
  printf("\n%ld char Push to vector\n", index);
  printf("\tvector head: %c\n", *(char*)VGetAccessToElement(vector, index));
  printf("\tsize: %ld\n", VectorSize(vector)); 
  printf("\tIsEmpty: %s\n", VectorIsEmpty(vector) == 0 ? "FALSE" : "TRUE"); 
}

void VectorPushDouble_test(vector_ty *vector, const void *data, size_t index)
{
  VectorPushBack(vector, data);
  printf("\n%ld double Push to vector\n", index);
  printf("\tvector head: %f\n", *(double*)VGetAccessToElement(vector, index));
  printf("\tsize: %ld\n", VectorSize(vector)); 
  printf("\tIsEmpty: %s\n", VectorIsEmpty(vector) == 0 ? "FALSE" : "TRUE"); 
}

/****************************test Pop*************************************/

void VectorPopInt_test(vector_ty *vector, size_t index)
{
  VectorPopBack(vector);
  printf("\nPop from vector\n");
  printf("\tvector head: %d\n", *(int*)VGetAccessToElement(vector, index));
  printf("\tsize: %ld\n", VectorSize(vector)); 
  printf("\tIsEmpty: %s\n", VectorIsEmpty(vector) == 0 ? "FALSE" : "TRUE"); 
}

void VectorPopChr_test(vector_ty *vector, size_t index)
{
  VectorPopBack(vector);
  printf("\nPop from vector\n");
  printf("\tvector head: %c\n", *(char*)VGetAccessToElement(vector, index));
  printf("\tsize: %ld\n", VectorSize(vector)); 
  printf("\tIsEmpty: %s\n", VectorIsEmpty(vector) == 0 ? "FALSE" : "TRUE"); 
}

void VectorPopDouble_test(vector_ty *vector, size_t index)
{
  VectorPopBack(vector);
  printf("\nPop from vector\n");
  printf("\tvector head: %f\n", *(double*)VGetAccessToElement(vector, index));
  printf("\tsize: %ld\n", VectorSize(vector)); 
  printf("\tIsEmpty: %s\n", VectorIsEmpty(vector) == 0 ? "FALSE" : "TRUE"); 
}