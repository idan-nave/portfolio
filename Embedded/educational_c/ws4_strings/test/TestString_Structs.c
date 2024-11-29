/*************************** TestStrings.C META  ******************************/
/*
  Name: HRD 32
  Project: String Function Re-implementation
  Reviewer: Liel
  Date: 04/07/2023
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation and deallocation */
#include <TestString.h>  	/* For test fuctions & structs */
#include <string.h>   		/* For comparison testing */

#include "String.h" 		/* For team's API*/
#include "TestString.h" 	/* For team's API*/

/* #define NDEBUG               Define NDEBUG to disable assertions */
/* Custom implementation of assert that logs the
failed assertion and continues program execution */
#define assert_continue(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", \
                    #expr, __FILE__, __LINE__); \
            abort(); \
        } \
    } while (0)

#define EOS '\0'		/* For end of strings


/************************ TEST CASE STRUCT DEFINE  ****************************/

/* Structure for test cases */
typedef struct
{
    const char* desc; /* Special case description */
    const char* source;
    const char* expected;
    const int num;
} TestCase;

/************************** AUXILARY FUNCTIONS  *******************************/

/* Function to count the number of test cases in a test case structure */
int CountTestCases(TestCase* testCases)
{
    int count = 0;
    while (testCases[count].desc != NULL)
    {
        ++count;
    }
    return count;
}

/********************************** GLOBALS ***********************************/

/* Count test cases for strlen */
static int cnt_testCasesStrLen;
/* Count test cases for strcpy */
static int cnt_testCasesStrCpy;
/* Count test cases for strncpy */
static int cnt_testCasesStrnCpy;
/* Count test cases for strcmp */
static int cnt_testCasesStrCmp;
/* Count test cases for strncmp */
static int cnt_testCasesStrnCmp;
/* Count test cases for strcasecmp */
static int cnt_testCasesStrCaseCmp;
/* Count test cases for strchr */
static int cnt_testCasesStrChr;
/* Count test cases for strdup */
static int cnt_testCasesStrDup;
/* Count test cases for strcat */
static int cnt_testCasesStrCat;
/* Count test cases for strncat */
static int cnt_testCasesStrnCat;
/* Count test cases for strstr */
static int cnt_testCasesStrStr;
/* Count test cases for strspn */
static int cnt_testCasesStrSpn;


/***************************** TEST CASES MEMBERS  ****************************/

/* Test cases array for strlen */
static TestCase testCases_StrLen[] = {
    /* Test 1: Normal case */
    {"Normal case", "Infinity HRD32", "", 14},
    
    /* Test 2: Empty string */
    {"Empty string", "",  "", 0},
    
    /* Test 3: Null source string */
    /*{"Null source string", NULL, "", 0}*/
};

/* Test cases array for StrCpy */
static TestCase testCases_StrCpy[] = {
    /* Test 1: Normal case */
    {"Normal case", "Infinity HRD32", "Infinity HRD32", 0},
    
    /* Test 2: Empty string */
    {"Empty string", "", "", 0},
    
    /* Test 3: Null source string */
    {"Null source string", NULL, "", 0}
};

/* Test cases array for StrnCpy */
static TestCase testCases_StrnCpy[] = {
    /* Test 1: Limited length copy */
    {"Limited length copy", "Infinity HRD32", "Infin", 5},
    
    /* Test 2: Copy entire string */
    {"Copy entire string", "Infinity HRD32", "Infinity HRD32", 20},
    
    /* Test 3: Zero-length copy */
    {"Zero-length copy", "Infinity HRD32", "Infin", 0}
};

/* Test cases array for strcmp */
static TestCase testCases_StrCmp[] = {
    /* Test 1: Strings are equal */
    {"Strings are equal", "Hello", "Hello", (int)('o'-'o')},
    
    /* Test 2: First string is less than the second */
    {"First string is less than the second", "Apple", "Banana", (int)('A'-'B')},
    
    /* Test 3: First string is greater than the second */
    {"First string is greater than the second", "Grapes", "Apple", (int)('G'-'A')},
    
    /* Test 4: First string is less and equal */
    {"First string is greater than the second", "Grape", "Grapes", (int)('\0'-'S')},
    
    /* Test 5: First string is greater and equal */
    {"First string is greater than the second", "Grapes", "Grape", (int)('S'- '\0')}
};

