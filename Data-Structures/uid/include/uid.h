/******************************************************************************/
/*
  Name: Idan Nave
  Project: Work Sheet #uid
  Reviewer: Dima
  Date: 06/09/23
  Version: 1.0
  
  Overview: Implementation of an UID generator.
*/

#ifndef __ILRD_UID_H__
#define __ILRD_UID_H__

/******************************** Libraries  **********************************/

#include <stddef.h> /*size_t*/
#include <sys/types.h> /*pid_t, time_t*/

/******************************** Definitions  ********************************/

typedef struct uid
{
	size_t counter;
	time_t time_stamp;
	pid_t pid;
}uid_ty;

extern const uid_ty invalid_uid;
typedef enum {FALSE = 0, TRUE} boolean_t;

/*********************** UID API Declerations  ********************************/

/*
  Description: Function that provides a new UID.
  Arguments: None.
  Return value: New UID by value. Returns invalid_uid on failure.
  Complexity: O(1). 
  Undefined B.: None
*/
uid_ty UIDCreate(void);

/*
  Description: Function that checks if two UID are equal.
  Arguments: 'original_uid', 'uid_tyo_cmp' -
  UID's to be compared.
  Return value: TRUE if UIDs are equal, otherwise FALSE.
  Complexity: O(1).
  Undefined B.: None. 
*/
int UIDIsSame(uid_ty original_uid, uid_ty uid_to_cmp);

void PrintUID(uid_ty to_print);

/******************************************************************************/

#endif /*__ILRD_UID_H__*/