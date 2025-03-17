



int CountingSort(int arr[], size_t length)
{
	int *count = NULL;
	int *sorted = (int *)calloc(length, sizeof(int));
	size_t max = 0;
	size_t min = 0;
	int i = 0;
	
	assert(NULL != arr);
	
	if (NULL == sorted)
	{
		return 1;
	}
	for(i = 0, max = arr[0], min = arr[0]; (size_t)i < length; ++i)
	{
		if (arr[i] < (int)min)
		{
			min = arr[i];
		}
		
		if (arr[i] > (int)max)
		{
			max = arr[i];
		}
	}
	
	count = (int *)calloc(max + 1 - min, sizeof(int));
	if (NULL == count)
	{
		free(sorted);
		return 1;
	}
	
	for(i = 0; (size_t)i < length; ++i) /*	histogram of values */
	{
		count[arr[i] - min] +=1;
	}
	
	for(i = 1; (size_t)i < (max - min + 1); ++i) /*	comulative histogram of values */
	{
		count[i] += count[i - 1] ;
	}
	
	for(i = (length - 1); i >= 0; --i)
	{
		sorted[count[arr[i] - min] - 1] = arr[i];
		--count[arr[i] - min];	
	}
	
	for(i = 0; (size_t)i < length; ++i)
	{
		arr[i] = sorted[i];
	}
	
	free(sorted);
	sorted = NULL;
	
	free(count);
	count = NULL;
	return 0;

}




static void SwapByIndex(int *arr, size_t index1, size_t index2)
{
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}


void SelectionSort(int *arr, size_t length)
{
	size_t sorted = 0;
	size_t min = 0;
	size_t i = 0;
	
	while(sorted < length)
	{
		for(i = sorted, min = sorted; i < length; ++i)
		{
			if(arr[i] < arr[min])
			{
				min = i;
			}
		}
		
		SwapByIndex(arr, sorted, min);
		++sorted;
	}
}


void InsertionSort(int arr[], size_t length)
{
	size_t sorted_size = 1;
	int swap_temp = 0;
	size_t i = 0;
		
	for(sorted_size = 1; sorted_size < length; ++sorted_size)
	{		
		if (arr[sorted_size] < arr[sorted_size -1])
		{
			i = (sorted_size - 1);
			swap_temp = arr[sorted_size];
			while(arr[i] > swap_temp)
			{
				arr[i + 1] = arr[i];
				--i;
			}
			arr[i + 1] = swap_temp;
		}
	}

}



