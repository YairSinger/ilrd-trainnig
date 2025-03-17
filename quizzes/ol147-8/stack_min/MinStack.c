#include <stdio.h> 	/* printf */
#include <stdlib.h> /* size_t */
#include "stack.h"

typedef struct min_stack
{
	stack_t *stack_ptr;
	stack_t *min_stack;	
}min_stack_t;

min_stack_t *StackMinCreate(size_t capacity, size_t element_size)
{
	min_stack_t *stack_of_min = (min_stack_t *) malloc (sizeof(min_stack_t));
	if (NULL  == stack_of_min)
	{
		return NULL;
	}
	
	stack_of_min->stack_ptr = StackCreate(capacity,element_size);
	if (NULL == stack_of_min->stack_ptr)
	{
		free (stack_of_min);
		return NULL;
	}
	stack_of_min->min_stack = StackCreate(capacity,element_size);
	if (NULL == stack_of_min->min_stack)
	{
		StackDestroy(stack_of_min->stack_ptr);
		free (stack_of_min);
		return NULL;
	}
	return stack_of_min;
}
/*******************************************/


void Destroy(min_stack_t *stack_of_min)
{
	StackDestroy(stack_of_min->stack_ptr);
	StackDestroy(stack_of_min->min_stack);
	free(stack_of_min);
}

/*******************************************/

void StackPushMin (min_stack_t *stack_of_min, int *input)
{
	stack_t *stack_ptr = stack_of_min->stack_ptr;
	stack_t *min_stack = stack_of_min->min_stack;
	
	int cur_min = 0;
	
	if ( 0 != StackSize(stack_ptr))
	{
		StackPeek(min_stack, (void *)&cur_min);		
		if (StackSize(stack_ptr) == 0 || *input <= cur_min)
		{	
			StackPush(min_stack, (const void *) input );
		}
	}
	else 
	{
		StackPush(min_stack, (const void *) input );
	}
	StackPush(stack_ptr, (const void *) input );
	
}

/*********************************************/


int StackMin(min_stack_t *stack_of_min)
{
	int min = 0;
	stack_t *min_stack = stack_of_min->min_stack;
		
	StackPeek(min_stack, (void *)&min);
	return min;
}
/***********************************************/


void StackPopMIN(min_stack_t *stack_of_min)
{
	int poped_value = 0;
	stack_t *stack_ptr = stack_of_min->stack_ptr;
	stack_t *min_stack = stack_of_min->min_stack;
	
	StackPeek(stack_of_min->stack_ptr, &poped_value);
	if (poped_value == StackMin(stack_of_min))
	{
		StackPop(min_stack);
	}
	StackPop(stack_ptr);
}
/***************************************************/

int main()
{
	min_stack_t *stack_dec = StackMinCreate(5, sizeof(int));
	min_stack_t *stack_inc = StackMinCreate(5, sizeof(int));
	min_stack_t *stack_mix = StackMinCreate(5, sizeof(int));

	int arr_dec[5] = {10,9,8,7,6};
	int res_dec[5] = {6,7,8,9,10};
	
	int arr_inc[5] = {2,3,4,5,6};
	int res_inc[5] = {2,2,2,2,2};
	
	int arr_mix[5] = {0,-2,5,-4,6};
	int res_mix[5] = {-4,-4,-2,-2,0};
	size_t i = 0;
	int fails = 0;
	
	for (i = 0; i<5; ++i)
	{
		StackPushMin (stack_dec, &arr_dec[i]);
		StackPushMin (stack_inc, &arr_inc[i]);
		StackPushMin (stack_mix, &arr_mix[i]);
	}
	
	for (i = 0; i < 5; ++i)
	{
		if(StackMin(stack_dec) != res_dec[i])
		{
			++fails;
			printf("dec failed %d vs %d expected\n",StackMin(stack_dec) , res_dec[i]);
		}
		
		if(StackMin(stack_inc) != res_inc[i])
		{
			++fails;
			printf("inc failed %d vs %d expected\n",StackMin(stack_inc) , res_inc[i]);
		}
		
		if(StackMin(stack_mix) != res_mix[i])
		{
			++fails;
			printf("mix failed %d vs %d expected\n",StackMin(stack_mix) , res_mix[i]);
		}
	
		StackPopMIN(stack_dec);
		StackPopMIN(stack_inc);
		StackPopMIN(stack_mix);
		
	}
	
	if (0 ==fails)
	{
		printf("passed\n");
	}
	
	Destroy(stack_dec);
	Destroy(stack_inc);
	Destroy(stack_mix);
	

	
	return 0;
}


	

