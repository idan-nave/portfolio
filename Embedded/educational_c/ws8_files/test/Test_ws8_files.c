/******************************** Test_ws8_files.h  ***************************/
/*
  Name: HRD 32
  Project: Work Sheet 8 - Files
  Reviewer: 1. ORI - TODOs are in seperate copy in folder
            2. Dima  - RESENT
  Date: 23/07/23
  Version: 1.0 - 23/07/23 - publish
           1.1 - 25/07/23 - minor syntax & conventions changes
           1.2 - 26/07/23 - fixed TODOs by Dima (see reviewed copy)
*/
  
/******************************** LIBRARIES  **********************************/
#include "ws8_files.h" 		        /* For team's API*/
#include "Test_ws8_files.h" 		/* For team's API*/

/************************************** Main **********************************/

int main(int argc, char *argv[])
{  
    /*  char *envp - UNUSED */
    return LoggerApp(argc, (const char*)argv[1]);
}
