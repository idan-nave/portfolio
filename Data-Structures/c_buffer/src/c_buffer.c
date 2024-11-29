/************************************ ws10_cbuff.c ***************************/
/*
  Name: Idan Nave
  Project: Work Sheet 10 - Data Structures - Circular Buffer
  Reviewer: Dima
  Date: 20/08/23
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <stdio.h>              /* FILEs, stderr, stdin, stdout */
#include <stdlib.h>             /* malloc(), free() */
#include <string.h>             /* memcpy, string manipulation */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */

#include "c_buffer.h" 		

#define BUFFER_META_OFFSET 3*sizeof(size_t)

/*****************************************************************************/
/**************************** Testing Data-structures ************************/
/*****************************************************************************/
 
  /******************************** TypeDefs  *******************************/

struct c_buff
{
    size_t capacity;
    size_t read_idx;
    size_t size;
    char arr[1];			
};

/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/

c_buff_ty *CbuffCreate(size_t capacity)
{
    /* init buffer with one malloc, element 0 will remain out of use*/
    size_t buffer_capacity = (sizeof(char)) * (capacity);
    c_buff_ty* new_buffer =
              (c_buff_ty*)malloc(BUFFER_META_OFFSET + buffer_capacity);
 
    /* validate successful malloc*/
    if(NULL == new_buffer)
    {
        errno = ENOMEM;
        perror("Unsuccessful allocation of new buffer");
        return NULL;
    }

    /* init buffer fields*/
    new_buffer->capacity = capacity;
    new_buffer->read_idx = 0;    /* init w_idx = -1*/
    new_buffer->size = 0;    			/* init w_idx = 0*/
   /* new_buffer->arr =(char*)( new_buffer + BUFFER_META_OFFSET);*/
    return new_buffer;
}

void CbuffDestroy(c_buff_ty *buffer)
{
  assert(NULL != buffer);

  free(buffer);
  buffer = NULL;
}

size_t CbuffWrite(c_buff_ty *buffer, void *src, size_t bytes)
{
	size_t w_idx = buffer->read_idx + buffer->size;
	size_t orig_size = buffer->size;

	assert(NULL != buffer);
	assert(NULL != src);
	
	if(CbuffFreeSpace(buffer) < bytes)
	{
		bytes = CbuffFreeSpace(buffer);
	}

	if(buffer->capacity - w_idx < bytes)
	{
		size_t tmp_bytes = bytes;
		bytes = buffer->capacity - w_idx;
		memcpy(buffer->arr + w_idx, src, bytes) ;
		buffer->size += bytes;
		w_idx = 0;
		bytes = tmp_bytes - bytes; 
	}

	memcpy(buffer->arr + w_idx, src , bytes) ;
	buffer->size += bytes;
	w_idx = w_idx + bytes;

	return buffer->size - orig_size;
}

size_t CbuffRead(c_buff_ty *buffer, void *dest, size_t bytes)
{

	size_t r_idx = buffer->read_idx;
	size_t orig_size = buffer->size;

	assert(NULL != buffer);
	assert(NULL != dest);
	
	if(buffer->size < bytes)
	{
		bytes = buffer->size;
	}
	if(buffer->capacity - r_idx < bytes)
	{
		size_t tmp_bytes = bytes;
		bytes = buffer->capacity - r_idx;
		memcpy( dest, buffer->arr + r_idx, bytes) ;
		buffer->size -= bytes;
		r_idx = 0;
		bytes = tmp_bytes - bytes; 
	}	
	memcpy(dest, buffer->arr + r_idx, bytes) ;
	buffer->size -= bytes;
	r_idx = (r_idx + bytes) % buffer->capacity;

	return buffer->size - orig_size;
}

	 /* CASE#1 : write_idx is before read_idx
	 *  | _ | X| X | X | _ | _ | _ | X |
	 *    	  ^                	 ^
	 *  	Read                Write    */
	 /* CASE#2 : write_idx is before read_idx
	 *  | X | _ | _ | _ | _ | _ | x | X |
	 *    	  ^                	 ^
	 *  	Write                Read    */

status_ty CbuffIsEmpty(const c_buff_ty *buffer)
{
    return !(0 == buffer->size);
}

size_t CbuffCapacity(const c_buff_ty *buffer)
{
    return buffer->capacity;
}

size_t CbuffSize(const c_buff_ty *buffer)
{
    return buffer->size;
}

size_t CbuffFreeSpace(const c_buff_ty *buffer)
{
 	 return buffer->capacity - (buffer->size);
}

