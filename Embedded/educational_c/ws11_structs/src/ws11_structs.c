/******************************* ws11_structs.c  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet #11 - Structs
  Reviewer: Uri
  Date: 31/07/23
  Version: 1.0
*/

/************************* NOTES - IMPORTANT  **********************************/
 /* *(int*)&(element->data) = data 
 LOOK FOR ABOVE EXP. NEEDS TO BE REIMPLEMENTED WITH THE RIGHT MEANING.
 INIT BY VAL, NOT BY REF (IN THIS SPECIFIIC EXERCIZE)
 
 
 ADD ASSERT TO ALL INPUTS
 */

/******************************** LIBRARIES  **********************************/
#include <assert.h> 		  /* For input validation */
#include <stddef.h>  		  /* For size_t type*/
#include <stdio.h>  		  /* For standard input/output */
#include <stdlib.h> 		  /* For memory allocation & abs() */
#include <string.h>               /* For string manipulation */
#include <time.h>                 /* For random */

#include "ws11_structs.h" 	  /* For team's API*/

/****************************** DEFINITIONS  **********************************/

/* String Restrictions' Definition */
#define EOS '\0'		  /* For end of strings */
#define ELEM_MAX_STRING_LEN 10	  /* Max string length (MAX_INT_DIGITS+1) */
#define ELEM_MAX_NUMERIC_VAL 100  /* max range for multi-arr initialization */
#define MAX_INT_DIGITS 10	  /* max int digits in x64 */
#define ADD_ARBITRARY 245	  /* value for AddToAll function */

/* Architecture Indexes' Definition */
#define INT_FUNCS_IDX 0		  /* index for int-manipulation funcs */
#define FLOAT_FUNCS_IDX 1	  /* index for float-manipulation funcs */
#define STRING_FUNCS_IDX 2	  /* index for string-manipulation funcs */

/* Array Lengths' Definition */
#define MULTI_TYPE_ARR_LEN 10	  /* Length of multi-type array */
#define NUM_OF_SUPPORTED_TYPES 3  /* Length of funcs array */


/******************************************************************************/
/**************************** App's Data-structures ***************************/
/******************************************************************************/
 
  /********Error Info Struct Definition (appendix to the error Enum) ********/
typedef struct
{
    err_code_ty code;
    const char* message;
} err_msg_ty;

  /********************** Error Messages Array Definition *******************/
err_msg_ty info[] = {
    {NO_ERROR, "No error"},
    {FILE_NOT_FOUND, "File not found"},
    {FILE_READ_ERROR, "Error while reading from file"},
    {FILE_WRITE_ERROR, "Error while writing to file"},
    {NULL_STRING_ERROR, "Null string encountered"},
    {INVALID_ARGUMENT, "Invalid argument"},
    {MEMORY_ALLOCATION_ERROR, "Memory allocation error"},
    {INVALID_STRING, "Invalid string"},
    {PERMISSION_DENIED, "Permission denied"},
    {OTHER_ERROR, "Other error"},
    {INVALID_STRING_LEN, "Invalid String Length"}
};

  /******************************** TypeDefs  *******************************/

/* forward declaration of type element
in order for func-pointers-declaration to compile successfully*/
typedef struct element element_ty;

/* funcs to perform general manipulation over array elements */
typedef int (*add_func_ty)(element_ty* element, int);
typedef void (*print_func_ty)(const element_ty *element) ;
typedef void (*free_func_ty)(element_ty *element) ;

/* struct to contain the different algo-funcs. this struct will serve as 
"bank of options" to be executed on the very element it is held in */
typedef struct elements_funcs
{
  add_func_ty add;
  print_func_ty print;
  free_func_ty free_resource;
} element_funcs_ty;

/* struct that represents the basic array element:
      1. data with no type
      2. pointer to the array of funcs supported by API */
struct element
{
  void* data;
  element_funcs_ty* funcs;
};

  /******************************** GLobals  ********************************/

