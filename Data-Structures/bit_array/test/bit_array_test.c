/******************************* Test_BitArray.c  *****************************/
/*
  Name: Idan Nave
  Project: Work Sheet - DATA Structures
  Reviewer: ???
  Date: 07/08/23SS
  Version: 1.0
*/
/******************************** Libraries  **********************************/

#include <assert.h> 		/* assert() */
#include <stdio.h>  		/* FILEs, stderr, stdin, stdout */
#include <stdlib.h> 		/* malloc(), free() */
#include <string.h>             /* strcmp */
#include <math.h>               /* pow() */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */

#include "bit_array.h" 			

/******************************** Definitions  ********************************/

#define TEST_FAIL -1	        

/* Array Lengths' Definition */
#define TEST_ARR_LEN 4	         
#define SYS_WORD_SIZE 8	          
#define SYS_BYTE_SIZE 8	         
#define NUM_OF_BITS_IN_WORD 64	 

/* Bit Arrays constants */
#define SET_ALL 0xffffffffffffffff
#define UNSET_ALL 0

/******************************************************************************/
/**************************** Testing Data-structures *************************/
/******************************************************************************/

  /******************************** GLobals  ********************************/

const bit_array_ty g_generic_test_arr[TEST_ARR_LEN]  = {  0x0000000000000000,
                                                          0x000000000000000f,
                                                          0x00000000f000f0f0,
                                                          0x00000000f0000000 };
const bit_array_ty g_mirror_test_arr[TEST_ARR_LEN]  =  {  0x0000000000000000,
                                                          0xf000000000000000,
                                                          0x0f0f000f00000000,
                                                          0x0000000f00000000 };
                                                          
/******************************************************************************/
/**************** Forward Declarations of Static Functions ********************/
/******************************************************************************/ 

static int ExecuteApp();

static int Test_SetAll();
static int Test_ResetAll();
static int Test_SetOn();
static int Test_SetOff();
static int Test_SetBit();
static int Test_GetVal();
static int Test_Flip();
static int Test_Mirror();
static int Test_RotateRight();
static int Test_RotateLeft();
static int Test_CountOn();
static int Test_CountOff();
static int Test_ToString();

static int Test_CountOnByLUT();
static int Test_MirrorByLUT();

/************************************** Main **********************************/

int main()
{   
    /*  int argc, char *argv[], char *envp - UNUSED */
    return ExecuteApp();
}

/**************************** Tests Sequence **********************************/
 
int ExecuteApp()
{
    errno = 0; /* Clear errno before callingtest functions */
    
    errno =  Test_SetAll();
    if(errno)
    {
        printf("\n********Testing SetAll FAILED********\n");
        return errno;
    }

    errno =  Test_ResetAll();
    if(errno)
    {
        printf("\n********Testing ResetAll FAILED********\n");
        return errno;
    }
    
    errno =  Test_SetOn();
    if(errno)
    {
        printf("\n********Testing SetOn FAILED********\n");
        return errno;
    }
    
    errno =  Test_SetOff();
    if(errno)
    {
        printf("\n********Testing SetOff FAILED********\n");
        return errno;
    }
    
    errno =  Test_SetBit();
    if(errno)
    {
        printf("\n********Testing SetBit FAILED********\n");
        return errno;
    }
    
    errno =  Test_GetVal();
    if(errno)
    {
        printf("\n********Testing GetVal FAILED********\n");
        return errno;
    }
    
    errno =  Test_Flip();
    if(errno)
    {
        printf("\n********Testing Flip FAILED********\n");
        return errno;
    }
    
    errno =  Test_CountOn();
    if(errno)
    {
        printf("\n********Testing CountOn FAILED********\n");
        return errno;
    }
    
    errno =  Test_CountOff();
    if(errno)
    {
        printf("\n********Testing CountOff FAILED********\n");
        return errno;
    }
    
    errno =  Test_Mirror();
    if(errno)
    {
        printf("\n********Testing Mirror FAILED********\n");
        return errno;
    }
    
    errno =  Test_RotateLeft();
    if(errno)
    {
        printf("\n********Testing RotateLeft FAILED********\n");
        return errno;
    }
    
    errno =  Test_RotateRight();
    if(errno)
    {
        printf("\n********Testing RotateRight FAILED********\n");
        return errno;
    }
    
    errno =  Test_ToString();
    if(errno)
    {
        printf("\n********Testing ToString FAILED********\n");
        return errno;
    }

    /**************** LUT Testing **************************/
      
    errno =  Test_CountOnByLUT();
    if(errno)
    {
        printf("\n********Testing CountOnByLUT FAILED********\n");
        return errno;
    } 
      
    errno =  Test_MirrorByLUT();
    if(errno)
    {
        printf("\n********Testing MirrorByLUT FAILED********\n");
        return errno;
    }
    
    return 0;
}

