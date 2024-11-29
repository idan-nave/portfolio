/***************************** ws11_exersises.c  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet #11 - Structs
  Reviewer: Uri
  Date: 31/07/23
  Version: 1.0
*/
  
/******************************************************************************/
/*#################################   Exersises   ############################*/
/******************************************************************************/

/******************************************************************************/
/*5. Implement the macros MAX2 (a, b) and MAX3 (a, b, c). */
/******************************************************************************/

#include <stdio.h>

// Macro to find the maximum of two values
#define MAX2(a, b) ((a) > (b) ? (a) : (b))

// Macro to find the maximum of three values
#define MAX3(a, b, c) MAX2(MAX2(a, b), c)

int main()
{
    int num1 = 10, num2 = 25, num3 = 15;

    int maxOfTwo = MAX2(num1, num2);
    printf("Maximum of %d and %d is: %d\n", num1, num2, maxOfTwo);

    int maxOfThree = MAX3(num1, num2, num3);
    printf("Maximum of %d, %d, and %d is: %d\n", num1, num2, num3, maxOfThree);
    return 0;
}

Output:
Maximum of 10 and 25 is: 25
Maximum of 10, 25, and 15 is: 25

In this example, we defined two macros: `MAX2` and `MAX3`. The `MAX2` macro takes two arguments `a` and `b`, and it returns the maximum of the two values using the ternary operator (`?:`). The `MAX3` macro uses the `MAX2` macro twice to find the maximum of three values `a`, `b`, and `c`.

These macros are handy for finding the maximum value among a set of numbers and can be used with any data type that supports comparison with the `>` operator. Keep in mind that, like any macro, the arguments to these macros are evaluated multiple times, so you should be cautious when using expressions with side effects as arguments.

﻿/******************************************************************************/
/*6. Macro SIZEOF_VAR that returns size of variable without sizeof. */
/******************************************************************************/
 
we can utilize pointer arithmetic. The idea is to declare two pointers of the same type, and then calculate the difference in their addresses. The difference will give you the size of the variable.

#include <stdio.h>

// Macro to calculate the size of a variable without using sizeof
#define SIZEOF_VAR(var) ((char*)(&var + 1) - (char*)(&var))

int main()
{
    int num;
    double pi;
    char ch;
    
    printf("Size of num: %d\n", SIZEOF_VAR(num));
    printf("Size of pi: %d\n", SIZEOF_VAR(pi));
    printf("Size of ch: %d\n", SIZEOF_VAR(ch));
    return 0;
}

Output:
Size of num: 4
Size of pi: 8
Size of ch: 1

In this example, the `SIZEOF_VAR` macro calculates the size of the variable `var`. It takes the address of `var` and the address of `var + 1`, casts them to `char*` to ensure pointer arithmetic works in bytes, and then subtracts them. This will give the size of the variable in bytes.

﻿/******************************************************************************/
/*7. Macro SIZEOF_TYPE, that returns size of type (struct, int) without sizeof*/
/******************************************************************************/
 
we use the same approach as in the previous solution for the `SIZEOF_VAR` macro. The idea is to create a dummy pointer to the type, calculate the difference between two pointers, and obtain the size.

Heres how you can implement the `SIZEOF_TYPE` macro:

#include <stdio.h>

// Macro to calculate the size of a type without using sizeof
#define SIZEOF_TYPE(type) ((char*)((type*)0 + 1) - (char*)(type*)0)

int main()
{
    printf("Size of int: %d\n", SIZEOF_TYPE(int));
    printf("Size of double: %d\n", SIZEOF_TYPE(double));
    printf("Size of char: %d\n", SIZEOF_TYPE(char));
    
    struct MyStruct
    {
        int x;
        char c;
        double d;
    };
    printf("Size of struct MyStruct: %d\n", SIZEOF_TYPE(struct MyStruct));
    return 0;
}

Output:
Size of int: 4
Size of double: 8
Size of char: 1
Size of struct MyStruct: 16

In this example, the `SIZEOF_TYPE` macro calculates the size of the type specified as an argument. It creates a dummy pointer of the type (e.g., `int*`, `double*`, `struct MyStruct*`) with a value of 0 and then uses pointer arithmetic to calculate the size.
 
