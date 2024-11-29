/***************************** ws11_exersises.c  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet #11 - Structs
  Reviewer: ???
  Date: 30/07/23
  Version: 1.0
*/
  
/******************************************************************************/
/*##############################   Struct (keyword)   ########################*/
/******************************************************************************/
In C, a struct (short for "structure") is a composite data type that allows
you to group multiple variables of different data types together under a 
single name. It provides a way to create custom data types that can hold 
related pieces of data.

The syntax for declaring a struct in C is as follows:


struct struct_name
{
    data_type member1;
    data_type member2;
    // More members can be added as needed
};

Here's an example of a simple struct representing a point in 2D space:


struct Point
{
    int x;
    int y;
};

With this definition, you can create variables of the `struct Point` type:

struct Point p1; // Declaration of a variable of type struct Point
p1.x = 10;       // Accessing and assigning values to the members of the struct
p1.y = 5;

You can also initialize a struct when declaring it:


struct Point p2 = {3, 7}; // Initialize the struct members while declaring 
the variable

To make the syntax more concise, C allows you to use a typedef to create a 
new name for the struct type:

typedef struct Point
{
    int x;
    int y;
} Point; // Here, 'Point' is an alias for 'struct Point'

With the typedef, you can declare variables directly using the new name:


Point p3; // Declaration using the typedef
p3.x = 2;
p3.y = -4;

Structs are commonly used to create more complex data structures like
linked lists, trees, records, and more. They provide a way to organize
and manage related data in a more organized manner than using individual
variables.


/******************************************************************************/
/*##################################   Padding   ############################*/
/******************************************************************************/
 
 Padding in C refers to the insertion of extra bytes into data structures,
 particularly in structs, to ensure that each member of the structure is aligned properly in memory. The goal of padding is to optimize memory access and data
 alignment for more efficient memory management and CPU operations.

When you define a struct in C, the compiler may insert padding bytes between
the members of the struct to ensure that they are suitably aligned. Alignment requirements vary based on the data types used in the struct and the target architecture.

For example, consider the following struct:

struct MyStruct
{
    char a;
    int b;
    double c;
};

On most architectures, `char` requires just one byte, `int` requires four
bytes, and `double` requires eight bytes. The struct size would be 1 (char) + 3 (padding) + 4 (int) + 4 (double) = 12 bytes. The padding is inserted between
the `char` and `int` members to ensure that the `int` starts at an address
that is a multiple of four (common alignment for integers on many platforms).

You can use the `sizeof` operator to check the size of a struct:

printf("Size of MyStruct: %zu\n", sizeof(struct MyStruct));

Note that the actual padding and struct size may vary depending on the target architecture, compiler, and compilation flags.

To reduce padding and ensure tighter packing of struct members, you can use
compiler-specific attributes or pragmas to control the alignment and
packing behavior. However, keep in mind that modifying packing may have
implications for performance and portability, so it's generally recommended
to let the compiler handle padding for most cases.

Overall, understanding padding and data alignment can be important when working
with memory-constrained environments or when dealing with data structures that
need to be shared across different systems. However, for typical applications, 
the compiler's default padding behavior is usually sufficient and transparent to the programmer.
 
/******************************************************************************/
/*##################################   Alignment   ############################*/
/******************************************************************************/
Alignment refers to the memory address at which data is stored. It specifies the boundary or offset at which a variable of a particular data type should start in memory.
Certain data types have specific alignment requirements. For example, on many systems, int variables must start at addresses that are multiples of 4 bytes, and double variables must start at addresses that are multiples of 8 bytes.
Alignment is essential for the efficient access of data by the CPU. When data is properly aligned, the CPU can fetch it in one memory access operation, leading to faster and more efficient memory access.

struct MyStruct
{
    char a;    // Takes 1 byte, aligned on 1-byte boundary
    int b;     // Takes 4 bytes, aligned on a 4-byte boundary
    double c;  // Takes 8 bytes, aligned on an 8-byte boundary
};

