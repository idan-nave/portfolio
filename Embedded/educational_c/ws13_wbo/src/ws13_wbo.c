/********************************** ws13_WBO.c  ******************************/
/*
  Name: Idan Nave
  Project: Work Sheet #13 - Word Boundary Optimization
  Reviewer: Agbaria
  Date: 03/08/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/

#include <assert.h> 		/* assert() */
#include <stddef.h>  		/* size_t*/
#include <stdio.h>  		/* standard input/output */
#include <stdlib.h> 		/* malloc(), free() */
#include <string.h>             /* string manipulation */

#include "ws13_WBO.h" 	
/******************************** Definitions *********************************/

#define WORD_SIZE sizeof(size_t)

/******************************************************************************/
/**************************** App's Data-structures ***************************/
/******************************************************************************/
 
  /********Error Info Struct Definition (appendix to the error Enum) ********/
typedef struct
{
    err_code_ty code;
    const char* message;
}   err_msg_ty;

  /********************** Error Messages Array Definition *******************/
err_msg_ty info[] = {
    {NO_ERROR, "No error"},
    {FILE_NOT_FOUND, "File not found"},
    {FILE_READ_ERROR, "Error while reading from file"},
    {FILE_WRITE_ERROR, "Error while writing to file"},
    {NULL_STRING_ERROR, "Null string encountered"},
    {INVALID_ARGUMENT, "Invalid argument"},
    {MEMORY_ALLOCATION_ERROR, "Memory allocation error"},
    {INVALID_STRING, "Invalid string"},
    {PERMISSION_DENIED, "Permission denied"},
    {OTHER_ERROR, "Other error"},
    {FILE_EXISTS, "File already exists"},
    {NOT_FOUND, "Not Found"},
    {INVALID_STRING_LEN, "Invalid String Length"},
    {MEMORY_OPERATION_FAIL, "Memory Operation Fail"}
};

/* error code global for exit points */
err_code_ty err = NO_ERROR;

/******************************************************************************/
/**************** Forward Declarations of Static Functions ********************/
/******************************************************************************/

/* Refer to MemSet Description */
static void *MemSetByByte(void *s, int c, size_t n);
/* Refer to MemCpy Description */
static void *MemCpyByByte(void *dest, const void *src, size_t n);
 /* Refer to MemMove Description */
static void *MemMoveByByte(void *dest, const void *src, size_t n);
       
/* Function that places value c 8 times along full word,
in order to make a read to use chunk of reoccuring value c */
static long CastByteToChunk(char c);


/************************** Exercise Description ******************************/
/*  Write a static library that implements Memset, Memcpy, and Memove.
   - The functions should have the same signature as the original ones.
   - Write pseudo code. */
  

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/

/*New Implementations Signatures & Description*/
/* The `MemSet` function sets the first 'n' bytes of the memory area pointed
to by 's' to the specified value 'c'*/
void *MemSet(void *s, int c, size_t n)
{
    /* chunk holder */
    unsigned long mask_word = 0;
    /* address to be overwritten */
    unsigned long *add_to_overwrite = NULL;
    size_t i = 0;
    
    /* Input validation */
    assert(NULL != s);	
    
    mask_word = CastByteToChunk(c); /* mask of word with c val */

    add_to_overwrite = (unsigned long*)s;
    while(i < n/WORD_SIZE) /* word count by 8-multiplies of n */
    {
        add_to_overwrite[i] = mask_word;
        ++i;
    }
    /* remaining n bytes */
    MemSetByByte(&add_to_overwrite[i] , c, n%WORD_SIZE);
    return s;
}

/* The `MemCpy` function copies 'n' bytes from the memory area pointed 
to by 'src' to the memory area pointed to by 'dest'.*/
void *MemCpy(void *dest, const void *src, size_t n)
{
    /* casted address to be overwritten */
    unsigned long* new_dest = NULL;
    unsigned long* new_src = NULL;
    size_t i = 0;
    
    /* Input validation */
    assert(NULL != dest);
    assert(NULL != src);
       
    new_dest = (unsigned long*)dest;
    new_src = (unsigned long*)src;
    
    /* ADVANCED - ALIGNMENT CONSIDERATION:
    Check if dest is after src and if the difference is not a multiple of 8 */
    if (dest > src && (size_t)(new_dest - new_src) % WORD_SIZE != 0)
    {
        return MemCpyByByte(dest, src, n);
    }
    
    while(i < n/WORD_SIZE) /* word count by 8-multiplies of n */
    {
        new_dest[i] = new_src[i];
        ++i;
    }
    /* remaining n bytes */
    MemCpyByByte(&new_dest[i], &new_src[i], n%WORD_SIZE);
    return dest;
}

