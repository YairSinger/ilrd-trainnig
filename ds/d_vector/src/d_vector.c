/* name: shahar molina
 * Reviewer: Liach Fainer
 * File: d_vector.c
 * Date: 31/08/23 */

/*---------------------Includes----------------------*/
#include <stddef.h> /* size_t */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc, realloc, free */
#include <assert.h> /* assert */

#include "d_vector.h" /* my vector library */

/*---------------------Macros & Structs & Enums----------------------*/
#define GROWTH_FACTOR 2

struct d_vector
{
	char *data;
	size_t capacity;
	size_t element_size;
	size_t size;
};

enum status
{
	SUCCESS = 0,
	NEXT_PUSH_FAIL,
	REALLOCATION_FAILED

} status_t;

/*---------------------Definitions----------------------*/
d_vector_t *VectorCreate(size_t capacity, size_t elem_size)
{
	d_vector_t *ptr_new_vec = NULL;
	char *data = NULL;

	ptr_new_vec = (d_vector_t *)malloc(sizeof(d_vector_t));
	if (NULL == ptr_new_vec)
	{
		return NULL;
	}

	data = (char *)malloc(capacity * elem_size);
	if (NULL == data)
	{
		free(ptr_new_vec);
		return NULL;
	}

	ptr_new_vec->data = data;
	ptr_new_vec->capacity = capacity;
	ptr_new_vec->element_size = elem_size;
	ptr_new_vec->size = 0;

	return ptr_new_vec;

}

void VectorDestroy(d_vector_t *vec)
{
	assert(NULL != vec);

	free(vec->data);
	vec->data = NULL;
	free(vec);
	vec = NULL;
}

int VectorPushBack(d_vector_t *vec, const void *value)
{
	int status = SUCCESS;

	assert(NULL != vec);
	assert(NULL != value);
	assert(vec->size < vec->capacity);

	memcpy(vec->data + (vec->size * vec->element_size), value, vec->element_size);
	++vec->size;

	if (vec->size == vec->capacity)
	{
		status = VectorReserve(vec, (vec->capacity * GROWTH_FACTOR));
		if (SUCCESS != status)
		{
			return NEXT_PUSH_FAIL;
		}
	}

	return SUCCESS;
}

void VectorPopBack(d_vector_t *vec)
{
	assert(NULL != vec);
	assert(0 != vec->size);

	--(vec->size);
}

void *VectorGetElem(const d_vector_t *vec, size_t index)
{
	assert(NULL != vec);
	assert(index < vec->size);

	return (vec->data + (index * vec->element_size));
}

size_t VectorSize(const d_vector_t *vec)
{
	assert(NULL != vec);

	return vec->size;
}

size_t VectorCapacity(const d_vector_t *vec)
{
	assert(NULL != vec);

	return vec->capacity;
}

int VectorReserve(d_vector_t *vec, size_t new_capacity)
{
	char *reallocated_data = NULL;

	assert(NULL != vec);
	assert(vec->capacity <= new_capacity);

	reallocated_data = realloc(vec->data, new_capacity * vec->element_size);
	if (NULL == reallocated_data)
	{
		return REALLOCATION_FAILED;
	}

	vec->data = reallocated_data;
	vec->capacity = new_capacity;

	return SUCCESS;
}

int VectorShrink(d_vector_t *vec)
{
	char *reallocated_data = NULL;

	assert(NULL != vec);

	reallocated_data = realloc(vec->data, (vec->capacity / GROWTH_FACTOR + 1) *
	                                          vec->element_size);
	if (NULL == reallocated_data)
	{
		return REALLOCATION_FAILED;
	}

	vec->data = reallocated_data;
	vec->capacity = vec->capacity/GROWTH_FACTOR + 1;

	vec->size = (vec->size >= vec->capacity) ?
				vec->capacity : vec->size;

	return SUCCESS;
}

