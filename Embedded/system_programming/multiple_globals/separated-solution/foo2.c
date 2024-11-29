#include <stdio.h>
#include "mul_globals.h"

void Foo2(int num) 
{
     printf("Inside Foo 2");
     PrintGlobalVarAdd();
     printf("and also num=%d", num);
}

/*
2. Compile `foo.c` into an object file:
     bash   gcc -c foo.c -o foo.o
3. Create a static library `libfoo.a`:
     bash  ar rcs libfoo.a foo.o
*/