/* Test cases array for StrnCmp */
static TestCase testCases_StrnCmp[] = {
    /* Test 1: Limited length comparison */
    {"Limited length comparison", "Infinity HRD32", "Infin", 5},
    
    /* Test 2: Full string comparison */
    {"Full string comparison", "Infinity HRD32", "Infinity HRD32", 20},
    
    /* Test 3: Partial string comparison */
    {"Partial string comparison", "Infinity HRD32", "Infinity HRD32", 12}
};

/* Test cases array for StrCaseCmp */
static TestCase testCases_StrCaseCmp[] = {
    /* Test 1: Case-insensitive comparison */
    {"Case-insensitive comparison", "Infinity HRD32", "infinity hrd32", 0},
    
    /* Test 2: Case-sensitive comparison */
    {"Case-sensitive comparison", "Infinity HRD32", "Infinity HRD32", 0},
    
    /* Test 3: Partial string comparison */
    {"Partial string comparison", "Infinity HRD32", "Infin", 0}
};

/* Test cases array for StrChr */
static TestCase testCases_StrChr[] = {
    /* Test 1: Character found */
    {"Character found", "Infinity HRD32", (char*)'i', 0},
    
    /* Test 2: Character not found */
    {"Character not found", "Infinity HRD32", (char*)'z', 0},
    
    /* Test 3: Character not found */
    {"Character not found", "Infinity HRD32", (char*)'y', 0}
};

/* Test cases array for StrDup */
static TestCase testCases_StrDup[] = {
    /* Test 1: Normal case */
    {"Normal case", "Infinity HRD32", "Infinity HRD32", 0},
    
    /* Test 2: Empty string */
    {"Empty string", "", "", 0},
    
    /* Test 3: Null source string */
    {"Null source string", NULL, "", 0}
};

/* Test cases array for StrCat */
static TestCase testCases_StrCat[] = {
    /* Test 1: Concatenation */
    {"Concatenation", "Infinity ", "HRD32", 0},
    
    /* Test 2: Empty strings */
    {"Empty strings", "", "", 0},
    
    /* Test 3: Null source string */
    {"Null source string", NULL, "", 0}
};

/* Test cases array for StrnCat */
static TestCase testCases_StrnCat[] = {
    /* Test 1: Limited length concatenation */
    {"Limited length concatenation", "Infinity ", "HRD32", 5},
    
    /* Test 2: Empty strings */
    {"Empty strings", "", "", 10},
    
    /* Test 3: Null source string */
    {"Null source string", NULL, "", 5}
};

/* Test cases array for StrStr */
static TestCase testCases_StrStr[] = {
    /* Test 1: Normal case */
    {"Hello, World!", "Hello", "Hello, World!", 0},

    /* Test 2: String not found */
    {"Hello, World!", "Goodbye", NULL, 0},

    /* Test 3: Empty string */
    {"", "", "", 0},

    /* Test 4: Null source string */
    {NULL, "Hello", NULL, 0},

    /* Test 5: Null substring */
    {"Hello, World!", NULL, NULL, 0}
};

/* Test cases array for StrSpn */
static TestCase testCases_StrSpn[] = {
    /* Test 1: Normal case */
    {"Hello, World!", "Helo", (char*)NULL, 4},

    /* Test 2: No matching characters */
    {"Hello, World!", "abc", (char*)NULL, 0},

    /* Test 3: Empty string */
    {"", "abc", (char*)NULL, 0},

    /* Test 4: Null source string */
    {NULL, "abc", (char*)NULL, 0},

    /* Test 5: Null accept string */
    {"Hello, World!", NULL, (char*)NULL, 0}
};



/********************************** MAIN **************************************/