/* error code global for exit points */
err_code_ty err = NO_ERROR;
/* decleration of supported funcs-elements - for each supported operation*/
element_funcs_ty **arr_funcs;
/* decleration of multitype array, consists of "element_funcs_ty "elements*/
element_ty **arr_multi_type;
 
/******************************************************************************/
/**************** Forward Declarations of Static Functions ********************/
/******************************************************************************/
 
  /******************** Memory Allocations Functions ************************/

/* A Function to allocate program resources */
static int AllocateResources();
/* A Function to free allocated program resources */
static void FreeResources();
/* A Function to allocate the supported funcs-array */
static int AllocateFuncElements(element_funcs_ty ***arr, size_t arr_len);
/* A Function to allocate and initialize the multi-type array*/
static int AllocateMultiTypeArr(element_ty ***arr, size_t arr_len);
/* A Function to initialize the supported funcs-array */
static int InitFuncElements(element_funcs_ty **arr);
/* A Function to allocate and initialize the multi-type array*/
static int InitMultiTypeArr(element_ty **arr, size_t arr_len);
/* A Function to generate ranadom data-types by request */
/* Generate and returns a random int in range [lower, upper] */
static int GenRandomInt(int lower, int upper);
/* Generate and returns a random float in range [lower, upper] */
static float GenRandomFloat(int lower, int upper);
/* Generate and returns a random int in range [lower, upper] */
static int GenRandomString(size_t len, char* str_to_return);
/* A Function to init an element of multi-type arr with an int */
static int InitInt(element_ty *element, int data);
/* A Function to init an element of multi-type arr with a float */
static int InitFloat(element_ty *element, float data);
/* A Function to init an element of multi-type arr with a string */
static int InitString(element_ty *element, const char* data);

  /***************************** Printing Functions ************************/

/* Function to print int element with [] brackets */
static void PrintInt(const element_ty *elem_to_print);
/* Function to print float element with () brackets */
static void PrintFloat(const element_ty *elem_to_print);
/* Function to print string element with {} brackets */
static void PrintString(const element_ty *elem_to_print);
/* Function to print the whole multi-array */
static void PrintAll(const element_ty **arr, size_t arr_len);

  /***************************** Addition Functions ************************/

/* Function to add int element to specified int element */
static int AddToInt(element_ty *elem, int int_to_add);
/* Function to add int element to specified int element */
static int AddToFloat(element_ty *elem, int int_to_add);
/* Function to concatenate numeric string to specified string element */
static int AddToString(element_ty *elem, int num_str_to_add);
/* Function to add argument to all of the members in the multi-array */
static int AddToAll(element_ty **arr, size_t arr_len, int num_to_add);
/* Helper function to separate & store number of digits in a num */
static int NumToASciiString(int num, char* numeric_str);
/* Function that counts the number of digits in an integer number */
static int CountIntDigits(int num);

  /***************************** Clearing Functions ************************/

/* Function to free int element  */
static void FreeInt(element_ty *elem_to_free);
/* Function to free float element  */
static void FreeFloat(element_ty *elem_to_free);
/* Function to string int element  */
static void FreeString(element_ty *elem_to_free);
/* Function to free all of the members in the multi-array */
static void FreeAll(element_ty **arr, size_t arr_len);

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
  /**************** App Manager Function (called from Main) *****************/
 
int MultiTypeArrApp()
{         
     /* Random-resource Initialization, should only be called once.*/
     srand(time(NULL)); 
     
     /* Allocate Memory for runtime */
     err = AllocateResources();
     if(err)
     {
        FreeResources();
        return err;
     }
     
     /* DEBUG */ /* printf("****passed init**"); fflush(stdout); */
     
     /* Print the whole array */
     PrintAll((const element_ty **)arr_multi_type, MULTI_TYPE_ARR_LEN);
     
     /* Print the whole array */
     AddToAll(arr_multi_type, MULTI_TYPE_ARR_LEN, ADD_ARBITRARY);
    
    
     /* Print the whole array again */
     PrintAll((const element_ty **)arr_multi_type, MULTI_TYPE_ARR_LEN);
   
     /* Print the whole array again*/
     FreeAll(arr_multi_type, MULTI_TYPE_ARR_LEN); 
     
     /* free memory resources */
     FreeResources();
     return NO_ERROR;
}
  /****************** App Resources-allocating Managers ********************/
  
