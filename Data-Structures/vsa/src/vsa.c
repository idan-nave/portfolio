/******************************************************************************/
/*
  Name: Idan Nave
  Project: VSA
  Reviewer: Dima
  Date: 17/09/23
  Version: 1.0

  Overview: Implementation of an VSA Manager.

|---|----|---|----|---|----|---|----|---|----|---|----|-----|
| H | B1 | H | B2 | H | B3 | H | B4 | H | B5 | H | B6 | End |
|---|----|---|----|---|----|---|----|---|----|---|----|-----|
|+32| U  |-16| A  |+64| U  |+8 | U  |-32| A  |+16| U  |magic| U= Used,A= Avail
|---|----|---|----|---|----|---|----|---|----|---|----|-----|
Above Example info:
[Memory Pool]___168 total, 16+6*8=64 HDRs, 48/104 Avail___:  62% Efficiency

*/

/******************************** Libraries  **********************************/

#include <assert.h>             /* assert */
#include <stdlib.h>             /* abs()*/
#include <stddef.h>             /* size_t, NULL */

#include "vsa.h"

/********************************* Type Definitions **************************/

#define ZERO_CHUNK_REQUEST  0
#define NO_AVAIL_CHUNK      0
#define WORD_SIZE           sizeof(void*)
#define HDR_SIZE            sizeof(bl_hdr_t)
#define MIN_ALLOC_SIZE      HDR_SIZE + WORD_SIZE
#define MIN_POOL_SIZE       2*HDR_SIZE
#define END_MAGIC           0xDEADC0DE
#define PTR_MAGIC           0xDEADBEEF

typedef struct Block_Header
{
  long size_avail;
  
  #ifndef NDEBUG
     long magic;
  #endif
}bl_hdr_t;

/************************** Helper Functions Declerations ********************/

/* Defragmentations Functions */
static bl_hdr_t* GetChunkBySize(const vsa_t *vsa, size_t requested_size);
static bl_hdr_t* GetFirstChunkAvailable(bl_hdr_t *start,size_t* res_size);
static size_t DefragSequenceFrom(bl_hdr_t *start);
static void ToggleState(bl_hdr_t *header);
static void SetHdr(bl_hdr_t *header, size_t set_size);

/* Header Traversing */
static size_t AggregateHeader(bl_hdr_t *header);
static bl_hdr_t* GetNextHeader(bl_hdr_t *header);
static int IsAvailable(bl_hdr_t *header);
static int IsEnding(bl_hdr_t *header);

/* Parsing Functions */
static vsa_t* HdrToVSA(bl_hdr_t *to_parse);
static bl_hdr_t* VSAToHdr(vsa_t *to_parse);
static bl_hdr_t* ToHdr(void *to_parse);
static void* ToPtr(bl_hdr_t *to_parse);
static size_t AbsLong(long num);
static size_t GetSize(bl_hdr_t *header);

/* Alignment Functions */
static size_t AlignUp(size_t size, size_t align_to);
static size_t IsAlignedSize(size_t size, size_t align_to);

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/

vsa_t *VSAInit(void *pool, size_t pool_size)
{
    size_t size_avail = 0;
    bl_hdr_t *first_header = NULL;
    bl_hdr_t *ending_header = NULL;
    size_t pool_addr = (size_t)((char*)pool);
    size_t aligned_pool_addr = AlignUp(pool_addr, WORD_SIZE);
    char* aligned_pool = (char*)&aligned_pool_addr;
    size_t lost_space = aligned_pool_addr - pool_addr;
    size_t aligned_pool_size = pool_size - lost_space; /*assumption: aligned*/

    assert(NULL != pool);
    assert(MIN_POOL_SIZE <= pool_size);

    /*validate pool_size is aligned & compensate if needed*/
    if(!IsAlignedSize(aligned_pool_size, WORD_SIZE))
    {
        aligned_pool_size = 
        AlignUp(aligned_pool_size, WORD_SIZE) - WORD_SIZE;
    }
    /*up until now- pool usage is garenteed not to exceed user alloc'd space*/

    /*tail (magic number) & vsa 1st header are decremented from available size*/
    size_avail = aligned_pool_size - MIN_POOL_SIZE;

    /*1st header of the pool*/
    first_header = (bl_hdr_t*)((char*)pool + (pool_addr - aligned_pool_addr));

    /*init the first_header*/
    first_header->size_avail = size_avail;

    if(NO_AVAIL_CHUNK == size_avail)
    {
        return NULL; /*no usable space remains after alignment considerations*/
    }

    ToggleState(first_header); /*mark as avail (-)*/

    /*set the ending header to be aligned and contain magic number*/
    ending_header = (bl_hdr_t*)((char*)first_header + size_avail + HDR_SIZE);
    ending_header->size_avail = END_MAGIC;

    /*mark the first_header with unique magic*/
    #ifndef NDEBUG
    first_header->magic = PTR_MAGIC;
    #endif

    return (vsa_t*)(first_header);
}

