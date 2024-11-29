/***************************** UI_ws9_bitwise.c  ****************************/
/*
  Name: Idan Nave
  Project: Work Sheet #9 - BitWise
  Reviewer: Sahar Attia **APPROVED**
  Date: 23/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* For input validation */
#include <math.h> 		/* For arithmetics */
#include <errno.h> 		/* For Err Handling */
#include <stddef.h>  		/* For size_t type*/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation */
#include <string.h>             /* For string manipulation */

#include "Test_ws9_bitwise.h"   /* API Testing*/

#define MENU_CH_NUM 10        /* num of tests/inputs */
#define ESC_PRESSED 27        /* ESC ASCII */
#define NO_ERROR 0            /* Return idx */

/****************************** UI Implementations ****************************/


/* Function that prints a short manual from file */
void GreetUser()
{  
    printf("Hello, Welcome to ws9_bitwise Tester program!\n");
    printf("Enter Test index to initate test\n");
    /* print contents from header file, listing function indexes*/
    FilePrint("/home/idan/Documents/Dev/Git_WD/c/ws9_bitwise/"
    "test/man");
    HandleMenuInput();
}

/* Function that handles requests*/
size_t HandleMenuInput()
{    
      /* for each number, execute an operation*/
      switch(GetMenuSelection(MENU_CH_NUM))
      {
        case 1:
        printf("Test_MultXByPow2 has %d fails.\n", Test_MultXByPow2());
        break;
        case 2:
        printf("Test_CountOnes has %d fails.\n", Test_CountOnes());
        break;
        case 3:
        printf("Test_IsPowerOf2 has %d fails.\n", Test_IsPowerOf2());
        break;
        case 4:
        printf("Test_Add1ToIntBitWise has %d fails.\n", Test_Add1ToIntBitWise());
        case 5:
        break;
        printf("Test_PrintOnly3SetBits has %d fails.\n",
        Test_PrintOnly3SetBits());
        case 6:   
        break;
        printf("Test_ByteMirror has %d fails.\n", Test_ByteMirror());  
        case 7:
        break;
        printf("Test_CheckBoth2And6 has %d fails.\n", Test_CheckBoth2And6());  
        case 8:
        break;
        printf("Test_CheckOneOf2And6 has %d fails.\n", Test_CheckOneOf2And6());  
        case 9:
        break;
        printf("Test_Swap3rdAnd5thBits has %d fails.\n",
        Test_Swap3rdAnd5thBits());  
        case 10:
        break;
        printf("Test_ClosestDivisibleBy16Bitwise has %d fails.\n",
        Test_ClosestDivisibleBy16Bitwise());  
        case 11:
        break;
        Test_SwapWithoutThirdVariable();  
        case 12:
        break;
        printf("Test_CountSetBits has %d fails.\n", Test_CountSetBits());  
        case 13:
        break;
        TestPrintFloatBits();
        break;
        default:
      }
      return NO_ERROR;      
}

/* Function that receives user-input as option index accepts / ESC to exit
returns the input after validation, or 0 for exit*/
size_t GetMenuSelection(size_t range)
{    
    printf("Select option index\n");
    size_t i = 0;
    /* as long as Esc not pressed */
    while (i != ESC_PRESSED)    
    {
        /* read char */
        scanf("%ld",&i);
        /* validate input */
        if( i < range && i > 0)
        {
            printf("Test %ld Selected:\n", i);
            return i;
        }
        else
        {
        errno = 56; /* handle bad input */
        fprintf(stderr,"Invalid Input! #%d\n", errno);
        }
    } 
    /* end on escape */
    printf("User Exit\n");
    return NO_ERROR;
}


/* Function that prints current file contents to CLN*/
int FilePrint(const char *filename)
{        
    /* Open file*/
    FILE *fp = fopen(filename, "r");

    /* print contents from file */
    unsigned char c = ' ';
    while( fscanf(fp, "%c", &c) == 1 )
    {
        putchar(c);
    }
    
    /* close file & reset ptr */
    fclose(fp);
    fp = NULL;
  
    printf("\n");    /* end print at input descriptor*/
    return NO_ERROR;
}