In this example, the struct members have specific alignments. The char member requires no padding since it's already naturally aligned on a 1-byte boundary. The int member requires 3 bytes of padding to align it on a 4-byte boundary. The double member doesn't require any padding since it's already naturally aligned on an 8-byte boundary.

In summary, alignment defines the memory address at which data should start, and padding ensures that the data adheres to the proper alignment requirements. Both alignment and padding are important for memory efficiency and data access performance.

/******************************************************************************/
/*##################################   #pragma pack   ############################*/
/******************************************************************************/

`#pragma pack` is a preprocessor directive in C and C++ that controls the padding and alignment of data structures, particularly structs. It allows you to modify the default padding behavior of the compiler and achieve tighter packing of struct members in memory.

The `#pragma pack` directive takes a single argument, which specifies the new alignment to be used for the data members of the struct. The argument is typically a positive integer that represents the byte alignment you want for the struct.

The syntax for using `#pragma pack` is as follows:

#pragma pack(n)

Where `n` is the new byte alignment value you want to set. This value represents the number of bytes that the compiler should use as the alignment for the struct members.

After the `#pragma pack` directive, you can define your structs, and they will be packed according to the specified alignment until the end of the translation unit (typically until the end of the file).

Here's an example of how to use `#pragma pack` to achieve tight packing of a struct:

#pragma pack(1) // Set byte alignment to 1

struct PackedStruct {
    char a;
    int b;
    double c;
};

#pragma pack() // Reset to default byte alignment

In this example, the `PackedStruct` will have its members tightly packed with no padding between them. The byte alignment for this struct is set to 1, which means that each member will start at the next consecutive byte in memory.

Keep in mind that modifying the packing behavior with `#pragma pack` can have implications for memory access performance and portability. While it can be useful in certain scenarios, such as when dealing with binary data or interfacing with external systems with specific alignment requirements, it is essential to use it judiciously and understand the potential side effects. In most cases, relying on the compiler's default packing behavior is sufficient for typical high-level programming tasks.

/******************************************************************************/
/*##################################   Macro   ############################*/
/******************************************************************************/

1. Macros with Parameters:

// Macro to calculate the square of a number
#define SQUARE(x) ((x) * (x))

// Macro to calculate the maximum of two numbers
#define MAX(a, b) ((a) > (b) ? (a) : (b))

Usage:
int result1 = SQUARE(5); // Expands to: ((5) * (5)) => 25
int result2 = MAX(10, 7); // Expands to: ((10) > (7) ? (10) : (7)) => 10

2. Multi-Line Macros:

// Macro to calculate the sum and difference of two numbers
#define SUM_AND_DIFF(x, y, sum, diff) \
    do { \
        sum = (x) + (y); \
        diff = (x) - (y); \
    } while (0)

Usage:
int a = 10, b = 5;
int sum, diff;
SUM_AND_DIFF(a, b, sum, diff); // Expands to the block with sum and diff calculations

3. Macros with Variable Declarations:

// Macro to declare and initialize an integer array
#define DECLARE_ARRAY(arr_name, size) \
    int arr_name[size] = {0}

Usage:
DECLARE_ARRAY(my_array, 5); // Expands to: int my_array[5] = {0};

Costs and Benefits of Using Macros:

Costs:
- Lack of type-checking: Macros do not perform type-checking, so mistakes in the usage of arguments may lead to unexpected behavior or errors.
- Debugging can be challenging: Expansions of complex macros can be difficult to read, making debugging and code maintenance more complicated.
- Potential for code bloat: If used excessively, macros can increase the size of the compiled code since they are expanded inline at every usage.

Benefits:
- Performance: Macros can sometimes lead to more efficient code as they avoid function call overhead.
- Flexibility: Macros can accept any expression as arguments, providing flexibility that functions might not offer.
- Compiler Independence: Macros are preprocessor directives and work across different compilers, making them portable.

