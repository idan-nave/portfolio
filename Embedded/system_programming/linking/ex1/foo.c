/*reating and Using a Static Library**

1. Create a file named `foo.c` with the following content: */
  
   #include <stdio.h>
   void Foo(int num) 
   {
       printf("Foo: %d\n", num);
   }

/*
2. Compile `foo.c` into an object file:
     bash   gcc -c foo.c -o foo.o
3. Create a static library `libfoo.a`:
     bash  ar rcs libfoo.a foo.o
*/