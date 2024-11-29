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
#include <string.h> /*strncmp*/

#include "cbuff.h"

#define BUFFERSIZE 10

void BufferTest();
/*int TestProg();
c_buff_ty *CbuffCreate_Test(size_t capacity);
void ReadWriteDefaulCase(c_buff_ty *c_buffer, char *dest, char *src, size_t bytes_to_write, size_t bytes_to_read);
char *setstr(int bytes_to_write, int bytes_to_read);*/

/******************************************************************************/

int main()
{
	BufferTest();
	return 0;
}

/******************************************************************************/
void BufferTest()
{
	c_buff_ty *c_buff =  CbuffCreate(BUFFERSIZE);
	char *src = "sososo";
	char dest[7] = " ";

	if(0 != CbuffSize(c_buff))
	{
		printf("Failed on CbuffSize()\n");
	}
	
	if(BUFFERSIZE != CbuffFreeSpace(c_buff))
	{
		printf("Failed on CbuffFreeSpace()\n");
	}
	
	if(EMPTY != CbuffIsEmpty(c_buff))
	{
		printf("Failed on CbuffIsEmpty()\n");
	}
	
	if(6 != CbuffWrite(c_buff, src, 6))
	{
		printf("1Failed on CbuffWrite()\n");
	}
	
	if(NOT_EMPTY != CbuffIsEmpty(c_buff))
	{
		printf("Failed on CbuffIsEmpty()\n");
	}
	
	if(5 != CbuffRead(c_buff, dest, 5))
	{
		printf("Failed on CbuffRead()\n");
	}
	dest[5] = '\0';
	if(1 != CbuffSize(c_buff))
	{
		printf("Failed on CbuffSize()\n");
	}
	
	if(strcmp(dest, "sosos"))
	{
		printf("%s\n", dest);
		printf("Failed on CbuffRead() in strcmp\n");
	}

	if(6 != CbuffWrite(c_buff, src, 6))
	{
		printf("2Failed on CbuffWrite()\n");
	}
	
	if(0 != CbuffWrite(c_buff, src, 0))
	{
		printf("3Failed on CbuffWrite()\n");
	}
	
	if(3 != CbuffWrite(c_buff, src, 6))
	{
		printf("4Failed on CbuffWrite()\n");
	}
	
	if(BUFFERSIZE != CbuffSize(c_buff))
	{
		printf("%ld\n", CbuffSize(c_buff));
		printf("Failed on CbuffSize()\n");
	}
	
	if(0 != CbuffFreeSpace(c_buff))
	{
		printf("Failed on CbuffFreeSpace()\n");
	}
	
	if(5 != CbuffRead(c_buff, dest, 5))
	{
		printf("Failed on CbuffRead()\n");
	}
	
	if(strcmp(dest, "ososo"))
	{
		printf("%s\n", dest);
		printf("Failed on CbuffRead() in strcmp\n");
	}
	
	if(5 != CbuffSize(c_buff))
	{
		printf("Failed on CbuffSize()\n");
	}
	
	if(5 != CbuffRead(c_buff, dest, 5))
	{
		printf("Failed on CbuffFreeSpace()\n");
	}
	
	if(strcmp(dest, "sosos"))
	{
		printf("%s\n", dest);
		printf("Failed on CbuffRead() in strcmp\n");
	}
	
	if(0 != CbuffRead(c_buff, dest, 5))
	{
		printf("Failed on CbuffRead()\n");
	}
	
	if(0 != CbuffSize(c_buff))
	{
		printf("Failed on CbuffSize()\n");
	}
	
	if(BUFFERSIZE != CbuffFreeSpace(c_buff))
	{
		printf("Failed on CbuffFreeSpace()\n");
	}
	
	CbuffDestroy(c_buff);
	
	printf("Buffer is tested!\n");
	
}

/******************************************************************************/
/*
int TestProg()
{
	c_buff_ty *c_buffer = CbuffCreate_Test(6);
	char *dest = (char*)malloc(sizeof(char) * 20);
	char *src = "abcdefghijklmnopqrstuvwxyz";

	ReadWriteDefaulCase(c_buffer, dest, src, 4,4);
	ReadWriteDefaulCase(c_buffer, dest, src, 3,4);

	CbuffDestroy(c_buffer);
	free(dest);
	dest = NULL;
	return 0;
}*/

/******************************************************************************/

/*c_buff_ty *CbuffCreate_Test(size_t capacity)
{
	c_buff_ty *buff = CbuffCreate(capacity);

	if(NULL == buff)
	{
		printf("CbuffCreate function Failed!\n");
	}
	else
	{
		printf("CbuffCreate function Passed!\n");
	}

	return buff;
}*/

/******************************************************************************/

/*void ReadWriteDefaulCase(c_buff_ty *c_buffer, char *dest, char *src, size_t bytes_to_read, size_t bytes_to_write)
{
	size_t returned_w_bytes = CbuffWrite(c_buffer, src, bytes_to_write);
	size_t returned_r_bytes = CbuffRead(c_buffer, dest, bytes_to_read);
	char *str;

	if(returned_w_bytes > CbuffFreeSpace(c_buffer) || returned_r_bytes > CbuffFreeSpace(c_buffer))
	{
		printf("extra num of bytes was read/written!\n");
	}

	str = setstr(bytes_to_write,bytes_to_read);

	if(0 == strncmp(src,dest,returned_w_bytes))
	{
		printf("Read %s Write Passed!\n",str);
	}
	else
	{
		printf("Read %s Write Failed!\n",str);
	}
}*/

/******************************************************************************/

/*void OnlyRead(c_buff_ty *c_buffer, char *dest, size_t bytes_to_read)
{

}*/

/******************************************************************************/

/*void OnlyWrite(c_buff_ty *c_buffer, char *src, size_t bytes_to_write)
{
	
}*/

/******************************************************************************/

/*char *setstr(int bytes_to_write, int bytes_to_read)
{
	if(0 > (int)bytes_to_read - bytes_to_write)
	{
		return "less num_bytes than";
	}
	else
	{
		return "same num_bytes of";
	}
}*/