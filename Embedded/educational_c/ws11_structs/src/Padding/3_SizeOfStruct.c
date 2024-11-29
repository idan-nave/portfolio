#include <stdio.h>

/*3. What are the sizes of the following? (First calculate on paper without a 
computer, then try on your computer and make sure you understand the results.)*/

int main()
{
    typedef union data
    {
        int i;             
        float f;            
        char* c;            
    }data_ty;

    typedef struct element
    {
        data_ty data;
    }element_ty;
    
    element_ty.data.i = 42;
    printf("Value as int: %d\n", element_ty.data.i);

    element_ty.data.f = 3.14f;
    printf("Value as float: %f\n", element_ty.data.f);

    *(element_ty.data.c) = 'A';
    printf("Value as char: %c\n", *(element_ty.data.c);

    /* Since all members share the same memory,
    the value of intValue is now overwritten by char c*/

    return 0;
}
