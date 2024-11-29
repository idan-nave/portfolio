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


#include "ws7_funcs.h" 		

/************************************** Main **********************************/

int main()
{   
    /*
        program that receives input from the keyboard:
        • When the A or T keys are pressed, 'A-pressed' or 'T-pressed' will
        respectively be displayed in the terminal (3 different implementations).
        • When Esc is pressed, the program exits.
        • User keyboard pressing should not echo on terminal
        (use stty -icanon -echo and  stty icanon echo
        to stop and return terminal buffering and echoing).
        Use system("stty -icanon -echo") and system("stty icanon echo") inside
        the shell for automatic shell support of the commands.
    */
   return RunPressApp();
}
