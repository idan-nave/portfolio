/********************************** ws8_files.c  ******************************/
/*
  Name: HRD 32
  Project: Work Sheet 8 - Files
  Reviewer: 1. Uri
            2. Dima  - RESENT
  Date: 26/07/23
  Version: 1.0 - 23/07/23 - publish
           1.1 - 25/07/23 - static functions & conventions changes
           1.2 - 26/07/23 - fixed TODOs by Dima (see reviewed copy)
*/
  
/******************************** LIBRARIES  **********************************/
#include <assert.h> 		/* For input validation */
#include <stddef.h>  		/* For size_t type*/
#include <stdio.h>  		/* For standard input/output */
#include <stdlib.h> 		/* For memory allocation */
#include <string.h>             /* For string manipulation */
#include <unistd.h>             /* access(), lseek() files*/

#include "ws8_files.h" 		/* For team's API */

/******************************** DEFINES  **********************************/

#define EOS '\0'		/* For end of strings */
#define EOR "\0"		/* For end of strings */
	                        /* default path for file storing: */
#define FILES_REL_PATH "/home/idan/Documents/Dev/Git_WD/c/ws8_files/files/"

/* String Limitations */
#define MAX_BUFF 255	        /* Max Buffer size */
#define MAX_FileName 255	/* Max FileName size */
#define MAX_CMD_LEN 20	        /* Max command flag string length */
#define MENU_CH_NUM 6	        /* Number of menu choices */

/********Error Info Struct Definition (appendix to the error Enum) ************/
typedef struct
{
    err_code_ty code;
    const char* message;
} err_msg_ty;

/********************** Error Messages Array Definition **********************/
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
    {FILE_EXISTS, "File already Exists"}
};
 
/******************************************************************************/
/**************** Forward Declarations of Static Functions ********************/
/******************************************************************************/
 
  /******************** Memory Allocations Functions ************************/

/* Function that allocates & initialize program resources */
static int AllocateGlobals();
/* Function that free program resources */
static int FreeGlobals();
/* Function that allocates & initialize array of handlers */
static void InitHandlerStruct(op_handler_ty *arr);
/* Function that frees allocations of array of handlers */
static void FreeHandlerStruct(op_handler_ty* arr);

  /************************** User Input Functions **************************/

/* Function that prints a short manual from file */
static void GreetUser();
/* Function that validates main arguments equal allowed val*/
static int ValidateArguments(size_t argc, size_t val);
/* Function that compares user-input to a command request */
static int HandleUserInput();
/* Function that exit from user-input-loop by purging the used file name */
static int ExitLogger(const char *filename, const char *str);
/* Function that acquirers stdin into a specified buffer */
/* if echo is 1, notify success/errors. */
/* if extract_first_line is 1, only 1st line is considered input & add EOS. */
/* return 0: successfully | 1: Failed Acquiring String. */
static int GetInputString(char *buff, int echo, int extract_first_line);

  /************************** Files Functions *******************************/

/* Function that creates a new file based on given filename (and full path)
   filename validation must be done before call. */
static int FileCreate(const char *filename);
/* Function that opens a file by given name and opening mode as such: */
static int FileOpen(const char *filename, const char *mode);
/* Function that closes the log file using the global "current_file_ptr" */
static int FileClose();
/* Function that return true if the file specified by the filename exists */
static int IsFileExists(const char *filename);
/* Function that prints file to CLN*/
static int FilePrint(const char *filename, const char *str);
/* Function that validates a file pointer */
static int ValidateFilePointer(FILE *fp);

  /******************** String Hanldling Functions **************************/

/* Function to compare user flag with str */
static int CompareFlag(const char* flag, const char *str);
/* Function that validates a file name (for linux systems) */
static int ValidateFileName(const char* filename);
/* Function that build filename from relative path */
static int BuildFilePath(const char* rel_path, const char* filename);


/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
  /**************** App Manager Function (called from Main) *****************/
 
