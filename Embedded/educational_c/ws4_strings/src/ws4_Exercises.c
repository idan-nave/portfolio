/*************************** Quizz_2 META  ******************************/
/*
  Name: HRD 32
  Reviewer: Dima
  Date: 13/07/23
  Version: 1.0
  Palindrome
  7-Boom
  Space Review
*/

/******************************** LIBRARIES  **********************************/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation and deallocation */
#include <assert.h> 		/* For input validation */
#include <ctype.h>   		/* For alphabet manipulation */
#include <string.h>   	        /* For memmove */
#include <stddef.h>             /*Using size_t */

#define EOS '\0'		/* For end of strings

/******************************* DECLERATIONS *********************************/

size_t IsPalindrome(char* str);
void Test_IsPalindrome();

void PlaySevenBoom(const int from, const int to);
void Test_PlaySevenBoom();

void TrimAndCompressSpaces();
void Test_TrimAndCompressSpaces();

size_t UserInput(size_t range);

/**************************** DEBUG INFO **************************************/
/* 
  124  ulimit -c unlimited           //  The ulimit setting is used to define user system and process resource limits.
  130  cd /var/lib/apport/coredump
  131  ls
  132  cp core._home_idan_Documents_Dev_Git_WD_a_out.1000.fef690b2-8431-4687-86f2-b88820a83be9.19396.3496566 ~/Documents/Dev/Git_WD/
  133  cdgit
  139  gdb infinite_loop_dump.out core._home_idan_Documents_Dev_Git_WD_a_out.1000.fef690b2-8431-4687-86f2-b88820a83be9.19396.3496566 
       if using gdb, use tty /dev/pts/X for input
*/

/********************************** MAIN **************************************/

int main(int argc, char *argv[], char *envp)
{   
      printf("Hello, the following are the available tests:"
      "\n1.IsPalindrome \n2.PlaySevenBoom \n3.TrimAndCompressSpaces\n");
      
      switch(UserInput(3))
      {
      case 1: /*1) function to check if palindrome */
      Test_IsPalindrome(); break;
      
      case 2: /*2) function to play 7-boom */
      Test_PlaySevenBoom(); break;
      
      case 3: /*3) function to conduct space review */
      Test_TrimAndCompressSpaces(); break;
      
      default: printf("Bad Input. Exiting.\n");
      }
}


/*******************************  IMPLEMENTATIONS  ****************************/

/* 1) Function to check if a string is a palindrome */
size_t IsPalindrome(char* str)
{
    assert(NULL != str);                   /* Validate inputs */
    size_t i = 0;                          /* Counter to traverse forward */
    size_t j = strlen(str);                /* Counter to traverse backward */
    
    while (i <= strlen(str) / 2)
    {
        if (*(str + i) != *(str + j - 1))   /* Check if characters at
                                            corresponding positions are equal */
        {
            return 0;                      /* Not a palindrome */
        }
        ++i;                               /* Move forward in the string */
        --j;                               /* Move backward in the string */
    }
    
    return 1; /* Palindrome */
}

/* 1-test) function to test IsPalindrome() */
void Test_IsPalindrome()
{
    char* test_cases[] = {"radar", "level", "hello", "world", "madam"};
    int numtest_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    int i = 0;
    printf("Running tests for IsPalindrome:\n");
    
    while (i < numtest_cases)
    {
        char* tst_str = test_cases[i];
        printf("Test case '%s': ", tst_str);
        size_t result = IsPalindrome(tst_str);
        
        if (result)
        {
            printf("Palindrome\n");
        }
        else
        {
            printf("Not a palindrome\n");
        }
        ++i;
    }
}