void *VSAAlloc(vsa_t *vsa, size_t chunk_size)
{
    bl_hdr_t *allocd = NULL;
    size_t allocd_size = 0;

    assert( ZERO_CHUNK_REQUEST != chunk_size );
    assert( NULL != vsa );

    chunk_size = AlignUp(chunk_size, WORD_SIZE);

    /*validate available size is usable- at least
    enough for a Header & 8 Bytes to be requested*/

    if (VSALargestChunkAvailable(vsa) < MIN_ALLOC_SIZE) 
    {
        return NULL;
    }

    /*get available chunk & validate */
    allocd = GetChunkBySize( vsa, chunk_size );

    if (NULL == allocd)/*no fit for request*/
    {
       return NULL;
    }

    allocd_size = GetSize(allocd);

    /*case EXACT- no need to add new hdr, only set existing*/
    if( chunk_size == allocd_size ) 
    {
        ToggleState(allocd); /*mark used (+)*/
    }

    /*case GREATER- need to set hdr*/
    else if( chunk_size < allocd_size )
    {   
        size_t fragment = allocd_size - chunk_size;

        /*need to mark fragment using an addition of a new header */
        if (fragment >= MIN_ALLOC_SIZE)
        {
            bl_hdr_t *frag_hdr = NULL;

            /* set allocated header */
            SetHdr(allocd, chunk_size); /*mark used (+)*/
            /* insert new fragment header */
            frag_hdr = (bl_hdr_t*)((char*)allocd + HDR_SIZE + chunk_size);

            SetHdr(frag_hdr, fragment - HDR_SIZE);
            ToggleState(frag_hdr); /*mark free (-)*/
        }
        /*otherwise no point of adding a new header*/
    }
    return ToPtr( allocd );
}

void VSAFree(void *chunk_to_free)
{
    assert( NULL != chunk_to_free );
    /*A ptr that dosen't belongs to the VSA and failed parsing- isn't allowed*/
    assert( NULL != ToHdr(chunk_to_free) );
    /*A pointer that fits a Header that points to Available size isn't allowed*/
    assert( TRUE != IsAvailable(ToHdr(chunk_to_free)) );

    ToggleState( ToHdr(chunk_to_free) );
}

size_t VSALargestChunkAvailable(const vsa_t *vsa)
{
    size_t max_avail = 0;
    size_t res_avail = 0;
    bl_hdr_t* cur_header = VSAToHdr((vsa_t *)vsa);

    assert( NULL != vsa );

    while(NULL != cur_header)       
    {   
        cur_header = GetFirstChunkAvailable(cur_header, &res_avail);
        if (NULL == cur_header)/*no avail space*/
        {   
           return NO_AVAIL_CHUNK;
        }

        if( res_avail > max_avail )
        {
            max_avail = res_avail;
        }
        cur_header = GetNextHeader(cur_header);

        if( cur_header->size_avail == END_MAGIC )
        {
            return max_avail;
        }
    }
    return max_avail;
}

/******************************************************************************/
/************************** Helper Functions Decfinitons **********************/
/******************************************************************************/

/*********************** Defragmentation Functions  ***************************/

/*Function that provides an available chunk of the pool that fits (<=) the requested size (first-fit). On-Error returns NULL*/
static bl_hdr_t* GetChunkBySize(const vsa_t *vsa, size_t requested_size)
{
    size_t res_avail = 0;
    bl_hdr_t* cur_header = VSAToHdr((vsa_t *)vsa);

    assert( ZERO_CHUNK_REQUEST != requested_size );
    assert( NULL != vsa );

    while(NULL != cur_header)       
    {   
        cur_header = GetFirstChunkAvailable(cur_header, &res_avail);

        if (NULL == cur_header)/*no avail space*/
        {   
           return NULL;
        }

        if( res_avail >= requested_size )
        {
            return cur_header;
        }
        cur_header = GetNextHeader(cur_header);

        if( cur_header->size_avail == END_MAGIC )
        {
            return NULL;
        }
    }
    return NULL;
}

/*Function that provides a 1st available chunk of the pool, starting from a given header. Available size will be passed into 'res_size' ptr. On-Error returns NULL*/
static bl_hdr_t* GetFirstChunkAvailable(bl_hdr_t *start, size_t* res_size)
{
    bl_hdr_t* cur_header = start;

    assert( NULL != start );
    assert( NULL != res_size );

    while(!IsEnding(cur_header))       
    {   

        if(TRUE == IsAvailable(cur_header))
        {   
            *res_size = DefragSequenceFrom(cur_header);
            return cur_header;
        }
        cur_header = GetNextHeader(cur_header);
    }
    return NULL;
}

