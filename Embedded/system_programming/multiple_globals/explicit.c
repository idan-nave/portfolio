#include <dlfcn.h>
#include <gnu/lib-names.h> 
#include <stdio.h> 

typedef void (*Print)(void);
	
/*	int x=2; --causing multiple definition - Q3.A*/
int main()
{
  	void *handle;
  	void *handle2;
	Print print_func = NULL;
	PrintGlobalVariableAddress();

    handle = dlopen("./libfoo.so", RTLD_LAZY);
	if (NULL == handle)
	{
		fprintf(stderr, "Error: %s\n", dlerror());
		return 1;
	}
   	
	/*Cast the result of dlsym to the correct function pointer type*/
    *(void **)(&print_func) = dlsym(handle, "Foo");
    if (NULL == print_func)
	{
		fprintf(stderr, "Error: %s\n", dlerror());
		return 1;
	}

	print_func();		
	
    handle2 = dlopen("./libfoo2.so", RTLD_LAZY);
	if (NULL == handle2)
	{
		fprintf(stderr, "Error: %s\n", dlerror());
		return 1;
	}
   	

	/*Cast the result of dlsym to the correct function pointer type*/
	*(void **)(&print_func) = dlsym(handle2, "Foo2");	
	if (NULL == print_func)
	{
		fprintf(stderr, "Error: %s\n", dlerror());
		return 1;
	}
	
	print_func();	
	
	dlclose(handle);
	dlclose(handle2);
   	
   	return 1;
}

/*
1. Using `RTLD_NOW | RTLD_LOCAL`:
	handle = dlopen("./libfoo.so", RTLD_NOW | RTLD_LOCAL);

   - `RTLD_NOW`: This flag specifies that all unresolved symbols in the library should be resolved immediately, at the time `dlopen` is called. If any unresolved symbols are found, `dlopen` will fail with an error.
   - `RTLD_LOCAL`: This flag specifies that the symbols defined in the shared library will not be made available for symbol resolution of subsequently loaded libraries. It means that the symbols in `libfoo.so` won't be used to resolve symbols in other shared libraries loaded after this one.

   Using `RTLD_NOW` is generally a good practice because it helps catch symbol resolution errors at load time rather than at runtime when a function is called. `RTLD_LOCAL` can be used when you want to prevent symbols in the loaded library from being available to other libraries loaded later, which can help prevent symbol conflicts.

2. Using `RTLD_LAZY`:
   void *handle = dlopen("./libfoo.so", RTLD_LAZY);

   - `RTLD_LAZY`: This flag specifies that symbol resolution should be deferred until the symbols are actually referenced by the program. This means that unresolved symbols will not cause `dlopen` to fail; they will only cause errors at runtime when the unresolved symbols are used.

   Using `RTLD_LAZY` can make the loading process faster because it defers symbol resolution until necessary. However, it can lead to runtime errors if there are unresolved symbols that are not used, or if the symbols cannot be resolved at runtime.

The choice between `RTLD_NOW` and `RTLD_LAZY` depends on your specific use case and requirements. If you want to catch symbol resolution errors early and ensure that the library is fully loaded and ready to use, `RTLD_NOW` is a safer choice. If you want to optimize loading speed and are confident that all symbols will be used correctly, you can use `RTLD_LAZY`.

*/