#include "print.h"
#include <stdio.h>

int x = 10;

void PrintGlobalVariableAddress()
{
	printf("address of x %p\n", &x);
}



