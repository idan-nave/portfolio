/***************************** env.c  **********************************/
/*Name: HRD 32
  Project: WS6 - Array Pointers
  Reviewer: Aya ?
  Date: 13.07.23
  Version: 1.0*/
  
/******************************** LIBRARIES  **********************************/

#include <stdlib.h> 		/* For memory allocation and deallocation */
#include <stdio.h>  		/* For standard input/output */
#include <ctype.h>              /* For tolower() */
#include <string.h>    	        /* For strlen() */

#include "ArrPtrs.h"	        /* APIs Header */

#define MAX_STR 1000            /* MAX Env String size */

/******************************* Definitions *********************************/
    
int main(int argc, char *argv[], char *envp[])
{
    size_t i =0, j=0;
     char **buf;
     while(NULL != envp[i])
     {
        ++i;
     }
     
     printf("%zu\n", i);
     
      buf = (char**)malloc((sizeof(char*)*i)+sizeof(char*));
      buf[i] = NULL  ;
      i=0;

     while(NULL != envp[i])
     {
        while(envp[i][j] != '\0')
        {
              ++j;
              
        }
        
        buf[i] = (char*)malloc(sizeof(char)*(j+1));
        strcpy(buf[i], ToLowerStr(envp[i]));
        j=0;
        ++i;
     }

     i=0;
     while(NULL != *(buf+i))
     {
       printf("%s\n", buf[i]);
       ++i;
     }
     
     i=0;
     
     while(NULL != buf[i])
     {
        
        free(buf[i]);
        buf[i] = NULL;
         ++i;
     }
    free(buf[i]);
    buf[i]=NULL;  
    free(buf);
    buf=NULL;
     
     
     
     return 0;
}


char* ToLowerStr(char*str)
{
    size_t i = 0;
    char *low_s = str;
    while('\0' != str[i])
    { 
        low_s[i] = tolower(*(str+i));
        ++i;
    }
    return low_s;
}