/* The `MemMove` function copies n bytes from memory area src to memory area dest.
The memory areas may overlap: copying takes place as though the bytes in src 
are  first copied  into  a temporary array that does not overlap src or dest,
and the bytes are then copied from the temporary array to dest. */
void *MemMove(void *dest, const void *src, size_t n)
{
    /* chunks holders */
    unsigned long* new_dest = NULL;
    unsigned long* new_src = NULL;
    size_t i = 0;
    
    /* Input validation */
    assert(NULL != dest);
    assert(NULL != src);
      
    /* edge case - dest = src*/
    if(n == 0 || dest == src) 
    {
        return dest;
    }
      
    /* ADVANCED - ALIGNMENT CONSIDERATION:
    Check if dest is after src and if the difference is not a multiple of 8 */
    if (dest > src && (size_t)(new_dest - new_src) % WORD_SIZE != 0)
    {
        return MemCpyByByte(dest, src, n);
    }
    
    /* edge case - dest after src */
    if(dest > src) 
    {
        return MemCpy(dest, src, n);
    }
    
    new_dest = (unsigned long*)dest;
    new_src = (unsigned long*)src;
    while(i < n/WORD_SIZE)  /* word count by 8-multiplies of n */
    {
        new_dest[i] = new_src[i];
        ++i;
    }
    /* remaining n bytes */
    MemMoveByByte(&new_dest[i], &new_src[i], n%WORD_SIZE);
    return dest;
}

/******************************************************************************/
/***********************  Helper Functions Definitions ************************/
/******************************************************************************/

/* Refer to MemSet Description */
static void *MemSetByByte(void *s, int c, size_t n)
{
    /* chunks holders */
    unsigned char val_to_write = ' ';
    unsigned char* add_to_overwrite = NULL;
    size_t i = 0;
    
    /* Input validation */
    assert(NULL != s);	
    
    /* according to function signature, c can be max 2^7 occupied by lsb byte*/
    val_to_write = (unsigned char)c;
    /* address to be overwritten */
    add_to_overwrite = (unsigned char*)s;
    
    /* n bytes to be used as overwrite-length */
    while(i < n) 
    {
        add_to_overwrite[i] = val_to_write;
        ++i;
    }

    return s;
}

/* Refer to MemCpy Description */
static void *MemCpyByByte(void *dest, const void *src, size_t n)
{
    unsigned char* new_dest = NULL;
    unsigned char* new_src = NULL;
    size_t i = 0;
    
    new_dest = (unsigned char*)dest; /* return address */
    new_src = (unsigned char*)src;  /* source address */
        
    /* Input validation */
    assert(NULL != dest);
    assert(NULL != src);
    
    /* n bytes to be used as overwrite-length */
    while(i < n)
    {
        new_dest[i] = new_src[i];
        ++i;
    }

    return dest;
}

/* Refer to MemMove Description */
static void *MemMoveByByte(void *dest, const void *src, size_t n)
{

    unsigned char* new_dest = NULL;
    unsigned char* new_src = NULL;
    size_t i = n - 1;     /* runner end to start in order to mitigate runover */
    
    /* Input validation */
    assert(NULL != dest);
    assert(NULL != src);
    
    new_dest = (unsigned char*)dest; /* return address */
    new_src = (unsigned char*)src;  /* source address */

    /* n bytes to be used as overwrite-length */
    while(i > 0) 
    {
        new_dest[i] = new_src[i];
        --i;
    }
    /*Copy the first byte outside the loop to handle i = 0*/
    new_dest[0] = new_src[i];
    return dest;
}

/* Function that places value c 8 times along full word,
in order to make a read to use chunk of reoccuring value c */
static long CastByteToChunk(char c)
{
    size_t i = 0;
    unsigned long mask_word = 0U;
    mask_word |=  c;
    while(i < WORD_SIZE) /* n bytes were requested in signature */
    {
      mask_word <<= 8;
      mask_word |=  c;
      ++i;
    }
    return mask_word;
}

/********************************* Questions **********************************/
/* 
1. Is there a difference between reading from an unaligned buffer and writing 
to an unaligned buffer?
   - Yes, Reading from an unaligned buffer means accessing data that 
   does not start at a memory address that is a multiple of the data size. 
   This can result in performance penalties on some architectures as it may 
   require multiple memory accesses to retrieve a single data value. 
   On the other hand, writing to an unaligned buffer means storing data to 
   a memory location that is not aligned properly, and this can also lead 
   to performance penalties or even crashes on certain platforms. 

2. Why perform word boundary optimization on code?
   - Performing word boundary optimization in code, also known as aligning data 
   on word boundaries, can significantly improve the performance of memory 
   operations, especially on architectures that benefit from aligned memory 
   access. By aligning data on word boundaries (e.g., 4-byte or 8-byte 
   boundaries), memory reads and writes can be performed in a single, 
   efficient operation rather than requiring multiple accesses. 
   This optimization can result in faster and more efficient code execution.

3. What is the cross boundary issue?
   - The cross boundary issue occurs when data is accessed or manipulated 
   in a way that spans across multiple memory boundaries. For example, 
   if a memory operation involves copying or processing data that is not 
   aligned properly and crosses over multiple memory blocks, it can lead to 
   incorrect results, performance degradation, or even system crashes. 
   Handling cross boundary issues requires special care and sometimes 
   additional logic to ensure that the data is correctly handled and 
   processed. This is particularly important in low-level programming and 
   when dealing with architectures that have strict alignment requirements.
*/
