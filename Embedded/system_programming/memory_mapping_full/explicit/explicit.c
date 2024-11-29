#include <dlfcn.h>
#include <gnu/lib-names.h> 
#include <stdio.h> 

typedef int (*DynamicFunc)(int functions_arg_1,float functions_arg_2,double functions_arg_3);

int main(int argc, char** argv, char** envp)
{
    void *handle;
    DynamicFunc func = NULL;
    
    char** p_command_line_arguments = argv;
    char** p_environment_variables = envp;

    handle = dlopen("./libmemory_mapping.so", RTLD_LAZY);
    if (NULL == handle)
    {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }
    
    /*Cast the result of dlsym to the correct function pointer type*/
    *(void **)(&func) = dlsym(handle, "MemoryMappingCode1");
    if (NULL == func)
    {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    func(1,1.0f,1.0);   
    dlclose(handle);

    /* Cancel "unsused variable" warnings: */
    (void)p_environment_variables;
    (void)p_command_line_arguments;
    (void)argc;    

    return 1;
}