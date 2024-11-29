/********************************** Test_ws10_build.h ***************************/
/*
  Name: HRD 32
  Project: Work Sheet 10 - Build Process
  Reviewer: ???
  Date: 24/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* For input validation */
#include <stddef.h>  		/* For size_t type*/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation */
#include <string.h>             /* For string manipulation */

#include "ws10_build.h" 		/* For team's API*/
#include "Test_ws10_build.h" 		/* For team's API*/

#define EOS '\0'		/* For end of strings*/

/********************************** TypeDefs  *********************************/

/*
int X = 0;
int Y;
*/

static int x1 = 3;
static int x2 = 0;
static int x3;
int x4 = 10;
int x5 = 0;
int x6;


/************************************** Main **********************************/
int main()
{
    /*
    printf("%d/n ", fun());
    printf("%d/n ", fun());
    */
    extern int g_s;
    printf("%d in main\n ", g_s);
    Foo();
    printf("%d in main\n ", g_s);
    /*g();*/
    
    
    return 0;
}


/******************************* implementations ******************************/
int fun()
{
    static int count = 0;
    count++;
    return count;
}


/*********************************** outputs **********************************/
/* EX #2 - generate 2 object files */
/*
alias ws10_c='gcc -g -c -ansi -I$HOME/Documents/Dev/Git_WD/c/ws10_build/include $HOME/Documents/Dev/Git_WD/c/ws10_build/src/ws10_build.c $HOME/Documents/Dev/Git_WD/c/ws10_build/test/Test_ws10_build.c'
*/

/* EX #3 - List Symbols */
/*
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$ 
nm ws10_build.o Test_ws10_build.o 

ws10_build.o:
0000000000000000 T main

Test_ws10_build.o:
0000000000000000 T main
0000000000000000 B X
0000000000000004 B y
*/

/* EX #4.a - List common symbols */
/*
int X = 0; is commonly defined (-fcommon flag)
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$ 
ws10_f
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$ 
nm Test_ws10_build.o  ws10_build.o 

Test_ws10_build.o:
0000000000000000 T main
0000000000000000 B X
0000000000000004 C y

ws10_build.o:
0000000000000000 T main
0000000000000000 B X
*/

/* EX #4.b - List missing symbols */
/*
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$ 
ws10_g
/usr/bin/ld: /tmp/ccYpbPMc.o:/home/idan/Documents/Dev/Git_WD/c/ws10_build/test/Test_ws10_build.c:25: multiple definition of `X'; /tmp/cci1239x.o:/home/idan/Documents/Dev/Git_WD/c/ws10_build/src/ws10_build.c:23: first defined here
/usr/bin/ld: /tmp/ccYpbPMc.o: in function `main':
/home/idan/Documents/Dev/Git_WD/c/ws10_build/test/Test_ws10_build.c:33: undefined reference to `g'
collect2: error: ld returned 1 exit status

*/

/* EX #4.c - double main */
/*
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$
ws10_g
/usr/bin/ld: /tmp/ccNiMjby.o:/home/idan/Documents/Dev/Git_WD/c/ws10_build/test/Test_ws10_build.c:25: multiple definition of `X'; /tmp/ccvoRgub.o:/home/idan/Documents/Dev/Git_WD/c/ws10_build/src/ws10_build.c:23: first defined here
/usr/bin/ld: /tmp/ccNiMjby.o: in function `main':
/home/idan/Documents/Dev/Git_WD/c/ws10_build/test/Test_ws10_build.c:32: multiple definition of `main'; /tmp/ccvoRgub.o:/home/idan/Documents/Dev/Git_WD/c/ws10_build/src/ws10_build.c:30: first defined here
collect2: error: ld returned 1 exit status
*/

/* EX #5 - common symbols -can be used to list common global/func declerations */
/*
idan@idan-laptop:~$ cd /home/idan/Documents/Dev/Git_WD/c/ws10_build/bin
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$ ws10_f
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$ nm Test_ws10_build.o  ws10_build.o 

Test_ws10_build.o:
0000000000000000 T main ALL GLOBALS
0000000000000000 d x1 - initialized data sction
0000000000000004 b x2 - bss Segment - init to 0
0000000000000008 b x3 - BSS Segment uninit
0000000000000004 D x4 - Data Segment
0000000000000000 B x5 - BSS Segment uninit
0000000000000004 C x6 - common (fno common)

ws10_build.o:
0000000000000004 C x6
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$ ws10_fn
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$ nm Test_ws10_build.o  ws10_build.o 

Test_ws10_build.o:
0000000000000000 T main
0000000000000000 d x1
0000000000000008 b x2
000000000000000c b x3
0000000000000004 D x4
0000000000000000 B x5
0000000000000004 B x6
static int x1 = 3;
static int x2 = 0;
static int x3;
int x4 = 10;
int x5 = 0;
int x6;

ws10_build.o:
0000000000000000 B x6
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build/bin$ 
*/

/* EX #6 - create archive */
/*
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build$ ar r ws10.a src/ws10_build.c include/ws10_build.h
ar: creating ws10.a
idan@idan-laptop:~/Documents/Dev/Git_WD/c/ws10_build$ ar p ws10.a
*/

/*
extern from every file is allowd.
not from header - its unconventionl.
do not extern and declare at first row or row after row = will not compile.
if 2X g_s are available - weak will be ovweridden, 2 strongs will intercept
*/
