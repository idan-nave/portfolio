#include <stdio.h>
#include "mul_globals.h"

int main(int argc, char const *argv[])
{
     printf("Inside Foo 1\n");
     PrintGlobalVarAdd();
}


/*
########### EX 3.a ########

gcc mul_globals.c -c 
ar rcs libmul.a mul_globals.o

gcc -o static.out static.c -L. -lmul

print:
Inside Foo 1
var x=1 in 0x556b0714f010

*/