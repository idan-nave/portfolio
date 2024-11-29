/******************************* Test_ws10_cbuff.c ***************************/
/*
  Name: Idan Nave
  Project: Work Sheet 10 - Data Structures - Circular Buffer
  Reviewer: Dima
  Date: 20/08/23
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <stdio.h>              /* FILEs, stderr, stdin, stdout */
#include <stdlib.h>             /* malloc(), free() */
#include <string.h>             /* memcpy, string manipulation */
#include <errno.h>              /* errno global */
#include <stddef.h>             /* size_t, NULL */

#include "c_buffer.h"       

/******************************* Definitions  ********************************/

/* Size Definition */
#define CBUFF_CAPACITY 30  

/*****************************************************************************/
/**************************** App's Data-structures **************************/
/*****************************************************************************/

  /******************************** TypeDefs  *******************************/

struct c_buff
{
    size_t capacity;
    size_t read_idx;
    size_t size;
    char *arr;          /*char arr[1];*/
};

/*****************************************************************************/
/**************** Forward Declarations of Static Functions *******************/
/*****************************************************************************/
 
int ExecuteTestSequence();

  /****************************** Test Functions ****************************/

/* Function to validate buffer-creation*/
static int Test_CbuffCreate(size_t capacity);
/* Function to validate buffer-deletion*/
static int Test_CbuffDestroy(c_buff_ty *test_buffer);
/* Function to pop a specified anpont of elements in a row*/
static int Test_CbuffRead
(c_buff_ty *test_buffer, char* dest, size_t bytes_to_r, size_t bytes_expected);
    /* Function to pushs a specified anpont of elements in a row*/
static int Test_CbuffWrite
(c_buff_ty *test_buffer, char* src, size_t bytes_to_w, size_t bytes_expected);
    /* Function to validate buffer size equals cmp_data*/
static int Test_CbuffFreeSpace(const c_buff_ty *test_buffer, size_t cmp_size);
/* Function to validate buffer size equals cmp_data*/
static int Test_CbuffCapacity(const c_buff_ty *test_buffer, size_t cmp_size);
/* Function to validate buffer-status fits cmp_st*/
static int Test_CbuffIsEmpty(const c_buff_ty *test_buffer, status_ty cmp_st);

/************************************* Main **********************************/

int main()
{   
   return ExecuteTestSequence();
}

/*****************************************************************************/
/*************** Tests Implementation - Functions Definitions ****************/
/*****************************************************************************/

  /**************** App Manager Function (called from Main) *****************/
 
int ExecuteTestSequence()
{ 
    c_buff_ty *test_buffer = NULL;

    /*prepare test-helper arrays.*/
    char *src =  NULL;
    char *dest = NULL;
    src = (char*)malloc( sizeof(char)*CBUFF_CAPACITY );
    dest = (char*)malloc( sizeof(char)*CBUFF_CAPACITY );
    strcpy(src,  "AAAAAAAAA|BBBBBBBBB|CCCCCCCCC");
    strcpy(dest, "XXXXXXXXX|XXXXXXXXX|XXXXXXXXX");

    /*You should not use a pointer that has been released already.*/
    errno = SUCCESS;   

    printf("TESTING CBUFF CREATION:\n"); 
    /* test buffer-creation function*/
    errno = Test_CbuffCreate(CBUFF_CAPACITY);
    /* now, it is possible to create & init a new buffer */
    test_buffer = CbuffCreate(CBUFF_CAPACITY);
        
    Test_CbuffFreeSpace(test_buffer, CBUFF_CAPACITY);
    Test_CbuffCapacity(test_buffer, CBUFF_CAPACITY);
    Test_CbuffIsEmpty(test_buffer, 0);

    printf("WRITE 5 BYTES:\n"); 
    errno = Test_CbuffWrite(test_buffer, src, 5, 5);

    printf("READ 5 BYTES TO TERMINAL:\n\n"); 
    errno = Test_CbuffRead(test_buffer, dest, 5, 5);

    printf("WRITE 5 BYTES AGAIN:\n\n"); 
    errno = Test_CbuffWrite(test_buffer, src, 5, 5);

    printf("WRITE 24 BYTES:\nn"); 
    errno = Test_CbuffWrite(test_buffer, src, 24, 24);
    
    printf("WRITE REMAINING 1 LAST BYTE UP TO CAPACITY:\n\n"); 
    errno = Test_CbuffWrite(test_buffer, src, 1, 1);

    printf("READ 10 BYTES FROM BUFFER TO TERMINAL:\n\n"); 
    errno = Test_CbuffRead(test_buffer, dest, 10, 10);

    printf("READ REMAINING UNREAD:\n\n"); 
    errno = Test_CbuffRead(test_buffer, dest, 20, 20);
   
    Test_CbuffFreeSpace(test_buffer, CBUFF_CAPACITY);
    Test_CbuffIsEmpty(test_buffer, 0);

    printf("WRITE 40 BYTES AGAIN:\n\n"); 
    errno = Test_CbuffWrite(test_buffer, src, 40, 30);
    /* test destroying the buffer while it is empty */
        
    Test_CbuffFreeSpace(test_buffer, 0);
    Test_CbuffIsEmpty(test_buffer, 1);

    printf("DESTROYING CBUFF:\n\n"); 
    errno = Test_CbuffDestroy(test_buffer);
    
    /* free test arrays */
    free(src); src =  NULL;
    free(dest); src =  NULL;
    return errno;
}

  /****************************** Test Functions ****************************/

