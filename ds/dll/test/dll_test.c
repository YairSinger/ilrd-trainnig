#include <stdio.h> /*fputs, printf */
#include "dll.h"


#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

void TestCreateDestroy();
void TestDllInsert();

int main()
{
	TestCreateDestroy();
	TestDllInsert();
	
	return 0;
}

void TestCreateDestroy()
{
	dll_t *dll = DllCreate();
	int fails = 0;
	
	if(NULL != dll && !DllIsEmpty(dll))
	{
		++fails;
		printf(RED"dll CREATE FAILED \n"RESET_COLOR);
	}
	
	if (0 == fails)
	{
		printf(GREEN"dll CREATE PASSED\n"RESET_COLOR);
	}
	printf(GREEN"test valgrind for full memory release test\n\n"RESET_COLOR);
	DllDestroy(dll);

}

/***************************************/
void TestDllInsert()
{
	dll_t *dll = DllCreate();
	dll_iter_t iter = NULL;
	int x = 5;
	int y = 3;
	int fails = 0;
	
	/*test size increase and data in the right order*/
	

 	iter = DllInsert(dll, DllBegin(dll), (const void *) &x);
 	iter = DllInsert(dll, iter, (const void *) &y);
 	
 	if (2 != DllSize(dll))
 	{
 		++fails;
		printf(RED"dll insert FAILED size %lu vs 2 expected correct \n"RESET_COLOR, DllSize(dll));
 	}
 	
 	if (3 != *((int *)DllGetData((const dll_iter_t)iter)))
 	{
 		++fails;
		printf(RED"Test 2 dll insert FAILED insert order incorect \n"RESET_COLOR);
 	}
 	
 	iter = DllNext(iter);
 	
 	if (5 != *((int *)DllGetData((const dll_iter_t)iter)))
 	{
 		++fails;
		printf(RED"Test 2 dll insert FAILED insert order incorect \n"RESET_COLOR);
 	}
 	
 	if (0 == fails)
	{
		printf(GREEN"dll CREATE PASSED\n"RESET_COLOR);
	}
	DllDestroy(dll);
}
