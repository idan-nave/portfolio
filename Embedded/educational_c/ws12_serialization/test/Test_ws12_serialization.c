/************************ Test_ws12_serialization.c  *************************/
/*
  Name: HRD 32
  Project: Work Sheet #12 - Serialized Structs
  Reviewer: Sahar
  Date: 31/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <stdio.h>  		             /* standard input/output */
#include <string.h>                  /* memcmp() */
#include <errno.h>                   /* errno global */

#include "ws12_serialization.h"     

/************************************* Main **********************************/

int main(int argc, char *argv[])
{  
    
    /* handle file name input */
    if (argc < 2)
    {
        printf("Usage of app: %s <file_name>\n", argv[0]);
        return EINVAL;
    }

    return StudentGradesApp((const char*)argv[1]);
}

/************************************ Manual **********************************/
/* ﻿Exercises
1. Create a struct representing a student and the student's grades:
• The struct should contain the student's first name (plain array of chars), 
last name (plain array of chars), and grade struct instance.

• The grade struct itself should contain an instance of humanistic grades struct,
an instance of real grades struct and a sports grade field (float).

Add several grades in the appropriate places (such as physics, math, sociology,
psychology, literature, etc.).

2. Implement an API to save a student to a binary file and load a student from
a binary file.
• Note that the file format should be binary and not text. Why?

3. Test your API: Create a student instance, fill it with data, and save it
to a file. Then create another student instance and load it from the file.
Verify you got the exact same values in all fields.
*/