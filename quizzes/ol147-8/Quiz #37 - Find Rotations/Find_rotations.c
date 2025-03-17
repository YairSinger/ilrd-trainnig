
#include <stdio.h>




size_t NumOfRotations(int *arr, size_t size)
{
	size_t start_i = 0;
	size_t end_i = size -1;
	size_t mid_i = 0;
	
	while(start_i <= end_i)
	{
		 mid_i = (end_i + start_i) / 2;
		 
		if(arr[0] > arr[mid_i])
		{
			break;
		}
		if(arr[0] < arr[mid_i])
		{
			start_i = mid_i + 1;
		}
		else
		{
			end_i = mid_i - 1;
		}
	}
	
	while (arr[0] > arr[mid_i])
	{
		--mid_i;
	}
	
	return size - mid_i - 1;
}


int main()
{
	int arr1[6] = {1,4,5,7,8,11};
	int arr2[6] = {7,8,11,1,4,5};
	int arr3[6] = {11,1,4,5,7,8};
	
	if (0 == NumOfRotations(arr1,6) && 3 == NumOfRotations(arr2, 6) && 5 == NumOfRotations(arr3, 6))
	{
		printf("Passed\n");
	}
	else
	{
		printf("Failed\n");
		printf("arr1 resulted %lu\n",NumOfRotations(arr1,6));
		printf("arr2 resulted %lu\n",NumOfRotations(arr2,6));
		printf("arr3 resulted %lu\n",NumOfRotations(arr3,6));
	}
	return 0;
}