/******************************************************************************/
/************* Tests Implementation - Functions Definitions *******************/
/******************************************************************************/

/*Function that sets all the bits. 
  Arguments: array of 64 bits.
  Return value: It returns the set array.*/
static int Test_SetAll()
{
    size_t i = 0;                     /* runner for test array */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    errno = 0;                        /* init errno */
    
    printf("\n********Testing SetAlls********\n"); 
    while (i < TEST_ARR_LEN)
    {
        res_bit_arr = SetAll(g_generic_test_arr[i]); /* perform call */
        
        printf("%lu changed to %lu\n", g_generic_test_arr[i], res_bit_arr);
        if(res_bit_arr != SET_ALL)     /* validate all test cases pass at wil */
        {
            errno = TEST_FAIL;
        }
        ++i;
    }
    return errno;
}

static int Test_ResetAll()
{
    size_t i = 0;                     /* runner for test array */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    errno = 0;                        /* init errno */
    
    printf("\n********Testing ResetAlls********\n"); 
    while (i < TEST_ARR_LEN)
    {
        res_bit_arr = ResetAll(g_generic_test_arr[i]); /* perform call */
        /* change all bits to zero and check against 0 - words*/
        printf("%lu changed to %lu\n", g_generic_test_arr[i], res_bit_arr);
        if(res_bit_arr != 0)     /* validate all test cases pass at wil */
        {
            errno = TEST_FAIL;
        }
        ++i;
    }
    return errno;
}

static int Test_SetOn()
{
    size_t i = 0;                     /* runner for test array */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    errno = 0;                        /* init errno */
    /* change singular bit in all-zeroes Word and check value equals 2^i*/
    printf("\n********Testing SetOn********\n"); 
    while (i < SYS_WORD_SIZE)
    {
        res_bit_arr = SetOn(UNSET_ALL, i); /* perform call */
        
        printf("%lu changed to %lu\n", (size_t)(0), res_bit_arr);
        if(res_bit_arr != pow(2,i))     /* validate all test cases pass at wil */
        { 
            errno = TEST_FAIL;
        }
        ++i;
    }
    return errno;
}

static int Test_SetOff()
{
    size_t i = 0;                     /* runner */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    errno = 0;                        /* init errno */
    /* change singular bit in all-ones Word and check value equals MAX-2^i*/
    printf("\n********Testing SetOff********\n"); 
    while (i < SYS_WORD_SIZE)
    {
        res_bit_arr = SetOff(SET_ALL, i); /* perform call */
        /* change singular bit in all-ones Word and check value equals MAX-2^i*/
        printf("%lu changed to %lu\n", SET_ALL, res_bit_arr);
        if(res_bit_arr != SET_ALL - pow(2,i))     /* validate test cases pass */
        { 
            errno = TEST_FAIL;
        }
        ++i;
    }
    return errno;
}

static int Test_SetBit()
{
    size_t i = 0;                     /* runner for test array */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    errno = 0;                        /* init errno */
    printf("\n********Testing SetBit********\n"); 
    while (i < SYS_WORD_SIZE)
    {
        res_bit_arr = SetBit(UNSET_ALL, i, 1); /* perform call */
        /* change singular bit in all-zeroes Word and check value equals 2^i*/
        printf("%lu changed to %lu\n", (size_t)(0), res_bit_arr);
        if(res_bit_arr != pow(2,i))   /* validate all test cases pass at wil */
        { 
            errno = TEST_FAIL;
        }
        ++i;
    }
    if(errno)
    {
        return errno;
    }
    i = 0;   /* reset runner */
    while (i < SYS_WORD_SIZE)
    {
        res_bit_arr = SetBit(SET_ALL, i, 0); /* perform call */
        
        printf("%lu changed to %lu\n", SET_ALL, res_bit_arr);
        if(res_bit_arr != SET_ALL - pow(2,i))
        { 
            errno = TEST_FAIL;
        }
        ++i;
    }
    return errno;
}

