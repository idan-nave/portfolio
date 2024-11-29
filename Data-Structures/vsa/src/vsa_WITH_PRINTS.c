/******************************************************************************/
/*
  Name: Idan Nave
  Project: VSA
  Reviewer: Dima
  Date: 17/09/23
  Version: 1.0

  Overview: Implementation of an VSA Manager.
*/

/******************************** Libraries  **********************************/

#include <assert.h>             /* assert */
#include <stdio.h>              /* printf */
#include <stdlib.h>             /* malloc(), free() abs()*/
#include <stddef.h>             /* size_t, NULL */

#include "vsa.h"

/********************************* Type Definitions **************************/

#define WORD_SIZE sizeof(void*)
#define HDR_SIZE sizeof(bl_hdr_t)
#define MIN_ALLOC_SIZE HDR_SIZE + WORD_SIZE
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
static size_t GetAlignedSize(size_t size, size_t word_size);
static size_t IsAlignedSize(size_t size, size_t word_size);

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
/*[Memory Pool]___168 total, 16+6*8=64 HDRs, 48/104 Avail___:  62% Efficiency
|---|----|---|----|---|----|---|----|---|----|---|----|-----|
| H | B1 | H | B2 | H | B3 | H | B4 | H | B5 | H | B6 | End |
|---|----|---|----|---|----|---|----|---|----|---|----|-----|
|+32| U  |-16| A  |+64| U  |+8 | U  |-32| A  |+16| U  |magic| U= Used,A= Avail
|---|----|---|----|---|----|---|----|---|----|---|----|-----|*/

vsa_t *VSAInit(void *pool, size_t pool_size)
{
    size_t size_avail = 0;
    bl_hdr_t *vsa = NULL;
    bl_hdr_t *end = NULL;

    size_t pool_addr = (size_t)((char*)pool);
    size_t aligned_pool_addr = GetAlignedSize(pool_addr, WORD_SIZE);
    char* aligned_pool = (char*)&aligned_pool_addr;

    size_t lost_space = aligned_pool_addr - pool_addr;
    size_t aligned_pool_size = pool_size - lost_space; /*assumption: aligned*/

    assert(NULL != pool);
    assert(2*HDR_SIZE <= pool_size);
    printf("pool addr origin: %lx\n", pool_addr);
    printf("pool addr aligned: %lx\n", aligned_pool_addr);
    printf("lost_space: %ld\n", lost_space);
    printf("pool size origin: %ld\n", pool_size);
    printf("pool size minus lost_space: %ld\n", aligned_pool_size);

    /*validate pool_size is aligned & compensate if needed*/
    if(!IsAlignedSize(aligned_pool_size, WORD_SIZE))
    {
        aligned_pool_size = 
        GetAlignedSize(aligned_pool_size, WORD_SIZE) - WORD_SIZE;
    }/*now for sure- pool use wont exceed user alloc'd space*/
    printf("aligned pool size: %ld\n", aligned_pool_size);

    /*tail (magic number) & vsa 1st header are decremented from available size*/
    size_avail = aligned_pool_size - 2*HDR_SIZE;
    printf("pool available size: %ld\n", size_avail);

    /*vsa = (bl_hdr_t*)(aligned_pool);*/ /*1st header of the pool*/
    vsa = (bl_hdr_t*)((char*)pool + (pool_addr - aligned_pool_addr));
    printf("vsa addr aligned: %p\n", (char*)vsa);

    /*init the vsa*/
    vsa->size_avail = size_avail;

    if(0 == size_avail)
    {
        return NULL; /*no usable space remains after alignment considerations*/
    }

    ToggleState(vsa); /*mark as avail (-)*/
    printf("vsa long value: %ld\n", vsa->size_avail);

    /*set the ending header to be aligned and contain magic number*/
    end = (bl_hdr_t*)((char*)vsa + size_avail + HDR_SIZE);
    /*55b8be4f8520*/
    end->size_avail = END_MAGIC;
    printf("end addr aligned: %p\n", (char*)end);
    printf("HDR_SIZE: %ld\n", HDR_SIZE);

    /*mark the vsa with unique magic*/
    #ifndef NDEBUG
    vsa->magic = PTR_MAGIC;
    #endif

    return (vsa_t*)(vsa);
}

