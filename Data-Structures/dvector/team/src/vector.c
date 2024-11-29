/*Name: Aya
  Project: Dynamic Vector Implementation
  Reviewer: ???
  Date: 10/08/2023
  Version: 1.0
*/
/******************************************************************************/

#include <stddef.h> /*size_t*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/

#include "vector.h"

#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 2

/******************************************************************************/

struct vector
{
  size_t capacity;
  size_t size;
  size_t element_size;
  void *vector_arr;
};


/******************************************************************************/

vector_ty *VectorCreate(size_t capacity, size_t element_size)
{
  vector_ty *initialized_vector = (vector_ty*)malloc(sizeof(vector_ty));
  if(NULL == initialized_vector)
  {
    return NULL;
  }

  initialized_vector->capacity = capacity;
  initialized_vector->size = 0;
  initialized_vector->element_size = element_size;

  initialized_vector->vector_arr = (void*)malloc(capacity * element_size);
  if(NULL == initialized_vector->vector_arr)
  {
    return NULL;
  }

  return initialized_vector;
}

/******************************************************************************/

void VectorDestroy(vector_ty *vector)
{
  assert(NULL != vector);

  free(vector->vector_arr);
  vector->vector_arr = NULL;

  free(vector);
  vector = NULL;
}

/******************************************************************************/

void VectorPopBack(vector_ty *vector)
{
  assert(NULL != vector);

  if(0 < vector->size)
  {
    --vector->size;
  }
}

/******************************************************************************/

int VectorPushBack(vector_ty *vector, const void *data)
{
  size_t index = 0;

  assert(NULL != vector);

  if(vector->size < vector->capacity)
  {
    index = vector->size * vector->element_size;
    memcpy(((char*)vector->vector_arr) + index, data, vector->element_size);
    ++vector->size;
  }
  else
  {
    VectorReserve(vector, vector->capacity*GROWTH_FACTOR);
    index = vector->size * vector->element_size;
    memcpy(((char*)vector->vector_arr) + index, data, vector->element_size);
    ++vector->size;
  }

  return SUCCESS;
}

/******************************************************************************/

void *VGetAccessToElement(const vector_ty *vector, size_t index1)
{
  size_t curr_index = 0;

  assert(NULL != vector);
  
  curr_index = index1 * vector->element_size;
  return (((char*)vector->vector_arr) + curr_index);
}

/******************************************************************************/

size_t VectorSize(const vector_ty *vector)
{
  assert(NULL != vector);

  return vector->size;
}

/******************************************************************************/

int VectorIsEmpty(const vector_ty *vector)
{
  assert(NULL != vector);

  if(0 == vector->size)
  {
    return SUCCESS;
  }
  return FAILURE;
}

/******************************************************************************/

size_t VectorCapacity(const vector_ty *vector)
{
  assert(NULL != vector);

  return vector->capacity;
}

/******************************************************************************/

int VectorReserve(vector_ty *vector, const size_t new_capacity)
{
  void *new_vector_arr = (void*)NULL;

  assert(NULL != vector);

  if(new_capacity < vector->capacity)
  {
    vector->capacity = new_capacity;
    return SUCCESS;
  }

  new_vector_arr = (void*)realloc(vector->vector_arr, 
                                    new_capacity*vector->element_size);
  if (NULL == new_vector_arr)
  {
    free(new_vector_arr);
    new_vector_arr = NULL;
    return FAILURE;
  }

  vector->vector_arr = new_vector_arr;
  vector->capacity = new_capacity;

  return SUCCESS;
}

/******************************************************************************/

int VectorShrink(vector_ty *vector)
{
  assert(NULL != vector);
  
  if((vector->capacity / SHRINK_FACTOR) < vector->size)
  {
    return FAILURE;
  }
  
  vector->capacity /= SHRINK_FACTOR;
  return SUCCESS;
}