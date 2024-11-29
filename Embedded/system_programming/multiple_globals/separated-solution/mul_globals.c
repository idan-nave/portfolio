#include <stdio.h>
#include <stdlib.h>

#include "mul_globals.h"

int x = 1;

void PrintGlobalVarAdd()
{
   printf("var x=%d in %p\n", x, &x);
}


/*FOR TESTING*/
/*int main(int argc, char *argv[], char *envp[])
{
   PrintGlobalVarAdd();
   return 0;
}*/
