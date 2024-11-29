/********************************** Test_ws13_WBO.c  **************************/
/*
  Name: Idan Nave
  Project: Work Sheet #13 - Word Boundary Optimization
  Reviewer: Agbaria
  Date: 03/08/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/

#include <assert.h> 		/* For input validation */
#include <stddef.h>  		/* For size_t type*/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation */
#include <string.h>             /* For string manipulation */

#include "ws13_WBO.h" 	

/******************************** Definitions *********************************/

extern err_code_ty err;

/******************************************************************************/
/**************************** App's Data-structures ***************************/
/******************************************************************************/

typedef struct tst_pad     /* padded-struct for testing */
{
  int i_num;
  double d_num;
}with_pad_ty;

#pragma pack(1)
typedef struct tst_no_pad  /* regular struct for testing */
{
  int i_num;
  double d_num;
}no_pad_ty;

/* structs decletarions for original and implemented mem_functions*/
with_pad_ty tst_struc_mem_wp = {0};
with_pad_ty tst_struc_MEM_wp = {0};
no_pad_ty tst_struc_mem_np = {0};
no_pad_ty tst_struc_MEM_np = {0};

/* test-byte-arrays for testing */
char tst_arr_origin[] = "0123456|89ABCDE|F000000|";
char tst_arr_mem[]    = "aaaaaaa|bbbbbbb|ccccccc|";
char tst_arr_MEM[]    = "aaaaaaa|bbbbbbb|ccccccc|";

/****************************** Test Functions ********************************/

static int TestMemSet();
static int TestMemCpy();
static int TestMemMove();

/****************************** Helper Functions ******************************/

/* Initializer used before each test*/
static void InitTestStructures();
/* App Manager Function (called from Main) */
int WBO_App();
/* Structs Comperators*/
static int cmpStructsWithPadding(with_pad_ty* struct1, with_pad_ty* struct2);
static int cmpStructsWithoutPadding(no_pad_ty* struct1, no_pad_ty* struct2);

/************************************** Main **********************************/

int main()
{ 
    WBO_App();
    return NO_ERROR;
}

  /**************** App Manager Function (called from Main) *****************/

int WBO_App()
{
    /* Test newly implemented MEMset, MEMcpy, MEMMove */
    err = TestMemSet();
    if(err)
    {
        printf("\n********Testing MemSet FAILED********\n");
        return err;
    }
    err = TestMemCpy();
    if(err)
    {
        printf("\n********Testing MemCpy FAILED********\n");
        return err;
    }
    err = TestMemMove();
    if(err)
    {
        printf("\n********Testing MemMove FAILED********\n");
        return err;
    }
    return NO_ERROR;
}


static void InitTestStructures()
{
    /*initialize byte arrays */
    strcpy(tst_arr_mem, "0123456|89ABCDE|F000000|");
    strcpy(tst_arr_MEM, "0123456|89ABCDE|F000000|");
    
    /*initialize the structs*/
    tst_struc_mem_wp.i_num = 10;
    tst_struc_mem_wp.d_num = 10.0;
    tst_struc_MEM_wp.i_num = 10;
    tst_struc_MEM_wp.d_num = 10.0;
    tst_struc_mem_np.i_num = 10;
    tst_struc_mem_np.d_num = 10.0;
    tst_struc_MEM_np.i_num = 10;
    tst_struc_MEM_np.d_num = 10.0;
}

  /******************************** Test Functions***************************/

