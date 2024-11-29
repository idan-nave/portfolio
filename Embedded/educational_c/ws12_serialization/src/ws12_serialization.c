/*************************** ws12_serialization.c  **************************/
/*
  Name: HRD 32
  Project: Work Sheet #12 - Serialized Structs
  Reviewer: Sahar
  Date: 31/07/23
  Version: 1.0
*/
/****************************** LIBRARIES  **********************************/

#include <assert.h>                /* assert() */
#include <stdio.h>                 /* FILEs, stderr, stdin, stdout */
#include <stdlib.h>                /* malloc(), free() */
#include <string.h>                /* string manipulation */
#include <errno.h>                 /* errno global */
#include <stddef.h>                /* size_t, NULL */

#include "ws12_serialization.h"

/*Strings Defitions*/
#define MAX_NAME_LEN 20 
#define MAX_PATH_LENGTH 256 
#define UNIT_SIZE 1   
#define SUCCESS 0                         

/*Grades Defitions*/
#define MIN_GRADE 0      
#define MAX_GRADE 100       
#define NUM_OF_GRADES_IN_PORTFOLIO 3  
#define NUM_OF_PORTFOLIOS 2  
#define NUM_OF_GEN_GRADES 1  

#define FLOATS_ARR_SIZE \
        (NUM_OF_GRADES_IN_PORTFOLIO * NUM_OF_PORTFOLIOS) + NUM_OF_GEN_GRADES


/*****************************************************************************/
/*************************** App's Data-structures ***************************/
/*****************************************************************************/
 
typedef struct humnastics
{
    float physics_gr;
    float math_gr;
    float coding_gr;
}real_ty;

 /* struct to hold a group of reals grades  */
typedef struct reals
{
    float sociology_gr;
    float psychology_gr;
    float literature_gr;
}hum_ty;

 /* struct to hold a grades_portfolio descriptor */
typedef struct grades_portfolio
{
    float sport_gr;
    hum_ty grades_hum;
    real_ty grades_real;
}grades_ty;
 
 /* struct to hold a student descriptor */
struct student_grades
{
    char first_name[MAX_NAME_LEN];
    char last_name[MAX_NAME_LEN];
    grades_ty st_portfolio;
};
/*typedef struct student_grades student_ty;*/

  /*************************** Dev Globals  *******************************/

 int debug_file_opens = 0;
 int debug_file_closes = 0;

/*****************************************************************************/
/*************** Forward Declarations of Static Functions ********************/
/*****************************************************************************/

  /************************ Initialization Functions ***********************/

/* Generate and returns a random float in range [lower, upper] */
static float GenRandomFloat(int lower, int upper);
/* Function to initialize grades structures */
static void InitGrades(student_ty *student);
/* Function to initialize student structure */
static void InitStudent
            (student_ty **student, char *first_name, char *last_name);
/* Function to free student structure */
static void FreeStudent(student_ty **student);

  /************************** Serialization Functions **********************/

static int SerializeStudentsFloats(student_ty *student_data, FILE *file_ptr);
static int SerializeStudentsStrings(student_ty *student_data, FILE *file_ptr);
  
  /************************ Deserialization Functions **********************/

static int DeserializeStudentsFloats(student_ty *student_res,FILE *file_ptr);
static int DeserializeStudentsStrings(student_ty *student_res,FILE *file_ptr);
 
  /************************ Validation Functions ************************/

/* Function that Prints Is Successful deserialization-operation message */
static void ValidateDeserialization(student_ty* origin, student_ty* decoded);
static int CompareStudents(const student_ty *origin,const student_ty *decoded);

  /************************** Display Functions ****************************/

/* Function that prints humnastics grades*/
static void HumnasticsSheetPrint(hum_ty* hum_struct);
/* Function that prints reals grades*/
static void RealsSheetPrint(real_ty* real_struct);
/* Function that prints student portfolio*/
static void PortfolioPrint(grades_ty* grades_struct);
/* Function that prints student full data*/
static void StudentPrint(student_ty* student_struct);

  /************************** Files Functions ****************************/

