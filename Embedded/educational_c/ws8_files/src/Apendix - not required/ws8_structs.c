/*************************** ws8_structs_ex_1.c  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet 8 - FIles
  Reviewer: Ori
  Date: 19/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* For input validation */
#include <stddef.h>  		/* For size_t type*/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation */
#include <string.h>             /* For string manipulation */
#include <unistd.h>             /* For access() to check existance of a file*/

#define ST_NUM 10		/*  number of structs */

/********************************** TypeDefs  *********************************/
typedef struct
{
    int num;
    void (*Print)(int);
} print_me_ty;   

/************************* Structs Implementations ****************************/

/* Function to prints N */
void PrintN(int n)
{
    printf("%d, ", n);
}

/* Function to Allocate & Initialize Struct Array, user must free allocation */
print_me_ty* Allocate_And_InitializeStruct(int len)
{
    print_me_ty *arr = (print_me_ty*)malloc(sizeof(print_me_ty)*len);
    size_t i = 0;
    /* initialize each cell with sorted growing nums */
    while(len > i)
    {
       arr[i].num = i*10; /*arbitrary value*/
       arr[i].Print = &PrintN;
       ++i;
    }
    return arr;
}

/* Function to Print Struct Array */
void PrintStructArr(print_me_ty* p_s, size_t len)
{
    size_t i = 0;
    while(len > i)
    {
       printf(" \nCell #%lu:  ",i);
       /* call function of self-print */
       p_s[i].Print(p_s[i].num);
       ++i;
    }
}

/************************************** Main **********************************/
int main(int argc, char *argv[], char *envp)
{
      /* Allocate struct */
      print_me_ty* struc = Allocate_And_InitializeStruct(ST_NUM); 
      
      PrintStruct(struc, ST_NUM); 
      
      /* Free Allocation */
      free(struc); 
      struc = NULL; 
      
      return 0;
}
