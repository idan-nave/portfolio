
   #include <stdio.h>
   #include <dlfcn.h>

   int main()
   {
       void *handle = dlopen("./libfoo.so", RTLD_LAZY);
       if (NULL == handle)
       {
           fprintf(stderr, "Error: %s\n", dlerror());
           return 1;
       }

       void (*Foo)(int) = dlsym(handle, "Foo");
       if (NULL == Foo)
       {
           fprintf(stderr, "Error: %s\n", dlerror());
           dlclose(handle);
           return 1;
       }
       void *handle2 = dlopen("./libfoo2.so", RTLD_LAZY);
       if (NULL == handle2)
       {
           fprintf(stderr, "Error: %s\n", dlerror());
           return 1;
       }

       void (*Foo2)(int) = dlsym(handle2, "Foo2");
       if (NULL == Foo2)
       {
           fprintf(stderr, "Error: %s\n", dlerror());
           dlclose(handle2);
           return 1;
       }
        Foo(1);
        Foo2(2);

       dlclose(handle);
       dlclose(handle2);
       return 0;
   }
   
/* 

########### EX 3.b ########
added load.c - see in file

gcc -o exp_dyn.out load.c -L. -Wl,-rpath=. -lfoo -lfoo2
print:

Inside Foo 1var x=1 in 0x7fa7875e6018
and also num=1
Inside Foo 2var x=1 in 0x7fa7875e1018
and also num=2


########### EX 4 ########
addresses from EX.3 A & B are not the same:

0x556b0714f010 VS. 0x7fa7875e6018



static.c program is statically linked, meaning it doesn't load external libraries dynamically. Instead, it's part of a single executable binary. In this case, all the code and data, including the global variables, are linked into a single executable, and they share the same memory space. Therefore, the address of the x variable in static.c will be different from the address of x in libfoo.so and libfoo2.so because they are loaded separately.

########### EX 5 ########
Since EX.2a (using PIC Static lib) works but not reflect the real answer,
it can be used as a seperate solution.
*/