void *VSAAlloc(vsa_t *vsa, size_t chunk_size)
{
    bl_hdr_t *vsa_hdr = VSAToHdr(vsa);
    bl_hdr_t *allocd = NULL;
    size_t allocd_size = 0;

    assert( 0 != chunk_size );
    assert( NULL != vsa );
    printf("###Inside VSAAlloc ###\n");

    chunk_size = GetAlignedSize(chunk_size, WORD_SIZE);
        printf("###REQUESTED  IS OK: %ld ###\n", chunk_size);

    /*validate available size is usable- at least
    enough for a Header & 8 Bytes to be requested*/
    if (VSALargestChunkAvailable(vsa) < MIN_ALLOC_SIZE) 
    {
        return NULL;
    }

        printf("###POOL REMAINING SIZE IS OK: %ld ###\n", VSALargestChunkAvailable(vsa));
        /*        printf("###POOL REMAINING SIZE IS OK: %ld ###\n", VSALargestChunkAvailable(vsa));*/
    
    printf("BEFORE GetChunkBySize:  %p\n\n\n\n", vsa_hdr);

    /*get available chunk & validate */
    allocd = GetChunkBySize( vsa, chunk_size );
    if (NULL == allocd)/*no fit for request*/
    {
            printf("### GetChunkBySize rtrns null inside malloc ###\n\n\n\n");

       return NULL;
    }
    printf("### GetChunkBySize DONE ###\n\n\n\n");

    allocd_size = GetSize(allocd);

        printf("###allocd HDR is: %p ###\n", allocd);
    /*case EXACT- no need to add new hdr, only set existing*/
    if( chunk_size == allocd_size ) 
    {

        printf("\t\t###Inside IF #1 ###\n");
        printf("###chunk_size size is: %ld ###\n", chunk_size);
        printf("###allocd HDR size is: %ld ###\n", allocd_size);
        ToggleState(allocd); /*mark used (+)*/
    }
    /*case GREATER- need to set hdr*/
    else if( chunk_size < allocd_size )
    {   

        size_t fragment = allocd_size - chunk_size;
        printf("\t\t###Inside IF #2 ###\n");
        printf("###chunk_size size is: %ld ###\n", chunk_size);
        printf("###allocd HDR size is: %ld ###\n", allocd_size);
        /*need to mark fragment using an addition of a new header */
        if (fragment >= MIN_ALLOC_SIZE)
        {
            bl_hdr_t *frag_hdr = NULL;
        printf("###fragment size is: %ld ###\n", fragment);
        printf("###MIN_ALLOC_SIZE size is: %ld ###\n", MIN_ALLOC_SIZE);

            /* set allocated header */
            SetHdr(allocd, chunk_size); /*mark used (+)*/
        printf("***allocd->size_avail %ld ###\n", allocd->size_avail);
            /* insert new fragment header */
            frag_hdr = (bl_hdr_t*)((char*)allocd + HDR_SIZE + chunk_size);

            SetHdr(frag_hdr, fragment - HDR_SIZE);
            ToggleState(frag_hdr); /*mark free (-)*/
        printf("***frag_hdr add %p ###\n", frag_hdr);
        printf("***frag_hdr->size_avail %ld ###\n", frag_hdr->size_avail);
        }
        /*no point of adding a new header*/
    }

    printf("#################allocd->size_avail %ld ###\n", allocd->size_avail);   printf("#################vsa_hdr->size_avail %ld ###\n", vsa_hdr->size_avail);
            printf("***RTRND PTR add IS %p ###\n", ToPtr( allocd ));

    return ToPtr( allocd );
}

void VSAFree(void *chunk_to_free)
{
    assert( NULL != chunk_to_free );
    printf("PTR TO FREE long value: %ld\n", ToHdr(chunk_to_free)->size_avail);

    /*Available Header is not allowed*/
    assert( TRUE != IsAvailable(ToHdr(chunk_to_free)) );
    ToggleState( ToHdr(chunk_to_free) );
}