﻿/******************************************************************************/
/*1. Give two different ways to do typedef of a struct. */
/******************************************************************************/

1. Using the `typedef` keyword along with the struct definition:
typedef struct
{
    int age;
    char name[50];
} Person;

In this method, the `typedef` keyword is used with the struct definition itself. The `Person` becomes a new name (alias) for the struct type, so you can use `Person` as a type name instead of writing `struct <struct_name>`.

Example usage:
int main()
{
    Person person1;
    person1.age = 30;
    strcpy(person1.name, "John Doe");
    return 0;
}

2. Separating the struct definition from the typedef:
struct Employee
{
    int id;
    char name[50];
};
typedef struct Employee Employee; 
// Here, 'Employee' becomes the new name for 'struct Employee'

In this method, the struct definition is first written, and then the `typedef` keyword is used to create a new name (`Employee`) for the struct type (`struct Employee`).

Example usage:
int main()
{
    Employee emp1;
    emp1.id = 101;
    strcpy(emp1.name, "Alice");
    return 0;
}

﻿/******************************************************************************/
/*2. How to initialize a struct variable as part of its definition? */
/******************************************************************************/

1. Using Designated Initializers (C99 and later):
#include <stdio.h>
// Define a struct
The Designed Initializer came up since the ISO C99 and is a different and more dynamic way to initialize in C when initializing struct, union or an array.
 struct point p = { .y = 2, .x = 3 }; or
 struct point p = { y: 2, x: 3 };

int main()
{
    // Initialize a struct variable using designated initializers (C99)
    struct Person person1 = 
    {
        .age = 30,
        .name = "John Doe"
    };

    // Access and print the struct members
    printf("Age: %d\n", person1.age);
    printf("Name: %s\n", person1.name);
    return 0;
}

In this method, the struct members are initialized using designated initializers, where each member is assigned a value using the syntax `.member_name = value`.

2. Directly Assigning Values to Members:
#include <stdio.h>
// Initialize a struct variable by directly assigning values to its members
struct Person
{
    int age;
    char name[50];
} P1 = { 3,"aaaa" }

int main()
{


    // Access and print the struct members
    printf("Age: %d\n", person1.age);
    printf("Name: %s\n", person1.name);

    return 0;
}

In this method, the struct members are initialized by directly assigning values to them after declaring the struct variable.

Both methods achieve the same result of initializing the struct variable at the time of its declaration. The designated initializer method allows you to specify the values for individual members explicitly, which can be useful if you want to initialize only specific members and leave others to their default values (e.g., 0 for numeric types, '\0' for char arrays). The direct assignment method provides a more straightforward approach to initializing all the members at once.

﻿/******************************************************************************/
/*3. struct assignment (operator =) is legal in C. How is this possible?  */
/******************************************************************************/
  
In C, the assignment operator (`=`) is used for assigning values between variables of the same type. Struct assignment allows to copy the contents of one struct to another struct of the same type. The assignment operator works as expected for structs when both structs have the same members and member types.

Consider the following example:

#include <stdio.h>

struct Point
{
    int x;
    int y;
};

int main()
{
    struct Point point1 = {2, 3};
    struct Point point2;

    // Struct assignment (copying contents of point1 to point2)
    point2 = point1;

    printf("point1: x = %d, y = %d\n", point1.x, point1.y);
    printf("point2: x = %d, y = %d\n", point2.x, point2.y);

    return 0;
}

Output:
point1: x = 2, y = 3
point2: x = 2, y = 3

The reason struct assignment works is that the assignment operator simply copies the values of each member from the source struct to the destination struct. The members of the structs are treated like any other variable, and the assignment is done member-wise.

However, its important to note that struct assignment only copies the values of the members. If the struct contains pointers or dynamically allocated memory, a shallow copy of the pointers will be made, not a deep copy of the data they point to. In such cases, you need to be careful about potential issues related to memory management.

﻿/******************************************************************************/
/*4. Why is it erroneous to compare two struct variables using memcmp() ?
    Note: Write a function that compares member by member instead.*/
/******************************************************************************/
  
