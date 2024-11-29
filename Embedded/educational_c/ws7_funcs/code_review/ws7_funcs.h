/********************************** ws7_stack.c  ******************************/
/*
  Name: HRD 32
  Project: WS7_Stack Frames & Functions
  Reviewer: Aya
  Date: 13/07/23
  Version: 1.0 - 16/07/23 - publish
           1.1 - 25/07/23 - minor syntax & conventions changes
           1.2 - 26/07/23 - fixed TODOs (code review)
*/
  
/******************************** LIBRARIES  **********************************/

#ifndef __WS7_FUNCS_H__
#define __WS7_FUNCS_H__

#include <stddef.h>  /*Using size_t in header file*/

/********************************** TypeDefs  *********************************/

/* Structure for basic types*/
typedef struct
{
    char* str;
    int snum;
    size_t num;
} basic_ty;

/*A typedef to create a named function pointer type called printer:
the function accepts int, returns int*/	
typedef int (*ptr_to_func_ty)(int);						

/******************************* DECLERATIONS *********************************/

/* Function that runs menu */
int RunPressApp();

/* Function that receives A / T / ESC input from the keyboard USING IF*/
int KeyboardInputByIf();

/* Function that receives A / T / ESC input from the keyboard USING SWITCH*/
int KeyboardInputBySwitch();

/* Function that receives A / T / ESC input from the keyboard USING LUT*/
int KeyboardInputByLUT();

/* Function to prints N */
void print_n(int num);
/* Function to prints up to N */
void print_to_n(int num);

/* Function to print using function pointers */
void print_using_func_pointers();

/* Function to do nothing */
int DummyFunction(int ch);

/* Function to print pressed ASCII */
int PrintAsciiOrExit(int ch);

#endif /*(__WS7_FUNCS_H__)*/