static int Test_GetVal()
{
    size_t i = 0;                     /* runner */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    int test_val = 0;                 /* hold callee result */
    errno = 0;                        /* init errno */
    /* change singular bit in all-ones Word and check value equals MAX-2^i*/
    printf("\n********Testing GetVal********\n"); 

    while (i < SYS_WORD_SIZE)
    {
        res_bit_arr = SetOn(UNSET_ALL, i*SYS_BYTE_SIZE); /* perform call */
        test_val = GetVal(res_bit_arr, i*SYS_BYTE_SIZE); /* save potential 1 */
        printf("val ind idx %ld of %lu is %d\n",
                i*SYS_BYTE_SIZE, res_bit_arr, test_val);
        if(test_val != 1)     /* validate test cases pass */
        { 
            errno = TEST_FAIL;
            return errno;
        }
        res_bit_arr = SetOff(SET_ALL, i*SYS_BYTE_SIZE); /* perform call */
        test_val = GetVal(res_bit_arr, i*SYS_BYTE_SIZE); /* save potential 0 */
        printf("val ind idx %ld of %lu is %d\n",
                i*SYS_BYTE_SIZE, res_bit_arr, test_val);
        if(test_val != 0)     /* validate test cases pass */
        { 
            errno = TEST_FAIL;
            return errno;
        }
        ++i;
    }
    return errno;
}


static int Test_Flip()
{
    size_t i = 0;                     /* runner */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    bit_array_ty mask_word = 0;     /* hold callee result */
    int test_val = 1;                 /* hold callee flipped odd-idx result */
    errno = 0;                        /* init errno */
    /* change singular bit in all-ones Word and check value equals MAX-2^i*/
    printf("\n********Testing Flip********\n"); 

    while (i < SYS_WORD_SIZE)
    {
        /* build some word  00001000 mask with 1 in place i*8 */
        mask_word = SetOn(UNSET_ALL, i*SYS_BYTE_SIZE);
        /* flip array to get word 11110111 mask with 0 in place i*8 */
        res_bit_arr = Flip(mask_word);
        test_val = GetVal(res_bit_arr, i*SYS_BYTE_SIZE); /* save potential 0 */
        printf("val ind idx %ld of %lu is %d\n",
                i*SYS_BYTE_SIZE, res_bit_arr, test_val);
        if(res_bit_arr != ~mask_word)     /* validate test cases pass */
        { 
            errno = TEST_FAIL;
            return errno;
        }
        /* build some word  11110111 mask with 0 in place i*8 */
        mask_word = SetOff(SET_ALL, i*SYS_BYTE_SIZE);
        /* flip array to get word 00001000 mask with 1 in place i*8 */
        res_bit_arr = Flip(mask_word);
        test_val = GetVal(res_bit_arr, i*SYS_BYTE_SIZE); /* save potential 1 */
        printf("val ind idx %ld of %lu is %d\n",
                i*SYS_BYTE_SIZE, res_bit_arr, test_val);
        if(res_bit_arr != ~mask_word)     /* validate test cases pass */
        { 
            errno = TEST_FAIL;
            return errno;
        }
        ++i;
    }
    return errno;
}

static int Test_Mirror()
{
    size_t i = 0;                     /* runner for test array */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    errno = 0;                        /* init errno */
    
    printf("\n********Testing Mirror********\n"); 
    while (i < TEST_ARR_LEN)
    {
        res_bit_arr = Mirror(g_generic_test_arr[i]); /* perform call */
        
        printf("%lu changed to %lu\n", g_generic_test_arr[i], res_bit_arr);
        if(res_bit_arr != g_mirror_test_arr[i])/* validate against real mirror*/
        {
            errno = TEST_FAIL;
        }
        ++i;
    }
    return errno;
}

static int Test_RotateLeft()
{    
    size_t mask1 = 0x000000000000000f;
    size_t i = 0;                     /* runner */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    errno = 0;                        /* init errno */

    printf("\n********Testing RotateLeft********\n"); 
    while (i < SYS_WORD_SIZE)
    {
        res_bit_arr = RotateLeft(mask1, 1); /* perform call */
        /* shift singular bit in mask */
        printf("%ld changed to %ld\n", mask1, res_bit_arr);
        if(res_bit_arr != mask1*(2))     /* validate multiples of 2 */
        { 
            errno = TEST_FAIL;
            return errno;
        }
        ++i;
    }
    return errno;
}

static int Test_RotateRight()
{    
    size_t mask1 = 0xf000000000000000;
    size_t i = 0;                     /* runner */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    errno = 0;                        /* init errno */

    printf("\n********Testing RotateRight********\n"); 
    while (i < SYS_WORD_SIZE)
    {
        res_bit_arr = RotateRight(mask1, 1); /* perform call */
        /* shift singular bit in mask */
        printf("%ld changed to %ld\n", mask1, res_bit_arr);
        if(res_bit_arr != mask1/(2))     /* validate multiples of 2 */
        { 
            errno = TEST_FAIL;
            return errno;
        }
        ++i;
    }
    return errno;
}

