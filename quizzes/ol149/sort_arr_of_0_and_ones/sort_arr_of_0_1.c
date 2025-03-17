#include <stdio.h>


void SortArr(int *arr, size_t size)
{
	int *head = arr;	
	int *first_1 = NULL;
	
	while (0 == *head && head != (arr + size) )
	{
		++head;
	}
	
	first_1 = head;
	
	while (head != (arr + size))
	{
		if (0 == *head)
		{
			*head = !*head;
			*first_1 = !*first_1;
			++first_1;
		}
		
		++head;
	}
}

int main()
{
	int arr[] = {0,0,0,0,1,1,1,0,1,0,1,0,1};
	int arr1[] = {1,0,0,0,1,1,1,0,1,0,1,0,1};
	int arr2[] = {1,1,1,1,1,1,1,1,1,1,1,1,1};
	int arr3[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
	size_t i = 0;
	
	SortArr(arr,13);
	SortArr(arr1,13);
	SortArr(arr2,13);
	SortArr(arr3,13);
	
	for (i = 0; i < 13; ++i)
	{
		printf("%d, %d, %d, %d\n", arr[i], arr1[i], arr2[i], arr3[i]);
	}
	return 0;
}
