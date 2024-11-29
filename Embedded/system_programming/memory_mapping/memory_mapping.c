#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#include "memory_mapping.h"

int global_var1 = 1;
int global_var2 = 2;
int global_var3 = 3;

static void StaticFunction()
{

}

extern void ExternFunction();

int MemoryMappingCode1(int functions_arg_1,float functions_arg_2,double functions_arg_3)
{
    static int recursion_level = 0;

    int i = 5;
    int* p_i = &i;
    char a = 'h';
    char* p_a = &a;
    char b = 'w';
    char* p_b = &b;
    int j = 1;
    int* p_j = &j;

    int* p_arg1 = &functions_arg_1; 
    float* p_arg2 = &functions_arg_2;
    double* p_arg3 = &functions_arg_3;
    
    void(*p_static_function)() = StaticFunction;
    void(*p_extern_function)() = ExternFunction;
    int* p_heap_var = (int*)malloc(sizeof(int));
    char* p_heap_var2 = (char*)malloc(sizeof(char)); /* Check allignment */
    short* p_heap_var3 = (short*)malloc(sizeof(short)); /* Check allignment */    
    const int const_local = 5;
    const int* p_const_local = &const_local;
    const int non_const_local = 5;
    const int* p_non_const_local = &non_const_local;
    int* p_global_var1 = &global_var1;
    int* p_global_var2 = &global_var2;
    int* p_global_var3 = &global_var3;
    static int static_local_var1 = 111;
    static int static_local_var2 = 222;
    static int static_local_var3 = 333;
    int* p_static_local_var1 = &static_local_var1;
    int* p_static_local_var2 = &static_local_var2;
    int* p_static_local_var3 = &static_local_var3;
    int* p_static_global_var1 = &static_global_var1;
    int* p_static_global_var2 = &static_global_var2;
    int* p_static_global_var3 = &static_global_var3;
    char* string_literal = "abc";
    int* p_global_weak_symbol = &g_weak_symbol;

    ++recursion_level;

    /* While debugging, when you want to stop the recursion and see stack unwinding - 
       set this variable to 0 (using the debugger itslef: */
    if (global_var1 == 0)
    {
        return recursion_level;
    }

    MemoryMappingCode2(functions_arg_1+1,functions_arg_2+1,functions_arg_1+1);

    /* Cancel "unsused variable" warnings: */
    (void)i;
    (void)p_i;
    (void)a;
    (void)p_a;
    (void)b;
    (void)p_b;
    (void)p_j;
    (void)p_arg1;
    (void)p_arg2;
    (void)p_arg3;
    (void)p_static_function;
    (void)p_extern_function;
    (void)p_heap_var;
    (void)p_heap_var2;
    (void)p_heap_var3;
    (void)const_local;
    (void)p_const_local;
    (void)non_const_local;
    (void)p_non_const_local;
    (void)p_global_var1;
    (void)p_global_var2;
    (void)p_global_var3;    
    (void)global_var3;
    (void)static_local_var1;
    (void)static_local_var2;
    (void)static_local_var3;
    (void)p_static_local_var1;
    (void)p_static_local_var2;
    (void)p_static_local_var3;
    (void)p_static_global_var1;
    (void)p_static_global_var2;
    (void)p_static_global_var3;
    (void)string_literal;
    (void)p_global_weak_symbol;

    /* Unreachable code: */

    /* free is here for bravity, code is unreachable, we never free - 
       in order to examine heap allocations growth. */
    free(p_heap_var);
    free(p_heap_var2);
    free(p_heap_var3);

    return recursion_level;
}

int main(int argc, char *argv[], char *envp[])
{
    char** p_command_line_arguments = argv;
    char** p_environment_variables = envp;

    MemoryMappingCode1(1,1.0f,1.0);

    /* Cancel "unsused variable" warnings: */
    (void)p_environment_variables;
    (void)p_command_line_arguments;
    (void)argc;    

    return 0;
}

