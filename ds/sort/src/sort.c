#include <assert.h>
#include <stdlib.h> /*calloc */
#include <stdio.h>
#include "sort.h"





static void SwapMembers(void *a, void *b, size_t size)
{
    size_t num_words, i;
    size_t remaining_bytes;
    char *a_char, *b_char;
    size_t tmp;
	char tmp_char;
	
    num_words = size / sizeof(size_t);
    
    for (i = 0; i < num_words; ++i) 
    {
        tmp = ((size_t *)a)[i];
        ((size_t *)a)[i] = ((size_t *)b)[i];
        ((size_t *)b)[i] = tmp;
    }

    remaining_bytes = size % sizeof(size_t);
    a_char = (char *)a + num_words * sizeof(size_t);
    b_char = (char *)b + num_words * sizeof(size_t);
    
    for (i = 0; i < remaining_bytes; ++i) 
    {
        tmp_char = a_char[i];
        a_char[i] = b_char[i];
        b_char[i] = tmp_char;
    }
}


/*===================== BubbleSort ==================*/


void BubbleSort(int arr[], size_t length)
{
	size_t comulative_sorted = 0;
	size_t i = 0;
	int swap_temp = 0;
	
	assert(NULL != arr);
	
	while (comulative_sorted < length)
	{
		for(i = 1; i < length; ++i)
		{
			if(arr[i-1] > arr[i])
			{
				comulative_sorted = 0;
				
				swap_temp = arr[i];
				arr[i] = arr[i-1];
				arr[i-1] = swap_temp;
			}
			else
			{
				++comulative_sorted;
			}
		
		}
	}
}


/*===================== GenericBubbleSort ==================*/

/*void GenericBubbleSort(void *arr, size_t elem_size, size_t length, int (*cmp_func)(const void *lhs, const void *rhs))
{
	size_t comulative_sorted = 0;
	size_t i = 0;
			
	assert(NULL != arr);
	
	while (comulative_sorted < length)
	{
		for(i = elem_size; i < (length * elem_size); i += elem_size)
		{
			if(0 < cmp_func((void *)((char *)arr+i-elem_size), (void *)((char *)arr +i)))
			{
				comulative_sorted = 0;
				SwapMembers((void *)((char *)arr + i - elem_size), (void *)((char *)arr + i), elem_size);				
			}
			else
			{
				++comulative_sorted;
			}
		
		}
	}
}*/

void GenericBubbleSort(void *arr, size_t elem_size, size_t length, int (*cmp_func)(const void *lhs, const void *rhs))
{
	int is_swaped = 1;
	size_t i = 0;
	char *runner = (char *)arr;
	char *end_of_arr = (char *)arr + (elem_size * length);
	
	while(is_swaped)
	{
		is_swaped = 0;
		for (runner = (char *)arr + elem_size; runner < end_of_arr; runner += elem_size)
		{
			if(0 < cmp_func(runner - elem_size,runner))
			{
				is_swaped = 1;
				SwapMembers(runner,runner - elem_size, elem_size);
			}
		}
	}
}


/*===================== CountingSort ==================*/

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


/*===================== SelectionSort ==================*/

void SelectionSort(int arr[], size_t length)
{
	size_t sorted_size = 0;
	int current_min = 0;
	size_t i = 0;
	size_t min_index = 0;
	assert(NULL != arr);
	
	for (sorted_size = 0; sorted_size < length; ++sorted_size)
	{
		for (i = sorted_size, min_index = sorted_size; i < length; ++i)
		{
			if (arr[i] < arr[min_index])
			{
				min_index = i;
			}		
		}
		current_min = arr[min_index];
		arr[min_index] = arr[sorted_size];
		arr[sorted_size] = current_min;
		
		
	}
}




/*===================== InsertionSort ==================*/

