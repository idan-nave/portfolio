/***************************** Test_ws9_bitwise.c  ****************************/
/*
  Name: HRD 32
  Project: Work Sheet #9 - BitWise
  Reviewer: Sahar Attia **APPROVED**
  Date: 23/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* For input validation */
#include <math.h> 		/* For arithmetics */
#include <stddef.h>  		/* For size_t type*/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation */
#include <string.h>             /* For string manipulation */

#include "ws9_bitwise.h" 		/* API*/
#include "Test_ws9_bitwise.h" 		/* API Testing*/


/********************************** TypeDefs  *********************************/

/************************************** Main **********************************/

int main(int argc, char *argv[], char *envp)
{   
    /* Run tests using CLN UI implemented in UI_ws9_bitwise.c*/
    setvbuf(stdout, NULL, _IONBF, 0);
    GreetUser();
    return 0;
}

/* Test function to validate Test_MultXByPow2() */
int Test_MultXByPow2()
{ 
    printf("Testing MultXByPow2:\n");  
    /* test matrix- every row contains x,y,result to validate */
    int tst_arr[3][2] = { {2,2}, {-5,5}, {8,6} };
    size_t i = 0;       /* runner for row */
    size_t fails = 0;   /* counter for fails */
    int result = 0;     /* var to hold computation by arithmetics */
    int tested = 0;     /* var to hold computation by tested func */
    
    while(i < 3)
    {
       result = tst_arr[i][0] * pow( 2, tst_arr[i][1] );
       tested = MultXByPow2(tst_arr[i][0], tst_arr[i][1]);
       if(result == tested)
       {
          printf("Test #%ld Pass: %d*2^%d=%d\n", i,
          tst_arr[i][0], tst_arr[i][1], result);  
       }
       else
       {
          printf("Test #%ld Failed: %d*2^%d=%d, !=%d\n",
          i, tst_arr[i][0], tst_arr[i][1], tested, result);  
          ++fails;
       }
       ++i;
    }
    return fails;
}

/* Test function to validate MultXByPow2() */
int Test_CountOnes()
{ 
    printf("Testing CountOnes:\n");  
    /* test matrix- every row contains x,num of bits to validate */
    unsigned int tst_arr[5][2] = {
    {0x0A, 2}, /* Hexadecimal for 10 */
    {0x14, 2}, /* Hexadecimal for 20 */
    {0x1E, 4}, /* Hexadecimal for 30 */
    {0x28, 2}, /* Hexadecimal for 40 */
    {0x32, 3}  /* Hexadecimal for 50 */};
    
    size_t i = 0;       /* Runner for row */
    size_t fails = 0;   /* Counter for fails */
    size_t result = 0;  /* Variable to hold computation by arithmetics */
    size_t tested = 0;  /* Variable to hold computation by tested func */

    while (i < 5)
    {
        result = tst_arr[i][1];
        tested = CountOnes(tst_arr[i][0]);

        if (result == tested)
        {
            printf("Test #%ld Pass: (%d) ", i, tst_arr[i][0]);
            PrintBinary(tst_arr[i][0], 8);
            printf(" has %ld ones\n", tested);
        }
        else
        {
            printf("Test #%ld Failed: (%d) ", i, tst_arr[i][0]);
            PrintBinary(tst_arr[i][0], 8);
            printf(" has %ld ones, != %ld\n", result, tested);
            ++fails;
        }
        ++i;
    }
    return fails;
}

