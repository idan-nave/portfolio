/********************************** ws7_stack.c  ******************************/
/*
  Name: HRD 32
  Project: WS7_Stack Frames & Functions
  Reviewer: Aya
  Date: 13/07/23
  Version: 1.0 - 16/07/23 - publish
           1.1 - 25/07/23 - minor syntax & conventions changes
           1.2 - 26/07/23 - fixed TODOs
*/
  
/******************************** LIBRARIES  **********************************/
/*TODO: usage in 1 word*/


#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 	        /* For System */

#include "ws7_funcs.h" 

#define EOS '\0'		/* For end of strings */
#define MAX_S 256		/* For ASCII LUT */
#define ESC_PRESSED 27		/* input ASCII */
#define A_PRESSED 65		/* input ASCII */
#define T_PRESSED 84		/* input ASCII */
#define SYS_CALL_FAIL 0		/* input termination */
#define SUCCESS 1		/* input termination */
#define ASCII_TABLE_SIZE 256    /* input termination */

/*******************************  App Runner **********************************/

/* Function that manages menu for the pressing app */
int RunPressApp()
{
  int menu_num = 0;
  /* Menu */
  printf("Choose PressingApp Implementatin to run:\n");
  printf("1) if/else\n");
  printf("2) switch case\n");
  printf("3) LUT\n");
  printf("4) exit\n");

  if(0 == scanf("%d",&menu_num))
  {
      return SYS_CALL_FAIL;
  } /*TODO: check scanf*/
  
  switch(menu_num)  /* Route to desired Implementation */
  {
    case 1:
      if(KeyboardInputByIf()) return 0;
      break;
    case 2: 
      if(KeyboardInputBySwitch()) return 0;
      break;
    case 3: 
      if(KeyboardInputByLUT()) return 0;
      break;
    case 4: 
      return 0;
      break;
    default: /* validate input */
      printf("invalid input, Try again!\n");
      if(0 == scanf("%d",&menu_num))
      {
          return SYS_CALL_FAIL;
      } /*TODO: check scanf*/
      break;
  } 
  return 1;
} 

/*******************************  IMPLEMENTATIONS  ****************************/

/* Function that receives A / T / ESC input from the keyboard USING IF*/
int KeyboardInputByIf()
{   
    char input_ch = '0';
    printf("Enter one char\n");
    /* Disable terminal echoing */
    system("stty -icanon -echo");
    
    while (input_ch != ESC_PRESSED)   /* end when Esc pressed */
    {
        if(0 == scanf("%c",&input_ch))
        {
            return SYS_CALL_FAIL;
        }

        if(input_ch == A_PRESSED || input_ch == T_PRESSED) 
        {
            printf("%c Pressed\n", input_ch);    /* print  value */    
        }
    }                  
    printf("Escape was pressed\n");                     /* after escape */
    /* Enable terminal echoing */
    system("stty icanon echo");
    return SUCCESS;
}

/* Function that receives A / T / ESC input from the keyboard USING SWITCH*/
int KeyboardInputBySwitch()
{   
    char input_ch = '0';
    printf("Enter one char\n");

    /* Disable terminal echoing */
    system("stty -icanon -echo");
    
    while (input_ch != ESC_PRESSED) /* end when Esc pressed */
    {
        if(0 == scanf("%c",&input_ch))
        {
            return SYS_CALL_FAIL;
        }
        switch(input_ch)
        {
          case A_PRESSED:
          printf("%c Pressed\n", input_ch);
          break;
          
          case T_PRESSED:
          printf("%c Pressed\n", input_ch);
          break;
          
          default:
          break;
        }
    }                  
    printf("Escape was pressed\n");                  /* after escape */
    /* Enable terminal echoing */
    system("stty icanon echo");
    return SUCCESS;
}

/* Function that initialises LUT array*/
void InitLUT(ptr_to_func_ty *lut, size_t lut_len)
{
    size_t i = 0;
    /* a lut array of function pointers that is
    initialized to a "DummyFunction function" */

    while (i < lut_len)
    {
      lut[i] = DummyFunction;
      ++i;
    }
    lut[A_PRESSED] = PrintAsciiOrExit;
    lut[T_PRESSED] = PrintAsciiOrExit;
    lut[ESC_PRESSED] = PrintAsciiOrExit;
    
}

/* Function that receives A / T / ESC input from the keyboard USING LUT*/
int KeyboardInputByLUT()
{       
    ptr_to_func_ty lut[ASCII_TABLE_SIZE];
    char input_ch = 0; /* ch- index to scan lut cells" */
    printf("Enter one char\n");
    

    InitLUT(lut, ASCII_TABLE_SIZE);

    /* Disable terminal echoing */
    system("stty -icanon -echo");


    while (lut[(size_t)input_ch])    /* end when Esc pressed */
    {

        if(0 == scanf("%c",&input_ch))
        {
            return SYS_CALL_FAIL;
        }
        if(!lut[(size_t)input_ch](input_ch)) /* will keep print A\T using the lut func */
        {
            printf("Escape was pressed\n");      /* after escape */
            
            /* Enable terminal echoing */
            system("stty icanon echo");						
            return 0;
        }
    }
    return SUCCESS;
}

/* Function to do nothing */
int DummyFunction(int unused)
{
  if(unused == ' ')
  {
    return 1;
  }
  return 1;
}

/* Function to print pressed ASCII */
int PrintAsciiOrExit(int ch)
{
    if(ch == A_PRESSED || ch == T_PRESSED) /* A or T */ 

    {
        printf("%c Pressed\n", ch);  /* print  value */ 
        return 1;
    }
    return 0;
}

/* Function to print N */
void print_n(int num)
{
    printf("%d\n", num);
}

/* Function to prints up to N */
void print_to_n(int num)
{
    int i = 1;
    for (; i <= num; ++i)
    {
      printf("%d\n", i);
    }
        
}
