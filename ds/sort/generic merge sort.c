#include <stdio.h>

void Merge(void *arr, size_t l_size, size_t r_size, size_t elm_size, int (*cmp_fnc)(void *elm1, void *elm2))
{
	char *left = (char*)malloc(l_size*elm_size);
	char *right = (char*)malloc(r_size*elm_size);
	size_t l_inx = 0, r_inx = 0, i = 0;
	
	if(NULL == left || NULL == right)
	}
		if(NULL != left)
		{
			free(left);
		}
		if(NULL != right)
		{
			free(right);
		}
		return;	
	}
	
	memcpy(left,arr,l_size);
	memcpy(right,(char *)arr + l_size * elm_size, r_size);	
	
	
	while(l_inx < l_size && r_inx < r_size)
	{
		if(0 < cmp_fnc(left + (elm_size * l_inx), right + (elm_size * r_inx)))
		{
			arr[i++] = left[l_inx++];
		}
		else
		{
			arr[i++] = right[r_inx++];
		}
	}
	
	if(l_inx == l_size)
	{
		while( r_inx < r_size)
		{		
			arr[i++] = right[r_inx++];
			
		}
	}
	
	if(r_inx == r_size)
	{
		while( l_inx < l_size)
		{		
			arr[i++] = left[l_inx++];
			
		}
	}
	
	free(left);
	free(right);
}

void MergeSort(void *arr, size_t elm_size, size_t size, int (*cmp_fnc)(void *elm1, void *elm2))
{
	if(size <= 1)
	{
		return;
	}
	
	MergeSort(arr,elm_size,size/2, cmp_fnc);
	MergeSort((char*)arr + (elm_size * size / 2),elm_size, size - size / 2, cmp_fnc);
	
	Merge(arr, size / 2, size - size / 2, elm_size, cmp_fnc);
}
