/******************************************************************************/
/*
  Name: Idan Nave
  Project: Work Sheet #uid
  Reviewer: Dima
  Date: 06/09/23
  Version: 1.0
  
  Overview: Tester of an UID generator.
*/
  
/******************************** Libraries  **********************************/
#include <stdio.h>
#include "uid.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KDEF  "\033[0m"

#define NUMBER_OF_TESTS 100


void UIDTest();

int main()
{	
	UIDTest();
	
	return 0;
}

void UIDTest()
{
	uid_ty uid_arr[NUMBER_OF_TESTS] = {0};
	size_t i = 0;
	size_t j = 0;
	size_t tst_count = 0;
	double percentage = 0;
	
	for(i=0; i<NUMBER_OF_TESTS; ++i)
	{
		uid_arr[i] = UIDCreate();
		++tst_count;
	}
	
	tst_count = 0;
	
	for(i=0; i<NUMBER_OF_TESTS; ++i)
	{
		percentage = (((double)i)/NUMBER_OF_TESTS)*100;
		if(0.001 >= percentage - (int)percentage)
		{
			/*printf("Testing: ...%d%%...\n", (int)percentage);*/
		}
		
		for(j=0; j<NUMBER_OF_TESTS; ++j)
		{
			if(i!=j && TRUE == UIDIsSame(uid_arr[i], uid_arr[j]))
			{
				printf("%sUID test failed!%s 'Different UID test' at UID#%ld & UID#%ld\n",KRED, KDEF,i, j);
				return;
			}
			
			if(TRUE == UIDIsSame(invalid_uid, uid_arr[j]))
			{
				printf("%sUID test failed!%s 'invalid_uid test' at UID#%ld\n",KRED, KDEF, j);
				return;
			}
			
			if(i==j && FALSE == UIDIsSame(uid_arr[i], uid_arr[j]))
			{
				printf("%sUID test failed%s 'Same UID test' at UID#%ld\n",KRED, KDEF, j);
				return;
			}
			
		++tst_count;
		}
	}
/*	printf("\n%sUID test success!%s \nUnfortunately the test covered just %ld comparisons, and that's not good enough.%s\n\n", KGRN, KWHT, tst_count, KDEF);*/
	printf("%ld comparisons done,%s %sUID generator is valid!%s\n",tst_count, KWHT, KGRN, KWHT);

}