static int AllocateResources()
{   
    /* Allocates supported functions for multi-type array */
    err = AllocateFuncElements(&arr_funcs, NUM_OF_SUPPORTED_TYPES);
    if(err)
    {
      return err;
    }
    /* Allocates multi-type array  */
    err = AllocateMultiTypeArr(&arr_multi_type, MULTI_TYPE_ARR_LEN);
    if(err)
    {
      return err;
    }
    /* Initialize supported functions for  multi-type array */
    err = InitFuncElements(arr_funcs);
    if(err)
    {
      return err;
    }
    /* Initialize multi-type array */
    err = InitMultiTypeArr(arr_multi_type, MULTI_TYPE_ARR_LEN);
    if(err)
    {
      return err;
    }
    return NO_ERROR;
}

static void FreeResources()
{
    size_t i = 0;    /* Runner for freeing array-resources */

    while(i < NUM_OF_SUPPORTED_TYPES)  /* Free arr_funcs elements*/
    {
        if(NULL != arr_funcs[i])
        {
            free(arr_funcs[i]);
            ++i;
        }
    }
    
    i = 0;
    
    while(i < MULTI_TYPE_ARR_LEN)   /* Free arr_multi_type elements*/
    {
        if(NULL != arr_multi_type[i])
        {
            free(arr_multi_type[i]);
            ++i;
        }
    }
    
    free(arr_funcs);
    arr_funcs = NULL;
    free(arr_multi_type);
    arr_multi_type = NULL;
}

  /***************************** Clearing Functions ************************/

/* Function to free int element  */
static void FreeInt(element_ty *elem_to_free)
{
   /* free((int*)elem_to_free->data); */
}

/* Function to free float element  */
static void FreeFloat(element_ty *elem_to_free)
{
    /*free((float*)elem_to_free->data);*/
}

/* Function to string int element  */
static void FreeString(element_ty *elem_to_free)
{
    free((char*)elem_to_free->data);
}

/* Function to free all of the members in the multi-array */
static void FreeAll(element_ty **arr, size_t arr_len)
{
    size_t i = 0;
    while(i < arr_len )
    {
      /* array pattern is: int, float, str ... each has its own print func */
      arr[i]->funcs->free_resource(arr[i]); /*free using element-unique free*/
      ++i;
    }
}

  /************************ Initialization Functions ************************/