void InsertionSort(int arr[], size_t length)
{
	size_t sorted_size = 1;
	int swap_temp = 0;
	size_t i = 0;
	
	
	assert(NULL != arr);
	
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

/*===================== RadixSort static functions ==================*/

static size_t NumDigits(int num)
{
	size_t count = 0;
	
	while(0 != num)
	{
		num /= 10;
		++count;
	}
	
	return count;
}

static int ExstractDigit(int num, size_t digit_index)
{
	int divider = 10;
	size_t i = 0;
	
	for(i = 0; i < digit_index ; ++i)
	{
		divider *= 10;
	}
	
	num = num % divider ;
	num /= (divider / 10);
	
	return num;
}


static int CountingSortDigits(int arr[], size_t length,size_t digit_index)
{
	int count[10] = {0};
	int *sorted = (int *)calloc(length, sizeof(int));
	int i = 0;
	
	assert(NULL != arr);
	
	if (NULL == sorted)
	{
		return 1;
	}
	
	for(i = 0; (size_t)i < length; ++i) /*	histogram of values */
	{
		count[ExstractDigit(arr[i], digit_index)] +=1;
	}
	
	for(i = 1; i < 10; ++i) /*	comulative histogram of values */
	{
		count[i] += count[i - 1] ;
	}
	
	for(i = (length - 1); i >= 0; --i)
	{
		sorted[count[ExstractDigit(arr[i], digit_index)] - 1] = arr[i];
		--count[ExstractDigit(arr[i], digit_index)];	
	}
	
	for(i = 0; (size_t)i < length; ++i)
	{
		arr[i] = sorted[i];
	}
	
	free(sorted);
	sorted = NULL;
	
	return 0;

}



/*===================== RadixSort ==================*/


int RadixSort(int arr[], size_t length)
{
	int status = 0;
	size_t i = 0;
	size_t max_digits = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < length; ++i)
	{
		if(NumDigits(arr[i]) > max_digits)
		{
			max_digits = NumDigits(arr[i]);
		}
	}
	
	for(i = 0; i < max_digits && 0 == status ; ++i)
	{
		status = CountingSortDigits(arr, length, i);
	}
	
	return status;
}
	
/*===================== MergeSort ==================*/

static int Merge(int arr[], size_t l_num_elem, size_t r_num_elem)
{
	int *left = (int *) malloc(sizeof(int) * l_num_elem);
	int *right = (int *) malloc(sizeof(int) * r_num_elem); 
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	
	if (NULL == left || NULL == right)
	{
		return 1;
	}
	
	for(i = 0; i < l_num_elem; ++i)
	{
		left[i] = arr[i];
	}
	
	for(i = l_num_elem; i < (l_num_elem + r_num_elem); ++i)
	{
		right[i - l_num_elem] = arr[i];
	}
	
	i = 0;
	j = 0;
	
	while (i < l_num_elem && j < r_num_elem)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			++i;
		}
		else
		{
			arr[k] = right[j];
			++j;
		}
		++k;
	}
	
	while (i < l_num_elem)
	{
		arr[k] = left[i];
		++i;
		++k;
	}
	
	while (j < r_num_elem)
	{
		arr[k] = right[j];
		++j;
		++k;
	}
	free(left); 
	free(right);
	
	return 0;
}





int MergeSort(int *arr_to_sort, size_t num_elements)
{
	size_t l_num_elem = num_elements / 2;
	size_t r_num_elem = num_elements - (num_elements / 2);
	int status1 = 0;
	int status2 = 0;
	assert(NULL != arr_to_sort);
	
	
	while (num_elements > 1)
	{
		status1 = MergeSort(arr_to_sort, l_num_elem); 
		status2 = MergeSort(arr_to_sort + l_num_elem, r_num_elem);
		
		if(0 == status1 && 0 == status2)
		{		
			 return Merge(arr_to_sort, l_num_elem, r_num_elem);
		}
		else
		{	
			return 1;
		}
	}
	
	return 0;
}



/*===================== QSort ==================*/



/* function to find the partition position*/
static int partition(void *base, int low_member, int high_member, size_t size, int (*compar)(const void *, const void *)) 
{
  
  /* select the rightmost element as pivot*/
	 void *pivot = (void *)((char *)base + (high_member * size));
	 int i = (low_member - 1);
	 int j = 0;
  
 for (j = low_member; j < high_member; j++)
 {
	if (0 <= compar((void *)((char *)base + (j * size)), pivot)) 
	{		
	  	++i;		 
		SwapMembers((void *)((char *)base + (i * size)), (void *)((char *)base + (j * size)), size);
	}
  }
  
  SwapMembers((void *)((char *)base + ((i + 1) * size)), (void *)((char *)base + (high_member * size)), size);
   
  /* return the partition point*/
  return (i + 1);
}

static void quickSort(void *base, int low_member, int high_member, size_t size, int (*compar)(const void *, const void *)) {
  if (low_member < high_member) {
    
     /*find the pivot element such that
     elements smaller than pivot are on left of pivot
     elements greater than pivot are on right of pivot*/
    int pi = partition(base, low_member, high_member, size, compar) ;
    
    /* call left of pivot*/
    quickSort(base, low_member, pi - 1, size, compar);
    
    /* call right of pivot*/
    quickSort(base, pi + 1, high_member, size, compar);
  }
}

