#include <assert.h>
#include <stddef.h> 	/* size_t 			*/
#include <stdlib.h> 	/* malloc 			*/
#include <stdio.h>	 	/* fputs, stderr    */
#include <string.h> 	/* memmove 			*/
#include "dvector.h"

struct d_vector
{
	size_t capacity;
	size_t size;
	size_t element_size;
	void *buffer;
};

d_vector_t *DVectorCreate(size_t capacity, size_t element_size)
{
	void *user_buffer = (void *) malloc(element_size * capacity);
	d_vector_t *dv_ptr = NULL;
	
	if (NULL == user_buffer)
 	{
 		fputs("Failed to create new d_vector\n", stderr);
 		return NULL;
 	}
 	
 	dv_ptr = (d_vector_t *) malloc(sizeof(d_vector_t));
 	
 	if (NULL == dv_ptr)
 	{
 		free (user_buffer);
 		fputs("Failed to create new d_vector\n", stderr);
 		return NULL;
 	}
 	
 	dv_ptr->capacity = capacity;
 	dv_ptr->size = 0;
 	dv_ptr->element_size = element_size;
 	dv_ptr->buffer = user_buffer;
 	
 	
	return dv_ptr;
}


void DVectorDestroy(d_vector_t *vector_ptr)
{
	free(vector_ptr->buffer);
	free(vector_ptr);
	vector_ptr = NULL;
}

static d_vector_t *VectorRealloc(d_vector_t *vector_ptr, size_t new_size)
{
	void *buffer_holder = NULL;
	
	assert(NULL != vector_ptr);
	
	buffer_holder = realloc(vector_ptr->buffer,new_size);
		if (NULL == buffer_holder) 
		{
			/*if realloc failed, don't change buffer pointer */
		}
		else
		{
			vector_ptr->buffer = buffer_holder;
			vector_ptr->capacity = new_size /vector_ptr->element_size ; /*update capacity*/
		}
		return vector_ptr->buffer;
}

void *DVectorGetElementAccess(const d_vector_t *vector_ptr, size_t index)
{
	assert(index < DVectorSize(vector_ptr));
	
	return(((char *)(vector_ptr->buffer)) + (index * vector_ptr->element_size));
}

int DVectorPushBack(d_vector_t *vector_ptr, const void *element)
{
		
	assert(NULL != vector_ptr);
	assert(NULL != element);
		
	if(vector_ptr->size == vector_ptr->capacity)
	{
		vector_ptr->buffer = VectorRealloc(vector_ptr,vector_ptr->capacity * GROWTH_FACTOR * vector_ptr->element_size);
	}
	
	memmove((char *) vector_ptr->buffer + (vector_ptr->size * vector_ptr->element_size), element,vector_ptr->element_size);
	++vector_ptr->size;
	return 0;
}

void DVectorPopBack(d_vector_t *vector_ptr)
{
	--vector_ptr->size;
}

size_t DVectorSize(const d_vector_t *vector_ptr)
{
	return vector_ptr->size;
}

size_t DVectorCapacity(const d_vector_t *vector_ptr)
{
	return 	vector_ptr->capacity;
}

int DVectorShrink(d_vector_t *vector_ptr)
{
	size_t capacity_holder = vector_ptr->capacity;
	
	vector_ptr->buffer = VectorRealloc(vector_ptr, vector_ptr->size * vector_ptr->element_size);
	if (capacity_holder == vector_ptr->capacity)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
	
int DVectorReserve(d_vector_t *vector_ptr, size_t capacity)
{
	size_t capacity_holder = vector_ptr->capacity;
	if ( capacity > vector_ptr->capacity)
	{
		vector_ptr->buffer = VectorRealloc(vector_ptr, capacity * vector_ptr->element_size);
			
	}
	if (capacity_holder == vector_ptr->capacity) 
	{
		return 1;
	}
	else
	{
		return 0;
	}
		
}


 
