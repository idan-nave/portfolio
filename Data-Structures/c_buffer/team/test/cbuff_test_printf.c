/******************************** ws5_dc_buff.h  ******************************/
/*
  Name: HRD32
  Project: Work Sheet 8 - Data Structures - Circular Buffer
  Reviewer: Idan
  Date: 21/08/23
  Version: 1.0
*/

/******************************** Libraries  **********************************/
#include <stdio.h>  /*printf*/

#include "cbuff.h"

int main()
{
	c_buff_ty *c_buffer = CbuffCreate(6);
	char *dest = (char*)malloc(sizeof(char) * 20);
	char *src = "Helxo";

	printf("The size of the buff is: %lu\n", CbuffSize(c_buffer));
	printf("There is %lu free space in the buff.\n", CbuffFreeSpace(c_buffer));

	if(EMPTY == CbuffIsEmpty(c_buffer))
	{
		printf("The buff is empty\n");
	}
	else
	{
		printf("The buff is not empty\n");	
	}

	CbuffWrite(c_buffer, src, 4);
	printf("\nAfter writing 4 bytes\n");
	printf("The size of the buff is: %lu\n", CbuffSize(c_buffer));
	printf("There is %lu free space in the buff.\n", CbuffFreeSpace(c_buffer));

	if(EMPTY == CbuffIsEmpty(c_buffer))
	{
		printf("The buff is empty\n");
	}
	else
	{
		printf("The buff is not empty\n");	
	}




	CbuffRead(c_buffer, dest, 3);
	printf("\nAfter reading 3 bytes\n");
	printf("The size of the buff is: %lu\n", CbuffSize(c_buffer));
	printf("There is %lu free space in the buff.\n", CbuffFreeSpace(c_buffer));

	if(EMPTY == CbuffIsEmpty(c_buffer))
	{
		printf("The buff is empty\n");
	}
	else
	{
		printf("The buff is not empty\n");	
	}
	printf("dest contents: %s\n", (char*)dest);

	CbuffWrite(c_buffer, src, 2);
	printf("\nAfter writing 2 bytes\n");
	printf("The size of the buff is: %lu\n", CbuffSize(c_buffer));
	printf("There is %lu free space in the buff.\n", CbuffFreeSpace(c_buffer));

	if(EMPTY == CbuffIsEmpty(c_buffer))
	{
		printf("The buff is empty\n");
	}
	else
	{
		printf("The buff is not empty\n");	
	}

	CbuffRead(c_buffer, dest, 3);
	printf("\nAfter reading 3 bytes\n");
	printf("The size of the buff is: %lu\n", CbuffSize(c_buffer));
	printf("There is %lu free space in the buff.\n", CbuffFreeSpace(c_buffer));

	if(EMPTY == CbuffIsEmpty(c_buffer))
	{
		printf("The buff is empty\n");
	}
	else
	{
		printf("The buff is not empty\n");	
	}

	printf("dest contents: %s\n", (char*)dest);

	src = "abcdefghijklmnop";
	
	printf("\nAfter writing 12 bytes it write %lu\n",CbuffWrite(c_buffer, src , 12));
	printf("The size of the buff is: %lu\n", CbuffSize(c_buffer));
	printf("There is %lu free space in the buff.\n", CbuffFreeSpace(c_buffer));

	if(EMPTY == CbuffIsEmpty(c_buffer))
	{
		printf("The buff is empty\n");
	}
	else
	{
		printf("The buff is not empty\n");	
	}

	CbuffRead(c_buffer, dest, 3);
	printf("\nAfter reading 3 bytes\n");
	printf("The size of the buff is: %lu\n", CbuffSize(c_buffer));
	printf("There is %lu free space in the buff.\n", CbuffFreeSpace(c_buffer));

	if(EMPTY == CbuffIsEmpty(c_buffer))
	{
		printf("The buff is empty\n");
	}
	else
	{
		printf("The buff is not empty\n");	
	}

	printf("dest contents: %s\n", (char*)dest);

	printf("\nAfter reading 3 bytes it reads: %lu\n",CbuffRead(c_buffer, dest, 4));
	printf("The size of the buff is: %lu\n", CbuffSize(c_buffer));
	printf("There is %lu free space in the buff.\n", CbuffFreeSpace(c_buffer));

	if(EMPTY == CbuffIsEmpty(c_buffer))
	{
		printf("The buff is empty\n");
	}
	else
	{
		printf("The buff is not empty\n");	
	}

	printf("dest contents: %s\n", (char*)dest);

	CbuffDestroy(c_buffer);
	free(dest);
	dest = NULL;
	return 0;
}