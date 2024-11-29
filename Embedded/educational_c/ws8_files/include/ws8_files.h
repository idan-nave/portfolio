/********************************** ws8_files.h  ******************************/
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

#ifndef __HEADER_H__
#define __HEADER_H__

#include <stddef.h>              /*Using size_t in header file*/
#include <stdio.h>  		/* For standard input/output */

/********************************** ENUMs  ************************************/

/* Enum that map error codes */
typedef enum
{
    NO_ERROR = 0,
    FILE_NOT_FOUND = 1,
    FILE_READ_ERROR = 2,
    FILE_WRITE_ERROR = 3,
    NULL_STRING_ERROR = 4,
    INVALID_ARGUMENT = 5,
    MEMORY_ALLOCATION_ERROR = 6,
    INVALID_STRING = 7,
    PERMISSION_DENIED = 8,
    OTHER_ERROR = 9,
    FILE_EXISTS = 10,
    NOT_FOUND = 11
} err_code_ty;

/********************************** TypeDefs  *********************************/

typedef int (*func_ptr)(const char*, const char*);

typedef struct
{
  char *cmd;
  func_ptr compare_func;
  func_ptr operation_func;
} op_handler_ty;

/********************************** GLobals  **********************************/

/* buffer to hold continuous input from user*/
static char *input_buff = NULL;
/* buffer to hold filename - which is a global parameter throughout runtime*/
static char *current_file_name = NULL;
/* pointer to the current opened file. if no file is open, ptr is NULL*/
static FILE *current_file_ptr = NULL;
/* pointer to array of op_handler_ty, that will handle available operations */
static op_handler_ty *op_h_arr = NULL;
/* error code global for exit points */
static err_code_ty err = NO_ERROR;

/* File Open/Close Debug infrastructure*/
/*
static size_t debug_opens = 0;
static size_t debug_closes = 0;
*/

/***************** API Approved Functions - To Export *************************/
/* App Manager Function (called from Main) */
int LoggerApp(int argc, const char *filename_input);
/* Function that deletes a file. */
int FileRemove(const char *filename, const char* unused);
/* Function that counts lines in a file */
int FileCountLines(const char *filename, const char* unused);
/* Function that appends a string to an already current opened file*/
int FileAppend(const char *str, const char* unused);
/* Function that pre-appends a string to an already current opened file*/
int FilePreAppend(const char *str, const char* unused);


#endif /*(__HEADER_H__)*/
