/******************************* ws7.c  ***************************************/
/*
  Name: HRD 32
  Project: WS7_Stack Frames & Functions
  Reviewer: ???
  Date: 16/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* For input validation */
#include <stddef.h>  		/* For size_t type*/
#include <stdio.h>  		/* For standard input/output */
#include <string.h>

/********************************** TypeDefs  *********************************/
/*A typedef to create a named function pointer type called printer:
the function accepts int, returns int*/

/*TODO: typedef ends with _ty*/
/* Structure for basic types*/
typedef unsigned char uchar;

/*A typedef to an array:*/
typedef char (*PtrCharArrayOf3)[3];

/*A typedef to create a named function pointer type called printer:
the function accepts int, no return*/	
typedef void (*printer)(int);

/************************************** Main **********************************/

int main(int argc, char *argv[], char *envp)
{   

    printer x = &print_to_n;

    /* Function that takes a function pointer as a parameter */
    foo_takes_type(x, 10);

    return 0;
}

/*******************************  IMPLEMENTATIONS  ****************************/

/* Function that takes a function pointer as a parameter */
void foo_takes_type (printer p, int y)
{
    p(y);
}

/* Function to print range up to N */
void print_to_n(int n)
{
    int i = 1;
    for (; i <= n; ++i)
        printf("%d\n", i);
}

/* Function to print using function pointers */
void print_using_func_pointers()
{
    basic_ty b_s = {"abc", -1, 1};
    /*typedef char (*PtrCharArrayOf3)[3];*/
    char a[3] = "ab";     /* 'a' is a char[3] */
    PtrCharArrayOf3 ptr;  /* 'ptr' is a ptr to a char[3] */
    ptr = &a;
    uchar x;
    printf("%lu\n", sizeof(x));

    /*This creates a type, named printer for a pointer to a function that
    takes a single int argument and returns nothing, which matches the signatur
    of the functions we have at the API. To use it we create a variable of the 
    created type and assign it a pointer to one of the functions in question:*/
    
    printer p_w = &print_to_n;    /* Function Pointer using the defined type */
    void (*p_wo)(int) = &print_to_n; /* Function Pointer without the type */
    p_w(5);           /* Prints 1 2 3 4 5 on separate lines */
    (*p_wo)(5);       /* So does this */
}

