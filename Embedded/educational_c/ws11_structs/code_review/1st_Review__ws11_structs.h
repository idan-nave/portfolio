/******************************* ws11_structs.h  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet #11 - Structs
  Reviewer: Uri
  Date: 31/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/

#ifndef __WS11_STRUCT_H__
#define __WS11_STRUCT_H__

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
    INVALID_STRING_LEN = 10,
    NOT_FOUND = 11
} err_code_ty;


/***************** API Approved Functions - To Export *************************/

/* App Manager Function (called from Main) */
int MultiTypeArrApp();

/******************************************************************************/

#endif /*(__WS11_STRUCT_H__)*/
