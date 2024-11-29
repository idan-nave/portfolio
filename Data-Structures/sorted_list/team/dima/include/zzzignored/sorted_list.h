/******************************************************************************/
/*
  Name: Dima
  Project: Work Sheet 12 - Data Structures - Sorted List
  Reviewer: Amit
  Date: 23/08/23
  Version: 1.0
*/

#ifndef __HRD_SL_H__
#define __HRD_SL_H__

/******************************** Libraries  **********************************/

#include <stddef.h> /*size_t*/

/******************************** Definitions  ******************************/

typedef struct node node_t;
typedef node_t* dsl_iter_t;
typedef struct dsl dsl_t;

typedef enum  {SUCCESS = 0, FAILURE} status_t;
typedef enum {FALSE = 0, TRUE} boolean_t;

typedef int (*action_function_t)(void* data, void* param);
typedef int (*match_function_t)(const void* list_data, void* params);

/************************Sorted list API Declerations**************************/

dsl_t DslCreate();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
void DslDestroy();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
size_t DslSize();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
int DslIsEmpty();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslBegin();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslEnd();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslNext();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslPrev();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
int DslIsIterEqual();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
void *DslGetData();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslInsert();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslRemove();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslPopFront();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslPopBack();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
int DslForEach();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslMerge();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslFind();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
dsl_iter_t DslFindIf();
/*Description: 
		

  Arguments: 
  		
  
  Return value: 
  		
  
  Complexity: O().
  
  Undefined B.: 
*/
/******************************************************************************/
/******************************************************************************/

#endif /*(__HRD_SL_H__)*/