int main()
{

/********************************** GLOBALS ***********************************/

    /* Count test cases for strlen */
    cnt_testCasesStrLen = CountTestCases(testCases_StrLen);
    /* Count test cases for strcpy */
    cnt_testCasesStrCpy = CountTestCases(testCases_StrCpy);
    /* Count test cases for strncpy */
    cnt_testCasesStrnCpy = CountTestCases(testCases_StrnCpy);
    /* Count test cases for strcmp */
    cnt_testCasesStrCmp = CountTestCases(testCases_StrCmp);
    /* Count test cases for strncmp */
    cnt_testCasesStrnCmp = CountTestCases(testCases_StrnCmp);
    /* Count test cases for strcasecmp */
    cnt_testCasesStrCaseCmp = CountTestCases(testCases_StrCaseCmp);
    /* Count test cases for strchr */
    cnt_testCasesStrChr = CountTestCases(testCases_StrChr);
    /* Count test cases for strdup */
    cnt_testCasesStrDup = CountTestCases(testCases_StrDup);
    /* Count test cases for strcat */
    cnt_testCasesStrCat = CountTestCases(testCases_StrCat);
    /* Count test cases for strncat */
    cnt_testCasesStrnCat = CountTestCases(testCases_StrnCat);
    /* Count test cases for strstr */
    cnt_testCasesStrStr = CountTestCases(testCases_StrStr);
    /* Count test cases for strspn */
    cnt_testCasesStrSpn = CountTestCases(testCases_StrSpn);

/********************************** CODE **************************************/ 

    int totalPassedTests = 0;
    int totalFailedTests = 0;

    printf("Running String Function Tests\n");
    printf("=============================\n");

    printf("Testing StrLen...\n");
    int passedTestsStrLen = TestStrLen();
    totalPassedTests += passedTestsStrLen;
    totalFailedTests += (cnt_testCasesStrLen - passedTestsStrLen);
    printf("Passed: %d/%d\n", passedTestsStrLen, cnt_testCasesStrLen);

    printf("Testing StrCpy...\n");
    int passedTestsStrCpy = TestStrCpy();
    totalPassedTests += passedTestsStrCpy;
    totalFailedTests += (cnt_testCasesStrCpy - passedTestsStrCpy);
    printf("Passed: %d/%d\n", passedTestsStrCpy, cnt_testCasesStrCpy);
/*
    printf("Testing StrnCpy...\n");
    int passedTestsStrnCpy = TestStrnCpy();
    totalPassedTests += passedTestsStrnCpy;
    totalFailedTests += (cnt_testCasesStrnCpy - passedTestsStrnCpy);
    printf("Passed: %d/%d\n", passedTestsStrnCpy, cnt_testCasesStrnCpy);

    printf("Testing StrCmp...\n");
    int passedTestsStrCmp = TestStrCmp();
    totalPassedTests += passedTestsStrCmp;
    totalFailedTests += (cnt_testCasesStrCmp - passedTestsStrCmp);
    printf("Passed: %d/%d\n", passedTestsStrCmp, cnt_testCasesStrCmp);

    printf("Testing StrnCmp...\n");
    int passedTestsStrnCmp = TestStrnCmp();
    totalPassedTests += passedTestsStrnCmp;
    totalFailedTests += (cnt_testCasesStrnCmp - passedTestsStrnCmp);
    printf("Passed: %d/%d\n", passedTestsStrnCmp, cnt_testCasesStrnCmp);

    printf("Testing StrCaseCmp...\n");
    int passedTestsStrCaseCmp = TestStrCaseCmp();
    totalPassedTests += passedTestsStrCaseCmp;
    totalFailedTests += (cnt_testCasesStrCaseCmp - passedTestsStrCaseCmp);
    printf("Passed: %d/%d\n", passedTestsStrCaseCmp, cnt_testCasesStrCaseCmp);

    printf("Testing StrChr...\n");
    int passedTestsStrChr = TestStrChr();
    totalPassedTests += passedTestsStrChr;
    totalFailedTests += (cnt_testCasesStrChr - passedTestsStrChr);
    printf("Passed: %d/%d\n", passedTestsStrChr, cnt_testCasesStrChr);

    printf("Testing StrDup...\n");
    int passedTestsStrDup = TestStrDup();
    totalPassedTests += passedTestsStrDup;
    totalFailedTests += (cnt_testCasesStrDup - passedTestsStrDup);
    printf("Passed: %d/%d\n", passedTestsStrDup, cnt_testCasesStrDup);

    printf("Testing StrCat...\n");
    int passedTestsStrCat = TestStrCat();
    totalPassedTests += passedTestsStrCat;
    totalFailedTests += (cnt_testCasesStrCat - passedTestsStrCat);
    printf("Passed: %d/%d\n", passedTestsStrCat, cnt_testCasesStrCat);

    printf("Testing StrnCat...\n");
    int passedTestsStrnCat = TestStrnCat();
    totalPassedTests += passedTestsStrnCat;
    totalFailedTests += (cnt_testCasesStrnCat - passedTestsStrnCat);
    printf("Passed: %d/%d\n", passedTestsStrnCat, cnt_testCasesStrnCat);

    printf("Testing StrStr...\n");
    int passedTestsStrStr = TestStrStr();
    totalPassedTests += passedTestsStrStr;
    totalFailedTests += (cnt_testCasesStrStr - passedTestsStrStr);
    printf("Passed: %d/%d\n", passedTestsStrStr, cnt_testCasesStrStr);

    printf("Testing StrSpn...\n");
    int passedTestsStrSpn = TestStrSpn();
    totalPassedTests += passedTestsStrSpn;
    totalFailedTests += (cnt_testCasesStrSpn - passedTestsStrSpn);
    printf("Passed: %d/%d\n", passedTestsStrSpn, cnt_testCasesStrSpn);

*/
    printf("End of Tests\n");
    printf("=============================\n");
    printf("Total %d out of %d Passed\n", totalPassedTests, totalFailedTests+totalFailedTests);

}

