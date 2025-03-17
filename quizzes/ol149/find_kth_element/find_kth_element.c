#include <stddef.h>
#include <stdio.h>

int FindMinimumKVlaue(int *arr, size_t size, size_t k)
{
	size_t sorted = 0;
	size_t min_i = 0;
	size_t i = 0;
	int swap_temp = 0;
	
	while (sorted < k)
	{
		for (i = sorted, min_i = sorted; i < size; ++i)
		{
			if (arr[i] < arr[min_i])
			{
				min_i = i;
			}
		}
		
		swap_temp = arr[sorted];
		arr[sorted] = arr[min_i];
		arr[min_i] = swap_temp;
		
		++sorted;
	}
	
	return arr[sorted - 1];
}


int main()
{
	int arr1[] = {0,1,2,3,4,5,6,7,8,9};
	int arr2[] = {2,5,9,80,70,60,55,100,8,3};
	int fails = 0;
	
	if (0 != FindMinimumKVlaue(arr1,10,1))
	{
		++
		printf("failed first in list\n");
	} 
	if (2 != FindMinimumKVlaue(arr1,10,3))
	{
		printf("failed 3 in list\n");
	} 
	if (9 != FindMinimumKVlaue(arr1,10,10))
	{
		printf("failed last in list\n");
	} 

	if (2 != FindMinimumKVlaue(arr2,10,1))
	{
		printf("failed first1 in list\n");
	} 
	if (5 != FindMinimumKVlaue(arr2,10,3))
	{
		printf("failed 31 in list\n");
	} 
	if (100 != FindMinimumKVlaue(arr2,10,10))
	{
		printf("failed last1 in list\n");
	} 

	return 0;
}

