#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "String.h"

void strlen_Test ();
void strcmp_Test ();
void strcpy_Test();
void strncpy_Test();
void strncmp_Test();
void strcasecmp_Test();
void strchr_Test();
void strdup_Test();
void strcat_Test();
void strncat_Test();
void strstr_Test();
void strspn_Test();

int main()
{ 
   strlen_Test();   
   strcmp_Test();
   strcpy_Test();
   strncpy_Test();
   strncmp_Test();
   strcasecmp_Test();
   strchr_Test();
   strdup_Test();
   strcat_Test();
   strncat_Test();
   strstr_Test();
   strspn_Test();

   return 0;
}

void strlen_Test()
{
    char *str_arr[10] = {"","a","abc","abcd","abcde","abcdef","abcdefg","abcdefgh","abcdefghi","abdcefghij"};
    size_t i = 0;
    
    for(; i<10 ; ++i)
    {
       if(StrLen(str_arr[i]) != strlen(str_arr[i]))
       {
           printf("wrong calculation on %ld word \n", i);
       }
    }
    
    printf("StrLen checked:)\n");  
}

void strcmp_Test()
{
   char *str_arr1[10] = {"","a","abc","abccd","abcde","abcdef","abcdefg","abcdefgsh","abcdefghid","abdcefgzhij"};
   char *str_arr2[10] = {"ddf","","asbc","abcd","abcde","abcdef","abccdefg","abcdefgh","abcdefghis","abdcefgchij"};
   size_t i = 0;
   
   for(; i<10 ; ++i)
   {
      if(StrCmp(str_arr1[i],str_arr2[i]) != strcmp(str_arr1[i],str_arr2[i]))
      {
          printf("wrong comparation on %ld word \n", i);
      }
   }
   
   printf("StrCmp checked:)\n");
}

void strcpy_Test()
{
    char *source[] = {"ddf","","asbc","abcd","abcde","abcdef","abccdefg","abcdefgh","abcdefghis","abdcefgchij"};
    char *tested_destination;
    char *destination;
    size_t i = 0;
    size_t len = 0;
    
    for(; 10 > i ; ++i)
    {
        len = strlen(source[i])+1;
        destination = (char*)malloc(sizeof(char)*len);
        assert(destination);
        tested_destination = (char*)malloc(sizeof(char)*len);
        assert(tested_destination);
        
        strcpy(destination,source[i]);
        StrCpy(tested_destination,source[i]);
        
        if(0 != strcmp(tested_destination,destination))
        {
            printf("wrong copy on %ld word \n", i);
        }
        
        free(destination);
        destination=NULL;
        free(tested_destination);
        tested_destination=NULL;             
    }
    
    printf("StrCpy checked:)\n");

}

void strncpy_Test()
{
    char *source[] = {"ddf","","asbc","abcd","abcde","abcdef","abccdefg","abcdefgh","abcdefghis","abdcefgchij"};
    char *tested_destination;
    char *destination;
    size_t i = 0;
    size_t len = 0;
    
    for(; 10 > i ; ++i)
    {
        len = strlen(source[i]) + 1;
        destination = (char*)malloc(sizeof(char)*len);
        assert(destination);
        tested_destination = (char*)malloc(sizeof(char)*len);
        assert(tested_destination);
        
        strncpy(destination,source[i], i);
        StrnCpy(tested_destination, source[i], i);
        
        if(0 != strncmp(tested_destination,destination,i))
        {
            printf("wrong n copy on %ld word \n", i);
        }
        
        free(destination);
        destination = NULL;
        free(tested_destination);
        tested_destination = NULL;         
    }
    
    printf("StrnCpy checked:)\n");

}

void strncmp_Test()
{
   char *str_arr1[10] = {"","a","abc","accd","abcde","abdef","abcdefg","abcdefgsh","acdefghid","abdcefgzhij"};
   char *str_arr2[10] = {"ddf","","asbc","abcd","abcde","abcdef","abcdefg","abcdefgh","abcdefghis","abccfgchij"};
   size_t i = 0;
   
   for(; 10 > i ; ++i)
   {
      if(StrnCmp(str_arr1[i], str_arr2[i], 3) != strncmp(str_arr1[i], str_arr2[i], 3))
      { 
          printf("wrong n comparation on %ld word \n", i);
      }
   }
   
   printf("StrnCmp checked:)\n");
}

void strcasecmp_Test()
{
   char *str_arr1[10] = {"a{D[a","","aSbC","accd","abcde","a[cdeF","abcdefg","abcdefgh","abcdefghiS","abdcefgzhij"};
   char *str_arr2[10] = {"a{d{a","","asbc","accd","abcdE","a[cdef","abcDefg","abCdeFgh","abcdefghis","abccfgchij"};
   size_t i = 0;
   
   for(; i<10; ++i)
   {
      if(StrCaseCmp(str_arr1[i], str_arr2[i]) != strcasecmp(str_arr1[i], str_arr2[i]))
      {
          printf("wrong case comparation on %ld word \n", i);
      }
   }
   
   printf("StrCaseCmp checked:)\n");
}

