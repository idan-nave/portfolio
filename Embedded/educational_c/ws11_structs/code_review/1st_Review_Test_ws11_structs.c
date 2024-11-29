/******************************* Test_ws11_structs.c  *************************/
/*
  Name: HRD 32
  Project: Work Sheet #11 - Structs
  Reviewer: Uri
  Date: 31/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/

#include "ws11_structs.h"       /* For team's API               */
#include "Test_ws11_structs.h"  /* For team's API               */

/************************************** Main **********************************/

int main()
{  
    /*  int argc, char *argv[], char *envp - UNUSED */
    return MultiTypeArrApp();
}


/*********************************** App Manual ********************************
1. Write a program that creates an array of elements, prints them to the screen,
and can add to each element.

a. The elements may be of type int, float or string, all residing together in
the same array. In the future, more types may be added. 30/7/2023

b. add always adds an int value. Normal addition for int and float. For string,
it should do concatenation.For example, if the array contains the following
elements in the following order: 4.2, 6.7, "chapter", 12, 56.32, then 10 is
added to each element (by looping through the array), and the elements are then
printed by looping through the array again, the result would be as follows:
14.2, 16.7, chapter10, 22, 66.32 (probably with 6 places after the decimal
point, in the floating points).

c. Implement a cleanup function for each type.
Note: Not all types that are stored in the array require cleanup, but future types may.

2. Print the array and then add an int. Now print the array again to see the result.

3. When finished working with the array, loop over it one more time and execute the cleanup function of each element to free resources.
*******************************************************************************/