void QSort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
	quickSort(base, 0, (int)nmemb, size, compar);
}

/*===================== InsertionSort ==================*/




static void HeapifySortDown(int arr[], size_t size, size_t idx)
{
	size_t swap_idx = 0;
	size_t parent = idx;
	int temp = 0;
	
	/* left = idx * 2 + 1, right = idx * 2 + 2 */
	while (idx * 2 + 1 < size)
	{		
		swap_idx = idx * 2 + 1;
						
		if ((idx * 2 + 2 < size) && arr[idx * 2 + 2] > arr[idx * 2 + 1])
		{
			swap_idx = idx * 2 + 2;
		}
		
		if (arr[idx] > arr[swap_idx]) /* no need to swap */
		{
			break;
		}
				
		temp = arr[idx];
		arr[idx] = arr[swap_idx];
		arr[swap_idx] = temp;
		
		idx = swap_idx;
	}
}

void HeapSort(int arr[], size_t length)
{
	int runner = (length - 1) / 2; /*first non leaf index*/
	int unsorted_end_index = 0;
	int temp = 0;
	assert(NULL != arr);
	
	/*setting the array as heap */
	for(;runner >= 0; --runner)
	{
		HeapifySortDown(arr, length, runner);
	}
	
	unsorted_end_index = length - 1;
	runner = 0;
	while(0 < unsorted_end_index)
	{
		temp = arr[runner];
		arr[runner] = arr[unsorted_end_index];
		arr[unsorted_end_index] = temp;
		
		HeapifySortDown(arr , unsorted_end_index, runner);
		--unsorted_end_index;
	}
}



/*

stack_t *SortStack(stack_t *unsorted)
{
	size_t stack_size = 0;
	size_t sorted_size = 0;
	size_t i = 0;
	
	size_t moved = 0;
	stack_t *sorted = NULL; 
	
	int temp = 0;
	int *temp_ptr = &temp;
	
	int top = 0;
	int *top_ptr = &top;
	int passed_value = 0;
	
	assert(NULL != unsorted);
	
	stack_size = StackSize(unsorted);
	sorted = StackCreate(stack_size, sizeof(int));
	
	if (NULL == sorted)
	{
		return NULL;
	}
	
	StackPeek(unsorted, temp_ptr);
	StackPop(unsorted);
	StackPush(sorted, temp_ptr); 
	++sorted_size;
	
	while (sorted_size < stack_size)
	{
		StackPeek(unsorted, temp_ptr);
		StackPop(unsorted); 
		
		StackPeek(sorted, top_ptr);
		while(temp > top)
		{
			passed_value = top;
			StackPop(sorted);
			StackPush(unsorted, &passed_value);
			++moved;
		}
		
		StackPush(sorted, temp_ptr);
		while(moved > 0)
		{
			StackPeek(unsorted, &passed_value);
			StackPop(unsorted); 
			StackPush(sorted, &passed_value);
			--moved;
		}
		
		++sorted_size;
	}
	
	for (i = 0; i < stack_size; ++i)
	{
		StackPeek(sorted, &passed_value);
		StackPop(sorted);
		StackPush(unsorted, &passed_value);
	}
	
	StackDestroy(sorted);
	return unsorted;
}
*/




static size_t PartitionQuize(int *arr, size_t pivot)
{
	size_t i = 0;
	size_t swap_inx = 0;
	int temp = 0;

	while (i < pivot)
	{
		if (arr[i] <= arr[pivot])
		{
			temp = arr[i];
			arr[i] = arr[swap_inx];
			arr[swap_inx] = temp;
		}
		else
		{
			swap_inx = i;
		}

		++i;
	}

	temp = arr[swap_inx + 1];
	arr[swap_inx + 1] = arr[pivot];
	arr[pivot] = temp;

	return swap_inx + 1;
}

void QuickSortQuize(int *arr, size_t size)
{
	size_t pivot = size - 1;
	size_t partition_inx = 0;

	assert(NULL != arr);

	if (size <= 1)
	{
		return;
	}

	partition_inx = PartitionQuize(arr, pivot);

	QuickSortQuize(arr,partition_inx);
	QuickSortQuize(&arr[partition_inx + 1], size - partition_inx - 1);
}

