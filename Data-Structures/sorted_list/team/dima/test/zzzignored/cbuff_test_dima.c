/*Name: Agbaria Ahmad
  Project: Work Sheet 6 - Data Structures - Singly Linked LIst
  Reviewer: Dema
  Date: 14/08/2023
  Version: 1.0
*/
/******************************************************************************/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc()*/

#include "cbuff.h"

/****************************main test function********************************/
void TestProgram();

/*****************************user functions***********************************/

/*********************************** main *************************************/

int main()
{
	TestProgram();
	return 0;
}

/******************************************************************************/

void TestProgram()
{
	c_buff_ty *test_buffer = NULL;
	char *dest = (char *)malloc(sizeof(char)* 20);
	char *src = NULL;
	int i = 0;
	
	*(dest+19) = '\0'; 
	printf("...Creating buffer...\n");
	test_buffer = CbuffCreate(13);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	
	for(i=0; i<20; ++i)
	{
		printf("==========ITERATION NUMBER: %d ====",i);
		PrintData(test_buffer);
		CbuffWrite(test_buffer, "0123456789", i%10);
		CbuffRead(test_buffer, dest, i%10);
		PrintAllBuff(test_buffer);
	}
	
	printf("\n...Writing 5...\n");
	CbuffWrite(test_buffer, "123456", 5);
	PrintAllBuff(test_buffer);
	
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	
	printf("\n...Reading 3...\n");
	CbuffRead(test_buffer, dest, 3);
	printf("Data read: >%s<\n", dest);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	
	printf("\n...Writing 5...\n");
	CbuffWrite(test_buffer, "ABCDEF", 5);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	PrintAllBuff(test_buffer);
	
	
	printf("\n...Reading 5...\n");
	CbuffRead(test_buffer, dest, 5);
	printf("Data read: >%s<\n", dest);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);

	printf("\n...Writing 5...\n");
	CbuffWrite(test_buffer, "!@#$%^&", 5);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	PrintAllBuff(test_buffer);
	
	printf("\n...Reading 7...\n");
	CbuffRead(test_buffer, dest, 7);
	printf("Data read: >%s<\n", dest);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	
	printf("\n...Reading 7...\n");
	CbuffRead(test_buffer, dest, 7);
	printf("Data read: >%s<\n", dest);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	
	printf("\n...Writing 4...\n");
	CbuffWrite(test_buffer, "LMNOP", 4);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	PrintAllBuff(test_buffer);
	
	printf("\n...Writing 3...\n");
	CbuffWrite(test_buffer, "XYZ", 3);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	PrintAllBuff(test_buffer);
	
	printf("\n...Reading 5...\n");
	CbuffRead(test_buffer, dest, 5);
	printf("Data read: >%s<\n", dest);
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
	PrintData(test_buffer);
	
	printf("\n...Final result...\n");
	printf("Size: %ld, Free Space: %ld, Is empty? %d\n", CbuffSize(test_buffer), CbuffFreeSpace(test_buffer), CbuffIsEmpty(test_buffer));
		printf("...Printing All...\n");
	PrintAllBuff(test_buffer);
		printf("...44444444444...\n");
	CbuffDestroy(test_buffer);
}











