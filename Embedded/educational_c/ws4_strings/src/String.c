/******************************* Strings.C META  ******************************/
/*
  Name: HRD 32
  Project: String Function Re-implementation
  Reviewer: Aya
  Date: 04/07/2023
  Version: 1.0
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* For input validation */
#include <stddef.h>  		/* For size_t type*/
#include <stdlib.h> 		/* For memory allocation and de-allocation */

#include "String.h" 		/* For team's API*/

#define EOS '\0'		/* For end of strings

/******************** STRINGS API IMPLEMENTATIONS  ****************************/

/*The StrLen() compute and return the length of string*/
size_t StrLen(const char *str)
{
      	size_t i = 0;				/*initialize counter*/
	assert(NULL != str);			/*validate input*/
	
	while(EOS != *str)			/*while current elem not end str*/
	{
		++i;				/*increment counter*/
		++str;				/*increment element*/
	}
	return i;				/*return counter*/
}

/*The StrCmp() compare between two strings. return *str1-*str2
	•if str1 > str2 return positive
	•if str1 < str2 return negetive
	•if equals return 0*/
int StrCmp(const char *str1, const char *str2)/*function requires end '/0'*/
{
        assert(NULL != str1);			/*validate input*/
        assert(NULL != str2);			/*validate input*/
        
	/*while any curr elem not end*/
	while((*str1 == *str2) && (EOS != *str1))
	{
		++str1; ++str2;		        /*increment counters*/
	}
	return *str1 - *str2;		        /*return offset between ends*/
}

/*The StrnCmp() function compares only the first (at most)
  num bytes of the two strings str1 and str2.
  StrnCmp() returns an integer indicating the result of the comparison,
  as follows:
       • 0, if the str1 and str2 are equal;
       • a negative value if str1 is less than str2;
       • a positive value if str1 is greater than str2.*/
int StrnCmp(const char *str1, const char *str2, size_t num)
{
    size_t i = 0;
    assert(NULL != str1);			/*validate input*/
    assert(NULL != str2);			/*validate input*/

    while (i < num && str1[i] == str2[i] && str1[i] != '\0')
    {
        i++;		/*Keep iterate until same places chars are inequal*/
    }

    if (i == num)
    {
        return 0;
    } 
    else
    {	
/* return ASCII range between last char of shorter string and its counter char*/
        return (unsigned char)str1[i] - (unsigned char)str2[i];
    }
}

/*The StrCpy() Receives a pointer to a constant string to be copied, 
  and a pointer to the location to copy it into, 
  returns the pointer to the user/caller after the run finishes.*/
char *StrCpy(char *dest, const char *src)
{
	size_t i = 0;				/*Set counter i = 0*/
        assert(NULL != dest);			/*validate input*/
        assert(NULL != src);			/*validate input*/
        
	while(EOS != *(src+i))			/*while curr src-elem not end*/
	{
		*(dest+i) = *(src+i);
		++i;				/*increment shared counter*/
	}
	*(dest+i) = EOS;			/*Add exit charecter*/
	return dest;				/*return ASCII offset btwm ends*/
}

/*The StrnCpy() function  copies up to n character-string pointed to by src,
  NOT including the terminating null byte ('\0'),
  to the buffer  pointed  to  by  dest.*/
char *StrnCpy(char *dest, const char *src, size_t num)
{
	size_t i = 0;				/*Set counter i = 0*/
        assert(NULL != dest);			/*validate input*/
        assert(NULL != src);			/*validate input*/
        
	while(EOS != *(src+i) && i < num)	/*while curr src-elem < num
	                                        and not end*/
	{
		*(dest+i) = *(src+i);
		++i;				/*increment shared counter*/
	}
	while(i < StrLen(dest))
	{
	 	*(dest+i) = EOS;
	 	++i;				/*increment until dest end*/
	}
	return dest;				/*return ASCII offset btwm ends*/
}


/*The StrCaseCmp() compare between two strings.
return *str1-*str2 and ignores capitals
  if str1 > str2 return positive
  if str1 < str2 return negetive
  if equals return 0*/
int StrCaseCmp(const char *str1, const char *str2)
{
    size_t i = 0;
    assert(NULL != str1);			/*validate input*/
    assert(NULL != str2);			/*validate input*/
    
    /* iretate over both strings while enforcing lower casting */
    while (tolower(str1[i]) == tolower(str2[i]) && str1[i] != '\0')
    {
        i++;
    }
/* return ASCII range between last char of shorter string and its counter char*/
    return tolower(str1[i]) - tolower(str2[i]);
}

/*The StrChr() returns a pointer to the first occurrence
of the character chr in the string str*/
char *StrChr(const char *str, int chr)
{
    size_t i = 0;
    assert(NULL != str);			/*validate input*/
    
    while (str[i] != '\0')
    {
        if (str[i] == chr)
        {
            return (char*)(str + i); /* Return pointer to the found character*/
        }
        i++;
    }
    return NULL; /* Character not found*/
}

/*The StrDup() function returns a pointer to a new string 
  which is a duplicate of the string s.  
  Memory for the new string is obtained with malloc(3), 
  and can be freed with free(3)*/
char *StrDup(const char *str)
{
    assert(NULL != str);			/*validate input*/
        
    size_t len = StrLen(str) + 1;
    char* dup = (char*)malloc(len * sizeof(char));
    if (dup != NULL)	/* validate allocation success */
    {
        StrCpy(dup, str);
    }

    return dup;
}

/*The StrCat() function appends the src string to the dest string, 
  overwriting the terminat‐ing null byte ('\0') at the end of dest.*/
char *StrCat(char *dest, const char *src)
{
    assert(dest != src);			/*validate input*/
      
    /*USER MUST ENSURE DEST IS VALID AND LARGE ENOUGH TO ACCEPT append of both*/
    StrCpy(dest + StrLen(dest), src);	/* cat src starting from end of dest */

    return dest;
}

/*The StrnCat() function Appends the first num characters of source to destination, 
  plus a terminating null-characte*/
char *StrnCat(char *dest, const char *src, size_t num)
{
    assert(dest != src);			/*validate input*/
      
    /*USER MUST ENSURE DEST IS VALID AND LARGE ENOUGH TO ACCEPT append of both*/
    StrnCpy(dest + StrLen(dest), src, num);	/* cat src starting from end of */
    return dest;
}

/*The StrStr() function finds the first occurrence of the substring needle
  in the string haystack. 
  The terminating '\0' characters are not compared.*/
char *StrStr(const char *haystack, const char *needle)
{
	assert(NULL != needle);	              /*validate inputs*/
	char* found_start = StrChr(haystack, (int)needle[0]);
	/*if start of needle does not occures in haystack, end*/
	if(NULL == found_start) return NULL; 
	
	size_t len_needle = StrLen(needle) + 1;
  	if(StrnCmp(needle, haystack, len_needle))/* search sub-string in haystack */
	return found_start; 
}

/*The StrSpn() function calculates the length (in bytes) of the initial        
  segment of s which consists entirely of bytes in accept.*/
size_t StrSpn(const char *str, const char *accept)
{
	assert(NULL != accept);	/*validate inputs*/
	char* found_start = StrChr(accept, (int)str[0]);
	size_t i = 0;
	if(NULL == found_start) return i ;
	
        while (str[i] != '\0' &&  StrChr(accept, (int)str[i]))
        {
	    i++;
        }
        return i; /* Character not found*/	
}