/* Function to validate buffer-creation*/
static int Test_CbuffCreate(size_t capacity)
{
    c_buff_ty *new_buffer = NULL;

    errno = SUCCESS;
    new_buffer = CbuffCreate(capacity);

    if (CbuffCapacity(new_buffer) != capacity)
    {
        errno = EFAULT;
        perror("capacity init failed");
        return errno;
    }
/*    if (new_buffer->arr == NULL)
    {
        errno = EFAULT;
        perror("buffer_arr init failed");
        return errno;
    }*/
    printf("#####Cbuff Creation Success#####\n");

    CbuffDestroy(new_buffer);
    return errno;
}

/* Function to validate buffer-deletion*/
static int Test_CbuffDestroy(c_buff_ty *test_buffer)
{
    printf("#####Test_CbuffDestroy#####\n");
    errno = SUCCESS;
    CbuffDestroy(test_buffer);
    
/*    if (test_buffer != NULL)
    {
        errno = EFAULT;
        perror("Cbuff Destroy failed");
        return errno;
    }*/
    printf("#####Cbuff Destroy#####\n");
    return errno;
}

/* Function to pop a specified anpont of elements in a row*/
static int Test_CbuffRead
(c_buff_ty *test_buffer, char* dest, size_t bytes_to_r, size_t bytes_expected)
{
    size_t res_byte_size = 0;

    printf("#Before Read Operation:#\n");
    printf("\tFree Space is: %ld\n", CbuffFreeSpace(test_buffer));
    printf("\tDest is: %s\n", dest);

    res_byte_size = CbuffRead(test_buffer, dest, bytes_to_r);

    printf("#After Read Operation:#\n");
    printf("\tFree Space is: %ld\n", CbuffFreeSpace(test_buffer));
    printf("\tDest is: %s\n", dest);

    printf("\tDest in 30: %c\n", dest[29]);

    if(bytes_expected != bytes_to_r)
    {
        printf("Read from buffer failed, %ld/%ld were completed\n",
        res_byte_size, bytes_to_r);
        return  res_byte_size;
    }

    return errno;
}

/* Function to pushs a specified anpont of elements in a row*/
static int Test_CbuffWrite
(c_buff_ty *test_buffer, char* src, size_t bytes_to_w, size_t bytes_expected)
{
    size_t res_byte_size = 0;

    printf("#Before Write Operation:#\n");
    printf("\tW_idx is: %ld\n", CbuffSize(test_buffer));
    printf("\tFree Space is: %ld\n", CbuffFreeSpace(test_buffer));
    printf("\tSrc is: %s\n", src);

    res_byte_size = CbuffWrite(test_buffer, src, bytes_to_w);

    printf("#After Write Operation:#\n");
    printf("\tW_idx is: %ld\n", CbuffSize(test_buffer));
    printf("\tFree Space is: %ld\n", CbuffFreeSpace(test_buffer));

    if(bytes_expected != res_byte_size)
    {
        printf("Write to buffer failed, %ld/%ld were completed\n",
        res_byte_size, bytes_to_w);
        return  res_byte_size;
    }

    return errno;
}

/* Function to validate buffer size equals cmp_data*/
static int Test_CbuffCapacity(const c_buff_ty *test_buffer, size_t cmp_size)
{
    size_t buffer_size = CbuffCapacity(test_buffer);

    printf("#####Test_CbuffCapacity#####\n");
    errno = SUCCESS;

    printf("Cbuff Capacity is: %ld, expected %ld:\n", buffer_size , cmp_size); 
    
    if (buffer_size != cmp_size)
    {
        errno = EFAULT;
        perror("Cbuff Size Fail");
        return errno;
    }
    return SUCCESS;
}

/* Function to validate buffer-status fits cmp_st*/
static int Test_CbuffIsEmpty(const c_buff_ty *test_buffer, status_ty cmp_st)
{
    status_ty buffer_st = CbuffIsEmpty(test_buffer);

    printf("#####Test_CbuffIsEmpty#####\n");
    errno = SUCCESS;

    printf("Cbuff Status is: %d, expected %d:\n", buffer_st , cmp_st); 
    if (buffer_st != cmp_st)
    {
        errno = EFAULT;
        perror("Cbuff Status Fail");
        return errno;
    }
    return SUCCESS;
}

static int Test_CbuffFreeSpace(const c_buff_ty *test_buffer, size_t cmp_size)
{
    size_t buff_size = CbuffFreeSpace(test_buffer);

    printf("#####Test_CbuffFreeSpace#####\n");
    errno = SUCCESS;

    printf("Cbuff Free Space is: %ld, expected %ld:\n", 
                                                buff_size , cmp_size); 
    if (buff_size != cmp_size)
    {
        errno = EFAULT;
        perror("Cbuff Status Fail");
        return errno;
    }
    return SUCCESS;
}