/*

Hi guys,

Regarding Memory Mapping exercise: 

- use the gcc -no-pie flag when compiling (why?). Also, turn the ASLR when you run the memory mapping .c file. (Again, like in Dumb and Dumber, don't forget to turn it back on when you're done)

- In exercise 1 you dont have to create your own program, You are allowed to use the attached files.

- The final product should be a layout which represents the memory ranges that memory segments occupy. (Exercise 3).



##########Disable ASLR ###########
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
echo 2 | sudo tee /proc/sys/kernel/randomize_va_space






The output you've provided appears to be the memory mapping information for a program as viewed in the GNU Debugger (GDB). This information shows how the program's memory is organized and what permissions are associated with each memory segment. Let's break down the information:

1. **Start Addr and End Addr:** These columns indicate the starting and ending addresses of each memory segment.

2. **Size:** This column specifies the size of each memory segment.

3. **Offset:** The offset column indicates the offset of each memory segment within the file, if applicable.

4. **Perms:** This column describes the permissions associated with each memory segment. The common permissions include:
   - `r`: Readable
   - `w`: Writable
   - `x`: Executable

5. **objfile:** This column typically specifies the path to the file or object associated with each memory segment.

Now, let's break down the individual memory segments:

- **Segment 1:** This segment spans from 0x400000 to 0x401000 and is marked as readable (`r--p`). It represents a read-only section of the program file.

- **Segment 2:** This segment spans from 0x401000 to 0x402000 and is marked as readable and executable (`r-xp`). It represents an executable section of the program.

- **Segment 3:** Similar to Segment 1, this segment spans from 0x402000 to 0x403000 and is marked as readable (`r--p`).

- **Segment 4:** Another read-only segment, spanning from 0x403000 to 0x404000 (`r--p`).

- **Segment 5:** This segment spans from 0x404000 to 0x405000 and is marked as readable and writable (`rw-p`). It represents a section of the program that can be both read and written to.

- **Segment 6:** This segment spans from 0x405000 to 0x426000 and is labeled as `[heap]`. It is the program's heap, used for dynamic memory allocation during runtime. It is marked as readable and writable (`rw-p`).

- **Segments 7-10:** These segments represent shared libraries loaded by the program (in this case, libc). They have various permissions and represent different sections of the shared library file.

- **Segments 11-14:** These segments appear to be related to the system's dynamic linker (`ld-linux-x86-64.so.2`) and have various permissions.

- **Segment 15:** This segment appears to be the stack of the program (`[stack]`). It is marked as readable and writable (`rw-p`) and is used for function call frames and local variables.

- **Segment 16:** This segment, with the address range from 0xffffffffff600000 to 0xffffffffff601000, is labeled `[vsyscall]`. It is a virtual system call page used by the kernel for very fast system calls.

This information is valuable for debugging and understanding how a program's memory is organized during its execution. It shows which parts of memory are executable, which are read-only, and which are read-write, among other details.


Position Independent Executables (PIE) are executables that can be loaded and executed at any memory address without causing problems. They are essential for security and memory management in modern operating systems. Here's how PIE, fPIC (Position Independent Code), dynamic linking, shared objects, and the `-no-pie` flag relate to each other and why they matter:

1. **Position Independent Executables (PIE):**
   - PIE executables are designed to be loaded at any address in memory. This property enhances security because it makes it harder for attackers to predict the location of critical code and data structures.
   - PIE executables are the default on many modern systems, including most Linux distributions. This helps mitigate certain types of attacks, such as buffer overflow attacks and Return-Oriented Programming (ROP) attacks, by introducing address space layout randomization (ASLR).

2. **Position Independent Code (fPIC):**
   - Position Independent Code (fPIC) is a compilation option used when building shared libraries (shared objects) and some executables. It ensures that the code can be loaded and executed at any memory address.
   - fPIC is crucial for shared libraries because multiple processes may load the same shared library into different memory locations simultaneously. If the code were not position independent, there would be conflicts.
   - Executables can also benefit from fPIC when they use shared libraries to ensure that the entire program can still be loaded at random memory addresses.

3. **Dynamic Linking:**
   - Dynamic linking is a mechanism that allows multiple programs to share a single copy of a library in memory, saving memory space and making updates easier.
   - Dynamic linking is facilitated by shared objects (shared libraries) that contain code and data that can be used by multiple programs.

4. **Shared Objects (Shared Libraries):**
   - Shared objects are files containing compiled code and data that multiple programs can use at runtime. They are loaded into memory when a program starts and are shared among different processes.
   - Shared objects help save memory because the code and data are loaded only once, even if multiple programs are using them.
   - fPIC is essential when building shared objects to ensure they can be loaded at any memory address.

5. **-no-pie Flag:**
   - The `-no-pie` flag is a compilation flag used with GCC (GNU Compiler Collection). When you compile a program with `-no-pie`, you are creating a non-PIE executable.
   - Non-PIE executables are typically linked at fixed memory addresses and do not take advantage of ASLR. They can be easier targets for certain types of attacks, as the memory layout is predictable.
   - `-no-pie` is sometimes used for compatibility with older systems or to create statically linked executables, but it may reduce security.

In summary, Position Independent Executables (PIE) and Position Independent Code (fPIC) are essential for security and memory management. They allow code and libraries to be loaded at arbitrary memory addresses, which makes it more challenging for attackers to exploit vulnerabilities. Shared objects (shared libraries) take advantage of these features to save memory and enable code sharing between processes. The `-no-pie` flag, when used, creates non-PIE executables, which may have predictable memory layouts and reduced security compared to PIE executables.




Yes, you can keep Address Space Layout Randomization (ASLR) enabled on your system while compiling specific executables with the `-no-pie` flag. ASLR is a system-wide security feature that randomizes the memory address layout of various program components (stack, heap, shared libraries, etc.) each time a program is loaded into memory. This randomness helps protect against certain types of attacks that rely on predictable memory layouts.

The `-no-pie` flag, when used during compilation, affects the individual executable being built. It essentially tells the linker to create a non-Position Independent Executable (non-PIE), meaning that the resulting executable is linked to specific memory addresses and does not take advantage of ASLR for its own code and data segments. However, ASLR will still apply to other parts of the program, such as shared libraries and the stack.

Here's a breakdown of how this works:

- When you use `-no-pie` to compile an executable, that executable's code and data segments will not be randomized by ASLR when loaded into memory. These segments will be loaded at predictable memory addresses.

- ASLR will still apply to other parts of the program, such as shared libraries (`libc.so`, etc.) and the stack. These parts will continue to be randomized, enhancing the overall security of the program.

So, you can use `-no-pie` when compiling an executable if you have a specific need for non-PIE behavior, but the system-wide AS


Non-Position Independent Executable (non-PIE) behaviors refer to the characteristics and properties of executable files that are compiled and linked without the Position Independent Executable (PIE) flag or attribute. PIE executables, as mentioned previously, are designed to be loaded at any memory address, making them more secure against certain types of attacks. In contrast, non-PIE executables have specific memory addresses where they are loaded, and they lack the security benefits associated with PIE executables. Here are some key characteristics and behaviors of non-PIE executables:

1. **Fixed Memory Addresses:** Non-PIE executables are linked to specific memory addresses during the compilation process. When they are loaded into memory, they are placed at these predetermined addresses. This means that their code and data segments are not randomized.

2. **Predictable Memory Layout:** Because non-PIE executables have fixed memory addresses, their memory layout is predictable. This predictability can be exploited by attackers who are trying to carry out memory-related attacks, such as buffer overflows and code injection.

3. **Reduced Security:** Non-PIE executables are generally considered less secure than PIE executables because they lack the protection provided by Address Space Layout Randomization (ASLR). ASLR is a security feature that randomizes the memory layout of a program's components, making it more challenging for attackers to find and exploit vulnerabilities.

4. **Compatibility:** Non-PIE executables may be used when compatibility with older systems or specific requirements is necessary. Some software or systems may not support PIE executables, so non-PIE executables are used to ensure compatibility.

5. **Static Linking:** Non-PIE executables are often associated with static linking, where all dependencies are included within the executable itself. This can result in larger executable files but eliminates the need for external shared libraries.

6. **No ASLR Benefits:** Non-PIE executables do not benefit from ASLR protection for their code and data segments. However, other parts of the program, such as shared libraries and the stack, may still have ASLR applied.

In summary, non-PIE behaviors refer to the characteristics of executables that are compiled and linked without the Position Independent Executable (PIE) attribute. They have fixed memory addresses, predictable memory layouts, reduced security, and are often used for compatibility or specific use cases where PIE executables are not feasible or required.


*/