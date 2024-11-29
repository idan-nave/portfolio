#include <stdio.h>

typedef unsigned char U_CHAR_TY;
typedef int(*plus_one_func_ptr)(int, U_CHAR_TY);

int PlusOne (int num, U_CHAR_TY ch);

int main(int argc, int*argv[], int*envp)
{
    plus_one_func_ptr p_o_no_amprecent = PlusOne;
    plus_one_func_ptr p_o_with_amprecent = &PlusOne;
     
    /* int a = *p_o1(1,'a');*/
    /*int b = *p_o2(1,'a');*/

    
    printf("Printing addresses when calling without amprecent:\n");
    int var_with_deref = (*p_o_no_amprecent)(1,'a');
    int var_without_deref = p_o_no_amprecent(1,'a');
    
    printf("Returned Value is %d, Addr of PlusOne"
    "without amprecent and with deref is: %p\n",
    var_with_deref, p_o_no_amprecent);
    
    printf("Returned Value is %d, Addr of PlusOne"
    "without amprecent and with deref is: %p\n", var_with_deref);
    "%p\n", var_without_deref);
    
    return 0;
}

int PlusOne (int num, U_CHAR_TY ch)
{
   return num+1 ;
  
}
