
/* ----------------------------------------------------------
 * Filename:    heap.c
 * Author:      Shahar Molina
 * Reviewer:	Yael Hava
 * Date:        15.11.2023
 * Course:      OL-149
 * Description: Implementation of
 * ----------------------------------------------------------
 */
/*---Includes---*/
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "d_vector.h" /* API d_vector */
#include "heap.h"     /* API heap */

/*---Constants---*/
static const size_t default_capacity = 10;

/*---Enum & Struct---*/
typedef enum heap_status
{
	HEAP_SUCCESS,
	HEAP_FAILURE,
	HEAP_ALLOCATION_FAILURE
} heap_status_t;

struct heap
{
	d_vector_t *arr;
	heap_cmp_func_t cmp_func;
};

/*---Functions Declerations---*/
static void HeapHeapifyUp(heap_t *heap, size_t index);
static void HeapHeapifyDown(heap_t *heap, size_t index);

static void HeapSwap(heap_t *heap, size_t left_index, size_t right_index);
static void *HeapGet(const d_vector_t *vec, size_t index);
static void HeapSet(const d_vector_t *vec, size_t index, void *value);
static heap_status_t HeapPushBack(d_vector_t *vec, void *element);

static size_t GetParentIndex(size_t index);
static size_t GetLeftChildIndex(size_t index);
static size_t GetRightChildIndex(size_t index);



/*---Functions Definitions---*/
heap_t *HeapCreate(heap_cmp_func_t cmp_func)
{
	d_vector_t *arr = NULL;
	heap_t *heap = NULL;

	assert(cmp_func);

	heap = (heap_t *)malloc(sizeof(heap_t));
	if (!heap)
	{
		return NULL;
	}

	arr = VectorCreate(default_capacity, sizeof(void*));
	if (!arr)
	{
		free(heap);
		heap = NULL;

		return NULL;
	}

	heap->arr = arr;
	heap->cmp_func = cmp_func;

	return heap;
}

void HeapDestroy(heap_t *heap)
{
	assert(heap);

	VectorDestroy(heap->arr);
	heap->arr = NULL;

	free(heap);
	heap = NULL;
}

int HeapPush(heap_t *heap, void *element)
{
	int status = HEAP_SUCCESS;

	assert(heap);
	assert(element);

	status = HeapPushBack(heap->arr, element);
	if (0 != status)
	{
		return status;
	}

	HeapHeapifyUp(heap, HeapSize(heap) - 1);

	return status;
}

static void HeapHeapifyUp(heap_t *heap, size_t index)
{
	size_t parent_index = GetParentIndex(index);

	while (index > 0 &&
	       heap->cmp_func(HeapGet(heap->arr, index),
	                      HeapGet(heap->arr, parent_index)) > 0)
	{
		HeapSwap(heap, index, parent_index);
		index = parent_index;
		parent_index = GetParentIndex(index);
	}
}

void HeapPop(heap_t *heap)
{
	assert(heap);

	HeapSwap(heap, 0, VectorSize(heap->arr) - 1);
	VectorPopBack(heap->arr);
	HeapHeapifyDown(heap, 0);
}

static void HeapHeapifyDown(heap_t *heap, size_t index)
{
	size_t priority_child_index = 0;

	size_t left_child_index = GetLeftChildIndex(index);
	size_t right_child_index = GetRightChildIndex(index);

	while (left_child_index < VectorSize(heap->arr))
	{
		size_t parent_index = index;
		priority_child_index = left_child_index;

		if (right_child_index < VectorSize(heap->arr) &&
		    heap->cmp_func(HeapGet(heap->arr, right_child_index),
		                   HeapGet(heap->arr, left_child_index)) >
		        0)
		{
			priority_child_index = right_child_index;
		}

		if (heap->cmp_func(HeapGet(heap->arr, priority_child_index),
		                   HeapGet(heap->arr, parent_index)) <= 0)
		{
			return;
		}

		HeapSwap(heap, priority_child_index, parent_index);

		index = priority_child_index;
		left_child_index = GetLeftChildIndex(index);
		right_child_index = GetRightChildIndex(index);
	}


}

void *HeapRemove(heap_t *heap, heap_match_func_t match_func,
                 const void *base_data)
{
	size_t index = 0;
	size_t size = 0;
	size_t last_index = 0;
	void **removed_elem = NULL;

	assert(heap);
	assert(match_func);
	assert(base_data);

	size = VectorSize(heap->arr);

	while ((index < size) &&
	       (!match_func(HeapGet(heap->arr, index), base_data)))
	{
		++index;
	}

	if (index == size)
	{
		return NULL;
	}

	last_index = size - 1;
	HeapSwap(heap, index, last_index);

	removed_elem = HeapGet(heap->arr, last_index);
	VectorPopBack(heap->arr);

	if (index < last_index)
	{
		HeapHeapifyUp(heap, index);
		HeapHeapifyDown(heap, index);
	}


	return removed_elem;
}

void *HeapPeek(const heap_t *heap)
{
	assert(heap);

	return HeapGet(heap->arr, 0);
}

int HeapIsEmpty(heap_t *heap)
{
	assert(heap);

	return (0 == VectorSize(heap->arr));
}

size_t HeapSize(heap_t *heap)
{
	assert(heap);

	return VectorSize(heap->arr);
}


/*---Service Functions---*/
static void HeapSwap(heap_t *heap, size_t left_index, size_t right_index)
{
	void *tmp = HeapGet(heap->arr, left_index);
	HeapSet(heap->arr, left_index, HeapGet(heap->arr, right_index));
	HeapSet(heap->arr, right_index, tmp);
}

static void *HeapGet(const d_vector_t *vec, size_t index)
{
	return *(void **)VectorGetElem(vec, index);
}

static void HeapSet(const d_vector_t *vec, size_t index, void *value)
{
	*(void **)VectorGetElem(vec, index) = value;
}

static heap_status_t HeapPushBack(d_vector_t *vec, void *element)
{
	if (0 != VectorPushBack(vec, &element))
	{
		return HEAP_ALLOCATION_FAILURE;
	}

	return HEAP_SUCCESS;
}

static size_t GetParentIndex(size_t index)
{
	return ((index - 1) / 2);
}

static size_t GetLeftChildIndex(size_t index)
{
	return ((2 * index) + 1);
}

static size_t GetRightChildIndex(size_t index)
{
	return ((2 * index) + 2);
}