When to Use a Macro over a Function:

- Performance critical code: In performance-sensitive sections of code, macros can be used to avoid the overhead of function calls.
- Simple and short operations: Macros are suitable for simple, one-liner operations where the overhead of a function call is unnecessary.
- Working with constants: Macros can be used to define constant values or expressions that would be computed at compile-time, allowing better optimization.

However, it's important to use macros judiciously, as their lack of type-checking and potential for side effects can lead to unexpected results. In many cases, functions are preferred over macros for their safety and maintainability. As a general rule, use macros when they offer a significant advantage in performance or expressiveness and when their potential drawbacks are well understood and managed.

/******************************************************************************/
/*#########################   predefined macros   ############################*/
/******************************************************************************/
predefined macros that the preprocessor provides. These macros are replaced with specific values by the preprocessor during compilation. They are commonly used in debugging, logging, and other situations where you want to include information about the source code in the compiled program.

___TIME___:

This macro expands to a string constant that represents the time at which the compilation started.

The format of the time string is "hh:mm:ss", where hh is the hour (00-23), mm is the minutes (00-59), and ss is the seconds (00-59).

Example usage:
printf("Compilation started at: %s\n", ___TIME___);
___LINE___:

This macro expands to an integer constant that represents the current line number in the source file being compiled.

It is particularly useful for debugging and error reporting to identify the exact line of code where a particular message or issue occurs.

Example usage:
printf("This message is printed from line number: %d\n", ___LINE___);
___DATE___:

This macro expands to a string constant that represents the date on which the compilation started.

The format of the date string is "Mmm dd yyyy", where Mmm is the abbreviated month (e.g., Jan, Feb), dd is the day of the month (01-31), and yyyy is the year.

Example usage:
printf("Compilation date: %s\n", ___DATE___);
___FILE___:

This macro expands to a string constant that represents the name of the current source file being compiled.

The string includes the full path to the file, if provided during compilation.

Example usage:
printf("Currently compiling file: %s\n", ___FILE___);

/******************************************************************************/
/*###############################   typedef for   ############################*/
/******************************************************************************/

1. Basic Types:

#include <stdio.h>

int main()
{
    int integerVariable = 42;
    float floatVariable = 3.14f;
    char charVariable = 'A';
    double doubleVariable = 2.718281828;

    printf("Integer: %d\n", integerVariable);
    printf("Float: %f\n", floatVariable);
    printf("Character: %c\n", charVariable);
    printf("Double: %lf\n", doubleVariable);
    return 0;
}


2. Struct:

#include <stdio.h>

struct Point 
{
    int x;
    int y;
};

int main()
{
    struct Point p1 = {5, 10};
    printf("Point: (%d, %d)\n", p1.x, p1.y);
    return 0;
}

3. Enum:

#include <stdio.h>

enum DaysOfWeek
{
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

int main()
{
    enum DaysOfWeek today = TUESDAY;
    printf("Today is day %d\n", today);
    return 0;
}

4. Pointer to Function:


#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}
int subtract(int a, int b)
{
    return a - b;
}

int main()
{
    int (*operation)(int, int);
    // Pointer to a function that takes two int parameters and returns an int
    operation = add;

    int result = operation(5, 3);
    printf("Result of addition: %d\n", result);

    operation = subtract;
    result = operation(10, 4);
    printf("Result of subtraction: %d\n", result);
    return 0;
}

5. Pointer to Array:

#include <stdio.h>

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    int (*ptrToArray)[5]; // Pointer to an array of 5 integers

    ptrToArray = &arr; // Point the pointer to the array

    for (int i = 0; i < 5; i++)
    {
        printf("Element %d: %d\n", i, (*ptrToArray)[i]);
    }

    return 0;
}

/******************************************************************************/
/*##################################   Union   ############################*/
/******************************************************************************/