/* Test function to validate IsPowerOf2Loop() && IsPowerOf2Simple() */
int Test_IsPowerOf2()
{ 
    printf("Testing Test_IsPowerOf2:\n");  
    /* test matrix- every row contains num to validate ,2 (pow) */
    int tst_arr[5][2] = { {10,2}, {64,2}, {-5,2}, {130,2}, {32,2} };
    size_t i = 0;         /* runner for row */
    size_t fails = 0;     /* counter for fails */
    double sqrtValue = 0; /* testing sqrt of num */
    int intSqrtValue = 0; /* testing sqrt of num */
    size_t result = 0;       /* var to hold bool by arithmetics */
    size_t tested1 = 0;       /* var to hold bool by tested func */
    size_t tested2 = 0;       /* var to hold bool by tested func */
    
    while(i < 5)
    {
       result = IsPowerOf2Arth(tst_arr[i][0]);
       tested1 = IsPowerOf2Loop(tst_arr[i][0]);
       tested2 = IsPowerOf2Simple(tst_arr[i][0]);
       if(result == tested1 && result == tested2)
       {
          if(result) printf("Test #%ld Pass: %d is pow of 2\n", i, tst_arr[i][0]);
          else printf("Test #%ld Pass: %d is not pow of 2\n", i, tst_arr[i][0]);
       }
       else
       {
          if(result) printf("Test #%ld Failed: %d is pow of 2,"
          "func1 says: %ld, func2 says: %ld\n", i, tst_arr[i][0], tested1, tested2);
          else printf("Test #%ld Failed: %d is not a pow of 2,"
          "func1 says: %ld, func2 says: %ld\n", i, tst_arr[i][0], tested1, tested2);
          ++fails;
       }
       ++i;
    }
    return fails;
}

/* Test function to validate Add1ToIntBitWise() */
int Test_Add1ToIntBitWise()
{ 
    printf("Testing Add1ToIntBitWise:\n");  
    /* test matrix- every row contains x,x+1 */
    int tst_arr[5][2] = { {10,11}, {-64,-63}, {-5,-4}, {130,131}, {32,33} };
    
    size_t i = 0;       /* Runner for row */
    size_t fails = 0;   /* Counter for fails */
    int result = 0;  /* Variable to hold computation by arithmetics */
    int tested = 0;  /* Variable to hold computation by tested func */

    while (i < 5)
    {
        result = tst_arr[i][1];
        tested = Add1ToIntBitWise(tst_arr[i][0]);
        if(result == tested)
        {
          printf("Test #%ld Pass: %d+1=%d\n", i,
          tst_arr[i][0], result);  
        }
        else
        {
          printf("Test #%ld Failed: %d+1=%d, !=%d\n",
          i, tst_arr[i][0], result, tested);  
          ++fails;
        }
        ++i;
    }
    return fails;
}

/* Test function to validate PrintOnly3SetBits() */
int Test_PrintOnly3SetBits()
{ 
    printf("Testing PrintOnly3SetBits:\n");  
    /* test array- every row contains num  */
    unsigned int tst_arr[5] = {
    0x0A, /* Hexadecimal for 10 - 2 ones */
    0x14, /* Hexadecimal for 20 - 2 ones */
    0x1E, /* Hexadecimal for 30 - 4 ones */
    0x28, /* Hexadecimal for 40 - 2 ones */
    0x32  /* Hexadecimal for 50 - 3 ones */};
    
    size_t i = 0;       /* Runner for row */
    size_t fails = 0;   /* Counter for fails */
    size_t result = 0;  /* Variable to hold bool by arithmetics */
    size_t tested = 0;  /* Variable to hold bool by tested func */
     
    tested = PrintOnly3SetBits(tst_arr, 5);
        
    while (i < 5)
    {
        result = CountOnesArth(tst_arr[i]);

        if (result == 3)
        {
             PrintBinary(tst_arr[i], 8);
             printf("(%d) has 3 ones\n", tst_arr[i]);
        }
        ++i;
    }
    return fails;
}

/* Test function to validate ByteMirrorLoop() & ByteMirrorMask() */
int Test_ByteMirror()
{ 
    printf("Testing ByteMirror:\n");  
    /* test matrix- every row contains x,reversed x of bits to validate */
    unsigned char tst_arr[5][2] = {
    {0xE5, 0xA7}, /* 11100101 ,10100111*/
    {0xA3, 0xC5}, /* 10100011 */
    {0x66, 0x66}, /* 01100110 */
    {0xF2, 0x4F}, /* 11110010 */
    {0x3B, 0xDC}  /* 00111011 */};
    
    size_t i = 0;       /* Runner for row */
    size_t fails = 0;   /* Counter for fails */
    unsigned char result = 0;        /* var to hold byte validator */     
    unsigned char tested1 = 0;       /* var to hold byte returned by tested func */
    unsigned char tested2 = 0;       /* var to hold byte returned by tested func */
    
    while(i < 5)
    {
       result = tst_arr[i][1];
       tested1 = ByteMirrorLoop(tst_arr[i][0]);
       tested2 = ByteMirrorMask(tst_arr[i][0]);
       if(result == tested1 && result == tested2)
       {
          printf("\nTest #%ld Pass:", i);
          PrintBinary(result, 8);
          printf(" is mirror of: ");
          PrintBinary(tst_arr[i][0], 8);
       }
       else
       {
          printf("\nTest #%ld Failed: ", i);
          PrintBinary(tested1, 8);
          printf(" , ");
          PrintBinary(tested2, 8);
          printf(" are not mirror of: ");
          PrintBinary(tst_arr[i][0], 8);
          ++fails;
       }
       ++i;
    }
    printf("\n");
    return fails;
}

