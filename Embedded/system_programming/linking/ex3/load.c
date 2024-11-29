
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

       Foo(42);

       dlclose(handle);
       return 0;
   }
   
/* 
 gcc -c -fPIC foo.c
 gcc -shared -o libfoo.so foo.o
 LD_LIBRARY_PATH=.
 export LD_LIBRATY_PATH
 ./load.out
Foo: 42
*/