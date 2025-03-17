#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>

ssize_t FindMinimumKVlaue(int *arr, size_t size, size_t k)
{
	size_t min = 0, max = 0;
	size_t i = 0, j = 0;
	size_t *lut = NULL;
	ssize_t res = -1;
	
	for (i = 0 ; i < size ;++i)
	{
		if( arr[i] > arr[max])
		{
			max = i;
		}
		if (arr[i] < arr[min])
		{
			min = i;
		}
	}
		
	lut = (size_t *) calloc((arr[max] - arr[min]) + 1, sizeof(size_t));
	
	if (NULL != lut)
	{
		for (i = 0; i < size; ++i)
		{
			lut[arr[i] - arr[min] ] = i;
		}
		
		for(j = 0, i = 0; j <= k ; ++i)
		{
			if (lut[i] != 0)
			{
				++j;
			}
		}
		res = lut[j - 1];
		free (lut);
	}
	return res;
}


int main()
{
	int arr1[] = {0,1,2,3,4,5,6,7,8,9};
	int arr2[] = {2,5,9,80,70,60,55,100,8,3};
	int fails = 0;
	
	if (0 != FindMinimumKVlaue(arr1,10,0) || 0 != FindMinimumKVlaue(arr2,10,0))
	{
		++fails;
		printf("failed %lu first, %lu sec\n" , FindMinimumKVlaue(arr1,10,0),FindMinimumKVlaue(arr2,10,0));
	}
	if (3!= FindMinimumKVlaue(arr1,10,4) || 8 != FindMinimumKVlaue(arr2,10,4))
	{
		++fails;
		printf("failed %lu first, %lu sec\n" , FindMinimumKVlaue(arr1,10,4),FindMinimumKVlaue(arr2,10,4));
	}
	if (fails == 0)
	{
		printf("Passed\n");
	}

	return 0;
}