/* Test function to validate CheckBoth2And6 */
int Test_CheckBoth2And6()
{ 
    printf("Testing CheckBoth2And6:\n");  
    size_t fails = 0;   /* Counter for fails */

    /* Test examples: each row contains the input value */
    unsigned char test_cases[2] = {0xA5, 0x35};
    size_t i = 0;

    while (i < 2)
    {
        unsigned char test_ch = test_cases[i];
        int result_check = CheckBoth2And6(test_ch);
        if (result_check == 0)
        {
            printf("Test Pass: 2nd and 6th bits are not set in ");
            PrintBinary(test_ch, 8);
            printf("\n");
        }
        else
        {
            printf("Test Failed: 2nd and 6th bits are set in ");
            PrintBinary(test_ch, 8);
            printf("\n");
            ++fails;
        }
        ++i;
    }
    return fails;
}

/* Test function to validate CheckOneOf2And6 */
int Test_CheckOneOf2And6()
{ 
    printf("Testing CheckOneOf2And6:\n");  
    size_t fails = 0;   /* Counter for fails */

    /* Test examples: each row contains the input value */
    unsigned char test_cases[2] = {0xA5, 0x35};
    size_t i = 0;

    while (i < sizeof(test_cases)/sizeof(test_cases[0]))
    {
        unsigned char test_ch = test_cases[i];
        int result_check = CheckOneOf2And6(test_ch);
        if (result_check == 1)
        {
            printf("Test Pass: 2nd and 6th bits are set in ");
            PrintBinary(test_ch, 8);
            printf("\n");
        }
        else
        {
            printf("Test Failed: 2nd and 6th bits are not set in ");
            PrintBinary(test_ch, 8);
            printf("\n");
            ++fails;
        }
        ++i;
    }
    return fails;
}

/* Test function to validate Swap3rdAnd5thBits */
int Test_Swap3rdAnd5thBits()
{ 
    printf("Testing Swap3rdAnd5thBits:\n");  
    unsigned char tst_arr[3][2] = {
        {0xA5, 0x95}, /* Binary: 10100101 -> Expected: 10010101 */
        {0x3B, 0x2B}, /* Binary: 00111011 -> Expected: 00101011 */
        {0x90, 0x90}  /* Binary: 10010000 -> Expected: 10010000 */
    };
    
    size_t i = 0;       /* Runner for row */
    size_t fails = 0;   /* Counter for fails */
    unsigned char result = 0;    /* var to hold byte validator */     
    unsigned char tested = 0;    /* var to hold byte returned by tested func */
    
    while(i < 3)
    {
        result = tst_arr[i][1];
        tested = Swap3rdAnd5thBits(tst_arr[i][0]);
        if (result == tested)
        {
            printf("Test Pass: Swapped bits of ");
            PrintBinary(tst_arr[i][0], 8);
            printf(" is ");
            PrintBinary(tested, 8);
            printf("\n");
        }
        else
        {
            printf("Test Failed: Swapped bits of ");
            PrintBinary(tst_arr[i][0], 8);
            printf(" is ");
            PrintBinary(tested, 8);
            printf(", but expected ");
            PrintBinary(result, 8);
            printf("\n");
            ++fails;
        }
        ++i;
    }
    printf("Test_Swap3rdAnd5thBits has %ld fails.\n", fails);
    return fails;
}