In C, a union is a composite data type that allows you to define a variable that
can hold different types of data, but only one at a time. It allocates enough
memory to hold the largest member of the union, and all members share the same
memory location. This means that changing the value of one member will affect
the value of other members since they occupy the same memory space.

The syntax for declaring a union in C is similar to that of a struct:


union UnionName
{
    member_type1 member_name1;
    member_type2 member_name2;
    // Additional members can be added with different data types
};


Here's an example of a union representing different types of data:


#include <stdio.h>

union Data
{
    int intValue;
    float floatValue;
    char charValue;
};

int main()
{
    union Data myData;

    myData.intValue = 42;
    printf("Value as int: %d\n", myData.intValue);

    myData.floatValue = 3.14f;
    printf("Value as float: %f\n", myData.floatValue);

    myData.charValue = 'A';
    printf("Value as char: %c\n", myData.charValue);

    // Since all members share the same memory,
    the value of intValue is now overwritten by charValue
    printf("Value as int after setting char: %d\n", myData.intValue);

    return 0;
}

Output:
Value as int: 42
Value as float: 3.140000
Value as char: A
Value as int after setting char: 65

In this example, we defined a union named `Data` with three members: `intValue`, `floatValue`, and `charValue`. We can access and modify these members as needed, but only one member can hold a value at any given time.

Unions are useful in situations where you want to save memory by sharing memory space between different types of data when only one of them will be used at a time. However, be cautious when using unions, as accessing the wrong member can lead to undefined behavior and unexpected results. Unions should be used with care to ensure proper handling of the data they hold.

/******************************************************************************/
/*##################################   Bit fields   ##########################*/
/******************************************************************************/

In C, bit fields are a feature that allows you to specify the size of individual fields (members) within a struct or union in terms of bits. This means you can control the memory usage of each field more precisely, which can be particularly useful when working with hardware registers, packing data for storage, or implementing data structures with specific memory constraints.

The syntax for declaring a bit field within a struct is as follows:

struct BitFieldExample
{
    type fieldName : width;
};

Where:
- `type`: The data type of the bit field.
- `fieldName`: The name of the bit field.
- `width`: The number of bits to allocate for the bit field.

Here's an example to illustrate how to use bit fields in C:


#include <stdio.h>

struct Flags
{
    unsigned int flag1 : 1; // One bit for flag1
    unsigned int flag2 : 3; // Three bits for flag2
    unsigned int flag3 : 8; // Eight bits for flag3
};

int main()
{
    struct Flags myFlags;

    myFlags.flag1 = 1;
    myFlags.flag2 = 5; // Binary representation: 101 (3 bits wide)
    myFlags.flag3 = 255;

    printf("Flag1: %u\n", myFlags.flag1);
    printf("Flag2: %u\n", myFlags.flag2);
    printf("Flag3: %u\n", myFlags.flag3);

    printf("Size of struct Flags: %zu bytes\n", sizeof(struct Flags));

    return 0;
}


Output:
Flag1: 1
Flag2: 5
Flag3: 255
Size of struct Flags: 4 bytes

In this example, we have defined a struct named `Flags` with three bit fields: `flag1`, `flag2`, and `flag3`. We explicitly specified the width of each bit field to control the memory usage.

Keep in mind the following important points when working with bit fields:

1. The width of a bit field cannot exceed the size of its data type. For example, you cannot have a 9-bit wide bit field of type `int`.

2. The memory allocation of a bit field may vary depending on the target architecture and the compiler's implementation of bit fields.

3. Bit fields are not suitable for all situations, especially when portability across different systems is a concern, as the memory layout of bit fields may vary on different architectures.

4. Bit fields should be used with caution as they may lead to issues related to endianness, padding, and alignment, depending on the compiler and target architecture.

Overall, bit fields can be a powerful tool for packing data more efficiently, but their usage requires careful consideration of the specific requirements and constraints of your application.