size_t VSALargestChunkAvailable(const vsa_t *vsa)
{
    size_t temp_i = 0;
    size_t max_avail = 0;
    size_t res_avail = 0;
    size_t *res_ptr = &res_avail;
    bl_hdr_t* cur_header = VSAToHdr((vsa_t *)vsa);
    printf("###Inside VSALargest ###\n");
    printf("VSALargest_FirstChunk_header:  %p\n", (char*)cur_header);
    assert( NULL != vsa );

        printf("start loop\n");
    while(NULL != cur_header)       
    {   
        ++temp_i;  
        printf("VSALargest #: %ld : %p\n", temp_i, (char*)cur_header);
        printf("res_ptr_before_func #: %ld : %ld\n", temp_i, *res_ptr);

        /*cur_header = GetNextHeader(cur_header);*/
        cur_header = GetFirstChunkAvailable(cur_header, res_ptr);
        if (NULL == cur_header)/*no avail space*/
        {   
           return 0;
        }
        printf("^^^^FirstChunkADDRS:  %p\n", (char*)cur_header);

        if( res_avail > max_avail )
        {
            max_avail = res_avail;
        }
        printf("cur_header->size_avail #: %ld \n", cur_header->size_avail);
        cur_header = GetNextHeader(cur_header);

        

        if( cur_header->size_avail == END_MAGIC )
        {
            return max_avail;
        }
        printf("res_avail #: %ld : %ld\n", temp_i, res_avail);
        printf("max_avail #: %ld : %ld\n", temp_i, max_avail);

        if(temp_i == 10)
        {
            printf("### VSALargest Terminated after %ld times###\n", temp_i);
            return 0;
        }
    }
    printf("VSALargest RTRN max_avail:  %ld\n", max_avail);
    return max_avail;
}

/******************************************************************************/
/************************** Helper Functions Decfinitons **********************/
/******************************************************************************/

/*********************** Defragmentation Functions  ***************************/

/*Function that provides an available chunk of the pool that fits (<=) the requested size (first-fit). On-Error returns NULL*/
static bl_hdr_t* GetChunkBySize(const vsa_t *vsa, size_t requested_size)
{
    size_t temp_i = 0;
    size_t res_avail = 0;
    size_t *res_ptr = &res_avail;
    bl_hdr_t* cur_header = VSAToHdr((vsa_t *)vsa);
    printf("###Inside GetChunkBySize ###\n");
    printf("GetChunkBySize Chunk_header:  %p\n", (char*)cur_header);
    assert( NULL != vsa );

    while(NULL != cur_header)       
    {   
        ++temp_i;  
        printf("GetChunkBySize #: %ld : %p\n", temp_i, (char*)cur_header);
        printf("res_ptr_before_func #: %ld : %ld\n", temp_i, *res_ptr);

        /*cur_header = GetNextHeader(cur_header);*/
        cur_header = GetFirstChunkAvailable(cur_header, res_ptr);
        if (NULL == cur_header)/*no avail space*/
        {   
           return NULL;
        }
                printf("res_ptr_after_func #: %ld : %ld\n", temp_i, *res_ptr);
        if( res_avail >= requested_size )
        {
            return cur_header;
        }
        printf("cur_header->size_avail #: %ld \n", cur_header->size_avail);
        cur_header = GetNextHeader(cur_header);

        

        if( cur_header->size_avail == END_MAGIC )
        {
            return NULL;
        }
        printf("res_avail #: %ld : %ld\n", temp_i, res_avail);

        if(temp_i == 10)
        {
            printf("### GetChunkBySize Terminated after %ld times###\n", temp_i);
            return 0;
        }
    }
        printf("\t\t\t\t\t\t###GetChunkBySize RTRNS NULL ###\n");

    return NULL;
}

