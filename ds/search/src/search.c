#include <assert.h>
#include <stdlib.h> /*calloc */
#include <stdio.h>
#include <math.h> /* sqrt */
#include "search.h"


ssize_t BinarySearch(int arr[], size_t length, int value_to_search)
{
	size_t start_i = 0;
	size_t end_i = length -1;
	size_t mid_i = 0;
	
	while(start_i <= end_i)
	{
		 mid_i = (end_i + start_i) / 2;
		 
		if(value_to_search == arr[mid_i])
		{
			return mid_i;
		}
		if(value_to_search > arr[mid_i])
		{
			start_i = mid_i + 1;
		}
		else
		{
			end_i = mid_i - 1;
		}
	}
		
	return -1;
}
/*======================== RecBinaSearch ====================*/

static ssize_t BinarySearchRec(int arr[], size_t start_i, size_t mid_i, size_t end_i, int value_to_search)
{
	if (value_to_search == arr[mid_i])
	{
		return mid_i;
	}
	if (start_i > end_i)
	{
		return -1;
	}
	if(value_to_search > arr[mid_i])
	{
		return BinarySearchRec(arr, mid_i + 1,(end_i + start_i)/2 ,end_i, value_to_search);
	}
	else
	{
		return BinarySearchRec(arr, start_i,(end_i + start_i)/2, mid_i - 1,value_to_search);
	}
}

/*======================== RecBinarySearch ====================*/

ssize_t RecBinarySearch(int arr[], size_t length, int value_to_search)
{
	size_t start_i = 0;
	size_t end_i = length -1;
	size_t mid_i = 0;
	
	return BinarySearchRec(arr, start_i, mid_i, end_i,value_to_search);

}


/*======================== JumpSearch ====================*/

ssize_t JumpSearch(int arr[], size_t length, int value_to_search)
{
	size_t jump = (size_t)sqrt((double)length);
	size_t i = 0;
	
	if(value_to_search < arr[0] || value_to_search > arr[length - 1])
	{
		return -1;
	}
		
	while (i < length && arr[i] <= value_to_search)
	{
		i += jump;
	}
		
	i -= jump;	
	while (arr[i] < value_to_search) 
	{
		++i;
	}
	
	if (arr[i] == value_to_search)
	{
		return i;
	}
	
	return -1;
}

/*======================== RecJumpSearch ====================*/

static ssize_t RecJump( int arr[],
						size_t length, 
						int value_to_search, 
						size_t i, 
						size_t jump, 
						size_t step)
{
	if(value_to_search < arr[0] || value_to_search > arr[length - 1])
	{
		return -1;
	}	
	
	if (arr[i] == value_to_search)
	{
		return i;
	}
	
	if (step > jump ||  (i > length && step != 0))
	{
		return -1;
	}
	
	if (arr[i] < value_to_search && step == 0 && i < length) /*move in jump */
	{
		return RecJump(arr, length, value_to_search, i + jump, jump,step);
	}

	if (step == 0) /*first step*/
	{
		return RecJump(arr, length, value_to_search, i - jump, jump, 1);
	}
	
	return RecJump(arr, length, value_to_search, i + 1, jump,step + 1);
		
}

ssize_t RecJumpSearch(int arr[], size_t length, int value_to_search)
{
	size_t jump = (size_t)sqrt((double)length);
	size_t step = 0;
	size_t i = 0;
	
	return RecJump(arr, length, value_to_search, i, jump,step);	




}

