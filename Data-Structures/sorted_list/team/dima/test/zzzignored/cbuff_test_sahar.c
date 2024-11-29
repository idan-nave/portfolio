#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/
#include "cbuff.h"

#define BUFFERSIZE 10
void BufferTest();

int main()
{
	BufferTest();
	return 0;
}

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
	
	if(1 != CbuffIsEmpty(c_buff))
	{
		printf("Failed on CbuffIsEmpty()\n");
	}
	
	if(6 != CbuffWrite(c_buff, src, 6))
	{
		printf("0Failed on CbuffWrite()\n");
	}
	
	if(0 != CbuffIsEmpty(c_buff))
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
		printf("1Failed on CbuffWrite()\n");
	}
	
	if(0 != CbuffWrite(c_buff, src, 0))
	{
		printf("2Failed on CbuffWrite()\n");
	}
	
	if(3 != CbuffWrite(c_buff, src, 6))
	{
		printf("3Failed on CbuffWrite()\n");
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
