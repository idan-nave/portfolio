/*
Name: HRD 32
Project: Infinite Loop Core Dump Debug
Reviewer: _
Date: 10/07/2023
Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/

#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>  /*Using size_t in header file*/

/******************************* DECLARATIONS *********************************/

/*
  ##### History of commands to perform
  124  ulimit -c unlimited           //  The ulimit setting is used to define user system and process resource limits.
  135  gcc -g ./infinite_loop_dump.c -o infinite_loop_dump.o
  125  ./infinite_loop_dump.out &   //  run in background
  129  kill -s SIGABRT 19396        //  abort() is usually called by library functions
                                  which detect an internal error or some seriously broken constraint.
                                  For example malloc() will call abort() if its internal structures
                                  are damaged by a heap overflow.
  130  cd /var/lib/apport/coredump
  131  ls
  132  cp core._home_idan_Documents_Dev_Git_WD_a_out.1000.fef690b2-8431-4687-86f2-b88820a83be9.19396.3496566 ~/Documents/Dev/Git_WD/
  133  cdgit
  139  gdb infinite_loop_dump.out core._home_idan_Documents_Dev_Git_WD_a_out.1000.fef690b2-8431-4687-86f2-b88820a83be9.19396.3496566 
*/


int main()
{
	int y =0, x = 0;	
	while(1)
	{
	
	  ++x;
	  ++y;
	
	}
}
