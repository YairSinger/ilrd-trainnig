#include <assert.h>
#include <stdlib.h> /* malloc  */
#include <stdio.h>  /* fputs   */
#include <stddef.h> /* size_t  */
#include <string.h> /* memmove */
#include "stack.h"


 struct stack
 {
 	size_t element_size;
 	size_t capacity;
 	size_t current_size;
 	void *buffer; /* pointer to the array of elements */
 };
 
 stack_t *StackCreate(size_t capacity, size_t element_size)
 {
 	void *user_buffer = (void *) malloc(element_size * capacity);
 	stack_t *stack_p = (stack_t *)malloc(sizeof(stack_t));
 	
 	if (NULL == user_buffer)
 	{
 		fputs("Failed to create new stack\n", stderr);
 		return NULL;
 	}
 	
 	if (NULL == stack_p)
 	{
 		free (user_buffer);
 		fputs("Failed to create new stack\n", stderr);
 		return NULL;
 	}
 	
 	stack_p->element_size = element_size;
 	stack_p->capacity = capacity;
 	stack_p->current_size = 0;
 	stack_p->buffer = user_buffer;
 	
 	
 	return stack_p;
 }
 
void StackDestroy(stack_t *stack_ptr)
{
	assert(NULL != stack_ptr);
	/*return buffer to point on first adress */
	if (stack_ptr->current_size > ((stack_ptr->capacity) ))
	{
		stack_ptr->buffer = ((char *)stack_ptr->buffer - ((stack_ptr->capacity) * (stack_ptr->element_size)));
	}
	else 
	{
		stack_ptr->buffer = ((char *)stack_ptr->buffer - ((stack_ptr->current_size) * (stack_ptr->element_size))) ;
	}
	
	
	free(stack_ptr->buffer);
	free(stack_ptr);
	stack_ptr = NULL;
}

void StackPush(stack_t *stack_ptr, const void *element)
{
	memmove(stack_ptr->buffer , element, stack_ptr->element_size);
	stack_ptr->current_size += 1 ;
	stack_ptr->buffer = ((char *)stack_ptr->buffer + stack_ptr->element_size);
}

void StackPop(stack_t *stack_ptr)
{
	stack_ptr->buffer = ((char *)stack_ptr->buffer - stack_ptr->element_size);
	stack_ptr->current_size -= 1 ;
}

int StackIsEmpty(stack_t *stack_ptr)
{
	return (stack_ptr->current_size == 0 ? 1 : 0); 
}

size_t StackCapacity(stack_t *stack_ptr)
{
	return stack_ptr->capacity;
}

size_t StackSize(stack_t *stack_ptr)
{
	return stack_ptr->current_size;
}

void StackPeek(stack_t *stack_ptr, void *buffer)
{
	stack_ptr->buffer = ((char *)stack_ptr->buffer - stack_ptr->element_size);
	memmove(buffer, stack_ptr->buffer, stack_ptr->element_size);
	stack_ptr->buffer = ((char *)stack_ptr->buffer + stack_ptr->element_size);
}
