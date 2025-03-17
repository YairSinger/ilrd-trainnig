/***********************************************************
*PROJECT:Heap
*
*WRITER: Yair Singer
*
*REVIEWER: Omer Cohen
*
*STATUS: approved
*
*DATE: 8/10/23
***********************************************************/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include <string.h> /*memset */

#include "heap.h" /*API functions */
#include "dvector.h"

#define UNUSED(x) (void)x


struct heap 
{
	int (*priority_cmp)(const void *, const void *);
    d_vector_t *arr;         
};


heap_t *HeapCreate(int (*priority_cmp)(const void*, const void*))
{
	heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
	
	if(NULL == heap)
	{
		return NULL;
	}
	
	heap->arr = DVectorCreate(1, sizeof(size_t));
	if(NULL == heap->arr)
	{
		free(heap);
		return NULL;
	}
	
	heap->priority_cmp = priority_cmp;
	return heap;
}

/*=====================================================*/
void HeapDestroy(heap_t *heap)
{
	
	assert(NULL != heap);
	
	DVectorDestroy(heap->arr);
	memset(heap, 0, sizeof(heap_t));
	free(heap);
}

/*=====================================================*/

static void Swap(d_vector_t *arr, size_t index1, size_t index2)
{
	void **element1 = (void **)DVectorGetElementAccess(arr, index1);
	void **element2 = (void **)DVectorGetElementAccess(arr, index2);
	void *temp = *element1;
	
	*element1 =  (void *)((size_t *)*element2);
	*element2 =  (void *)((size_t *)temp);
}


static void HeapifyUp(heap_t *heap, size_t index)
{
	int tested_index = index;

	assert(NULL != heap->arr);
	
	while(0 != tested_index && 
		0 < heap->priority_cmp(*(void **)DVectorGetElementAccess(heap->arr, tested_index),
										*(void **)DVectorGetElementAccess(heap->arr, (tested_index - 1) / 2)))
	{
		Swap(heap->arr, tested_index, (tested_index - 1) / 2);
		tested_index = (tested_index - 1) / 2;
	}
}


int HeapPush(heap_t *heap, const void *data)
{
	int insert_status = 0;
	assert(NULL != heap);
	assert(NULL != data);
	
	insert_status = DVectorPushBack(heap->arr, &data);	
	if (0 == insert_status)
	{
		HeapifyUp(heap, DVectorSize(heap->arr) - 1);
	}
	
	return insert_status;
}

/*=====================================================*/
void *HeapPeek(const heap_t *heap)
{
	size_t root_index = 0;
	
	assert(NULL != heap);
	
	return *(void **)DVectorGetElementAccess(heap->arr, root_index);
}
/*=====================================================*/

size_t HeapGetSize(const heap_t *heap)
{
	assert(NULL != heap);
	
	return DVectorSize(heap->arr);
}
/*=====================================================*/

int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);
	
	return 0 == HeapGetSize(heap);
}

/*=====================================================*/

static void HeapifyDown(heap_t *heap, size_t index)
{
	size_t continue_swap = 1;
	size_t left_child = 0;
	size_t right_child = 0;
	size_t higher_proirity = 0;
	size_t size = 0;
	size_t last_non_leaf_i = 0;
	int priority_res = 0;
	
	assert(NULL != heap);
	
	size = HeapGetSize(heap);
	last_non_leaf_i = (size % 2 == 0) ? (size - 1) / 2 : (size - 2) / 2;
	while (1 == continue_swap && 0 < size && index <= last_non_leaf_i)
	{
		continue_swap = 0;
		left_child = index * 2 + 1;
		right_child = index * 2 + 2;
		if (right_child < size)
		{
			/*check priority left and right */
			priority_res = heap->priority_cmp
								(*(void **)DVectorGetElementAccess(heap->arr, left_child),
								*(void **)DVectorGetElementAccess(heap->arr, right_child)); 
			higher_proirity = 0 < priority_res ? left_child : right_child ;
			/*check priority higher_proirity and index */
			priority_res = heap->priority_cmp
								(*(void **)DVectorGetElementAccess(heap->arr, higher_proirity ),
								*(void **)DVectorGetElementAccess(heap->arr, index));
			if (0 < priority_res)
			{
				Swap(heap->arr, index, higher_proirity);
				index = higher_proirity;
				continue_swap = 1;			
			}
		}
		else if ((left_child < size) && 0 < heap->priority_cmp
								(*(void **)DVectorGetElementAccess(heap->arr, left_child),
								*(void **)DVectorGetElementAccess(heap->arr, index)))
		{
			Swap(heap->arr, index, left_child);
			index = left_child;
			continue_swap = 1;
		}
	}
}

void HeapPop(heap_t *heap)
{
	size_t end_i = 0;
	
	assert(NULL != heap);
	
	end_i = HeapGetSize(heap) - 1;
	if (0 < end_i)
	{
		Swap(heap->arr, 0, end_i);
	
	}
	DVectorPopBack(heap->arr);
	
	HeapifyDown(heap, 0);
}

/*=====================================================*/

void *HeapRemove(heap_t *heap, const void *param, int(*heap_is_match)(const void *data, const void *param))
{	
	size_t remove_i = 0;
	size_t end_i = 0;
	size_t size = 0;
	int is_match = 0;
	void **removed_add = 0;
	
	assert(NULL != heap);
	assert(NULL != heap_is_match);
	
	size = HeapGetSize(heap);	
	for (remove_i = 0; remove_i < size; ++remove_i)
	{
		is_match = heap_is_match(*(void **)DVectorGetElementAccess(heap->arr, remove_i), param);
		if (1 == is_match)
		{
			break;
		}		
	}
	
	if (1 != is_match)
	{
		return NULL;
	}
	
	removed_add = *(void **)DVectorGetElementAccess(heap->arr, remove_i);
	end_i = HeapGetSize(heap) - 1;
	Swap(heap->arr, remove_i, end_i);
	DVectorPopBack(heap->arr);
	
	if (remove_i != end_i)
	{
		HeapifyUp(heap, remove_i);
		HeapifyDown(heap, remove_i);	
	}
	return removed_add;
}

