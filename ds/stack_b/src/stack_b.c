#include <stdio.h>	/* size_t */
#include <assert.h>	/* assert */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc, free */

#include "stack_b.h"

struct Stack
{
	size_t size;			/* Number of elements currently in Stack	 */
	size_t capacity;		/* How many elements can the stack hold 	*/
	size_t element_size;	/* Element size in bytes 				   */
	
	char *top;				/* Pointer to top bullet                 */
};

stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *ptr_to_stack = (stack_t *)malloc(sizeof(stack_t) + ((capacity * element_size)));
	if (NULL == ptr_to_stack)
	{
		return (NULL);
	}

	ptr_to_stack->size = 0; 						/* Num of elements 			 */
	ptr_to_stack->capacity = capacity;				/* User defined sizeof stack */
	ptr_to_stack->element_size = element_size;		
	ptr_to_stack->top = (char *)ptr_to_stack + sizeof(stack_t);
	
	return (ptr_to_stack);
}

void StackDestroy(stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	free(my_stack);
	my_stack = NULL;
}

void StackPush(stack_t *my_stack, const void *element)
{
	assert(NULL != element);
	assert(NULL != my_stack);
	
	memcpy(my_stack->top, element, my_stack->element_size);
	
	my_stack->top += my_stack->element_size;
	
	my_stack->size += 1;
}

void StackPop(stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	my_stack->top -= my_stack->element_size;
	my_stack->size -= 1;
}

void *StackPeek(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return my_stack->top - my_stack->element_size;
}

int StackIsEmpty(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return (0 == my_stack->size);
}

size_t StackSize(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return my_stack->size;
}

size_t StackCapacity(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return my_stack->capacity;
}