/* A Function to allocate the supported funcs-array */
static int AllocateFuncElements(element_funcs_ty ***arr, size_t arr_len)
{   
    /* Runner for initalization */
    size_t i = 0;
    /* validate array length within limitations */
    if(arr_len > NUM_OF_SUPPORTED_TYPES)
    {
        fprintf(stderr, "AllocateFuncElements Error: %s\n",
        info[INVALID_ARGUMENT].message);
        return INVALID_ARGUMENT;
    }

    /* allocate functions array */
    *arr = (element_funcs_ty**)malloc(sizeof(element_funcs_ty*)*arr_len);
    /* validate successful allocation */
    if (NULL == arr)
    {
        fprintf(stderr, "AllocateFuncElements Error: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }
    /* allocate functions elements */
    while(i < arr_len)
    {
      (*arr)[i] = (element_funcs_ty*)malloc(sizeof(element_funcs_ty));
      ++i;
    }
    return NO_ERROR;
}

/* A Function to allocate the multi-type array */
static int AllocateMultiTypeArr(element_ty ***arr, size_t arr_len)
{   
    /* Runner for initalization */
    size_t i = 0;
    /* validate array length within limitations */
    if(arr_len > MULTI_TYPE_ARR_LEN)
    {
        fprintf(stderr, "AllocateMultiTypeArr Error: %s\n",
        info[INVALID_ARGUMENT].message);
        return INVALID_ARGUMENT;
    }

    /* allocate multi-type array */
    *arr = (element_ty**)malloc(sizeof(element_ty*)*arr_len);
    /* validate successful allocation */
    if (NULL == arr)
    {
        fprintf(stderr, "AllocateMultiTypeArr Error: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }
    /* allocate multi-type array elements */
    while(i < arr_len)
    {
      (*arr)[i] = (element_ty*)malloc(sizeof(element_ty));
      ++i;
    }
    return NO_ERROR;
}

/* A Function to initialize the funcs-array with "element_funcs_ty" elements */ 
static int InitFuncElements(element_funcs_ty **arr)
{      
    /* populate funcs-array with sub-funcs (type oriented) */
    arr[INT_FUNCS_IDX]->add = AddToInt;
    arr[INT_FUNCS_IDX]->print = PrintInt;
    arr[INT_FUNCS_IDX]->free_resource = FreeInt;
    
    arr[FLOAT_FUNCS_IDX]->add = AddToFloat;
    arr[FLOAT_FUNCS_IDX]->print = PrintFloat;
    arr[FLOAT_FUNCS_IDX]->free_resource = FreeFloat;

    arr[STRING_FUNCS_IDX]->add = AddToString;
    arr[STRING_FUNCS_IDX]->print = PrintString;
    arr[STRING_FUNCS_IDX]->free_resource = FreeString;
    
    return NO_ERROR;
}

/* A Function to initialize the multi-type array*/
static int InitMultiTypeArr(element_ty **arr, size_t arr_len)
{
    /* Runner for initalization */
    size_t i = 0;
    /* max range for multi-arr */
    size_t elem_num_range = ELEM_MAX_NUMERIC_VAL;
    size_t elem_str_len = ELEM_MAX_STRING_LEN;
    /* pointer to accept generated string*/
    char* gen_str = NULL;
    
    while(i < arr_len)    /* Initialization loop */
    {
      /* random size for each element in the multi-array*/
      elem_num_range = rand() % ELEM_MAX_NUMERIC_VAL;
      elem_str_len = rand() % ELEM_MAX_STRING_LEN;
      /* the array will be initialized with the pattern [int, float, str ...] */
        switch((i + NUM_OF_SUPPORTED_TYPES)  % 3)
        {
          case INT_FUNCS_IDX:  /* initialize data with int */
              err = InitInt(arr[i], GenRandomInt((-1)*elem_num_range, elem_num_range));
              /* initialize elements' supported funcs with int funcs */
              arr[i]->funcs = arr_funcs[INT_FUNCS_IDX];
          break;
        
          case FLOAT_FUNCS_IDX:  /* initialize data with float */
              err = InitFloat(arr[i], GenRandomFloat((-1)*elem_num_range, elem_num_range));
              /* initialize elements' supported funcs with float funcs */
              arr[i]->funcs = arr_funcs[FLOAT_FUNCS_IDX];
          break;
          
          case STRING_FUNCS_IDX:/* create string address to pass for random str */
              gen_str = (char*)malloc(sizeof(char)*elem_num_range);
              if (NULL == gen_str) /* validate successful allocation */
              {
                  fprintf(stderr, "InitMultiTypeArr Error: %s\n",
                  info[MEMORY_ALLOCATION_ERROR].message);
                  return MEMORY_ALLOCATION_ERROR;
              }
              err = GenRandomString(elem_str_len, gen_str);
              err = InitString(arr[i], (const char*)gen_str);

              /* initialize elements' supported funcs with string funcs */
              arr[i]->funcs = arr_funcs[STRING_FUNCS_IDX];
              /*free gen_str every-time the case is being executed */
              free(gen_str);
              gen_str = NULL;
          break;
                
          default:
          break;
         }
       
       if(err)
       {
         return err;
       }
       ++i;
    }
    return NO_ERROR;
}

/* A Function to init an element of multi-type arr with an int,
returned data is stored into new pointer in order for the data to be stored in
heap after callee's frame collapses. */
static int InitInt(element_ty *element, int data)
{
    *((int*)&(element->data)) = data;
    return NO_ERROR;
}

/* A Function to init an element of multi-type arr with a float */
static int InitFloat(element_ty *element, float data)
{
    *((float*)&(element->data)) = data;
    return NO_ERROR;
}

/* A Function to init an element of multi-type arr with a string */
static int InitString(element_ty *element, const char* data)
{
    size_t all_str_len = strlen(data) + 1;
    /* an allocated string in order to achieve unique address to hold date */
    char* new_all_str = NULL;
    
    /* validate data string is within limitations */
    if(all_str_len > ELEM_MAX_STRING_LEN)
    {
        fprintf(stderr, "InitString Error: %s\n",
        info[INVALID_STRING_LEN].message);
        return INVALID_STRING_LEN;
    }
    new_all_str = (char*)malloc(sizeof(char)*all_str_len);
    if (NULL == new_all_str) /* validate successful allocation */
    {
        fprintf(stderr, "InitString Error: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }

    /* append new initializtion */
    strcpy(new_all_str, data);            
    element->data = (void*)new_all_str; 
    return NO_ERROR;
}

/* Generate and returns a random int in range [lower, upper] */
static int GenRandomInt(int lower, int upper)
{
  return (rand() % (upper - lower + 1)) + lower;
}

/* Generate and returns a random float in range [lower, upper] */
static float GenRandomFloat(int lower, int upper)
{
  return (((float)upper - (float)lower)* ((float)rand() / RAND_MAX)) + lower;
}

/* Generate and returns a random string with length len into  str_to_return*/
static int GenRandomString(size_t len, char* str_to_return)
{
    /* string-required vars */
    size_t i = 0;
    int slct_from_charset = 0;
    /* the alphbetic array to build chars */
    const char charset[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    
    /* validate random string is within limitations */
    if(len > ELEM_MAX_STRING_LEN)
    {
        fprintf(stderr, "GenRandomString Error: %s\n",
        info[INVALID_STRING_LEN].message);
        return INVALID_STRING_LEN;
    }
    
    /* Placement to string */
    while (i < len - 1)
    {     /* mark random char from char-set */
          slct_from_charset = rand() % (int)(sizeof(charset) - 1);
          /* placement of marked char into random */
          str_to_return[i] = charset[slct_from_charset];
          ++i;
    }
    str_to_return[len-1] = EOS;
    return NO_ERROR;
}

  /***************************** Printing Functions ************************/

/* Function to print int element with [] brackets */
static void PrintInt(const element_ty *elem_to_print)
{
    printf("[ %d ]", *((int*)&(elem_to_print->data)) );
}

/* Function to print float element with () brackets */
static void PrintFloat(const element_ty *elem_to_print)
{
    printf("( %f )", *((float*)&(elem_to_print->data)) );
}

/* Function to print string element with {} brackets */
static void PrintString(const element_ty *elem_to_print)
{
    printf("{ %s }", ( (char*)elem_to_print->data)  );
}

/* Function to print the whole multi-array */
static void PrintAll(const element_ty **arr, size_t arr_len)
{
    size_t i = 0;
    printf("\n");
    while(i < arr_len)
    {     
      /* array pattern is: [int, float, str ..] each has its own print func */
      /* printf("****in PrintString***%d\n", *(int*)arr[i].data);*/
      arr[i]->funcs->print(arr[i]); /*print using element-unique print*/
      ++i;
      printf(", "); /* seperate elements with comma */
    }
    /*print last element without comma*/
/*    arr[i]->funcs->print(arr[i]);*/
    printf("\n");
}

  /***************************** Addition Functions ************************/

/* Function to add int element to specified int element */
static int AddToInt(element_ty *elem, int int_to_add)
{
    *((int*)&(elem->data)) += int_to_add;
    return NO_ERROR;
}

/* Function to add float element to specified float element */
static int AddToFloat(element_ty *elem, int int_to_add)
{
    *((float*)&(elem->data)) += (float)int_to_add;
    return NO_ERROR;
}

/* Function to concatenate numeric string to specified string element */
static int AddToString(element_ty *elem, int num_str_to_add)
{
    /* vars to hold allocations sizes calculations */
    size_t max_size_to_append = 0;
    size_t alloc_size = 0;
    size_t original_size = strlen((char*)elem->data);
    
    /* string to store converted numeric_str */
    char* numeric_str = NULL;     
    /* string to store final data, init with original data-str */
    char *final_str =  NULL;     
    
    /* calculate remained space in str with reference to max allowed */
    max_size_to_append = ELEM_MAX_STRING_LEN - original_size - 1;
    /* calculate alloc length = digits + minus + termination char */
    alloc_size = CountIntDigits(num_str_to_add) + 1 + (num_str_to_add < 0);

    /* allocating string to store converted asciis */
    numeric_str = (char*)malloc(sizeof(char)*alloc_size);
    if (NULL == numeric_str) /* validate successful allocation */
    {
        fprintf(stderr, "AddToString Error: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }
    err = NumToASciiString(num_str_to_add, numeric_str);

    /* ensure final string length, will stay compatible: concatenate converted
    num to end of original data string only up to ELEM_MAX_STRING_LEN */
    if(max_size_to_append > 0)
    {                                      
        /* allocating new final string to store final concatenation */
        final_str = (char*)malloc(sizeof(char)*( original_size + alloc_size ) );
        if (NULL == final_str) /* validate successful allocation */
        {
            fprintf(stderr, "AddToString Error: %s\n",
            info[MEMORY_ALLOCATION_ERROR].message);
            return MEMORY_ALLOCATION_ERROR;
        }
        strcpy(final_str, (char*)elem->data);
        /* done using old value */ free((char*)elem->data);
        strncat(final_str, numeric_str, alloc_size - 1);
        /* assign new data */
        elem->data = (void*)final_str; /* element got the address of final_str*/
        /* free local resources */
    }
    /* done using str_dig */
    free(numeric_str);
    numeric_str = NULL;
    return NO_ERROR;
}

/* Function to add argument to all of the members in the multi-array */
static int AddToAll(element_ty **arr, size_t arr_len, int num_to_add)
{
    size_t i = 0;
    while(i < arr_len)
    {
      /* array pattern is: int, float, str ... each has its own add func */
      arr[i]->funcs->add(arr[i], num_to_add); /*free using element-unique free*/
      ++i;
    }
    return NO_ERROR;
}

/* Helper function to separate & store number of digits in a num */
static int NumToASciiString(int num, char* numeric_str)
{
    size_t i = 0;                   /* Runner for init & counter for digits  */
    size_t num_digs = 0;            /* num of digs  */
    char numeric_char = '-';        /* char to convert digit to ascii */
    
    /* validate not-null passed string  */
    if(NULL == numeric_str) 
    {
      fprintf(stderr, "NumToASciiString: %s\n",
      info[NULL_STRING_ERROR].message);
      return NULL_STRING_ERROR;
    }
    
    /* when negative number: start appending after ' - ' sign  */
    if(num < 0)
    {
        numeric_str[0] = numeric_char;
        i = 1;
    }

    num_digs = CountIntDigits(num);

    /* Disassemble num into chars */
    while( 0 != num)
    {
        numeric_char = num % 10;
        numeric_str[num_digs -1 - i] = (char)(numeric_char + '0');
        num /= 10;
        ++i;
    }
    numeric_str[i] = EOS; /* sign string with termination char */
    return NO_ERROR;
}

/* Function that counts the number of digits in an integer number */
static int CountIntDigits(int num)
{
    size_t count_digs = 0;

    /* Handle the case of 0 separately*/
    if (num == 0)
    {
        return 1;
    }

    /* For negative numbers, remove the sign and count the digits*/
    if (num < 0)
    {
        num = -num;
    }

    while (num != 0)
    {
        num /= 10;
        ++count_digs;
    }

    return count_digs;
}
