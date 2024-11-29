/******************************************************************************/
/*
  Name: Idan Nave
  Project: VSA
  Reviewer: Dima
  Date: 17/09/23
  Version: 1.0

  Overview: Implementation of an 'first-fit' VSA Manager.
*/

#ifndef __ILRD_VSA_H__
#define __ILRD_VSA_H__

/******************************** Libraries  **********************************/

#include <stddef.h>         /*size_t*/

/******************************** Definitions *********************************/
/*struct Block_Header
{
  long size_available;

  #ifndef NDEBUG
   size_t magic;
  #endif
};*/

typedef struct bl_hdr_t vsa_t;
typedef enum {SUCCESS = 0, FAILURE} vsa_status_t;
typedef enum {FALSE = 0, TRUE} vsa_boolean_t;
/*typedef enum {FREE = 1, USED = -1} vsa_hdrmark_t;
*/
/**************************** VSA API Declarations ****************************/

/* Function that initializes a VSA (Variable-Size Allocator).
   Arguments:    'pool' - Pointer to the memory pool used by the VSA-
                          allocated by user. Min alloc'd space must be 24 Bytes.
                 'size_of_pool' - Total size of the memory pool.
   Return value: Pointer to the newly initialized VSA. On error, returns NULL.
                 By default, The VSA address & Pool size will be aligned to WORD_SIZE, user is encouraged to input aligned values to maximize the VSA pool size in advance.
   Complexity: O(1).
   Undefined Behavior: NULL pointer to VSA,
                       'size_of_pool' smaller than 24 Bytes*/
vsa_t *VSAInit(void *pool, size_t size_of_pool);

/* Function that allocates a varible sized-chunk out from the VSA.
   Arguments:   'vsa' - VSA pointer.
                 'chunk_size' - requeste cunk size.
   Return value: Pointer to the allocated block. On Error- Returns NULL.
   Complexity: O(n), 'n' is num of pool chunks managed at time of call.
   Undefined Behavior: NULL pointer to VSA,  zero 'chunk_size', 
                       pointer that does not belong to a valid 'vsa'
                       supported by this API*/
void *VSAAlloc(vsa_t *vsa, size_t chunk_size);

/* Function that deallocates a given vsa-related pointer,
   makaing it re-available.
   Arguments:    'vsa' - VSA pointer.
                 'block_to_free' - Pointer to the block to be freed.
   Return value: None.
   Complexity: O(1).
   Undefined Behavior: Freed-Already Pointer, pointer that does not belong to a valid 'vsa' supported by this API, Acessing addresses at bounderies of requested pool size*/
void VSAFree(void *chunk_to_free);

/* Function that retrieves the available (free) size within the VSA.
   Arguments:   'vsa' - VSA pointer.
   Return value: size in bytes.
   Complexity: O(n).
   Undefined Behavior: NULL pointer to VSA, pointer that does not belong to a valid 'vsa' supported by this API.*/
size_t VSALargestChunkAvailable(const vsa_t *vsa);

#endif /* __ILRD_VSA_H__ */