/* Function that creates a valid binary file in path
ends with .bin, overwrie / appends depends on mode "wb"/"ab", returns errno*/
static int CreateBinaryFile(char *file_name, const char *rel_path, char *mode);
/* Function that validates a file name */
static int IsFileNameValid(const char *file_name);
static void AddExtensionIfNeeded(char *file_name, const char *extension);
/* Function that deletes a file. */
static int FileRemove(const char *filename);

/*****************************************************************************/
/*************** API Implementation - Functions Definitions ******************/
/*****************************************************************************/

  /**************** App Manager Function (called from Main) *****************/
 
int StudentGradesApp(const char *bin_file_name)
{
    /* declare apps datatypes */
    student_ty *student_src = NULL;
    student_ty *student_res = NULL;
    char *file_name = (char*)bin_file_name; 
    char *first_name = "Idan";
    char *last_name = "Nave";
   

    /* create a binary file in the right project folder */
    errno = CreateBinaryFile(file_name, "../files", "wb");
    if (errno)
    {
        perror("Error creating binary file");
        return EINVAL;
    }
    printf("Binary file created successfully.\n");


    /* initialize student structures */
    InitStudent(&student_src, first_name, last_name);
    InitStudent(&student_res, "", "");

    /* populate student character */
    InitGrades(student_src);
    /* print original initialized structure */
    StudentPrint(student_src);

    /* Serialization & Deserialization by member */
    errno =SerializeStudents(student_src, file_name);
    if (errno)
    {
        perror("Serialization Failed");
        return EINVAL;
    }
    DeserializeStudents(student_res, file_name);
    
    /* print deserialized structure */
    StudentPrint(student_res);

    /* validate successful Serialization & Deserialization in memory */
    ValidateDeserialization(student_src, student_res);

    /*FileRemove(file_name);*/
    FreeStudent(&student_src);
    FreeStudent(&student_res);

    return SUCCESS;
}

  /*********************** Serialization Functions *************************/

/* Function to Serialize the Whole Student-Struct by Members*/
int SerializeStudents(student_ty *student_data, char *file_name)
{

    /* open file for appending data*/
    FILE *file = fopen(file_name, "ab");
        if (file == NULL)
        {
            perror("Error opening file");
            return EBADFD;
        }
    /* perform the whole serialization process*/
    errno = SerializeStudentsStrings(student_data, file);
    errno = SerializeStudentsFloats(student_data, file);
    
    fclose(file);
    return errno;
}

/* Function to De-Serialize the Whole Student-Struct by Members*/
int DeserializeStudents(student_ty *student_res, char *file_name)
{
    /* open file for readin once, reading op. always brinds file descriptior to the begining of the file*/
    FILE *file = fopen(file_name, "rb");
        if (file == NULL)
        {
            perror("Error opening file");
            return EBADFD;
        }
    /* perform the whole Deserialization process*/
    DeserializeStudentsStrings(student_res, file);
    DeserializeStudentsFloats(student_res, file);
    fclose(file);
}

/* Function to serialize student string data into a file*/
static int SerializeStudentsStrings(student_ty *student_data, FILE *file_ptr)
{
    size_t data_written = 0;
    size_t data_size_valid = 0;

    size_t f_name_len = 0;
    size_t l_name_len = 0;
    f_name_len = strlen(student_data->first_name) + 1;
    l_name_len = strlen(student_data->last_name) + 1;
    
    data_size_valid  = 2 + l_name_len + f_name_len;
    /* serialize name length & string into file */
    data_written += fwrite(&f_name_len, sizeof(size_t), UNIT_SIZE, file_ptr);
    data_written += 
        fwrite(student_data->first_name, sizeof(char), f_name_len, file_ptr);
    data_written += fwrite(&l_name_len, sizeof(size_t), UNIT_SIZE, file_ptr);
    data_written +=
        fwrite(student_data->last_name, sizeof(char), l_name_len, file_ptr);

    /* validate successful writing */
    if (data_written != data_size_valid)
    {
        perror("Error writing names");
        printf("\n %ld != %ld", data_size_valid,data_written);
        return EBADF;
    }
    return SUCCESS;
}

