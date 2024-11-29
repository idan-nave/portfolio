
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

       handle = dlopen("./libfoo.so", RTLD_LAZY);
       if (NULL == handle)
       {
           fprintf(stderr, "Error: %s\n", dlerror());
           return 1;
       }

       Foo = dlsym(handle, "Foo");
       if (NULL == Foo)
       {
           fprintf(stderr, "Error: %s\n", dlerror());
           dlclose(handle);
           return 1;
       }
       handle2 = dlopen("./libfoo2.so", RTLD_LAZY);
       if (NULL == handle2)
       {
           fprintf(stderr, "Error: %s\n", dlerror());
           return 1;
       }

       Foo2 = dlsym(handle2, "Foo2");
       if (NULL == Foo2)
       {
           fprintf(stderr, "Error: %s\n", dlerror());
           dlclose(handle2);
           return 1;
       }
        Foo(1);
        Foo2(2);

       return 0;
   }
   
/* 

########### Q4 ########

gcc -o exp_dyn2.out load2.c -L. -Wl,-rpath=. -lfoo -lfoo2
print:

Inside Foo 1var x=1 in 0x7f61c7cc4018
and also num=1Inside Foo 2var x=1 in 0x7f61c7cbf018
and also num=2Inside Foo 1var x=1 in 0x7f61c7cc4018
and also num=1Inside Foo 2var x=1 in 0x7f61c7cbf018
and also num=2
*/