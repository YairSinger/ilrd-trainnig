#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int MaxSubArray(int *arr, size_t arr_size, size_t indexs[])
{
	size_t i = 0;
	int cur_sum = arr[0], max_sum = arr[0];
	int cur_left = 0;
	
	index[0] = 0;
	index [1] = 0;
	
	while (i < arr_size)
	{
		if( cur_sum >= max_sum)
		{	
			max_sum = cur_sum;
			index[0] = cur_left;
			index[1] = i;
		}
		else if (cur_sum < 0)
		{
			cur_sum = 0;
			cur_left = i + 1;
		}	
	
		++i;
	}
	
	return max_sum;
}
int main(void)
{
	int arr[] = {-2,1,-3,4,-1,2,3,-5,4};
	size_t index[2] = {0};
	printf("result sum %d, %lu, %lu\n", MaxSubArray(arr, 9, index),index[0], index[1]); 


	return 0;
}