static int TestMemSet()
{
    printf("\n********Testing MemSet********\n"); /*#########################*/
    InitTestStructures();
    
    printf("***Bytes testing***\n");
    memset(tst_arr_mem, 'A', 19);
    MemSet(tst_arr_MEM, 'A', 19);
    printf("%s [origin sector]\n", tst_arr_origin);
    printf("%s\n", tst_arr_mem);
    printf("%s\n", tst_arr_MEM);
    
    if(strcmp(tst_arr_mem, tst_arr_MEM))
    {
        printf("aligned strings not equal\n");
        return MEMORY_OPERATION_FAIL;
    }
    
    printf("\n***With-Padding-Structs testing***\n"); /*##################*/
    InitTestStructures();
        
    memset(&tst_struc_mem_wp, 'A', 9);
    printf("memset struct with padding: %d, %.30f\n",
    tst_struc_mem_wp.i_num, tst_struc_mem_wp.d_num);
    MemSet(&tst_struc_MEM_wp, 'A', 9);
    printf("MemSet struct with padding: %d, %.30f\n",
    tst_struc_MEM_wp.i_num, tst_struc_MEM_wp.d_num);
    
    if(cmpStructsWithPadding(&tst_struc_mem_wp, &tst_struc_MEM_wp))
    {
      printf("structs with padding not equal\n");
      return  MEMORY_OPERATION_FAIL;
    }

    printf("\n***No-Padding-Structs testing***\n"); /*##################*/
    InitTestStructures();
        
    memset(&tst_struc_mem_np, 'A', 5);
    printf("memset struct without padding: %d, %.30f\n",
    tst_struc_mem_np.i_num, tst_struc_mem_np.d_num);
    MemSet(&tst_struc_MEM_np, 'A', 5);
    printf("MemSet struct without padding: %d, %.30f\n",
    tst_struc_MEM_np.i_num, tst_struc_MEM_np.d_num);
    
    if(cmpStructsWithoutPadding(&tst_struc_mem_np, &tst_struc_MEM_np))
    {
      printf("structs without padding not equal\n");
      return  MEMORY_OPERATION_FAIL;
    }
    
    printf("\n\n");
    return NO_ERROR;
}

static int TestMemCpy()
{
    printf("\n********Testing MemCpy********\n"); /*#########################*/
    InitTestStructures();
    
    printf("***Bytes testing***\n");
    memcpy(tst_arr_mem, tst_arr_origin, 19);
    MemCpy(tst_arr_MEM, tst_arr_origin, 19);
    printf("%s [origin sector]\n", tst_arr_origin);
    printf("%s\n", tst_arr_mem);
    printf("%s\n", tst_arr_MEM);\
    
    if(strcmp(tst_arr_mem, tst_arr_MEM))
    {
        printf("aligned strings not equal\n");
        return MEMORY_OPERATION_FAIL;
    }
    
    printf("\n***With-Padding-Structs testing***\n"); /*##################*/
    InitTestStructures();
        
    memcpy(&tst_struc_mem_wp, tst_arr_origin, 9);
    printf("memcpy struct with padding: %d, %.30f\n",
    tst_struc_mem_wp.i_num, tst_struc_mem_wp.d_num);
    MemCpy(&tst_struc_MEM_wp, tst_arr_origin, 9);
    printf("MemCpy struct with padding: %d, %.30f\n",
    tst_struc_MEM_wp.i_num, tst_struc_MEM_wp.d_num);
    
    if(cmpStructsWithPadding(&tst_struc_mem_wp, &tst_struc_MEM_wp))
    {
      printf("structs with padding not equal\n");
      return  MEMORY_OPERATION_FAIL;
    }

    printf("\n***No-Padding-Structs testing***\n"); /*##################*/
    InitTestStructures();
        
    memcpy(&tst_struc_mem_np, tst_arr_origin, 5);
    printf("memcpy struct without padding: %d, %.30f\n",
    tst_struc_mem_np.i_num, tst_struc_mem_np.d_num);
    MemCpy(&tst_struc_MEM_np, tst_arr_origin, 5);
    printf("MemCpy struct without padding: %d, %.30f\n",
    tst_struc_MEM_np.i_num, tst_struc_MEM_np.d_num);
    
    if(cmpStructsWithoutPadding(&tst_struc_mem_np, &tst_struc_MEM_np))
    {
      printf("structs without padding not equal\n");
      return  MEMORY_OPERATION_FAIL;
    }
    
    printf("\n\n");
    return NO_ERROR;
}

