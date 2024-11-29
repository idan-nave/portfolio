#include <stdio.h>

 int main()
 {
   union numbers
    {
        int i;              /*4 bytes */
        short f;            /*2 bytes */
        char a[7];          /*7 bytes -> max member size: 8 */
    }n_ty;

    struct X
    {
        int *i;             /*8 bytes */
        char c;             /*1 bytes */
        short s;            /*2 bytes */
        int *j;             /*8 bytes */
                    /*total: 8*3 = 24 bytes */
    }x_ty;

    struct card
    {
        unsigned int i : 2;         /* 4 bytes occupied*/
        unsigned char c : 1;        /* uses i space */
        unsigned short s : 3;       /* uses i space */
        int *j ;                    /* not considered */
        unsigned char x : 2;        /* uses i space */
                                    /*total: 4 bytes */
    }c_ty;


    printf("Size of union numbers: %ld\n", sizeof(union numbers));
    printf("Size of struct X: %ld\n", sizeof(struct X));
    printf("Size of struct card: %ld\n", sizeof(struct card));
    return 0;
}

/* real output:
Size of union numbers: 8
Size of struct X: 24
Size of struct card: 4
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