/* Function to serialize student float data into a file*/
static int SerializeStudentsFloats(student_ty *student_data, FILE *file_ptr)
{
    size_t data_written = 0;
    size_t data_size_valid = 0;

    size_t mem_runner = 0;
    float *grade_arr[FLOATS_ARR_SIZE]= {0};

    grade_arr[SPORT_IDX]
                     = &student_data->st_portfolio.sport_gr;
    grade_arr[PHYSICS_IDX]
                     = &student_data->st_portfolio.grades_real.physics_gr;
    grade_arr[MATH_IDX]
                     = &student_data->st_portfolio.grades_real.math_gr;
    grade_arr[CODING_IDX]
                     = &student_data->st_portfolio.grades_real.coding_gr;
    grade_arr[SOCIOLOGY_IDX]
                     = &student_data->st_portfolio.grades_hum.sociology_gr;
    grade_arr[PSYCHOLOGY_IDX]
                     = &student_data->st_portfolio.grades_hum.psychology_gr;
    grade_arr[LITERATURE_IDX]
                     = &student_data->st_portfolio.grades_hum.literature_gr;
    /* serialize sport grade into file */
  
    data_size_valid  = FLOATS_ARR_SIZE;

    while(mem_runner < FLOATS_ARR_SIZE)
    {
      /* write all float-grader in a sequential order*/
       data_written += 
            fwrite(grade_arr[mem_runner], sizeof(float), UNIT_SIZE, file_ptr);
      ++mem_runner;
    }

    /* validate successful writing */
    if (data_written != data_size_valid)
    {
        perror("Error writing floats");
        printf("\n %ld != %ld", data_size_valid,data_written);
        return EBADF;
    }
    return SUCCESS;
}

/* Function to deserialize student string data from a file*/
static int DeserializeStudentsStrings(student_ty *student_res, FILE *file_ptr)
{
    size_t f_name_len = 0;
    size_t l_name_len = 0;
    
    /* deserialize name length & string into file */
    fread(&f_name_len, sizeof(size_t), UNIT_SIZE, file_ptr);
    fread(student_res->first_name, sizeof(char), f_name_len, file_ptr);
    fread(&l_name_len, sizeof(size_t), UNIT_SIZE, file_ptr);
    fread(student_res->last_name, sizeof(char), l_name_len, file_ptr);

    return SUCCESS;
}
    
/* Function to deserialize student floats data from a file*/
static int DeserializeStudentsFloats(student_ty *student_res, FILE *file_ptr)
{   
    size_t mem_runner = 0;
    float *grade_arr[FLOATS_ARR_SIZE]= {0};
    
    grade_arr[SPORT_IDX]
                     = &student_res->st_portfolio.sport_gr;
    grade_arr[PHYSICS_IDX]
                     = &student_res->st_portfolio.grades_real.physics_gr;
    grade_arr[MATH_IDX]
                     = &student_res->st_portfolio.grades_real.math_gr;
    grade_arr[CODING_IDX]
                     = &student_res->st_portfolio.grades_real.coding_gr;
    grade_arr[SOCIOLOGY_IDX]
                     = &student_res->st_portfolio.grades_hum.sociology_gr;
    grade_arr[PSYCHOLOGY_IDX]
                     = &student_res->st_portfolio.grades_hum.psychology_gr;
    grade_arr[LITERATURE_IDX]
                     = &student_res->st_portfolio.grades_hum.literature_gr;
    /* serialize sport grade into file */
  
    while(mem_runner < FLOATS_ARR_SIZE)
    {
      /* write all float-grader in a sequential order*/
       fread(grade_arr[mem_runner], sizeof(float), UNIT_SIZE, file_ptr);
      ++mem_runner;
    }
    return SUCCESS;

}
  /************************ Initialization Functions ************************/
  
