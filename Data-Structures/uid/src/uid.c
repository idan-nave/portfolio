/******************************************************************************/
/*
  Name: Idan Nave
  Project: Work Sheet #uid
  Reviewer: Dima
  Date: 06/09/23
  Version: 1.0

  Overview: Implementation of an UID generator.
*/

/******************************** Libraries  **********************************/
#include <stdio.h> /*printf*/
#include <stddef.h> /*size_t*/
#include <time.h> /*time_t*/
#include <unistd.h> /*getpid*/

#include "../include/uid.h"

/*************************** Definitions  *************************************/

const uid_ty invalid_uid = {(size_t)0, (time_t)-1, (pid_t)0};

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
uid_ty UIDCreate(void)
{
  static size_t counter = 1;
  uid_ty ret_uid = {0};

  ret_uid.counter = counter;
  ret_uid.time_stamp = time(NULL);
  ret_uid.pid = getpid();
  if(ret_uid.time_stamp == (time_t)-1)
  {
    return invalid_uid;
  }
  
  ++counter;

  return ret_uid;
}

int UIDIsSame(uid_ty original_uid, uid_ty uid_to_cmp)
{
  if((original_uid.counter == uid_to_cmp.counter) &&
     (original_uid.time_stamp == uid_to_cmp.time_stamp) &&
     (original_uid.pid == uid_to_cmp.pid))
  {
    return TRUE;
  }

  return FALSE;
}

void PrintUID(uid_ty to_print)
{
  printf("UID %ld was Gen. at %s\n",
         to_print.counter, ctime(&to_print.time_stamp));
}