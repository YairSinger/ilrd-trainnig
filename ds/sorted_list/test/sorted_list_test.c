#include <stdio.h> /*fputs, printf */
#include "dll.h"
#include "sorted_list.h"


#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

typedef int (*cmp_func)(const void *list_data, const void *user_data);

int AscendingInts(const void *list_data, const void *input)
{
	return (int *)input - (int *) list_data;		
}

void TestCreateDestroy();

int main()
{
	TestCreateDestroy();
	
	
	
	
	
	return 0;
}

void TestCreateDestroy()
{
	cmp_func cmp_ints = AscendingInts;
	sorted_list_t *sorted = SortedListCreate(cmp_ints);
	int fails = 0;
		
	if (NULL == sorted)
 	{
 		++fails;
		printf(RED"sorted list CREATE FAILED  \n"RESET_COLOR);
 	}
 	
 	
 	if (0 == fails)
	{
		printf(GREEN"sorted list CREATE PASSED\n"RESET_COLOR);
	}
	
	SortedListDestroy(sorted);
}