Using `memcmp()` to compare two struct variables is considered erroneous because it compares the memory contents of the structs byte by byte, treating them as raw data. This comparison can lead to unexpected and incorrect results, especially when the structs contain padding bytes or when their members are not stored in a contiguous manner due to alignment.

The `memcmp()` function is designed to compare memory blocks and is often used for comparing arrays or binary data. It does not consider the logical structure of the data it compares, which means that it wont be aware of the internal layout of the struct and its members.

To properly compare two struct variables member by member, you should write a custom comparison function that compares each member individually. This allows you to take into account the logical meaning of each member and handle any potential padding and alignment issues.

Heres an example of a custom comparison function for the `Point` struct from the previous example:

#include <stdio.h>
#include <stdbool.h>

struct Point
{
    int x;
    int y;
};

// Custom function to compare two Point structs member by member
bool comparePoints(const struct Point *p1, const struct Point *p2)
{
    if (p1->x == p2->x && p1->y == p2->y) {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    struct Point point1 = {2, 3};
    struct Point point2 = {2, 3};
    struct Point point3 = {4, 5};

    // Using the custom function to compare points
    if (comparePoints(&point1, &point2))
    {
        printf("point1 and point2 are equal.\n");
    } else {
        printf("point1 and point2 are not equal.\n");
    }

    if (comparePoints(&point1, &point3))
    {
        printf("point1 and point3 are equal.\n");
    } else {
        printf("point1 and point3 are not equal.\n");
    }
    return 0;
}

Output:
point1 and point2 are equal.
point1 and point3 are not equal.

﻿/******************************************************************************/
/*5. It is legal to send a struct by value in C,
but we don't usually do it. Why? When would we do this? */
/******************************************************************************/

Sending a struct by value in C is legal, and it means passing a copy of the entire struct to a function or returning it from a function. However, it is generally not recommended for several reasons:

1. Performance Overhead: Structs can be large, especially if they contain a lot of data. Passing them by value involves copying the entire struct, which can be inefficient and lead to performance overhead, particularly for large structs.

2. Memory Usage: Copying a struct by value consumes additional memory since it duplicates the data. If structs are large and frequently passed by value, it can quickly increase memory usage.

3. Side Effects: When you pass a struct by value, any modifications made to the copy within the function will not affect the original struct passed from the calling code. This can lead to unexpected behavior if the caller expects the modifications to be reflected in the original struct.

4. Function Call Overhead: Passing structs by value involves pushing the entire struct on the stack or using additional registers for the function call. This overhead can be more significant than passing a pointer to the struct.

When would we do this?
There are cases where it might be appropriate or necessary to pass a struct by value:

1. Small Structs: If the struct is small and contains only a few members, passing it by value might not have a significant performance impact.

2. Immutability: If you want to ensure that the original struct remains unchanged, passing by value provides a guarantee that the function cannot modify the original data.

3. Clarity and Simplicity: In some cases, passing a struct by value can make the code cleaner and more straightforward, especially if the function does not need to modify the struct and only uses it for read-only purposes.

In general, for larger structs or cases where the function needs to modify the structs content, it is recommended to pass structs by reference (using pointers) to avoid the overhead of copying and ensure changes are reflected in the original struct. Pointers allow direct access to the original data without copying, making them more efficient for larger data structures.

﻿/******************************************************************************/
/* 6. What will the following code print? */
/******************************************************************************/
struct point
{
    int x;
    int y;
};

int main(void)
{
    struct point p = {1, 2};
    int n = *(int *)&p;
    printf("%d", n);
    return 0;
}

n takes a pointer to the struct point variable p, casts it to a pointer to an int (int*), and then dereferences that pointer. Essentially, it tries to interpret the memory layout of the struct point as if it were an int. This can lead to undefined behavior because it violates strict aliasing rules.

Strict aliasing is a rule in C that says you should not access an object through a pointer of a different type. Doing so can result in unpredictable behavior because the compiler may make assumptions about the type of data being accessed and perform optimizations accordingly.

The result of the program is not predictable, and it may vary depending on the platform, compiler, and optimization settings. In my case it printed "1", may also print  some garbage value, or even crash with a segmentation fault. 

﻿/******************************************************************************/
/*7. How do you write a typedef to a function pointer? */
/******************************************************************************/
  
 To create a `typedef` for a function pointer in C, you can use the following syntax:

typedef return_type (*function_ptr_name)(parameter_type1, parameter_type2, ...);

Heres a breakdown of each part:

- `return_type`: The return type of the function.
- `function_ptr_name`: The name you want to give to the function pointer type.
- `parameter_type1`, `parameter_type2`, etc.: The types of parameters that the function takes. If the function does not take any parameters, leave this part empty.

Heres an example of how to use `typedef` to create a function pointer type:

#include <stdio.h>

// Function prototype
int add(int a, int b);

// Define the function pointer type using typedef
typedef int (*add_function_ptr)(int, int);

int main()
{
    add_function_ptr my_function_ptr;  // Declare a function pointer variable
    // Point the function pointer to the 'add' function
    my_function_ptr = add;
    // Call the function using the function pointer
    int result = my_function_ptr(5, 3);
    printf("Result: %d\n", result);
    return 0;
}

// Definition of the 'add' function
int add(int a, int b)
{
    return a + b;
}

  
﻿/******************************************************************************/
/*8. How to declare a struct & variable of that type with a single semicolon?*/
/******************************************************************************/

Designated initializers, a C99 feature, are supported for aggregate types, including arrays, structures, and unions. A designated initializer, or designator, points out a particular element to be initialized. A designator list is a comma-separated list of one or more designators. A designator list followed by an equal sign constitutes a designation.
Designated initializers allow for the following flexibility:

    Elements within an aggregate can be initialized in any order.
    The initializer list can omit elements that are declared anywhere in the aggregate, rather than only at the end. Elements that are omitted are initialized as if they are static objects: arithmetic types are initialized to 0; pointers are initialized to NULL.
    Where inconsistent or incomplete bracketing of initializers for multi-dimensional arrays or nested aggregates may be difficult to understand, designators can more clearly identify the element or member to be initialized.


Designator list syntax for arrays
Read syntax diagramSkip visual syntax diagram{
,[array subscript]=expression}
In the following example, the designator is .any_member and the designated initializer is .any_member = 13:

union { /* … */ } caw = { .any_member = 13 };

The following example shows how the second and third members b and c of structure variable klm are initialized with designated initializers:

struct xyz {
       int a;
       int b;
       int c;
       } klm = { .a = 99, .c = 100 };

struct point p = { .y = 2, .x = 3 };
struct point p = { y: 2, x: 3 };
 
﻿/******************************************************************************/
/*9. Compile the following program: gcc -c try.c, and use nm to investigate the different memory segments of the program.*/
/******************************************************************************/

#include <stdlib.h>
int g1;
static int g2;
static int g3 = 0;
static int g4 = 8;

static void foo1()
{
    static int g5;
    int l1 = 9;
}
void foo2()
{
    static int g6 = 0;
    static int g7 = 7;
    void *p = malloc(10);
    free(p); p = 0;
}
extern void bar();

﻿/*********************************** nm prints: *******************************/

1. `0000000000000000 t foo1-`: This line represents a local symbol named `foo1` in the text (code) section. The symbol is not globally accessible outside its compilation unit (file).
2. `0000000000000012 T foo2`: This line represents a global symbol named `foo2` in the text (code) section. The symbol is globally accessible and can be used by other compilation units.
3. `U free`: This line represents an undefined symbol named `free`. It means the code in this file refers to the `free` function, but the actual definition of the `free` function is not found in this file. The definition is expected to be provided by a different object file or library during the linking process.
4. `0000000000000000 B g1`: This line represents an uninitialized global variable named `g1` in the BSS section. The BSS section typically contains uninitialized data.
5. `0000000000000004 b g2`: This line represents an uninitialized local variable named `g2` in the BSS section. As it is a local symbol (lowercase 'b'), it is not accessible outside this compilation unit.
6. `0000000000000008 b g3`: This line represents an uninitialized local variable named `g3` in the BSS section.
7. `0000000000000000 d g4`: This line represents an initialized global variable named `g4` in the data section. The data section contains initialized data.
8. `000000000000000c b g5.2`: This line represents an uninitialized local variable named `g5.2` in the BSS section.
9. `0000000000000010 b g6.0`: This line represents an uninitialized local variable named `g6.0` in the BSS section. Again, t
10. `0000000000000004 d g7.1`: This line represents an initialized global variable named `g7.1` in the data section.
11. `U malloc`: This line represents an undefined symbol named `malloc`. It means the code in this file refers to the `malloc` function, but the actual definition of the `malloc` function is not found in this file. The definition is expected to be provided by a different object file or library during the linking process.

In summary, the provided snippet shows various symbols (functions and variables) in different sections of the object file. The 'T' and 't' symbols are for code (text) section, 'B' and 'b' symbols are for BSS section, and 'd' symbols are for data section. The 'U' symbols indicate undefined symbols, which need to be resolved during the linking phase.

﻿/******************************************************************************/
/*********************After Exercises - Additional Questions*******************/
/******************************************************************************/

﻿/******************************************************************************/
/*1. In the exercise, how would using a union make the code cleaner? Write the union and struct you would use.*/
/******************************************************************************/
    struct element
    {
        void* data;
        element_funcs_ty* funcs;
    };

    will be ported into:

    struct element
    {
        data_ty data;
        element_funcs_ty* funcs;
    };
    
    using:
    
    union data
    {
        int i;             
        float f;            
        char* c;            
    }data_ty;


int main()
{
    
    element.data.i = 42;
    printf("Value as int: %d\n", element.data.i);

    element.data.f = 3.14f;
    printf("Value as float: %f\n", element.data.f);

    *(element.data.c) = 'A';
    printf("Value as char: %c\n", *(element.data.c));

    /* Since all members share the same memory,
    the value of intValue is now overwritten by char c*/

    return 0;
}

﻿/******************************************************************************/
/*2. In general, when would you use a struct? A union?*/
/******************************************************************************/

A struct will be used in order to program with object-oriented-approach and submit cleaner and clearer code, in general.
a union will be used in cases when multiple datatypes are involved in our application and, our solution allows to store one over the other with no danger of overwriting.
it makes a simpler solution for mixed types storing.


﻿/******************************************************************************/
/*3. What are the sizes of the following? (First calculate on paper without a computer, then try on your computer and make sure you understand the results.)*/
/******************************************************************************/
#include <stdio.h>

 int main()
 {
   union numbers
    {
        int i;              /*4 bytes */
        float f;            /*4 bytes */
        double d;           /*8 bytes */
    }n_ty;
    /* max member size: 8* bytes */

    struct X
    {
        int i;             /*4 bytes */
        char c;            /*1 bytes */
        double d;          /*8 bytes */
        short s;           /*2 bytes */

    }x_ty;
    /* possible sizes: 8 words *4 members = 32 
    or optimized: [4,1],[8],[2] =3*8=24 */

    struct card
    {
        unsigned int suit : 2;
        unsigned int face : 4;
    }c_ty;
    /* possible sizes: 1 byte each (total 2) or 1 shared byte. */


    printf("Size of union numbers: %ld\n", sizeof(union numbers));
    printf("Size of struct X: %ld\n", sizeof(struct X));
    printf("Size of struct card: %ld\n", sizeof(struct card));
    return 0;
}

/* real output:
Size of union numbers: 8
Size of struct X: 24 (possible optimization)
Size of struct card: 4 ???
*/

/* Bit-fields RULES
#

    Arrays of bit-fields, pointers to bit-fields and functions returning bit-fields are not allowed.
    The address operator (&) cannot be applied to bit-field members.
    The data type of a bit-field must be wide enough to contain the size of the field.
    The sizeof() operator cannot be applied to a bit-field.
    There is no way to create a typedef for a bit-field in isolation (though you can certainly create a typedef for a structure containing bit-fields).

typedef struct mybitfield
{
    unsigned char c1 : 20;    incorrect, see point 3 
    unsigned char c2 : 4;     correct 
    unsigned char c3 : 1;
    unsigned int x[10]: 5;    incorrect, see point 1 
} A;

int SomeFunction(void)
{
    // Somewhere in the code
    A a = { … };
    printf("Address of a.c2 is %p\n", &a.c2);       incorrect, see point 2 
    printf("Size of a.c2 is %zu\n", sizeof(a.c2));  incorrect, see point 4 
}
*/