/*Function that provides a 1st available chunk of the pool, starting from a given header. Available size will be passed into 'res_size' ptr. On-Error returns NULL*/
static bl_hdr_t* GetFirstChunkAvailable(bl_hdr_t *start,size_t* res_size)
{
    size_t temp_i = 0;
    bl_hdr_t* cur_header = start;
    printf("###Inside GetFirstChunk ###\n");
    assert( NULL != start );
    assert( NULL != res_size );
    while(!IsEnding(cur_header))       
    {   
        ++temp_i;
        printf("GetFirstChunk #: %ld : %p\n", temp_i, (char*)cur_header);
        if(TRUE == IsAvailable(cur_header))
        {   
            *res_size = DefragSequenceFrom(cur_header);
            printf("GetFirstChunk RTRN cur_header:  %p\n", (char*)cur_header);
            return cur_header;
        }
        cur_header = GetNextHeader(cur_header);

        if(temp_i == 10)
        {
            printf("### GetFirstChunk Terminated after %ld times###\n", temp_i);
            return NULL;
        }
    }
            printf("\t\t\t\t\t\t###GetFirstChunkAvailable RTRNS NULL ###\n");

    return NULL;
}

/*Function to Defrag all Avail Headers that are in a sequence starting from valid available header 'start'. Returns the total number of available chunk sapce aggregated during the operation*/
static size_t DefragSequenceFrom(bl_hdr_t *start)
{
    size_t temp_i = 0;
    bl_hdr_t* cur_header = start;
    size_t chunk_aggregated = (-1) * HDR_SIZE; /*ignore starting header*/
    printf("###Inside DefragSequenceFrom ###\n");
    assert( NULL != start );
        printf("start long value: %ld\n", cur_header->size_avail);

    assert(FALSE != IsAvailable(start));/*USED Header is not allowed*/


        if (TRUE == IsAvailable(start))
        {
            printf("goooooooooooooooood\n");
        }    
    while( IsAvailable(cur_header) && !IsEnding(cur_header))       
    {   
        ++temp_i;
        printf("DefragSequence #: %ld : %p\n", temp_i, (char*)cur_header);
        chunk_aggregated += AggregateHeader(cur_header);
        printf("### chunk_aggregated = %ld ###\n",chunk_aggregated);

        cur_header = GetNextHeader(cur_header);
        if(temp_i == 10)
        {
            printf("### DefragSequence Terminated after %ld times###\n",temp_i);
            return 0;
        }
    }
    SetHdr(start, chunk_aggregated);
    ToggleState(start); /*mark free (-)*/
    printf("DefragSequence RTRN chunk_aggregated:  %ld\n", chunk_aggregated);
    return chunk_aggregated;
}

/*Function to toggle header's last property size (-)-->(+) or (+)-->(-)*/
static void ToggleState(bl_hdr_t *header)
{    
    assert( NULL != header );
    header->size_avail *= (-1);
}

/*Function to set a headers property size*/
static void SetHdr(bl_hdr_t *header, size_t set_size)
{    
    assert( NULL != header );
    assert( 0 != set_size );
    header->size_avail =  (long)set_size;
}

/*************************** Header Traversing  *******************************/

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
/*        printf("printX:  %lx\n", (size_t)((char*)header));
*/

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

/************************** Parsing Functions  ********************************/

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
         printf("printX:\n");

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

/************************ Alignment Functions  ********************************/

/*Function that passes an aligned 'size' with respect to 'word size'*/
static size_t GetAlignedSize(size_t size, size_t word_size)
{
   size_t alignment_mask = 0;
   size_t aligned_size = 0;

   /*Calculate the alignment mask*/
   alignment_mask = word_size - 1;

   /*Use bitwise AND to align size to a multiple of word_size*/
   aligned_size = (size + alignment_mask) & ~alignment_mask;

   return aligned_size;
}

/*Function that validates an aligned 'size' with respect to 'word size'*/
static size_t IsAlignedSize(size_t size, size_t word_size)
{
    /* Check if the original size matches the aligned size */
    if (size == GetAlignedSize(size, word_size))
    {
        return TRUE; /* Size is aligned */
    } 
    return FALSE; /* Size is not aligned */
}

/*Function to Defrag all Avail Headers that are in a sequence starting from valid available header 'start'. Returns the total number of available chunk sapce aggregated during the operation*/
/*static size_t DoesBelongToVsa(void* vsa_ptr)
{
    bl_hdr_t* cur_header = vsa_ptr - HDR_SIZE;
    printf("###Inside ValidatePtr ###\n");
    assert( NULL != vsa_ptr );

    while(!IsEnding(cur_header))       
    {   
        cur_header = GetNextHeader(cur_header);
    }

    return chunk_aggregated;
}
*/