/* Test function to validate ClosestDivisibleBy16Arth */
int Test_ClosestDivisibleBy16Bitwise()
{ 
    printf("Testing ClosestDivisibleBy16Bitwise:\n");  
    /* test matrix- every row contains num, expected result */
    unsigned int tst_arr[5][2] = {
        {33, 32}, /* Closest smaller number divisible by 16 is 32 */
        {17, 16}, /* Closest smaller number divisible by 16 is 16 */
        {22, 16}, /* Closest smaller number divisible by 16 is 16 */
        {48, 48}, /* Closest smaller number divisible by 16 is 48 (already divisible) */
        {12, 0}   /* Closest smaller number divisible by 16 is 0 (less than 16) */
    };
    
    size_t i = 0;       /* Runner for row */
    size_t fails = 0;   /* Counter for fails */
    unsigned int result = 0;        /* var to hold result validator */     
    unsigned int tested = 0;        /* var to hold result returned by tested func */
    
    while(i < 5)
    {
       result = tst_arr[i][1];
       tested = ClosestDivisibleBy16Bitwise(tst_arr[i][0]);
       if(result == tested)
       {
          printf("Test #%ld Pass: Closest smaller number divisible"
          " by 16 for %d is %d\n", i, tst_arr[i][0], result);
       }
       else
       {
          printf("Test #%ld Failed: Closest smaller number divisible"
          " by 16 for %d is %d, but expected %d\n",
                 i, tst_arr[i][0], tested, result);
          ++fails;
       }
       ++i;
    }
    printf("\n");
    return fails;
}

/* Function to test SwapWithoutThirdVariable */
void Test_SwapWithoutThirdVariable()
{
    int a = 10;
    int b = 10;

    printf("Before swap: a = %d, b = %d\n", a, b);
    SwapWithoutThirdVariable(&a, &b);
    printf("After swap: a = %d, b = %d\n", a, b);
}

/* Test function to validate both CountSetBitsLoop and CountSetBitsNoLoop */
int Test_CountSetBits()
{
    printf("Testing CountSetBits:\n");  
    /* test matrix- every row contains x,num of bits to validate */
    int tst_arr[5][2] = {
    {-100, 28}, /* Hexadecimal for 10 */
    {-34, 30}, /* Hexadecimal for 20 */
    {67, 3}, /* Hexadecimal for 30 */
    {363, 6}, /* Hexadecimal for 40 */
    {-1, 32}  /* Hexadecimal for 50 */};
    
    size_t i = 0;       /* Runner for row */
    size_t fails = 0;   /* Counter for fails */
    size_t result = 0;  /* Variable to hold computation by arithmetics */
    size_t tested1 = 0;  /* Variable to hold computation by tested func */
    size_t tested2 = 0;  /* Variable to hold computation by tested func */
    
    while (i < 5)
    {
        result = tst_arr[i][1];
        tested1 = CountSetBitsLoop(tst_arr[i][0]);
        tested2 = CountSetBitsNoLoop(tst_arr[i][0]);
        
        if (result == tested1 && result == tested2)
        {
            printf("Test #%ld Pass: (%d) ", i, tst_arr[i][0]);
            PrintBinary(tst_arr[i][0], 8);
            printf(" has %ld ones\n", result);
        }
        else
        {
            printf("Test #%ld Failed: (%d) ", i, tst_arr[i][0]);
            PrintBinary(tst_arr[i][0], 8);
            printf(" has %ld ones, != %ld, != %ld\n", result, tested1, tested2);
            ++fails;
        }
        ++i;
    }
    return fails;
}

/* Function to test the PrintFloatBits function */
void TestPrintFloatBits()
{
    float input;
    printf("Enter a float: ");
    scanf("%f", &input);

    printf("Binary representation of the float: ");
    PrintFloatBits(input);
}

/****************************** Auxiliary Functions ***************************/

/* Function to check if an integer is a power of 2 using arithmetic operations */
int IsPowerOf2Arth(int num)
{
    if (num <= 0)
    {
        return 0; /* Numbers less than or equal to 0 are not powers of 2 */
    }
    while (num % 2 == 0)
    {
        num /= 2;
    }
    /* Return 1 if the result becomes 1, indicating it's a power of 2,
    otherwise return 0 */
    return (num == 1); 
}

/* Function to count ones using arithmetic operations */
size_t CountOnesArth(unsigned int num)
{
    size_t count = 0;
    /* Count the ones using arithmetic operations */
    while (num != 0)
    {
        if (num % 2 == 1)
        {
            ++count;
        }
        num /= 2;
    }
    return count;
}
