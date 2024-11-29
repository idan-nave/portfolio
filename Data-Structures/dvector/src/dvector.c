/*
  Name: Idan Nave
  Project: Work Sheet 5 - Data Structures - Dynamic Vector
  Reviewer: Uri
  Date: 12/08/23
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <stddef.h>                 /*size_t*/
#include <stdlib.h>                 /*malloc*/
#include <string.h>                 /*memcpy*/
#include <stdio.h>                  /*perror*/
#include <assert.h>                 /*assert*/

#include "dvector.h" 		

  /******************************** TypeDefs  *******************************/

struct vector
{
    size_t capacity;
    size_t size;
    size_t element_size;
    void *vector_arr;
};

/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/

vector_t *VectorCreate(size_t capacity, size_t element_size)
{
    vector_t *vector_res = (vector_t*)malloc(sizeof(vector_t));
    char *res_arr = NULL;
    
    if(NULL == vector_res)
    {
        return NULL;
    }
    
    vector_res->capacity = capacity;
    vector_res->element_size = element_size;
    vector_res->size = 0;
    res_arr = (char*)malloc(sizeof(char)*capacity*element_size);
    
    if(NULL == res_arr)
    {
        free(vector_res);
        vector_res = NULL;
        return NULL;
    }
    vector_res->vector_arr = (void*)res_arr;
    
    return vector_res;
}

void VectorDestroy(vector_t *vector)
{
    assert(NULL != vector);
    
    free(vector->vector_arr);
    vector->vector_arr = NULL;
    free(vector);
    vector = NULL;
}

void VectorPopBack(vector_t *vector)
{

    assert(NULL != vector);
    
    if(0 == vector->size)
    {
        perror("Error: stack is empty\n");
        return;
    } 

    vector->size -= vector->element_size;
}

int VectorPushBack(vector_t *vector, const void *data)
{
    char *res = NULL;
    size_t size_to_grow = 0;
    assert(NULL != vector);
    assert(NULL != data);
    
    if(vector->size == vector->capacity * vector->element_size)
    {
        size_to_grow = vector->capacity * GROWTH_FACTOR;
        if(FAILURE == VectorReserve(vector, size_to_grow))
        {
            return FAILURE;
        }
    }
    
    res = (char*)vector->vector_arr;
    memcpy(&res[vector->size], data, vector->element_size);
    vector->size += vector->element_size;
    
    return SUCCESS;
}

void *VGetAccessToElement(const vector_t *vector, size_t index)
{
    unsigned char *res = NULL;
    assert(NULL != vector);
    
    if(index > (vector->size / vector->element_size) -1)  
    {
        perror("Error: iligale index\n");
        return NULL;
    }
    
    res = (unsigned char*)vector->vector_arr;
    
    return &res[index * vector->element_size];
}

size_t VectorSize(const vector_t *vector)
{
    assert(NULL != vector);

    return vector->size / vector->element_size;
}

int VectorIsEmpty(const vector_t *vector)
{
    assert(NULL != vector);
    
    if(0 != vector->size)
    {
        return FAILURE;
    }
    return SUCCESS;
}

size_t VectorCapacity(const vector_t *vector)
{
    assert(NULL != vector);
    
    return vector->capacity;
}

int VectorReserve(vector_t *vector, const size_t new_capacity)
{
    char *res = (char*)realloc(res, sizeof(char)*new_capacity*vector->element_size);
    
    if(new_capacity < vector->size / vector->element_size)
    {
        return FAILURE;
    }
    
/*    res = (char*)realloc(res, sizeof(char)*new_capacity*vector->element_size);
*/    
    if(NULL == res)
    {
        return FAILURE;
    }
    
    (char*)vector->vector_arr = res;
    vector->capacity = new_capacity;
    
    return SUCCESS;
}

int VectorShrink(vector_t *vector)
{
    size_t size_to_shrink = 0;
    
    size_to_shrink = vector->capacity * SHRINK_FACTOR;
    
    return VectorReserve(vector, size_to_shrink);
}


/*****************************************************************************/
/************************* Helper Functions Definitions **********************/
/*****************************************************************************/

static int VectorDynamicGrowth(vector_t *vector)
{
    size_t size_to_grow = 0;
    
    size_to_grow = vector->capacity * GROWTH_FACTOR;
    
    return VectorReserve(vector, size_to_grow);
}

