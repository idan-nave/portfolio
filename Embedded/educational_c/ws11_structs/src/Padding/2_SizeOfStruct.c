#include <stdio.h>
#include <string.h>

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
        char a[23];             
        short s;            
        char c;  
    }element_ty;
    
    element_ty my_e;
    
    strcpy(my_e.a, "hello");
    printf("char[23] a in add %p is: %s\n", &my_e.a, my_e.a);

    my_e.s = 1;
    printf("short a in add %p is: %d\n", &my_e.s, my_e.s);

    my_e.c = 'a';
    printf("char a in add %p is: %d\n", &my_e.c, my_e.c);

    /* Since all members share the same memory,
    the value of intValue is now overwritten by char c*/

    return 0;
}
/*
void* temp = realloc(existing_memory, new_size);
if (temp != NULL)
{
    existing_memory = temp;
} else {
    
}*/