int LoggerApp(int argc, const char *filename_input)
{  
      /* if only program name was entered, show manual*/
      if (1 == argc)
      {
        GreetUser();
        return NO_ERROR;
      }
      
      /* Validate Arguments - must be 2: #1- main, #2- filename*/
      err = ValidateArguments(argc, 2);
      /*chain errors from auxiliary functions up-to main.
      this practice will be held throughout the implementation*/
      if(err)
      {
        return err;
      }

       /* Allocate Memory for runtime */
       AllocateGlobals();
       if(err)
       {
          return FreeGlobals();
       }
       
        /* replace the \n' at end of filename with termination */
       strcpy(current_file_name, filename_input);
       current_file_name[strlen(filename_input)+1] = EOS;
       
       /* Validate entered filename against allowed inputs*/
       err = ValidateFileName(current_file_name);
       if(err)
       {
          return FreeGlobals();
       }

       /* Build a filename so the file be stored under .../files/
       with respect to executable file, this will update the global
       "current_file_name" */
       err = BuildFilePath(FILES_REL_PATH, current_file_name);
       if(err)
       {
          return FreeGlobals();
       }
       
       /* Create the log file inside the relative path */
       err = FileCreate(current_file_name);
       if(err == FILE_EXISTS)
       {
            /* if file already exists, new copy log is generated */
            strcat(current_file_name, "-new");
            /* continue logging in a new file*/
            printf("A new log was generated:\n '%s-new'\n" ,filename_input);
       }
       else if (err)
       {
          return FreeGlobals();
       }

       /* Allocates & initialize array of command handlers */
       InitHandlerStruct(op_h_arr);
       
       /* keep take input from user & analyze operation requests */
       err = HandleUserInput();
       if(err)
       {
          return FreeGlobals();
       }

       /* free memory resources */
       err = FreeGlobals();
       if(err)
       {
         return err;
       }
       
       return NO_ERROR;
}


/* Function that appends a string to an already current opened file*/
int FileAppend(const char *str, const char* filename)
{
    filename; /* unused */ 
    /* Open file*/
    err = FileOpen(current_file_name,"a");
    if(err)
    {
      return err;
    }
    
    /* append to file using fputs() */
    /* The return value of fputs is the number of characters written 
    (excluding the null-terminator) if successful. else - returns EOF */
    if (fputs(str, current_file_ptr) != EOF)
    {
        fprintf(stderr, "FileAppend Error: %s\n",
        info[FILE_WRITE_ERROR].message);
        err = FileClose();
        return FILE_WRITE_ERROR;
    }
        
    /* Close file*/
    err = FileClose();
    if(err)
    {
      return err;
    }
    return NO_ERROR;
}

