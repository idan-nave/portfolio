/*
  Project: Calculator (State Machine Project)
  Reviewer: Ahmad
  Date: 03/10/2023
  Version: 1.0 - Publication

  Project Overview: API for a Calculator based on State Machine
*/
/******************************** Libraries  *********************************/

#include <stdio.h>              /* printf */
#include <stdlib.h>             /* malloc(), free() */
#include <stddef.h>             /* size_t, NULL */
#include <string.h>             /* strcpy */
#include <time.h>               /* clock() */

#include "calc.h"    

/*****************************************************************************/

#define PRINT_RESULT TRUE


int main()
{

    /*Array to map enum values to strings*/
    static const char status_info[4][20] = {"SUCCESS", "FAILURE", "MATH_ERROR", "SYNTAX_ERROR"};

    double res = 0;
    char expression_to_calc[EXP_MAX_LEN] = "1+1";
    int status = 0;


   char *str_arr1[10] = {"","a","abc","abccd","abcde","abcdef","abcdefg","abcdefgsh","abcdefghid","abdcefgzhij"};
   char *str_arr2[10] = {"ddf","","asbc","abcd","abcde","abcdef","abccdefg","abcdefgh","abcdefghis","abdcefgchij"};
   size_t i = 0;
   
   for(; i<10 ; ++i)
   {
      if(StrCmp(str_arr1[i],str_arr2[i]) != strcmp(str_arr1[i],str_arr2[i]))
      {
          printf("wrong comparation on %ld word \n", i);
      }
   }


    strcpy(expression_to_calc, "1+1");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);

    strcpy(expression_to_calc, "10-15");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);

    strcpy(expression_to_calc, "1-1-1");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);

    strcpy(expression_to_calc, "1-1");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);

    strcpy(expression_to_calc, "1+1*3");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);
    
    strcpy(expression_to_calc, "10/5");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);

    strcpy(expression_to_calc, "10/0");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);

    strcpy(expression_to_calc, "(10/5)");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);

    strcpy(expression_to_calc, "1+1*3*5");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);

    strcpy(expression_to_calc, "1+(1*3)");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);


    strcpy(expression_to_calc, "1*5+(2-(1/3))");
    res = Calculate(expression_to_calc, &status);
    printf("%s = %.0f \t Status: %s\n", expression_to_calc, res, status_info[status]);

    return 0;
}

int ValidateCalcResult(char* exp_to_calc, double valid_res, int valid_status)
{
    int status = 0;
    double res = Calculate(exp_to_calc, &status);

    PRINT_RESULT
    if (PRINT_RESULT == TRUE)
    {
      printf("%s = %.0f  ; \t Should be: %.0f;  \t %s\n", exp_to_calc, res, valid_res,status_info[status]);
    }
  

    if (valid_status == status && valid_res == res)
    {
        return SUCCESS;
    }
    return FAILURE;
}