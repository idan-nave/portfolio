/********************************** src.c  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet 8 - FIles
  Reviewer: Or (Yet to be Approved)
  Date: 00/00/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* For input validation */
#include <stddef.h>  		/* For size_t type*/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation */
#include <string.h>             /* For string manipulation */
#include <unistd.h>             /*access() to check existance of a file*/
#include <ctype.h>              /* isdigit()*/
#include <errno.h>              /* Error handling */

#include "ws8_files.h" 		/* For team's API */

/****************************** UI Implementations ****************************/

/* Function that greets user for handling files, 2 operation modes: */
/* Mode 1 - use key presses, Mode 2 - use CLN commands with flags */
void GreetUser(int mode)
{  
    printf("Hello, Welcome to the File Logger program!"
    "\n Use the following options:\n");
    switch(mode)
    {
      case 1: /*1) use menu */
      printf("1.Assign Name \n2.Open file \n3.Close file"
      "\n4.Append a String to file\n");
      break;
      
      case 2: /*2) use flags */
      /*FilePrint( FileBuildName(current_file_name, FILES_REL_PATH) );*/
      break;   
    }
}     

/* Function that receives user-input as option index accepts / ESC to exit */
size_t GetMenuSelection(size_t range)
{    
    printf("Select option index\n");
    size_t i = 0;
    /* as long as Esc not pressed */
    while (i != 27)    
    {
        /* read char */
        scanf("%ld",&i);
        /* validate inputr */
        if( i < range && i > 0)
        {
            printf("Option %ld Selected:\n", i);
            return i;
        }
        else
        {
        errno = 56; /* handle bad input */
        fprintf(stderr,"Error #%d", errno);
        }
    } 
    /* end on escape */
    printf("Escape was pressed\n");
    return 0;
}

/* Function that handles requests*/
size_t HandleMenuInput()
{    
      /* for each number, execute an operation*/
      switch(GetMenuSelection(MENU_CH_NUM))
      {
        case 1: /*1) creates a new file */
        printf("Enter a name for the file to be created:\n"); /* instruct */
        GetInputString(input_buff,1,1); /* echo & remove \n */
        FileCreate((const char*)input_buff);  /* call helper function*/
        break;
        
        case 2: /*2) open file */
        printf("Enter a name for the file to be opened:\n"); /* instruct */
        GetInputString(input_buff,1,1);  /* echo & remove \n */
        /* updates current file global with the opened file */
        errno = FileOpenByName(current_file, input_buff, "w");
        break;
        
        case 3: /*3) append string to file */
        errno = FileAppend(current_file, input_buff,"file.txt");
        if(errno) return errno;
        
        break;
        
        case 4: /*4) close file */
        errno = FileClose(current_file, NULL, NULL);
        if(errno) return errno;
        
        break;
        
        default: printf("User Exit.\n");
      }
}
