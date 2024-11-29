/******************************************************************************/
/*
  Name: Idan Nave
  Project: FSA
  Reviewer: Aya
  Date: 13/09/23
  Version: 1.0

  Overview: Implementation of an FSA Manager.
*/

/******************************** Libraries  **********************************/

#include <stdio.h>               /* printf */
#include <stddef.h>              /*size_t*/
#include "fsa.h"

/********************************* Type Definitions **************************/

#define WORD_SIZE sizeof(void*)
#define MAGIC_NUM (char)0xCD

struct FSA
{
  size_t next_avail;
};


/************************** Helper Functions Declerations ********************/
static size_t GetAlignedBlockSize(size_t block_size, size_t word_size);
static void* ToPtr(char *to_parse);

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
size_t FSASuggestedSize(size_t block_size, size_t num_of_blocks)
{
   size_t aligned_block_size = GetAlignedBlockSize(block_size, WORD_SIZE);
   assert(0 != block_size);
   assert(0 != num_of_blocks);

   return aligned_block_size * num_of_blocks + sizeof(fsa_t);
}

fsa_t *FSAInit(void *pool, size_t block_size, size_t size_of_pool)
{
   assert(NULL == pool);
   size_t aligned_block_size = GetAlignedBlockSize(block_size, WORD_SIZE);
   size_t num_of_blocks = (size_of_pool - sizeof(fsa_t)) / aligned_block_size;
   size_t i = 0;
   size_t offset = sizeof(fsa_t);
   size_t next_avail = aligned_block_size;
   fsa_t *fsa = (fsa_t*)pool;
   
   fsa->next_avail = 0;
   while(i < num_of_blocks)
   {
      *(((char*)pool)+offset) = next_avail;
      next_avail += aligned_block_size;
      offset += aligned_block_size;
      ++i;
   }

   offset -= aligned_block_size;

   *(((char*)pool)+offset) = MAGIC_NUM;

   return fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
   size_t available_offset = 0;
   char* ret_addr = NULL;
   assert(NULL != fsa);

   if(MAGIC_NUM == (char)fsa->next_avail)
   {
      return NULL;
   }

   available_offset = fsa->next_avail + sizeof(fsa_t);
   ret_addr = (char*)fsa + available_offset;
   fsa->next_avail = *(ret_addr);

   return ToPtr(ret_addr);
}

void FSAFree(fsa_t *fsa, void *block_to_free)
{
   assert(NULL != fsa);
   assert(NULL != block_to_free);   
   *((char*)block_to_free) = fsa->next_avail;
   fsa->next_avail = (size_t)block_to_free - (size_t)fsa - sizeof(fsa_t);
}

size_t FSACountFree(const fsa_t *fsa)
{
   size_t free_counter = 0;
   size_t block_iter = fsa->next_avail;
   char* curr_block = NULL;
   
   assert(NULL != fsa);

   while(block_iter != (MAGIC_NUM))
   {
      ++free_counter;
      curr_block = block_iter + sizeof(fsa_t) + (char*)fsa;
      block_iter = *(curr_block);
   }

   return free_counter;
}

/****************************** Helper Functions ******************************/

static size_t GetAlignedBlockSize(size_t block_size, size_t word_size)
{
   size_t alignment_mask = 0;
   size_t aligned_block_size = 0;

   /*Ensure word_size is a power of 2 (for efficient bitwise operations)
        But not mandatory in all systems*/
   if ((word_size & (word_size - 1)) != 0) 
   {
      /*word_size is not a power of 2, handle this error condition*/
      return 0;
   }

   /*Calculate the alignment mask*/
   alignment_mask = word_size - 1;

   /*Use bitwise AND to align block_size to a multiple of word_size*/
   aligned_block_size = (block_size + alignment_mask) & ~alignment_mask;

   return aligned_block_size;
}

static void* ToPtr(char *to_parse)
{
    return (void*)(to_parse);
}


/*################### GetAlignedBlockSize Explanation ######################*/
/*
Checking if word_size is a power of 2:

The function starts by checking if word_size is a power of 2. This check is essential because the method used relies on word_size being a power of 2 for efficient bitwise operations.

let's consider word_size = 8, which is a power of 2.

Calculating the alignment mask:
The alignment mask is calculated as alignment_mask = word_size - 1. In our example with word_size = 8, the alignment mask is 7 in binary, which is 111.

Aligning block_size:
To align block_size to a multiple of word_size, the function uses bitwise operations. It adds the alignment_mask to block_size, which sets the lower bits to 1 while keeping the higher bits unchanged. Then, it uses bitwise AND with the complement of the alignment_mask to clear the lower bits, ensuring that the result is aligned.

Let's say block_size = 17. In binary, this is 10001. When we add the alignment_mask (111) to it, we get 10100. Finally, using the bitwise AND with the complement of the alignment_mask, we clear the lower 3 bits, resulting in 10000.

So, aligned_block_size becomes 16, which is a multiple of 8 (our word_size).

Returning the aligned size:

The function returns the aligned_block_size, which is now aligned to a multiple of word_size.

In summary, this function takes a block_size and aligns it to the nearest multiple of word_size. It does so by calculating an alignment_mask based on the word_size, adding this mask to block_size to round it up, and then clearing the lower bits to ensure alignment. This technique is particularly useful when working with memory allocation and data structures that require alignment to a specific word size.
*/