/* Function that pre-appends a string to an already current opened file*/
int FilePreAppend(const char *str, const char* filename)
{
    /* Get the current position of the file */
    size_t fileSize = ftell(current_file_ptr);  
    
    /* temp to store the existing content of the file */
    char* temp = (char*)malloc(fileSize + 1);
    
    filename; /* unused */
    /* Open file (updates current_file_ptr) */
    err = FileOpen(current_file_name, "r");
    if(err)
    {
      return err;
    }
    
    /* Calculate the size of the file */
    /* Set the file position indicator to EOF */
    fseek(current_file_ptr, 0, SEEK_END); 
    /* Reset the file position indicator to SOF */
    fseek(current_file_ptr, 0, SEEK_SET);  

    if (NULL == temp)
    {
        /* handle memory allocation error */
        fprintf(stderr, "FilePreAppend Error: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }

    /* Read the contents of the file, 1 byte at the time - into temp */
    fread(temp, 1, fileSize, current_file_ptr);  
    temp[fileSize] = '\0';
         
    /* Close file*/
    err = FileClose();
    if(err)
    {
      return err;
    }

    /* Open file with w for overwriting*/
    err = FileOpen(current_file_name,"w");
    if(err)
    {
      return err;
    }
    
    /* append to file using fputs() */
    /* The return value of fputs is the number of characters written 
    (excluding the null-terminator) if successful. else - returns EOF */
    if (fputs(str, current_file_ptr) != EOF
    && fputs(temp, current_file_ptr) != EOF)
    {
        fprintf(stderr, "FilePreAppend Error: %s\n",
        info[FILE_WRITE_ERROR].message);
        err = FileClose();
        return FILE_WRITE_ERROR;
    }
    
    /* Free the allocated memory */
    free(temp);   temp = NULL;
        str;
    /* close the file */
    err = FileClose();
    if(err)
    {
      return err;
    }
    
    return NO_ERROR;
}

/* Function that deletes a file. */
int FileRemove(const char *filename, const char* str)
{
    str; /* unused */
    /* Remove file, but if within program -
    new inputs will create and write to file*/
    if (remove(filename) != 0)
    {
        fprintf(stderr, "FileRemove Error: %s\n",
        info[FILE_READ_ERROR].message);
        return FILE_READ_ERROR;
    }
    return NO_ERROR;
    
    /* close file & reset ptr */
    FileClose();
}

/* Function that counts lines in a file */
int FileCountLines(const char *filename, const char* str)
{
    /* print number of lines to CNL */
    size_t l_count = 0;
    /* hold counted char */
    char c = fgetc(current_file_ptr);
    
    str; /* unused */
    /* Open file*/
    err = FileOpen(filename,"r");
    if(err)
    {
      return err;
    }

    while(EOF != c)
    {
        /* detect new line using \n */
        if('\n' == c)
        {
          ++l_count;
        }
        c = fgetc(current_file_ptr);
    }
    /*report count of lines*/
    printf("File %s has %lu lines\n", filename, l_count);
    
    /* Close file*/
    err = FileClose();
    if(err)
    {
      return err;
    }
    
    return l_count;
}

/* Function that prints current file contents to CLN*/
static int FilePrint(const char *filename, const char *str)
{   
    size_t l_count = FileCountLines(filename, "unused");
    size_t i = 0;
    unsigned char c = ' ';   /* holds contents from file */ 
    
    str; /*unused */
     
    /* Open file*/
    err = FileOpen(filename,"r");
    if(err)
    {
      return err;
    }
    
    /* print contents from file */
    while (i < l_count)
    {
        putchar(c);
        c = fgetc(current_file_ptr);
        if (c == '\n') ++i;
    }
    
    /* Close file*/
    err = FileClose();
    if(err)
    {
      return err;
    }
    
    printf("\n");    /* end print back at input descriptor*/
    return NO_ERROR;
}


/******************************************************************************/
/******************************************************************************/

/************************ Memory Allocations Functions ************************/

/* Function that allocates & initialize program resources */
static int AllocateGlobals()
{ 
    /* allocate array of handlers*/
    op_h_arr =
    (op_handler_ty*)malloc(sizeof(op_handler_ty)*MENU_CH_NUM);
    /* allocate string for user-inputs storing*/
    input_buff = (char*)malloc(sizeof(char)*MAX_BUFF); 
    /* allocate string to hold log name */
    current_file_name = (char*)malloc(sizeof(char)*MAX_FileName); 
    
    /* validate successful allocations */
    if (NULL == op_h_arr && NULL == input_buff && NULL == current_file_name)
    {
        fprintf(stderr, "AllocateGlobals Error: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }
    return NO_ERROR;
}

/* Function that free program resources */
static int FreeGlobals()
{
    /* free array of command handlers */
    FreeHandlerStruct(op_h_arr);
       
    /* allocate array of handlers*/
    free(op_h_arr);             op_h_arr = NULL;
    free(input_buff);           input_buff = NULL;
    free(current_file_name);    current_file_name = NULL;
    
    return NO_ERROR;
}

/* Function that allocates & initialize array of handlers */
static void InitHandlerStruct(op_handler_ty *arr)
{
    /* initial values stored in arrays, to be populating the handlers structs */
    char com_arr[][MAX_CMD_LEN] =
    {"-remove", "-count", "-exit", "<", "-print", "\0"};
    func_ptr op_arr[] = 
    {FileRemove, FileCountLines, ExitLogger, FilePreAppend, FilePrint, NULL};
    
    size_t i = 0;
    /* as long as did not reach end of struct marked by "\0" in member ".cmd" */
    while( i < MENU_CH_NUM )
    {
      /* initialize members with the above-arrays values */
      arr[i].cmd = (char*)malloc(sizeof(char)*MAX_CMD_LEN);
      strcpy(arr[i].cmd, com_arr[i]);
      arr[i].compare_func = CompareFlag;
      arr[i].operation_func = op_arr[i];
      ++i;
    }
}

/* Function that frees allocations of array of handlers */
static void FreeHandlerStruct(op_handler_ty *arr)
{
    size_t i = 0;
    /* as long as did not reach end of struct marked by "\0" in member ".cmd" */
    while( i < MENU_CH_NUM )
    {
      /* initialize members with the above-arrays values */
      free(arr[i].cmd);
      arr[i].cmd = NULL;
      ++i;
    }
}

/****************************** User Input Functions **************************/

/* Function that prints a short manual from file */
static void GreetUser()
{  
    printf("Hello, Welcome to the File Logger program!\n"
    "Dont forget to enter file name!\n");
    /* print contents from manual file */
    FilePrint("/home/idan/Documents/Dev/Git_WD/c/ws8_files/files/man", "unused");
    /*FilePrint(FILES_REL_PATH"/man", "unused"); optional solution?*/
}

/* Function that validates main arguments equal allowed val*/
static int ValidateArguments(size_t argc, size_t val)
{
    if(argc != val)
    {
        fprintf(stderr, "Bad Arguments # %d", err);
    }
    return err;
}

/* Function that compares user-input to a command request */
static int HandleUserInput()
{
  /* listen for user inputs */
  size_t i = 0;
  size_t skip_flag_len = 0;
  size_t found_flag = 0;
  /* as long as the file_name is valid (was not purged by  user action) */   
  while (NULL != current_file_name)
  {
    /* update buffer with user inputs */   
    GetInputString(input_buff,0,0);
    
    /* as long as not finish scanning the handlers array 
    (strcmp returns other-than-0 if not equal) */  
    while( 0 != strcmp(op_h_arr[i].cmd, EOR) && !found_flag)
    {
        /* compare the op command against the input using the .compare_func: 
        if flag found: */   
        if(NOT_FOUND != op_h_arr[i].compare_func(op_h_arr[i].cmd, "unused") )
        {
            found_flag = 1;
            skip_flag_len = strlen(op_h_arr[i].cmd);
            if( 0 == strcmp(op_h_arr[i].cmd, "<") )
            {
                /* pre-append func needs to recieve str as argument */
                op_h_arr[i].operation_func(input_buff + skip_flag_len, "unused");
            }
            else
            {  
                /* any other func needs to recieve filename as argument */
                op_h_arr[i].operation_func(current_file_name, "unused");
            }
        }
        ++i;
    }
    /* if flag was not found, keep append strings to end of file (append) */
    if(0 == found_flag)
    {
        FileAppend(input_buff, current_file_name);
    }
    i = 0;
    found_flag = 0;
  }
  printf("End of user input, Goodbye!\n");
  return NO_ERROR;
}

/* Function that exit from user-input-loop by purging the used file name */
static int ExitLogger(const char *filename, const char *str)
{
    str; /*unused */
    filename; /*unused */
    /* purge filename pointer as it is a requirement for input listening loop */
    free(current_file_name);    current_file_name = NULL;
    return NO_ERROR;
}

/* Function that acquirers stdin into a specified buffer */
/* if echo is 1, notify success/errors. */
/* if extract_first_line is 1, only 1st line is considered input & add EOS. */
/* return 0: successfully | 1: Failed Acquiring String. */
static int GetInputString(char *buff, int echo, int extract_first_line)
{
   /* taking user input from the console using fgets() */
   if(NULL != fgets(buff, MAX_BUFF, stdin))
   {    
        /* if was asked to echo input */
        if(echo) printf("The entered string is : %s", buff);
        /* if was asked to remove the '\n' because of CLN behaviour */
        if(extract_first_line)
        {   /* replace the first occurance on '\n' with termination */
            char* idx_to_trm = strchr( (const char*)buff,'\n');
            *idx_to_trm = EOS;
        }
        return NO_ERROR;
   }
   /* else */
   fprintf(stderr, "GetInputString Error: %s\n",
   info[INVALID_STRING].message);
   return INVALID_STRING;
}

/****************************** Files Functions *******************************/

/* Function that creates a new file based on given filename (and full path)
   filename validation must be done before call. */
static int FileCreate(const char *filename)
{
    /*check if file already exists - if so, do not create new one*/
    if (0 == IsFileExists(filename))
    {
        fprintf(stderr, "FileCreate Error: %s\n",
        info[FILE_EXISTS].message);
        return FILE_EXISTS;
    }
    
    /* proceed to create within the default path*/
    err = FileOpen(filename,"w");
    if(err)
    {
      return err;
    }
    
    /* close the created file */
    err = FileClose();
    if(err)
    {
      return err;
    }
    return NO_ERROR;
}

/* Function that opens a file by given name and opening mode as such: */
/*
    "r": Open for reading. The file must exist.
    "w": Open for writing. If the file exists, its contents are truncated, 
        meaning that all existing data in the file will be deleted.
        If the file does not exist, a new file is created.
    "a": Open for appending. Data is written at the end of the file. 
      If the file does not exist, a new file is created.
    "b": Open in binary mode. This flag is typically used in combination 
      with other flags (e.g., "rb", "wb") to perform binary file operations.
    "+": Open for both reading and writing. This flag allows you to perform 
      both read and write operations on the file.
    "t": Open in text mode. This is the default mode, and it can be omitted.
      Text mode performs newline translation and platform-specific operations.
    supports multiple flags by concatenating them as strings. example: "rb" rep
*/
static int FileOpen(const char *filename, const char *mode)
{
   
    /* Validate no file is open before proceeding */
    /* if so- it means bad closing handling within implementation */
    if (NULL != current_file_ptr)
    {
        fprintf(stderr, "Error: Another File (%d) "
        "is already open\n", current_file_ptr->_fileno);
        return PERMISSION_DENIED;
    }
    
    /* proceed to open file */
    current_file_ptr = fopen(filename, mode);
    
    /* DEBUG MESSAGE */
     /*fprintf(stderr, "opened file #(%d), times: %ld\n",
    current_file_ptr->_fileno, ++debug_opens); */
    
    err = ValidateFilePointer(current_file_ptr);
    if(err)
    {
      return err;
    }
    return NO_ERROR;   
}

/* Function that closes the log file using the global "current_file_ptr" */
static int FileClose()
{               
    /* DEBUG MESSAGE */
    /*fprintf(stderr, "closed file #(%d), times: %ld\n",
    current_file_ptr->_fileno, ++debug_closes);*/
              
    /* close file & reset ptr */
    fclose(current_file_ptr);
    current_file_ptr = NULL;
    return NO_ERROR;
}

/* Function that return true if the file specified by the filename exists */
static int IsFileExists(const char *filename)
{
    /*returns 0 if the access is permitted, or 1 otherwise.*/
    return access(filename, F_OK) != 0;
    /*    R_OK – test for the read permission
          W_OK – test for the write permission
          X_OK – test for the execute permission
          F_OK – test for the existence of the file.    */
}

/* Function that validates a file pointer */
static int ValidateFilePointer(FILE *fp)
{   
    /* validate file pointer not null*/
    if(NULL == fp)
    {
        fprintf(stderr, "ValidateFilePointer Error: %s\n",
        info[NULL_STRING_ERROR].message);
        return NULL_STRING_ERROR;
    }
    return NO_ERROR;
}

/************************ String Hanldling Functions **************************/

/* Function to compare user flag with str, returns index found, otherwise NOT_FOUND */
static int CompareFlag(const char* flag, const char *str)
{    
    str;
    /* strstr returns NULL if not found, if flag found: */   
    if(NULL == strstr(input_buff, flag) )
    {
          return NOT_FOUND;
    }
    /* return idx of first char in flag str */   
    return strchr( input_buff, *flag ) - input_buff;
}

/* Function that validates a file name (for linux systems) */
/*
    Maximum Length:  255 characters.
    Character Restrictions: "/", "", "?", "*", ":", "<", ">", "|", quotes ('"').
    Reserved Characters: ".", "..", "~". have specific meanings 
    Null Byte: Filenames cannot contain a null byte (ASCII value 0)mum filename 
*/
static int ValidateFileName(const char* filename)
{   
    /* array of invalid characters as needed */
    const char invalid_chars[] = {'/', '\\', '?', '~'}; 
    size_t i = 0;

    /* validate filename not NULL or empty*/
    if(0 == strlen(filename) )
    {
        fprintf(stderr, "ValidateFileName Error:  name: %s\n %s\n",
        filename, info[NULL_STRING_ERROR].message);
        return NULL_STRING_ERROR;
    }    
    
    /*as long as a restricted character is not found */
    while(i < sizeof(invalid_chars))
    {
        if(NULL != strchr(filename, invalid_chars[i]))
        {
            fprintf(stderr, "ValidateFileName Error: invalid char #%ld-'%c':"
            " in file: %s\n, %s\n", i, invalid_chars[i],
             filename, info[INVALID_STRING].message);
            return INVALID_STRING;
        }
        ++i;
    }
    return NO_ERROR;
}

/* Function that build filename from relative path */
static int BuildFilePath(const char* rel_path, const char* filename)
{
    /* temp for original name */
    char* temp_name = (char*)malloc(strlen(filename) + 1);
    if (NULL == temp_name)
    {
        /* handle memory allocation error */
        fprintf(stderr, "BuildFilePath Error: %s\n",
        info[MEMORY_ALLOCATION_ERROR].message);
        return MEMORY_ALLOCATION_ERROR;
    }
    /* store filename in temp */
    strcpy(temp_name, filename);
    
    strcpy(current_file_name, "\0");    /* purge string*/
    strcpy(current_file_name, rel_path);/* copy path*/
    strcat(current_file_name, temp_name);/* copy name*/
     
     /* Free the allocated temp */
    free(temp_name);   temp_name = NULL;
    
    if(NULL == current_file_name)
    {
        fprintf(stderr, "BuildFilePath Error: %s\n",
        info[NULL_STRING_ERROR].message);
        return NULL_STRING_ERROR;
    }
    return NO_ERROR;
}