/******************** TESTING API IMPLEMENTATIONS  ****************************/

/* Test function for StrLen */
int TestStrLen()
{

    int failedTests = 0;
    int i = 0;
    for (; i < cnt_testCasesStrLen; i++)
    {
        const char* source = testCases_StrLen[i].source;
        const char* expected = testCases_StrLen[i].expected;

        /* Calculate length using the tested function */
        size_t result = StrLen(source);

        /* Compare the result with the expected value */
        if (result != testCases_StrLen[i].num)
        {
            printf("Test %d failed: Expected length %s, got %zu\n", i + 1, expected, result);
            failedTests++;
        }
    }

    if (failedTests == 0)
    {
        printf("All tests passed for StrLen\n");
    }

    return failedTests;
}

/* Test function for StrCpy */
int TestStrCpy()
{
    int failedTests = 0;
    int i = 0;
    for (; i < (int)cnt_testCasesStrCpy; i++) 
    {
        const char* source = testCases_StrCpy[i].source;
        const char* expected = testCases_StrCpy[i].expected;
        
        /* Allocate memory for destination string */
        char* destination = (char*)malloc((strlen(source) + 1) * sizeof(char));
        if (destination == NULL)
        {
            printf("Memory allocation failed for test case %d\n", i + 1);
            failedTests++;
            return failedTests;
        }
        
        /* Copy using the tested function */
        StrCpy(destination, source);
        
        /* Compare the results */
        if (strcmp(destination, expected) != 0) /* 0 is success */
        {
            printf("Test case %d failed: %s\n", i + 1, testCases_StrCpy[i].desc);
            failedTests++;
        }
        
        /* Free memory */
        free(destination);
        destination = NULL;
    }
    
    /* Return the number of failed tests */	
    return failedTests;
}

/* Test function for StrncCy */
int TestStrnCpy()
{
    int failedTests = 0;
    int i = 0;
    for (; i < (int)cnt_testCasesStrLen; i++)
    {
        const char* source = testCases_StrnCpy[i].source;
        const char* expected = testCases_StrnCpy[i].expected;
        int maxLength = testCases_StrnCpy[i].num;

        char* myDestination = (char*)malloc((maxLength + 1) * sizeof(char));
        strncpy(myDestination, source, maxLength);
        myDestination[maxLength] = EOS;  /* Ensure null-termination */

        if (strcmp(myDestination, expected) != 0)
        {
            printf("Test %d failed: Expected '%s', but got '%s'\n", i + 1, expected, myDestination);
            failedTests++;
        }

        free(myDestination);
    }

    return failedTests;
}