void strchr_Test()
{
   char *str_arr[5] = {"","http://www.tutorialspoint.com","abc","ac/cd","abcdfde"};
   int ch[5] = {',','.','b','/','g'};
   size_t i = 0;
   
   for(; 5 > i; ++i)
   {
        if(strchr(str_arr[i], ch[i]) != StrChr(str_arr[i], ch[i]))
        {
            printf("wrong strchr on %ld word \n", i);
        }  
   }
   
   printf("StrChr checked:)\n");
}

void strdup_Test()
{
    char *source[] = {"ddf","","asbc","abcd","abcde","abcdef","abccdefg","abcdefgh","abcdefghis","abdcefgchij"};
    char *duplicate;
    size_t i = 0;
    size_t old_len = 0;
    size_t new_len = 0;
    
    for(; 10 > i ; ++i)
    {
        duplicate = StrDup(source[i]);
        old_len = strlen(source[i]);
        new_len = strlen(duplicate);
        if(old_len != new_len)
        {
            printf("wrong len duplicate on %ld word \n", i);
        }
        if(strcmp(duplicate , source[i]))
        {
            printf("wrong duplicate on %ld word \n", i);
        }
        
        free(duplicate);
        duplicate = NULL;
                    
    }
    
    printf("StrDup checked:)\n");
}

void strcat_Test()
{
    char source1[10][20] = {"ddf","","asbc","abcd","abcde","abcdef","abccdefg","abcdefgh","abcdefghis","abdcefgchij"};
    char source2[10][20] = {"ddf","","asbc","abcd","abcde","abcdef","abccdefg","abcdefgh","abcdefghis","abdcefgchij"};
    char to_cat[10][3] = {"aa","bb","cc","dd","ee","ff","gg","hh","ii","jj"};
    size_t i = 0;
    
    for(; 10 > i ; ++i)
    {
        StrCat(source1[i],to_cat[i]);
        strcat(source2[i],to_cat[i]);
        if(strcmp(source1[i] , source2[i]))
        {
            printf("wrong cat on %ld word \n", i);
        }            
    }
    
    printf("StrCat checked:)\n");
}

void strncat_Test()
{
    char source1[10][20] = {"ddf","","asbc","abcd","abcde","abcdef","abccdefg","abcdefgh","abcdefghis","abdcefgchij"};
    char source2[10][20] = {"ddf","","asbc","abcd","abcde","abcdef","abccdefg","abcdefgh","abcdefghis","abdcefgchij"};
    char to_cat[10][3] = {"aa","bb","cc","dd","ee","ff","gg","hh","ii","jj"};
    size_t i = 0;
    
    for(; 10 > i ; ++i)
    {
        StrnCat(source1[i],to_cat[i],1);
        strncat(source2[i],to_cat[i],1);
        if(strcmp(source1[i] , source2[i]))
        {
            printf("wrong n cat on %ld word \n", i);
        }            
    }
    
    printf("StrnCat checked:)\n");
}

void strstr_Test()
{
    char source1[4][20] = {"Hello, how are you?","Aya Hamoud"};
    char source2[4][20] = {"you","ya"};
    char *result;
    char *expected_result;
    size_t i = 0;
    
    for(; 2 > i ; ++i)
    {
        result = StrStr(source1[i],source2[i]);
        expected_result = strstr(source1[i],source2[i]);
        if(strcmp(expected_result , result))
        {
            printf("wrong n cat on %ld word \n", i);
        }
            
    }
    
    printf("StrStr checked:)\n");
}

void strspn_Test()
{
   char *str_arr1[10] = {"red flowers","i don't know","right there","","sdd","compare these two variables","aaaaa","abcabc","abcdefghi","abdcefgzhij"};
   char *str_arr2[10] = {"are","i'm","the","dds","sd","two","a","sdf","as","dffr"};
   size_t i = 0;
   for(; i<10 ; ++i)
   {
      /*printf("strsp %s have %s: %ld | StrSpn %s have %s: %ld\n",str_arr1[i],str_arr2[i],strspn(str_arr1[i],str_arr2[i]),str_arr1[i],str_arr2[i],StrSpn(str_arr1[i],str_arr2[i]));*/
      if(StrSpn(str_arr1[i],str_arr2[i]) != strspn(str_arr1[i],str_arr2[i]))
      {
          printf("wrong spin on %ld word \n", i);
      }
   }
   
   printf("StrSpn checked:)\n");
}





