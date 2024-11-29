/***************************** Tst_ArrPtrs.c  **********************************/
/*Name: HRD 32
  Project: WS6 - Array Pointers
  Reviewer: Aya ?
  Date: 13.07.23
  Version: 1.0*/
  
/******************************** LIBRARIES  **********************************/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation and deallocation */

#include "ArrPtrs.h"    	/* APIs Header */
#include "Tst_ArrPtrs.h"        /* API Testing */

#define R 5
#define C 5
#define J 100
/******************************* Main *********************************/

int main(int argc, char *argv[], char *envp[])
{ 
    GenAndPrintMatrixRowSums(R, C);
    const size_t josephus_circle_len = J;
    size_t s = PlayJosephus(josephus_circle_len);
    printf("Last standing soldier in Josephus Circle is #%lu\n",s);
    TestJosephusGame(J, s);
}


/******************************* Definitions *********************************/

/*Function that tests PlayJosephus function, prints result according to formula*/
void TestJosephusGame(size_t circle_size, size_t last_soldier)
{
    int i = 1;
    int l = 0;
    int res = 0;
    int j_formula = 0;

    while ( (i * 2) < circle_size)
    {
        i *= 2; 
    }
    l = circle_size - i;
    j_formula = (2 * l) + 1;
    if(last_soldier = j_formula)  printf("Josephus Game OK\n");
    else  printf("Josephus Game FAIL\n");
}