static int Test_CountOn()
{    
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    size_t count = 0;                 /* test counter */
    errno = 0;                        /* init errno */

    printf("\n********Testing CountOn********\n"); 
    res_bit_arr = SetAll(res_bit_arr); /* perform set all */
    count = CountOn(res_bit_arr);
    printf("num of ones in %lu is %ld\n", res_bit_arr, count);
    if(count != NUM_OF_BITS_IN_WORD)     /* validate count is 64 */
    { 
        errno = TEST_FAIL;
    }
    res_bit_arr = ResetAll(res_bit_arr); /* perform unset all */
    count = CountOn(res_bit_arr);
    printf("num of ones in %lu is %ld\n", res_bit_arr, count);
    if(count != 0)                 /* validate count is 0 */
    { 
        errno = TEST_FAIL;
    }
    return errno;
}

static int Test_CountOff()
{    
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    size_t count = 0;                 /* test counter */
    errno = 0;                        /* init errno */

    printf("\n********Testing CountOff********\n"); 
    res_bit_arr = SetAll(res_bit_arr); /* perform set all */
    count = CountOff(res_bit_arr);
    printf("num of ones in %lu is %ld\n", res_bit_arr, count);
    if(count != 0)     /* validate count is 0 */
    { 
        errno = TEST_FAIL;
    }
    res_bit_arr = ResetAll(res_bit_arr); /* perform unset all */
    count = CountOff(res_bit_arr);
    printf("num of ones in %lu is %ld\n", res_bit_arr, count);
    if(count != NUM_OF_BITS_IN_WORD)                /* validate count is 64 */
    { 
        errno = TEST_FAIL;
    }
    return errno;
}

static int Test_ToString()
{    
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    size_t count = 0;                 /* test counter */
    char* dest = NULL;                /* string res */
    char* all_set =   "11111111111111111111111111111111"
                      "11111111111111111111111111111111";    /* string ones */
    char* all_unset = "00000000000000000000000000000000"
                      "00000000000000000000000000000000";    /* string zeroes */  
    
    dest = (char*)malloc(sizeof(char)*(NUM_OF_BITS_IN_WORD+1));
    errno = 0;                        /* init errno */

    printf("\n********Testing ToString********\n"); 
    res_bit_arr = SetAll(res_bit_arr); /* perform set all */
    ToString(res_bit_arr, dest);
    printf("num %lu \nis a string: \n%s\n", res_bit_arr, dest);
    printf("all set str is: \n%s\n", all_set);
    if(strcmp(dest, all_set) != 0)     /* validate count is 0 */
    { 
        errno = TEST_FAIL;
    }
    res_bit_arr = ResetAll(res_bit_arr); /* perform set all */
    ToString(res_bit_arr, dest);
    printf("num %lu \nis a string: \n%s\n", res_bit_arr, dest);
    printf("all unset str is: \n%s\n", all_unset);
    if(strcmp(dest, all_unset) != 0)                /* validate count is 64 */
    { 
        errno = TEST_FAIL;
    }
    free(dest);
    dest = NULL;
    return errno;
}

static int Test_CountOnByLUT()
{    
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    size_t count = 0;                 /* test counter */
    errno = 0;                        /* init errno */

    printf("\n********Testing CountOnByLUT********\n"); 
    res_bit_arr = SetAll(res_bit_arr); /* perform set all */
    count = CountOnByLUT(res_bit_arr);
    printf("num of ones in %lu is %ld\n", res_bit_arr, count);
    if(count != NUM_OF_BITS_IN_WORD)     /* validate count is 64 */
    { 
        errno = TEST_FAIL;
    }
    res_bit_arr = ResetAll(res_bit_arr); /* perform unset all */
    count = CountOnByLUT(res_bit_arr);
    printf("num of ones in %lu is %ld\n", res_bit_arr, count);
    if(count != 0)                 /* validate count is 0 */
    { 
        errno = TEST_FAIL;
    }
    return errno;
}

static int Test_MirrorByLUT()
{    
    size_t i = 0;                     /* runner for test array */
    bit_array_ty res_bit_arr = 0;     /* hold callee result */
    errno = 0;                        /* init errno */
    
    printf("\n********Testing MirrorByLUT********\n"); 
    while (i < TEST_ARR_LEN)
    {
        res_bit_arr = MirrorByLUT(g_generic_test_arr[i]); /* perform call */
        
        printf("%lu changed to %lu\n", g_generic_test_arr[i], res_bit_arr);
        if(res_bit_arr != g_mirror_test_arr[i])/* validate against real mirror*/
        {
            errno = TEST_FAIL;
            return errno;
        }
        ++i;
    }
    return errno;
}
