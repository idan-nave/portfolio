/*
  Project: Calculator (State Machine Project)
  Reviewer: Ahmad
  Date: 03/10/2023
  Version: 1.0 - Publication

  Project Overview: API for a Calculator based on State Machine
*/

/******************************************************************************/
/******************************** Libraries  **********************************/
/******************************************************************************/
#include <assert.h> /*assert*/
#include <stdlib.h> /*strtod*/
#include <string.h> /*strlen*/
#include <stdio.h>

#include "calc.h"
#include "stack.h"

/******************************************************************************/
/******************************** Definitions  ********************************/
/******************************************************************************/
#define NUM_OF_EXPRESSIONS 16
#define MAX_EXPRESSION_SIZE 50

#define REPORT(expected , result, str) \
  {\
      if (expected != result)\
      {\
        printf("%s has failed\n", str);\
      }\
  }

/*****************************************************************************/
/**************************** Test Functions Declerations ********************/
/*****************************************************************************/
static void CalculateTest();

/*****************************************************************************/
/*************************************** Main ********************************/
/*****************************************************************************/
int main()
{
    CalculateTest();
    return 0;
}

/*****************************************************************************/
/************************* Test Calculator Functions **************************/
/*****************************************************************************/

static void CalculateTest()
{
    int status_info[NUM_OF_EXPRESSIONS] = 
    {SUCCESS, SUCCESS, SUCCESS, SUCCESS, SUCCESS, MATH_ERROR, SUCCESS, SUCCESS, SUCCESS, SUCCESS, SYNTAX_ERROR, SYNTAX_ERROR, SYNTAX_ERROR, SYNTAX_ERROR, SYNTAX_ERROR, SUCCESS};
    
    double results[NUM_OF_EXPRESSIONS] = 
    {2.0, -1.0, 0.0, 4.0, 2.0, 0.0, 2.0, 16.0, 4.0, 16.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.0};
    
    char expressions[NUM_OF_EXPRESSIONS][MAX_EXPRESSION_SIZE] = 
    {"1+1", "1-1-1", "1-1", "1+1*3", "10/5", "10/0", "(10/5)", "1+1*3*5", "1+(1*3)", "1+5*(1*3)", "(8+3", "8+3)", "(8+3))", "2A6t+6", "32+1    -3", "1+(((5)))"};
    
    size_t i = 0;
    int status;
    double res = 0.0;
    char str_result[100] = "result of ";
    char str_status[100] = "status of ";

    while(NUM_OF_EXPRESSIONS > i)
    {
        res = Calculate(expressions[i], &status);

        strcpy(str_result , "result of ");
        strcpy(str_status , "status of ");

        strcat(str_result, expressions[i]);
        strcat(str_status, expressions[i]);
        /* printf("%s is: %0.f\n", str_result, res); */
        REPORT(results[i], res, str_result);
        REPORT(status_info[i], status, str_status);
        ++i;
    }

    printf("Calculator tested!\n");
}