/********************************** ws13_WBO.h  ******************************/
/*
  Name: Idan Nave
  Project: Work Sheet #13 - Word Boundary Optimization
  Reviewer: Agbaria
  Date: 03/08/23
  Version: 1.0
*/

#ifndef __WS13_WBO_H__
#define __WS13_WBO_H__

/******************************** LIBRARIES  **********************************/

#include <stddef.h>  /* size_t */


/********************************** ENUMs  ************************************/

/* Enum that map error codes */
typedef enum
{
    NO_ERROR = 0,
    FILE_NOT_FOUND = 1,
    FILE_READ_ERROR = 2,
    FILE_WRITE_ERROR = 3,
    NULL_STRING_ERROR = 4,
    INVALID_ARGUMENT = 5,
    MEMORY_ALLOCATION_ERROR = 6,
    INVALID_STRING = 7,
    PERMISSION_DENIED = 8,
    OTHER_ERROR = 9,
    FILE_EXISTS = 10,
    NOT_FOUND = 11,
    INVALID_STRING_LEN = 12,
    MEMORY_OPERATION_FAIL = 13
} err_code_ty;


/******************************************************************************/
/*********************** API  - Functions Declerations ************************/
/******************************************************************************/


/*New Implementations Signatures & Description*/
/* The `MemSet` function sets the first 'n' bytes of the memory area pointed
to by 's' to the specified value 'c'*/
void *MemSet(void *s, int c, size_t n);
/* The `MemCpy` function copies 'n' bytes from the memory area pointed 
to by 'src' to the memory area pointed to by 'dest'.*/
void *MemCpy(void *dest, const void *src, size_t n);
/* The `MemMove` function copies n bytes from memory area src to memory area dest.
The memory areas may overlap: copying takes place as though the bytes in src 
are  first copied  into  a temporary array that does not overlap src or dest,
and the bytes are then copied from the temporary array to dest. */
void *MemMove(void *dest, const void *src, size_t n);

/***************************** Requirements **********************************/
/*  Memset:
    • Copy word-size chunks when possible, instead of byte-by-byte.
    • Do not assume dest is aligned.
    • Test for det aligned and not aligned.
    Memcpy:
    • Copy word-size chunks when possible, instead of byte-by-byte.
    • Assume src and dest are aligned. [Advanced]: Ignore this assumption.
    Implement and test for src and dest aligned and not aligned.
    MeMove:
    • Copy byte-by-byte. [Advanced): copy word-size chunks when possible.
    • Assume src and dest are aligned. [Advanced]: Ignore this assumption.
    Implement and test for src and dest aligned and not aligned.
    • Do not allocate additional memory, work in-place.
    • Should work for overlapping ranges of src and dest.*/

/******************************************************************************/

#endif /*(__WS13_WBO_H__)*/
