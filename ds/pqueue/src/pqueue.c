#include <assert.h>
#include <stdlib.h> /* malloc  */
#include <stddef.h> /* size_t  */
#include "pqueue.h"
#include "sorted_list.h"

struct pqueue
{
	sorted_list_t *pq_ptr;
};
/*=================================================*/
pqueue_t *PQCreate(int (*priority_cmp_func)(const void *lhs, const void *rhs))
{
	pqueue_t *pqueue = (pqueue_t *) malloc(sizeof(pqueue_t));
	
	if (NULL == pqueue)
	{
		return NULL;
	}
	
	pqueue->pq_ptr = SortedListCreate(priority_cmp_func);
	
	if (NULL == (pqueue->pq_ptr))
	{
		free(pqueue);
		return NULL;
	}
	
	return pqueue;
}


/*=================================================*/
void PQDestroy(pqueue_t *queue)
{
	assert(NULL != queue);
	
	SortedListDestroy(queue->pq_ptr);
	queue->pq_ptr = NULL;
	free(queue);
}



/*=================================================*/
int PQEnqueue(pqueue_t *queue, const void *data)
{
	sorted_list_iter_t input_iter = {0};
	
	assert(NULL != queue);
	
	input_iter = SortedListInsert(queue->pq_ptr, data);
	
	return SortedListIsSameIter(input_iter, SortedListEnd(queue->pq_ptr));
}


/*=================================================*/
void PQDequeue(pqueue_t *queue)
{
	assert(NULL != queue);
	
	SortedListRemove(SortedListBegin(queue->pq_ptr));
}


/*=================================================*/
void *PQPeek(pqueue_t *queue)
{
	assert(NULL != queue);
	
	return SortedListGetData(SortedListBegin(queue->pq_ptr));
}


/*=================================================*/
int PQIsEmpty(const pqueue_t *queue)
{
	assert(NULL != queue);	
	
	return SortedListIsEmpty(queue->pq_ptr);
}


/*=================================================*/
size_t PQSize(const pqueue_t *queue)
{
	assert(NULL != queue);	
		
	return SortedListSize(queue->pq_ptr);
}


/*=================================================*/
void PQClear(pqueue_t *queue)
{
	assert(NULL != queue);
	
	while (!PQIsEmpty(queue))
	{
		PQDequeue(queue);
	}	
}


/*=================================================*/
void *PQErase(pqueue_t *queue, int (*is_match_func)(const void *lhs, const void *rhs), void *rhs)
{
	sorted_list_iter_t find_if_res = {0};
	void *poped = {0};
	assert(NULL != queue);
	
	find_if_res = SortedListFindIf(
				SortedListBegin(queue->pq_ptr),	SortedListEnd(queue->pq_ptr),
				is_match_func, rhs);
	if (!SortedListIsSameIter(find_if_res, SortedListEnd(queue->pq_ptr)))
	{
		poped = SortedListGetData(find_if_res);
		SortedListRemove(find_if_res);
		return poped;
	}
	else
	{
		return NULL;
	}
}
