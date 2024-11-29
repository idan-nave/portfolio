/******************************** ws5_dc_buff.h  ******************************/
/*
  Name: HRD32
  Project: Work Sheet 8 - Data Structures - Circular Buffer
  Reviewer: Idan
  Date: 21/08/23
  Version: 1.0
*/

/******************************** Libraries  **********************************/
#include <string.h> /*memcpy*/

#include "cbuff.h"
/******************************** Definitions  ********************************/
struct c_buff
{
  size_t capacity;
  size_t read_idx;
  size_t size;
  char arr[1];
};

/******************************************************************************/

c_buff_ty *CbuffCreate(size_t capacity)
{
  c_buff_ty *cbuff = (c_buff_ty*)malloc((sizeof(c_buff_ty) - 8) + 
                                        (sizeof(char) * capacity));
  if(NULL == cbuff)
  {
    return (c_buff_ty*)0;
  }

  cbuff->capacity = capacity;
  cbuff->size = 0;
  cbuff->read_idx = 0;

  return cbuff;
}

/******************************************************************************/

void CbuffDestroy(c_buff_ty *buffer)
{
  assert(NULL != buffer);

  free(buffer);
  buffer = NULL;

  return;
}

/******************************************************************************/

size_t CbuffRead(c_buff_ty *buffer, void *dest, size_t bytes)
{
  /*size_t dest_index = 0;
  size_t buffer_arr_index = 0;

  assert(NULL != buffer);  

  while (dest_index < bytes && 0 < buffer->size)
  {
    if(buffer->read_idx == buffer->capacity)
    {
      buffer->read_idx = 0;
    }

    memcpy((((char*)dest) + dest_index), (buffer->arr + buffer->read_idx), 1);
    ++dest_index;
    ++buffer->read_idx;
    --buffer->size;
  }

  return dest_index;*/

  size_t first_bytes = 0;
  char *dest_ptr = NULL;
  
  assert(NULL != buffer);

  dest_ptr = (char*)dest;
    
  if(0 == buffer->size)
  {
    return 0;
  }
  
  if(buffer->size < bytes)
  {
    bytes = buffer->size;
  }
  
  first_bytes = buffer->capacity - buffer->read_idx;
  
  if(first_bytes < bytes)
  {
    memcpy(dest_ptr,&(buffer->arr[buffer->read_idx]),
     first_bytes);  
    buffer->read_idx = 0;
    buffer->size -= first_bytes;
    dest_ptr += first_bytes;
    bytes -= first_bytes;
  }
  
  memcpy(dest_ptr, &(buffer->arr[buffer->read_idx]), bytes);
  buffer->size = buffer->size - bytes;
  buffer->read_idx += bytes;
  
  return bytes;
}

/******************************************************************************/

size_t CbuffWrite(c_buff_ty *buffer, void *src, size_t bytes)
{
  /*size_t src_index = 0;
  size_t buffer_arr_index = 0; 

  assert(NULL != buffer);

  while(src_index < bytes && 0 < CbuffFreeSpace(buffer))
  {
    buffer_arr_index = (buffer->size + buffer->read_idx)% buffer->capacity;
    memcpy((buffer->arr + buffer_arr_index), (((char*)src) + src_index), 1);
    ++src_index;
    ++buffer->size;
    
  }
  return src_index;*/

  size_t first_bytes = 0;
  char *src_ptr = NULL;
  size_t num_of_bytes = 0;
  
  assert(NULL != buffer);
  
  src_ptr = (char*)src; 
  if(CbuffFreeSpace(buffer) < bytes)
  {
    bytes = CbuffFreeSpace(buffer);
  }

  num_of_bytes = bytes;
  
  first_bytes = buffer->capacity - (buffer->size + buffer->read_idx);
  
  if(first_bytes < num_of_bytes)
  {
    memcpy(&(buffer->arr[(buffer->read_idx + buffer->size)]), src_ptr,
     first_bytes);
    buffer->size += first_bytes;
    num_of_bytes -= first_bytes;
    src_ptr += first_bytes;
  }
  
  memcpy(&(buffer->arr[(buffer->read_idx + buffer->size)%
       buffer->capacity]), src_ptr, num_of_bytes);
  buffer->size += num_of_bytes;
  
  return bytes;
}

/******************************************************************************/

size_t CbuffSize(const c_buff_ty *buffer)
{
  assert(NULL != buffer); 

  return buffer->size; 
}

/******************************************************************************/

int CbuffIsEmpty(const c_buff_ty *buffer)
{
  assert(NULL != buffer);

  if(buffer->size == 0)
  {
    return EMPTY;
  }

  return NOT_EMPTY;
}

/******************************************************************************/

size_t CbuffFreeSpace(const c_buff_ty *buffer)
{
  assert(NULL != buffer);

  return buffer->capacity - buffer->size;
}

