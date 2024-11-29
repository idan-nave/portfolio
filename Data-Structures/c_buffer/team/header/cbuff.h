/******************************** ws5_dc_buff.h  ***************************/
/*
  Name: Aya
  Project: Work Sheet 8 - Data Structures - Circular Buffer
  Reviewer: Idan
  Date: 20/08/23
  Version: 1.0
*/

#ifndef __C_BUFFER_H__
#define __C_BUFFER_H__

/******************************** Libraries  *******************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

typedef enum  {SUCCESS = 0, FAILURE = 1, EMPTY = 0, NOT_EMPTY = 1} status_ty;
typedef struct c_buff c_buff_ty;

/*Function that inits the c_buff struct
  Arguments: capacity of the c_buff, element size.
  Return value: pointer to the created c_buff struct
  Undefined B.: capacity = 0*/
c_buff_ty *CbuffCreate(size_t capacity);

/*Function that deletes the c_buff struct
  Arguments: pointer to the c_buff struct.
  Return value: void.
  Undefined B.: NULL ptr of c_buff*/
void CbuffDestroy(c_buff_ty *buffer);

/*Function that reads <bytes> amount of bytes from the c_buff.
  If it reaches the end of the c_buff, data will be kept readen from the start of the buffer.
  Arguments: pointer to the c_buff struct,
             destination pointer to write to,
             <bytes> amount to read.
  Return value: number of bytes actually written.
  Undefined B.: NULL ptr of c_buff & src */
size_t CbuffRead(c_buff_ty *buffer, void *dest, size_t bytes);

/*Function that writes <bytes> amount of bytes to the c_buff.
  If it reaches the end of the c_buff, data will be kept written from the start of buffer. If unavailable empty space in buffer, data is not written.
  Arguments: pointer to the c_buff struct,
             source pointer to read from,
             <bytes> amount to write.
  Return value: number of bytes actually written.
  Undefined B.: NULL ptr of c_buff & src */
size_t CbuffWrite(c_buff_ty *buffer, void *src, size_t bytes);

/*Function that returns the capacity of the c_buff
  Arguments: pointer to the c_buff struct.
  Return value: capacity of the c_buff.
  Undefined B.: NULL ptr of c_buff*/
size_t CbuffSize(const c_buff_ty *buffer);

/*Function that checks if the c_buff is empty
  Arguments: pointer to the c_buff struct.
  Return value: status_ty
  Undefined B.: NULL ptr of c_buff*/
int CbuffIsEmpty(const c_buff_ty *buffer);

/*Function that returns size of the remaining empty space in the buffer.
  Arguments: pointer to the c_buff struct.
  Return value: number of bytes.
  Undefined B.: NULL ptr of c_buff*/
size_t CbuffFreeSpace(const c_buff_ty *buffer);

#endif /*(__C_BUFFER_H__)*/
