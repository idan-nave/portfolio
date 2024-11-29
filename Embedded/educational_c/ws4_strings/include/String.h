/*Name: HRD 32
  Project: String Function Re-implementation
  Reviewer: Liel
  Date: 04/07/2023
  Version: 1.0*/
  
/******************************** LIBRARIES  **********************************/

#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>  /*Using size_t in header file*/

/******************************* DECLERATIONS *********************************/

/*compute and return the length of string*/
size_t StrLen(const char *str);

/*compare between two strings. return *str1-*str2
	•if str1 > str2 return positive
	•if str1 < str2 return negetive
	•if equals return 0*/
int StrCmp(const char *str1, const char *str2);

/*Receives a pointer to a constant string to be copied, 
  and a pointer to the location to copy it into, 
  returns the pointer to the user/caller after the run finishes.*/
char *StrCpy(char *dest, const char *src);

/*The  strncpy()  function  copies up to n character-string pointed to by src,
  NOT including the terminating null byte ('\0'),
  to the buffer  pointed  to  by  dest.*/
char *StrnCpy(char *dest, const char *src, size_t num);

/*The StrnCmp()function compares only the first (at most)
  num bytes of the two strings str1 and str2.
  StrnCmp() returns an integer indicating the result of the comparison,
  as follows:
       • 0, if the str1 and str2 are equal;
       • a negative value if str1 is less than str2;
       • a positive value if str1 is greater than str2.*/
int StrnCmp(const char *str1, const char *str2, size_t num);

/*compare between two strings. return *str1-*str2 and ignores capitals
  if str1 > str2 return positive
  if str1 < str2 return negetive
  if equals return 0*/
int StrCaseCmp(const char *str1, const char *str2);

/*The StrChr() returns a pointer to the first occurrence
of the character chr in the string str*/
char *StrChr(const char *str, int chr);

/*The  strdup() function returns a pointer to a new string 
  which is a duplicate of the string s.  
  Memory for the new string is obtained with malloc(3), 
  and can be freed with free(3)*/
char *StrDup(const char *str);

/*function appends the src string to the dest string, 
  overwriting the terminat‐ing null byte ('\0') at the end of dest.*/
char *StrCat(char *dest, const char *src);

/*strncat():Appends the first num characters of source to destination, 
  plus a terminating null-characte*/
char *StrnCat(char *dest, const char *src, size_t num);

/*function finds the first occurrence of the substring needle
  in the string haystack. 
  The terminating '\0' characters are not compared.*/
char *StrStr(const char *haystack, const char *needle);

/*strspn - function calculates the length (in bytes) of the initial        
  segment of s which consists entirely of bytes in accept.*/
size_t StrSpn(const char *str, const char *accept);


/******************************************************************************/

#endif /*(__STRING_H__)*/
