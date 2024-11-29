/***************************** ws14_exersises.c  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet #14 - ATOI ITOA
  Reviewer: Aya
  Date: 06/08/23
  Version: 1.0
*/
  
/******************************************************************************/
/*################################  Keywords   ###############################*/
/******************************************************************************/
/*
1. volatile: Indicate to the compiler that the variable may change its value at
   any time outside the normal flow of the program.
2. auto: Default storage class for variables within a function.
3. goto: Used for unconditional branching in the code.
4. Multi-dimensional arrays: Arrays can have more than one dimension,
   forming multi-dimensional arrays.
5. Little-endian / big-endian: Terms refer to the order in which bytes are
   stored in a multi-byte data type in computer memory.
   In a little-endian system, the least significant byte is stored first,
   while in a big-endian system, the most significant byte is stored first. 
  Endianness is important when data is transmitted or shared between systems
  with different byte orderings.
6. Uninitialized variables: Variables declared but not assigned a value.

Functions:
1. atof: Converts a string representing a floating-point number to a 'double'.
2. atoi: Converts a string representing an integer to an 'int'.
base range is 2 up to 36 because this is the max number of available symbols.
3. atol: Converts a string representing a long integer to a 'long'.

Examples:
(atof) "ASCII to double"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char str[] = "3.14";
    double value = atof(str);
    printf("Parsed value: %f\n", value);
    return 0;
}

(atoi) "ASCII to integer"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char str[] = "42";
    int value = atoi(str);
    printf("Parsed value: %d\n", value);
    return 0;
}

(atol) "ASCII to long"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    char str[] = "123456";
    long value = atol(str);
    printf("Parsed value: %ld\n", value);
    return 0;
}
*/
/******************************************************************************/
/*################################  Questions  ###############################*/
/******************************************************************************/
/*

1. What is a volatile variable?
A volatile variable is a type of variable in C that informs the compiler that
its value may change at any time without any action being taken by the code the
compiler finds nearby. This typically occurs when the variable is shared with 
hardware, memory-mapped I/O, or in a multi-threaded environment where the 
variable can be modified by external factors. By declaring a variable as 
volatile, you ensure that the compiler does not optimize out or reorder reads
and writes to that variable, ensuring that each access to the variable reflects 
its latest value.

2. When would we use goto ?
The goto statement allows you to perform unconditional jumps to labeled 
statements within the same function. It can be used to implement certain 
control flow patterns, but its use is generally discouraged in modern 
programming due to its potential to create spaghetti code, which can make the 
program harder to read, understand, and maintain. Structured programming 
constructs like loops (for, while, do-while) and conditional statements 
(if, switch) provide more organized control flow and are preferred over 
goto. goto is sometimes used in specialized situations, such as breaking 
out of nested loops, but it should be used with caution.


3. Memorize the following sizes: 1KB, 32KB, 64KB, 1MB, 1GB, 1TB. 
Why is this important?
  Understanding and interpreting file sizes and storage capacities.
  Allocating memory dynamically during programming.
  Optimizing memory usage and data structures.
  Comparing storage capacities of devices, files, or data sets.
  These sizes are commonly used in computing and data storage, so having a 
  basic understanding of their scale helps in making informed decisions and 
  working effectively in various computing tasks.
  
/******************************************************************************/
/*#####################  atoi arguments considerations  #######################*/
/******************************************************************************/
/*  
  Pros and Cons of Receiving a Pointer vs. Locally Allocating vs. 
  Using Static Local for itoa Out Parameter:
Receiving a Pointer:
    Pros:
    Allows the caller to specify the memory location where the result should 
    be stored. More flexible, as the caller can choose the storage duration 
    and scope of the result.
    Cons:
    Requires the caller to allocate memory for the result, which can lead to 
    potential memory management issues if not handled correctly.
Locally Allocating:
    Pros:
    Easier memory management, as the function takes care of memory allocation.
    Avoids the need for the caller to allocate memory and pass a pointer.
    Cons:
    The caller may not have control over the memory allocation after more
    function calls and need to free the pointer by himself.
Using Static Local:
    Pros:
    Avoids the need for memory allocation and pointer handling.
    The result persists across function calls, making it convenient for some cases.
    Cons:
    Not reentrant, as the static local variable is shared across function calls,
    which can lead to thread-safety issues.
    Limited usage when you need to store multiple results or when the function
    is called concurrently.

