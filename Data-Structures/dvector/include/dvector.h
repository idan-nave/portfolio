/******************************** ws5_dvector.h  ***************************/
/*
  Name: Idan Nave
  Project: Work Sheet 5 - Data Structures - Dynamic Vector
  Reviewer: Uri
  Date: 12/08/23
  Version: 1.0
*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

/******************************** Libraries  *******************************/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

#define NO_ERROR 0 
#define GROWTH_FACTOR 1.5
#define SHRINK_FACTOR 0.66 

typedef enum  {SUCCESS = 0, FAILURE = 1, EMPTY = 0, NOT_EMPTY = 1} status_t;
typedef struct vector vector_t;

/*Function that inits the vector struct
  Arguments: capacity of the vector, element size.
  Return value: pointer to the created vector struct
  Undefined B.: element_size = 0, capacity = 0*/
vector_t *VectorCreate(size_t capacity, size_t element_size);

/*Function that deletes the vector struct
  Arguments: pointer to the vector struct.
  Return value: void.
  Undefined B.: NULL ptr of vector*/
void VectorDestroy(vector_t *vector);

/*Function that deletes the last element from the vector struct
  Arguments: pointer to the vector struct.
  Return value: status_t.
  Undefined B.: NULL ptr of vector*/
void VectorPopBack(vector_t *vector);

/*Function that adds data to the first empty element in the vector struct.
  if it reach the end of the vector, vector will be automatically resized. 
  (by default growth factor).
  Arguments: pointer to the vector struct, data to be added.
  Return value: status_t
  Undefined B.: size of data > element_size, NULL ptr of vector*/
int VectorPushBack(vector_t *vector, const void *data);

/*Function that gets access to a specific element in the vector struct
  Arguments: pointer to the vector struct, index.
  Return value: void* that represent the element.
  Undefined B.: NULL ptr of vector, index > capacity*/
void* VGetAccessToElement(const vector_t *vector, size_t index);

/*Function that returns the size of the vector struct
  Arguments: pointer to the vector struct.
  Return value: size of the vector struct.
  Undefined B.: NULL ptr of vector*/
size_t VectorSize(const vector_t *vector);

/*Function that checks if the vector struct is empty
  Arguments: pointer to the vector struct.
  Return value: status_t
  Undefined B.: NULL ptr of vector*/
int VectorIsEmpty(const vector_t *vector);

/*Function that returns the capacity of the vector struct
  Arguments: pointer to the vector struct.
  Return value: capacity of the vector struct.
  Undefined B.: NULL ptr of vector*/
size_t VectorCapacity(const vector_t *vector);

/*Function that resized the space of the vector with the new capacity.
  If the new_capacity < size, function will do nothing (data will be kept).
  Arguments: pointer to the vector struct, new capacity.
  Return value: status_t
  Undefined B.: NULL ptr of vector*/
int VectorReserve(vector_t *vector, const size_t new_capacity);

/*Function that shrinks the space of the vector with the default shrink factor.
  If the shrink operation leads to data loss, function will do nothing.
  Arguments: pointer to the vector struct.
  Return value: status_t
  Undefined B.: NULL ptr of vector*/
int VectorShrink(vector_t *vector);
/*Function Description*/

/*App Manager Function (called from Main)*/
int ExecuteTestSequence();

#endif /*(__VECTOR_H__)*/
