#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*strlen*/
void swapValues(int *num1, int *num2)
{
	int num_holder = *num1;
	*num1 = *num2;
	*num2 = num_holder;		
}


int* copyArray (int *arr, int array_size)
{
	 int *arr_copy = (int*)malloc (array_size * sizeof(int));
	 int i = 0;
	 
	assert(arr);
	/*arr_copy = */
	
	for (i = 0 ; i < array_size ; i++)
	{
		arr_copy[i] = arr[i];	
		 
	}	
	return arr_copy;
}




void printAdresses()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int*)malloc(sizeof(int));
	int **ptr3 = 0;
	
	assert(ptr);
	ptr3 = &ptr;
	printf("static address = %p\n" ,(void *)&s_i);
	printf("local  address = %p\n" , (void *)&i);
	printf("local pointer address = %p\n" ,(void *)&ptr);
	printf("local pointer looks at address = %p\n" ,(void *)ptr);
	printf("dynamic pointer address = %p\n" ,(void *)&ptr2);
	printf("dynamic pointer looks at address = %p\n" ,(void *)ptr2);
	printf("local pointer pointer address = %p\n" ,(void *)&ptr3);
	printf("local pointer pointer looks at address = %p\n" ,(void *)ptr3);
	
	free(ptr2);
	ptr2 = NULL;
}

void SwapsTypeT(size_t *num1, size_t *num2)
{
	size_t size_holder = *num1;
	
	*num1 = *num2;
	*num2 = size_holder;
}

void SwapsTypeTPointers(size_t **num1, size_t **num2)
{	
	SwapsTypeT(*num1, *num2);
	
}
	
int IsPalindrome(char *str)
{



	char * str_end = 0;
	size_t len = 0;
	
	assert (NULL != str);
	len = strlen(str);
	str_end = str + len-1;
	
	while (str < str_end)
	{
		if (*str != *str_end)
		{
			return 1;
		}
		++str;
		--str_end;
	}
	return 0;
	
}




