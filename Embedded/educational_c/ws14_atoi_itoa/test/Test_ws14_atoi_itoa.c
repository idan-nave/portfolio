/***************************** Test_ws14_atoi_itoa.c  *************************/
/*
  Name: Idan Nave
  Project: Work Sheet 14 - atoi/itoa
  Reviewer: Aya
  Date: 07/08/23
  Version: 1.0
*/
/******************************** Libraries  **********************************/

#include <assert.h> 	       	/* assert() */
#include <stdio.h>  		    /* FILEs, stderr, stdin, stdout */
#include <stdlib.h> 		    /* malloc(), free(), atoi, itoa, strtol */
#include <string.h>             /* string manipulation */
#include <errno.h>              /* errno global */
#include <time.h>               /* strftime, localtime, difftime */
#include <ctype.h>              /* isalpha, isdigit, isspace */
#include <stddef.h>             /* size_t, NULL */

#include "ws14_atoi_itoa.h" 		

/******************************** Definitions  ********************************/

/* Array Lengths' Definition */
#define STRINGS_TEST_ARR_LEN 18	     
#define INTS_TEST_ARR_LEN 10     
#define BASES_TEST_ARR_LEN 4        

#define MAX_STR_LEN 16	         

/* Macro to Check System Endianness: */
#define IS_LITTLE_ENDIAN (*(unsigned char *)"x" == 'x')


/****************************************************************************/
/************************** Testing Data-structures *************************/
/****************************************************************************/

  /******************************** GLobals  ********************************/
const char* test_strings[STRINGS_TEST_ARR_LEN] = {  "123",
                                      "-456",
                                      "0",
                                      "98765",
                                      "9999999",
                                      "+4567",
                                      "-1",
                                      "f",
                                      "F",
                                      "//",
                                      "*",               /* Invalid string */
                                      "ffff",
                                      "QGT7",
                                      ".",
                                      "2147483647",      /* INT_MAX        */
                                      "-2147483648",     /* INT_MIN        */
                                      "NOTjunk",   /* Valid string   */  
                                      "1230123457777",   /* Beyond INT_MAX */};

const int test_ints[INTS_TEST_ARR_LEN]  = {   123,
                                           -456,
                                            0,
                                            98765,
                                            15,
                                            -1,
                                            2147483647,  /* INT_MAX        */
                                            -2147483648, /* INT_MIN        */
            /* not checked in itoa */       123,                 
           /* not checked in atoi&itoa */   123012345                                };

const size_t test_bases[BASES_TEST_ARR_LEN]  = {     10,
                                                     8,
                                                     16,
   /* not checked in atoi&itoa */                    0                       }; 
/****************************************************************************/
/************** Forward Declarations of Static Functions ********************/
/****************************************************************************/
 
  /********************************* Test Algo ******************************/

/*EX 1 a-f */
static int CmpStringToInt(const char* int_str ,size_t tst_base);
static int CmpIntToString(int int_num, size_t tst_base);
static int TestStringToInt();
static int TestIntToString();

/*EX 2-4 */
static int TestUniqueLettersInTwoOfThreeArrays();
static int TestIsLittleEndianFunc();
static int TestIsLittleEndianMacro();

int ExecuteApp();

/************************************ Main **********************************/

int main()
{   
    return ExecuteApp();
}

/****************************************************************************/
/************* API Implementation - Functions Definitions *******************/
/****************************************************************************/
 
  /**************** Test Manager Function (called from Main) *****************/

int ExecuteApp()
{
    errno = 0; /* Clear errno before calling StringToInt */
    /* Test newly implemented StringToInt, IntToString */
    /* errno = TestStringToInt(); */
    if(errno)
    {
        printf("\n********Testing StringToInt FAILED********\n");
        return errno;
    }
    errno = TestIntToString();
    if(errno)
    {
        printf("\n********Testing IntToString FAILED********\n");
        return errno;
    }
    /* errno = TestUniqueLettersInTwoOfThreeArrays(); */
    if(errno)
    {
        printf("\n********Testing Unique Letters In"
        "Two Of Three Arrays FAILED********\n");
        return errno;
    }
   /* errno = TestIsLittleEndianFunc();*/
    if(errno)
    {
        printf("\n********Testing IntToString FAILED********\n");
        return errno;
    }
    /* errno = TestIsLittleEndianMacro();*/
    if(errno)
    {
        printf("\n********Testing IntToString FAILED********\n");
        return errno;
    }
    return errno;
}

  /****************************** Test Handlers ****************************/