/* Function to initialize grades structures */
static void InitGrades(student_ty *student)
{      
    /* populate student grades */
    student->st_portfolio.sport_gr 
                                    = GenRandomFloat(MIN_GRADE, MAX_GRADE);
    student->st_portfolio.grades_real.physics_gr 
                                    = GenRandomFloat(MIN_GRADE, MAX_GRADE);
    student->st_portfolio.grades_real.math_gr 
                                    = GenRandomFloat(MIN_GRADE, MAX_GRADE);
    student->st_portfolio.grades_real.coding_gr 
                                    = GenRandomFloat(MIN_GRADE, MAX_GRADE);
    student->st_portfolio.grades_hum.sociology_gr 
                                    = GenRandomFloat(MIN_GRADE, MAX_GRADE);
    student->st_portfolio.grades_hum.psychology_gr 
                                    = GenRandomFloat(MIN_GRADE, MAX_GRADE);
    student->st_portfolio.grades_hum.literature_gr 
                                    = GenRandomFloat(MIN_GRADE, MAX_GRADE);
}

/* Function to initialize student structure */
static void InitStudent(student_ty **student, char *first_name,char *last_name)
{      
    *student = (student_ty*)malloc(sizeof(student_ty));
    /* populate student grades */
    strcpy(((*student)->first_name), first_name);
    strcpy(((*student)->last_name), last_name);
}

/* Function to free student structure */
static void FreeStudent(student_ty **student)
{      
    free(*student);
    *student = NULL;
}

/* Generate and returns a random float in range [lower, upper] */
static float GenRandomFloat(int lower, int upper)
{
  return (((float)upper - (float)lower)* ((float)rand() / RAND_MAX)) + lower;
}

  /************************ Validation Functions ************************/

/* Function that Prints Is Successful deserialization-operation message */
void ValidateDeserialization(student_ty* origin, student_ty* decoded)
{  
    /* use memcmp to compare entire blocks of ser & deser objects */
    errno = memcmp(origin, decoded, sizeof(student_ty));
    if(SUCCESS == errno)
    {
       printf("\nDeserialization Test using memcmp passed!\n");
    }
    else
    {
       printf("\nDeserialization Test using memcmp failed!\n");
    }

    /* validate successful Serialization & Deserialization in memory */
    if(SUCCESS == CompareStudents(origin, decoded) )
    {
       printf("\nDeserialization Test using members comparision passed!\n");
    }
    else
    {
       printf("\nDeserialization Test using members comparision failed!\n");
    }
}

static int CompareStudents(const student_ty *origin, const student_ty *decoded)
{
    if (origin == NULL || decoded == NULL)
    {
        perror("Invalid students structs");
        return EINVAL; 
    }

    /* Compare first and last names */
    if (strcmp(origin->first_name, decoded->first_name) != 0 ||
        strcmp(origin->last_name, decoded->last_name) != 0) {
        return E2BIG; /* Not equal */
    }

    /* Compare grades portfolio */
    if (        origin->st_portfolio.sport_gr
                == decoded->st_portfolio.sport_gr 
                && origin->st_portfolio.grades_hum.sociology_gr
                == decoded->st_portfolio.grades_hum.sociology_gr
                && origin->st_portfolio.grades_hum.psychology_gr
                == decoded->st_portfolio.grades_hum.psychology_gr
                && origin->st_portfolio.grades_hum.literature_gr
                == decoded->st_portfolio.grades_hum.literature_gr      )
    {
        return SUCCESS; /* equal */
    }
    else
    {
        return E2BIG; /* Not equal */
    }
}

  /************************** Display Functions ****************************/