/*Function to Defrag all Avail Headers that are in a sequence starting from valid available header 'start'. Returns the total number of available chunk sapce aggregated during the operation*/
static size_t DefragSequenceFrom(bl_hdr_t *start)
{
    bl_hdr_t* cur_header = start;
    size_t chunk_aggregated = (-1) * HDR_SIZE; /*ignore starting header*/

    assert( NULL != start );
    assert(FALSE != IsAvailable(start));/*USED Header is not allowed*/
  
    while( IsAvailable(cur_header) && !IsEnding(cur_header))       
    {   
        chunk_aggregated += AggregateHeader(cur_header);
        cur_header = GetNextHeader(cur_header);
    }

    SetHdr(start, chunk_aggregated);
    ToggleState(start); /*mark free (-)*/
    return chunk_aggregated;
}

/*Function to toggle header's sign of available size (-)-->(+) or (+)-->(-)*/
static void ToggleState(bl_hdr_t *header)
{    
    assert( NULL != header );
                    /*BITWISE IMP. OF header->size_avail *= (-1);*/
    header->size_avail = ~(header->size_avail) + 1;
}

/*Function to set a headers property size*/
static void SetHdr(bl_hdr_t *header, size_t set_size)
{    
    assert( NULL != header );
    assert( 0 != set_size );
    header->size_avail =  (long)set_size;
}

/******************************************************************************/
/*************************** Header Traversing  *******************************/
/******************************************************************************/

/*Function to pass a header's property size, taking into account the header*/
static size_t AggregateHeader(bl_hdr_t *header)
{    
    assert( NULL != header );
    return GetSize(header) + HDR_SIZE;
}

/*Function to provide the next header of 'header'*/
static bl_hdr_t* GetNextHeader(bl_hdr_t *header)
{    
    assert( NULL != header );
    return (bl_hdr_t*)((char*)header + HDR_SIZE + GetSize(header));
}

/*Function to validate header's availability property*/
static int IsAvailable(bl_hdr_t *header)
{    
    assert( NULL != header );
    return ( (header->size_avail < 0) && (!IsEnding(header)) );
}

/*Function to validate end of pool mark*/
static int IsEnding(bl_hdr_t *header)
{    
    assert( NULL != header );
    return (header->size_avail == END_MAGIC);
}

/******************************************************************************/
/************************** Parsing Functions  ********************************/
/******************************************************************************/

/*Function to parse a vsa ptr into a header ptr*/
static bl_hdr_t* VSAToHdr(vsa_t *to_parse)
{    
    assert( NULL != to_parse );
    return (bl_hdr_t*)(to_parse);
}

/*Function to parse a vsa ptr into a header ptr*/
static vsa_t* HdrToVSA(bl_hdr_t *to_parse)
{    
    assert( NULL != to_parse );
    return (vsa_t*)(to_parse);
}

/*Function to parse a void ptr into a header ptr*/
static bl_hdr_t* ToHdr(void *to_parse)
{    
    bl_hdr_t* parsed = NULL;

    assert( NULL != to_parse );

    parsed = (bl_hdr_t*)(((char*)to_parse) - HDR_SIZE);
    
    #ifndef NDEBUG
    if (PTR_MAGIC != parsed->magic)
    {
        return NULL;
    }
    #endif

    return parsed; /*decremented by HDR size*/
}

/*Function to parse a header ptr into a void ptr*/
static void* ToPtr(bl_hdr_t *to_parse)
{    
    assert( NULL != to_parse );
    
    #ifndef NDEBUG
    to_parse->magic = PTR_MAGIC;
    #endif

    return (void*)((char*)to_parse + HDR_SIZE); /*increment HDR*/
}

/*Function that passes an absolute value of a header's size mark*/
static size_t AbsLong(long num)
{
    return (size_t)(abs((int)(num)));
}

/*Function to return the available size pointed by the header metainfo*/
static size_t GetSize(bl_hdr_t *header)
{    
    assert( NULL != header );
    return AbsLong(header->size_avail);
}

/******************************************************************************/
/************************ Alignment Functions  ********************************/
/******************************************************************************/

/*Function that passes an aligned 'val' with respect to 'align_to'*/
static size_t AlignUp(size_t val, size_t align_to)
{
   size_t alignment_mask = 0;
   size_t aligned_val = 0;

   /*Calculate the alignment mask*/
   alignment_mask = align_to - 1;

   /*Use bitwise AND to align val to a multiple of 'align_to'*/
   aligned_val = (val + alignment_mask) & ~alignment_mask;

   return aligned_val;
}

/*Function that validates an aligned 'val' with respect to 'align_to'*/
static size_t IsAlignedSize(size_t val, size_t align_to)
{
    /* Check if the original value matches the aligned value */
    if (val == AlignUp(val, align_to))
    {
        return TRUE; /* Size is aligned */
    } 

    return FALSE; /* Size is not aligned */
}