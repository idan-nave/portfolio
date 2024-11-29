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