static int TestStringToInt()
{
    size_t i = 0;    /* Runner for strings test array */
    size_t j = 0;    /* Runner for base test array */

    printf("\n********Testing StringToInt********\n"); 
    while (j < BASES_TEST_ARR_LEN)
    {
        printf("\n********Testing Base %ld********\n", test_bases[j]); 
        while (i < STRINGS_TEST_ARR_LEN)
        {
            printf("\n********Testing String %s********\n", test_strings[i]); 
            errno = CmpStringToInt(test_strings[i], test_bases[j]);
            ++i;
        }
        ++j;
        i = 0;
    } 
    return errno;
}

static int TestIntToString()
{
    size_t i = 0;    /* Runner for ints test array */
    size_t j = 0;    /* Runner for base test array */

    printf("\n********Testing IntToString********\n"); 
    while (j < BASES_TEST_ARR_LEN)
    {
        printf("\n********Testing Base %ld********\n", test_bases[j]); 
        while (i < INTS_TEST_ARR_LEN)
        {
            printf("\n********Testing Int %d********\n", test_ints[i]); 
            errno = CmpIntToString(test_ints[i],test_bases[j]);
            ++i;
        }
        ++j;
        i = 0;
    } 
    return errno;
}

static int TestUniqueLettersInTwoOfThreeArrays()
{
    const char arr1[] = "abcderthrthfg";
    const char arr2[] = "xyzahdgjyyyyfjfbc";
    const char arr3[] = "efgfjfjqqqqqshijg";
    printf("arr1 is: %s\n", arr1);
    printf("arr2 is: %s\n", arr2);
    printf("arr3 is: %s\n", arr3);

    PrintUniqueLettersInTwoOFThreeArrays(arr1, arr2, arr3);

    return 0;
}

static int TestIsLittleEndianFunc()
{
    if (IsLittleEndian())
    {
        printf("The system is little-endian.\n");
    }
    else
    {
        printf("The system is big-endian.\n");
    }

    return 0;
}

static int TestIsLittleEndianMacro()
{
    if (IS_LITTLE_ENDIAN)
    {
        printf("The system is little-endian.\n");
    }
    else
    {
        printf("The system is big-endian.\n");
    }

    return 0;
}

/****************************************************************************/
/*************************** ATOI / ITOA  Definitions ***********************/
/****************************************************************************/

static int CmpStringToInt(const char* int_str ,size_t tst_base)
{
    int api_res = 0;
    int strtol_res = strtol(int_str, NULL, tst_base);
    
    errno = 0; /* Clear errno before calling StringToInt */
    errno = StringToInt(&api_res, int_str, tst_base);

    if (errno != PASS)
    {
        fprintf(stderr, "Error message: %s\n", strerror(errno));
        return errno;
    }

    printf("_____strtol Parsed %s is: %d\n", int_str, strtol_res);
    printf("StringToInt Parsed %s is: %d\n", int_str, api_res);

    if (strtol_res != api_res)
    {
        fprintf(stderr, "failed %s: %d != %d\n", int_str, strtol_res, api_res);
        return FAIL;
    }
    return PASS;
}

static int CmpIntToString(int int_num ,size_t tst_base)
{
    char* api_res = NULL;
    char* itoa_res = NULL;

    api_res = (char*)malloc(sizeof(char) * MAX_INT_DIGS);
    itoa_res = (char*)malloc(sizeof(char) * MAX_INT_DIGS);

    /* atoi function is not defined in ANSI-C, alternative is sprintf:*/
    if(tst_base == 10)
    {
        sprintf(itoa_res,"%d",int_num); /*converts to decimal base.*/
    }
    else if(tst_base == 8)
    {
        sprintf(itoa_res,"%o",int_num); /*converts to octal base.*/
    }
    else if(tst_base == 16)
    {
        sprintf(itoa_res,"%x",int_num); /*converts to hexadecimal base.*/
    }

    errno = 0; /* Clear errno before calling IntToString */
    errno = IntToString(int_num, api_res, tst_base);

    if (errno != PASS)
    {
        fprintf(stderr, "Error message: %s\n", strerror(errno));
        free(api_res);
        free(itoa_res);
        return errno;
    }

    printf("_______itoa Parsed %d is: %s\n", int_num, itoa_res);
    printf("IntToString Parsed %d is: %s\n", int_num, api_res);

    if (strcmp(itoa_res, api_res) != 0) 
   {
        fprintf(stderr, "failed %d: %s != %s\n", int_num, itoa_res, api_res);
        free(api_res);
        free(itoa_res);
        return FAIL;
    }
    free(api_res);
    free(itoa_res);
    return PASS;
}