/* Function that prints humnastics grades*/
static void HumnasticsSheetPrint(hum_ty* hum_struct)
{
    printf("\t\t\tsociology_gr: %.1f\n", hum_struct->sociology_gr );
    printf("\t\t\tpsychology_gr: %.1f\n", hum_struct->psychology_gr );
    printf("\t\t\tliterature_gr: %.1f\n", hum_struct->literature_gr );
}

/* Function that prints reals grades*/
static void RealsSheetPrint(real_ty* real_struct)
{
    printf("\t\t\tphysics_gr: %.1f\n", real_struct->physics_gr );
    printf("\t\t\tmath_gr: %.1f\n", real_struct->math_gr );
    printf("\t\t\tcoding_gr: %.1f\n", real_struct->coding_gr );
}

/* Function that prints student portfolio*/
static void PortfolioPrint(grades_ty* grades_struct)
{
      printf("\tStudent Portfolio contains:\n");
      printf("\t\tsport_gr: %.1f\n", grades_struct->sport_gr);
      HumnasticsSheetPrint(&grades_struct->grades_hum);
      RealsSheetPrint(&grades_struct->grades_real);
}

/* Function that prints student full data*/
static void StudentPrint(student_ty* student_struct)
{
    printf("Student First Name: %s\n", (student_struct->first_name) );
    printf("Student Last Name: %s\n", (student_struct->last_name) );
    PortfolioPrint(&student_struct->st_portfolio);
}

  /************************** Files Functions ****************************/

static int IsFileNameValid(const char *file_name)
{
    size_t i = 0;
    /* Define a list of disallowed characters in file names */
    const char disallowed_chars[] = {'<', '>', '?', '~'}; 
    errno = SUCCESS;
    while (i < strlen(disallowed_chars) )
    {
        if (strchr(file_name, disallowed_chars[i]) != NULL)
        {
            perror("Invalid file name");
            return EINVAL; /* File name contains disallowed character */
        }
         ++i;
    }

    return SUCCESS; /* File name is valid */
}

static void AddExtensionIfNeeded(char *file_name, const char *extension)
{
    size_t file_name_len = strlen(file_name);
    size_t extension_len = strlen(extension);

    if (file_name_len < extension_len ||
         strcmp(file_name + file_name_len - extension_len, extension) != 0)
    {
        strcat(file_name, extension);
    }
}

static int CreateBinaryFile(char *file_name, const char *rel_path, char *mode)
{
    FILE *file = NULL;
    /* Construct the full file path */
    char full_path[MAX_PATH_LENGTH];
    errno = SUCCESS;

    if (file_name == NULL || rel_path == NULL || mode == NULL)
    {
        perror("NULL arguments");
        return EINVAL; /* Invalid arguments */
    }

    if (SUCCESS != IsFileNameValid(file_name))
    {
        return EINVAL; /* Invalid file name */
    }

    /* validate .bin exxtension*/
    AddExtensionIfNeeded(file_name, ".bin");

    /* build full path for file to be located in requested path*/
    if (rel_path[0] == '.' && (rel_path[1] == '/' 
                            || (rel_path[1] == '.' && rel_path[2] == '/')))
    {
        strcpy(full_path, rel_path);
        strcat(full_path, "/");
        strcat(full_path, file_name);
    }
    else
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", rel_path, file_name);
    }

    /* validate path*/
    file = fopen(full_path, mode);
    if (file == NULL)
    {
        perror("Error opening file in the requested path");
        return EINVAL;
    }

    fclose(file);

    /* update file name*/
    strcpy(file_name, full_path);

    return SUCCESS; 
}

/* Function that deletes a file. */
static int FileRemove(const char *filename)
{    if (remove(filename) != 0)
    {
        perror("File removal fail");
        return EBADF;
    }
    return SUCCESS;
}