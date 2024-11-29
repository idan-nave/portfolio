/*************************** ws12_serialization.h ****************************/
/*
  Name: HRD 32
  Project: Work Sheet #12 - Serialized Structs
  Reviewer: Sahar
  Date: 31/07/23
  Version: 1.0
*/
  
#ifndef __WS12_SERIALIZATION_H__
#define __WS12_SERIALIZATION_H__
	

/********************************* ENUMs  ************************************/
/* Enum that maps student grades storing index */
typedef enum
{
    SPORT_IDX = 0,
    PHYSICS_IDX = 1,
    MATH_IDX = 2,
    CODING_IDX = 3,
    SOCIOLOGY_IDX = 4,
    PSYCHOLOGY_IDX = 5,
    LITERATURE_IDX = 6
} grade_idx_ty;

/****************************************************************************/
/************************** App's Data-structures ***************************/
/****************************************************************************/

 /* struct to hold a student descriptor */
typedef struct student_grades student_ty;

/**************** API Approved Functions - To Export ************************/

/* App Manager Function (called from Main) */
int StudentGradesApp(const char *bin_file_name);

  /* Serialization & Deserialization Functions */
int SerializeStudents(student_ty *student_data, char *file_name);
int DeserializeStudents(student_ty *student_res, char *file_name);

#endif /*(__WS12_SERIALIZATION_H__)*/