/* 2) function to play 7-boom */
void PlaySevenBoom(const int from, const int upto)
{
    const int range = upto - from;      /* Initialize range with computation */
    size_t num_dig = 1;           /* Counter for number of digits */
    size_t tested_num = from;     /* Initialize to lower range */
    
    assert(range > 0);  /* Validate inputs */
    
    /* Find out how many digits in range */
    int temp_range = range;
    while (temp_range)
    {
        temp_range /= 10;
        num_dig++;
    }
    
    while (tested_num <= upto)                        /* While in range */
    {
        size_t found = 0;              /* Counter for not found */
        size_t temp_tested = tested_num;
        size_t i = num_dig;            /* Reset i to the number of digits */
        
        while (!found && i > 0)              /* Check for 7's multiples */
        {                                    /* Check if the last digit is 7 */
            found = temp_tested % 10 == 7;
            temp_tested /= 10;               /* Remove the last digit */
            --i;                             /* Decrement the digit counter */
        }
        
        if (found)
        {                                    /* Display the number if it contains 7 */
            printf("%ld is Boom!\n", tested_num); 
        }
        
        ++tested_num;                         /* Increment to the next number */
    }
}

/* 2-test) function to test PlaySevenBoom() */
void Test_PlaySevenBoom()
{
    int test_cases[] =
    {7, 17, 27, 37, 47, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84};
    int numtest_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    int i = 0;
    
    printf("Running tests for Test_PlaySevenBoom:\n");
    /* every close pair in the test array is checked */
    while (i < numtest_cases-1)
    {
        int s = test_cases[i];
        int e = test_cases[i+1];
        printf("Test range %d - %d: \n", s, e);
        PlaySevenBoom(s, e);
         ++i;
    }
}


/* 3) function to conduct space review */
void TrimAndCompressSpaces(char* src)
{
    assert(NULL != src);  /* Validate inputs */

    size_t i = 0;
    size_t len = strlen(src);
    size_t write_index = 0;
    int count_space = 0;

    /* Skip leading spaces */
    while(isspace(src[i]))
    {
        ++i;
    }

    /* Compress multiple spaces into a single space */
    for(; i < len; ++i)
    {
        if(isspace(src[i]))
        {
            if(!count_space)
            {   
                src[write_index++] = ' '; /* Add a single space */
                count_space = 1;
            }
        }
        else
        {
            src[write_index++] = src[i];
            count_space = 0;             /* Copy non-space characters */
 
        }
    }

    /* Handle trailing space */
    if(count_space && write_index > 0)
    {
        --write_index;                  /* Remove the trailing space */
    }

    /* Terminate the string */
    src[write_index] = '\0';
}

/* 3-test) function to test TrimAndCompressSpaces() */
void Test_TrimAndCompressSpaces()
{
    char* test_cases[] = {"  Hello,   World!  ", " le vel", "hello ",
    "w or ld", "m  ad  am", "  m  a   d  am  ", "a  b b c    c    c   "};
    int numtest_cases = 6;
    int i = 0;
    printf("Running tests for TrimAndCompressSpaces:\n");
    
    while (i < numtest_cases)
    {
        char tst_str[30];
        strcpy(tst_str, test_cases[i]);
        printf("Test case '%s'\n: ", tst_str);
        TrimAndCompressSpaces(tst_str);
        printf("After Review: '%s'\n: ", tst_str);
        ++i;
    }
}


/* Function that receives test index number / ESC input from the keyboard*/
size_t UserInput(size_t range)
{   
    /*
        program that receives input from the keyboard:
        • When the number 1 up to range key is pressed,
        program will respectively brun a test.
        • When Esc is pressed, the program exits.
        • User keyboard pressing should not echo on terminal
        (use stty -icanon -echo and  stty icanon echo
        to stop and return terminal buffering and echoing).
        Use system("stty -icanon -echo") and system("stty icanon echo") inside
        the shell for automatic shell support of the commands.
    */
    
    printf("Enter test index\n");
    size_t i = 0;
    while (i != 27)    /* end when Esc pressed */
    {
        scanf("%ld",&i);
        if(i < range && i > 1) printf("Test %ld Selected:\n", i);/* print  value */
        return i;
    }                  
    printf("Escape was pressed\n");      /* after escape */

    return 0;
}