static int TestMemMove()
{
    printf("\n********Testing MemMove dest before source********\n"); /*#####*/
    InitTestStructures();
    
    printf("***Bytes testing***\n");
    memmove(tst_arr_mem, tst_arr_mem + 7, 6);
    MemMove(tst_arr_MEM, tst_arr_mem + 7, 6);
    printf("%s [origin sector]\n", tst_arr_origin);
    printf("%s\n", tst_arr_mem);
    printf("%s\n", tst_arr_MEM);\
    
    if(strcmp(tst_arr_mem, tst_arr_MEM))
    {
        printf("aligned strings not equal\n");
        return MEMORY_OPERATION_FAIL;
    }
    
    printf("\n********Testing MemMove source before dest********\n"); /*#####*/
    InitTestStructures();
    
    printf("***Bytes testing***\n");
    memmove(tst_arr_mem + 7, tst_arr_mem, 6);
    MemMove(tst_arr_MEM + 7, tst_arr_mem, 6);
    printf("%s [origin sector]\n", tst_arr_origin);
    printf("%s\n", tst_arr_mem);
    printf("%s\n", tst_arr_MEM);\
    
    if(strcmp(tst_arr_mem, tst_arr_MEM))
    {
        printf("aligned strings not equal\n");
        return MEMORY_OPERATION_FAIL;
    }
        
    printf("\n***With-Padding-Structs testing***\n"); /*##################*/
    InitTestStructures();
        
    memmove(&tst_struc_mem_wp, &tst_struc_mem_wp+1, 2);
    printf("memmove struct with padding: %d, %.30f\n",
    tst_struc_mem_wp.i_num, tst_struc_mem_wp.d_num);
    MemMove(&tst_struc_MEM_wp, &tst_struc_MEM_wp+1, 2);
    printf("MemMove struct with padding: %d, %.30f\n",
    tst_struc_MEM_wp.i_num, tst_struc_MEM_wp.d_num);
    
    if(cmpStructsWithPadding(&tst_struc_mem_wp, &tst_struc_MEM_wp))
    {
      printf("structs with padding not equal\n");
      return  MEMORY_OPERATION_FAIL;
    }

    printf("\n***No-Padding-Structs testing***\n"); /*##################*/
    InitTestStructures();
        
    memmove(&tst_struc_mem_np, &tst_struc_mem_np+2, 2);
    printf("memmove struct without padding: %d, %.30f\n",
    tst_struc_mem_np.i_num, tst_struc_mem_np.d_num);
    MemMove(&tst_struc_MEM_np, &tst_struc_MEM_np+2, 2);
    printf("MemMove struct without padding: %d, %.30f\n",
    tst_struc_MEM_np.i_num, tst_struc_MEM_np.d_num);
    
    if(cmpStructsWithoutPadding(&tst_struc_mem_np, &tst_struc_MEM_np))
    {
      printf("structs without padding not equal\n");
      return  MEMORY_OPERATION_FAIL;
    }
    
    printf("\n\n");
    return NO_ERROR;
}

static int cmpStructsWithPadding(with_pad_ty* struct1, with_pad_ty* struct2)
{
  if(struct1->i_num != struct2->i_num)
  {
    return  MEMORY_OPERATION_FAIL;
  }

  if(struct1->d_num != struct2->d_num)
  {
    return  MEMORY_OPERATION_FAIL;
  }

  return 0;
}

static int cmpStructsWithoutPadding(no_pad_ty* struct1, no_pad_ty* struct2)
{
  if(struct1->i_num != struct2->i_num)
  {
    return  MEMORY_OPERATION_FAIL;
  }

  if(struct1->d_num != struct2->d_num)
  {
    return  MEMORY_OPERATION_FAIL;
  }

  return 0;
}
