#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> /* INT_MAX, INT_MIN */

#define LUT_SIZE 2 * (long)INT_MAX + 1 

int IsNumInArray(const int arr[], size_t size, int num)
{
	size_t i = 0;
	
	for(i = 0; arr[i] != num && i < size ; ++i)
	{
	/*empty loop*/
	}
	
	return (i != size);
}
int main()
{
	int arr[] = {484,-458,-4,-3284,854,3874,874,71466,-9441};
	size_t size = 9;
	int included = -3284;
	int excluded = 0;
	
	if (1 == IsNumInArray(arr,  size, included))
	{
		printf("included result TRUE\n");
	}
	else
	{
		printf("included result FAILED\n");
	}
	
	if (0 == IsNumInArray(arr,  size, excluded))
	{
		printf("excluded result TRUE\n");
	}
	else
	{
		printf("excluded result FAILED\n");
	}
	
	
	return 0;

}	
