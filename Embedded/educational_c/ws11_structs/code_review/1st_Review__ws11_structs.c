/* TODO - beautiful. your code is beautiful. shapo.	*/

/******************************* ws11_structs.c  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet #11 - Structs
  Reviewer: Uri
  Date: 31/07/23
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		  /* For input validation */
#include <stddef.h>  		  /* For size_t type*/
#include <stdio.h>  		  /* For standard input/output */
#include <stdlib.h> 		  /* For memory allocation & abs() */
#include <string.h>               /* For string manipulation */
#include <time.h>                 /* For random */

#include "ws11_structs.h" 	  /* For team's API*/

/* String Restrictions' Definition */
/* TODO - optional - Liel instructed me to use '\0' directly in the code and that its not..
.. a magic number.	*/
#define EOS '\0'		  /* For end of strings */
#define MAX_STR_LEN 11	          /* Max element-string length */

/* Architecture Indexes' Definition */
/* TODO - optional - personally I would put the indices below in enum - makes more sense,
and you can add more types easily to it.	*/
#define INT_FUNCS_IDX 0		  /* index for int-manipulation funcs */
#define FLOAT_FUNCS_IDX 1	  /* index for float-manipulation funcs */
#define STRING_FUNCS_IDX 2	  /* index for string-manipulation funcs */
#define ELEM_MAX_SIZE 10	  /* max range for multi-arr initialization */
#define MAX_INT_DIGITS 20	  /* max int digits in x64 */
#define ADD_ARBITRARY 10	  /* value for AddToAll function */

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
/* TODO - global vars names are "g_name" if I recall correctly.	*/
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
static int AddToString(element_ty *elem, int numeric_str_to_add);
/* Function to add argument to all of the members in the multi-array */
static int AddToAll(element_ty **arr, size_t arr_len, int num_to_add);
/* Helper function to separate & store number of digits in a num */
static int NumToASciiString(int num, char* store_dig);

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
     {	/*TODO - optional - if you are here, one allocation failed inside AllocateResources.
     	which one? you can't(maybe you cant?) send all of them automatically to free, in case of 
     	an error during runtime, you will attempt (maybe) to free unallocated resources. 
		I don't know if it's a real problem or not, but... see 'TODO' inside AllocateResources().	*/
        FreeResources();
        return err;
     }
     
     /* DEBUG */ /* printf("****passed init**"); fflush(stdout); */
     
     /* Print the whole array */
     PrintAll((const element_ty **)arr_multi_type, MULTI_TYPE_ARR_LEN);
     
     /* Print the whole array */
     AddToAll(arr_multi_type, MULTI_TYPE_ARR_LEN, ADD_ARBITRARY);
    
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
    	/* TODO - if fail here, nothing to free in MultiTypeArrApp().*/
      return err;
    }
    /* Allocates multi-type array  */
    err = AllocateMultiTypeArr(&arr_multi_type, MULTI_TYPE_ARR_LEN);
    if(err)
    {
    	/* TODO - if fail here, free only the one allocated above. and so on.*/
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
    /* TODO - another option, I think it's cleaner and nicer, is to check here
    before each free, if the pointer isn't already NULL, and free only if so..?
    just sharing some thoughts with you, make your choice of course, leaving everything
    as is - maybe that's fine too, I am really no sure.	*/

    while(i < NUM_OF_SUPPORTED_TYPES)  /* Free arr_funcs elements*/
    {
      free(arr_funcs[i]);
      ++i;
    }
    
    i = 0;
    
    while(i < MULTI_TYPE_ARR_LEN)   /* Free arr_multi_type elements*/
    {
      free(arr_multi_type[i]);
      ++i;
    }
    
    free(arr_funcs);
    arr_funcs = NULL;
    free(arr_multi_type);
    arr_multi_type = NULL;
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
    size_t elem_range = ELEM_MAX_SIZE;
    /* pointer to accept generated string*/
    char* gen_str = NULL;
    
    while(i < arr_len)    /* Initialization loop */
    {
      /* random size for each element in the multi-array*/
      elem_range = rand() % ELEM_MAX_SIZE;
      /* the array will be initialized with the pattern [int, float, str ...] */
      switch((i + NUM_OF_SUPPORTED_TYPES)  % 3)
      {
      	/* TODO - optional - this function is 'bagging' to be devided - I would
      	send each 'case' to another function - but only if you have the time and
      	will to do so..	*/
        case INT_FUNCS_IDX:  /* initialize data with int */
            err = InitInt(arr[i], GenRandomInt((-1)*elem_range, elem_range));
            if(err)
            {
              return err;
            }
            /* initialize elements' supported funcs with int funcs */
            arr[i]->funcs = arr_funcs[INT_FUNCS_IDX];
        break;
      
        case FLOAT_FUNCS_IDX:  /* initialize data with float */
            err = InitFloat(arr[i], GenRandomFloat((-1)*elem_range, elem_range));
            if(err)
            {
              return err;
            }
            /* initialize elements' supported funcs with float funcs */
            arr[i]->funcs = arr_funcs[FLOAT_FUNCS_IDX];
        break;
        
        case STRING_FUNCS_IDX:/* create string address to pass for random str */
            gen_str = (char*)malloc(sizeof(char)*elem_range);
            if (NULL == gen_str) /* validate successful allocation */
            {
                fprintf(stderr, "InitMultiTypeArr Error: %s\n",
                info[MEMORY_ALLOCATION_ERROR].message);
                return MEMORY_ALLOCATION_ERROR;
            }
            err = GenRandomString(elem_range, gen_str);
            if(err)
            {
              return err;
            }
            err = InitString(arr[i], (const char*)gen_str);
            if(err)
            {
              return err;
            }
            /* initialize elements' supported funcs with string funcs */
            arr[i]->funcs = arr_funcs[STRING_FUNCS_IDX];
            /*free gen_str every-time the case is being executed */
            free(gen_str);
            gen_str = NULL;
        break;
              
        default:
        break;
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
    /* an allocated int in order to achieve unique address to hold date */
    int* new_all_int = NULL;
    new_all_int = (int*)malloc(sizeof(int));
      if (NULL == new_all_int) /* validate successful allocation */
      {
          fprintf(stderr, "InitInt Error: %s\n",
          info[MEMORY_ALLOCATION_ERROR].message);
          return MEMORY_ALLOCATION_ERROR;
      }

    *new_all_int = data;
    element->data = (void*)new_all_int;
    return NO_ERROR;
}

/* A Function to init an element of multi-type arr with a float */
static int InitFloat(element_ty *element, float data)
{
    /* an allocated float in order to achieve unique address to hold date */
    float* new_all_float = NULL;
    new_all_float = (float*)malloc(sizeof(float));
      if (NULL == new_all_float) /* validate successful allocation */
      {
          fprintf(stderr, "InitFloat Error: %s\n",
          info[MEMORY_ALLOCATION_ERROR].message);
          return MEMORY_ALLOCATION_ERROR;
      }
    *new_all_float = data;
    element->data = (void*)new_all_float;
    return NO_ERROR;
}

/* A Function to init an element of multi-type arr with a string */
static int InitString(element_ty *element, const char* data)
{
    size_t all_str_len = strlen(data) + 1;
    /* an allocated string in order to achieve unique address to hold date */
    char* new_all_str = NULL;
    
    /* validate data string is within limitations */
    if(all_str_len > MAX_STR_LEN)
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
    if(len > MAX_STR_LEN - 1)
    {
        fprintf(stderr, "GenRandomString Error: %s\n",
        info[INVALID_STRING_LEN].message);
        return INVALID_STRING_LEN;
    }
    
    /* Placement to string */
    while (i < len - 1)
    {     /* mark random char from char-set */
          slct_from_charset = rand() % (int)(sizeof charset - 1);
          /* placement of marked char into random */
          str_to_return[i] = charset[slct_from_charset];
          ++i;
    }
    str_to_return[len] = EOS;
    return NO_ERROR;
}

  /***************************** Printing Functions ************************/

/* Function to print int element with [] brackets */
static void PrintInt(const element_ty *elem_to_print)
{
    printf("[ %d ]", *((int*)(*elem_to_print).data));
}

/* Function to print float element with () brackets */
static void PrintFloat(const element_ty *elem_to_print)
{
    printf("( %f )", *(float*)elem_to_print->data);
}

/* Function to print string element with {} brackets */
static void PrintString(const element_ty *elem_to_print)
{
    size_t i = 0;
    printf("{");
    while(i < (size_t)strlen((char*)elem_to_print->data) + 1)
    {
      printf("%s", ( (char*)elem_to_print->data) + i );
      ++i;
    }
    printf("}");
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
    /* allocate new address */
    int* sum = NULL;
    sum = (int*)malloc(sizeof(int));
    if (NULL == sum) /* validate successful allocation */
    {
        fprintf(stderr, "AddToInt Error: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }
    /* add old data with new data inside sum */
    *sum = *((int*)elem->data) + int_to_add;
    /* free old data address as it receives now address*/
    free(elem->data);
    elem->data = NULL;
    /* TODO - I wonder if this line is necessary when looking..
    ..at the next one. I trust that you checked this and it is necessary :) 	*/
    /* overwrite addition */
    elem->data = (void*)sum;
    return NO_ERROR;
}

/* Function to add float element to specified float element */
static int AddToFloat(element_ty *elem, int int_to_add)
{
    /* allocate new address */
    float* sum = NULL;
    sum = (float*)malloc(sizeof(float));
    if (NULL == sum) /* validate successful allocation */
    {
        fprintf(stderr, "AddToFloat: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }
    /* add old data with new data inside sum */
    *sum = *((int*)elem->data) + int_to_add;
    /* free old data address as it receives now address*/
    free(elem->data);
    elem->data = NULL;	/* TODO - I wonder if this line is necessary when looking..
    ..at the next one. I trust that you checked this and it is necessary :) 	*/
    /* overwrite addition */
    elem->data = (void*)sum;
    return NO_ERROR;
}

/* Function to concatenate numeric string to specified string element */
static int AddToString(element_ty *elem, int numeric_str_to_add)
{
    /* Array to store converted numeric_str */
    char* store_dig = NULL;     
    /* Array to store original data-str */
    char *final_str = (char*)elem->data;
    /* allocating string to stire converted asciis */
    store_dig = (char*)malloc(sizeof(char)*MAX_INT_DIGITS + 1);
    if (NULL == store_dig) /* validate successful allocation */
    {
        fprintf(stderr, "AddToString Error: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }
    err = NumToASciiString(numeric_str_to_add, store_dig);
    if(err)
    {
      return err;
    }
    /* validate final string length, will stay compatible */     
    if(strlen(store_dig) + strlen(final_str) > MAX_STR_LEN - 1)
    {
      fprintf(stderr, "NumToASciiString: %s\n",
      info[INVALID_STRING_LEN].message);
      return INVALID_STRING_LEN;
    }
    
    /* concatenate converted num to end of original data string */
    strcat(final_str, store_dig);
    /* done using str_dig */
    free(store_dig);
    store_dig = NULL;
    /* free old data before overwriting */
    free((char*)elem->data); /* TODO - ok I think here you showed me that the 2..
    ..lines above are not necessary...?	*/
    /* assign new data */
    elem->data = (void*)final_str; /* now element has the addrs of final_str*/
    /* free local resources */
    return NO_ERROR;
}

/* Helper function to separate & store number of digits in a num */
static int NumToASciiString(int num, char* store_dig)
{
    size_t i = 0;               /* Runner for init & counter for digits  */
    char ascii_ref = '-';       /* char to convert digit to ascii */
    /* TODO - ascii_ref is not as informative as asci-minus or something like..
    ..that.	*/
    
    /* when negative number: start appending after ' - ' sign  */
    if(num < 0)
    {
        store_dig[0] = ascii_ref;
        i = 1;
    }
    /* TODO - move check before the line store_dig[0] = ascii"_ref;
    /* validate not-null passed string  */
    if(NULL == store_dig) 
    {
      fprintf(stderr, "NumToASciiString: %s\n",
      info[NULL_STRING_ERROR].message);
      return NULL_STRING_ERROR;
    }
    /* Disassemble num into chars */     
    while(0 != num)
    {
        ascii_ref = num % 10;
        store_dig[i] = (char)(ascii_ref + '0');
        num /= 10;
        ++i;
    }
    /* validate final string length, not including termination char */     
    if(i > MAX_STR_LEN - 1)
    {
      fprintf(stderr, "NumToASciiString: %s\n",
      info[INVALID_STRING_LEN].message);
      return INVALID_STRING_LEN;
    }
    store_dig[i] = EOS; /* sign string with termination char */
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

  /***************************** Clearing Functions ************************/

/* TODO - move those funcs to a more appropriate location above.	*/
/* Function to free int element  */
static void FreeInt(element_ty *elem_to_free)
{
    free((int*)elem_to_free->data);
}

/* Function to free float element  */
static void FreeFloat(element_ty *elem_to_free)
{
    free((float*)elem_to_free->data);
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
