/********************************** ws10_build.c  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet 10 - Build Process
  Reviewer: ???
  Date: 24/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/

#include <stddef.h>  		/* For size_t type*/
#include <stdio.h>  		/* For standard input/output */


#include "ws10_build.h" 		/* For team's API*/

#define EOS '\0'		/* For end of strings */

/********************************** TypeDefs  *********************************/
/*
int X = 0;
*/
/*
int x6=0;
*/

/*static int g_s = 3;
will give:
/usr/bin/ld: /tmp/cctm7G19.o: warning: relocation against `g_s' in read-only section `.text'
/usr/bin/ld: /tmp/cctm7G19.o: in function `main':
/home/idan/Documents/Dev/Git_WD/c/ws10_build/test/Test_ws10_build.c:45: undefined reference to `g_s'
/usr/bin/ld: /home/idan/Documents/Dev/Git_WD/c/ws10_build/test/Test_ws10_build.c:47: undefined reference to `g_s'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
*/

int g_s = 3;

void Foo()
{

  printf("%d in foo\n",g_s);
    g_s++;
}


/************************************** Main **********************************/

