#include <assert.h>
#include <stdlib.h> /* malloc  */
#include <stddef.h> /* size_t  */
#include "heap_pqueue.h"
#include "heap.h"

struct pqueue
{
	heap_t *pq_ptr;
};



/*=================================================*/
pqueue_t *PQCreate(int (*priority_cmp_func)(const void *lhs, const void *rhs))
{
	pqueue_t *pqueue = (pqueue_t *) malloc(sizeof(pqueue_t));
	
	if (NULL == pqueue)
	{
		return NULL;
	}
	
	pqueue->pq_ptr = HeapCreate(priority_cmp_func);
	
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
	
	HeapDestroy(queue->pq_ptr);
	queue->pq_ptr = NULL;
	free(queue);
}



/*=================================================*/
int PQEnqueue(pqueue_t *queue, const void *data)
{
	int insert_status = 0;
	assert(NULL != queue);
	
	insert_status =  HeapPush(queue->pq_ptr, data);
	
	return insert_status;
}


/*=================================================*/
void PQDequeue(pqueue_t *queue)
{
	assert(NULL != queue);
	
	HeapPop(queue->pq_ptr);
}


/*=================================================*/
void *PQPeek(pqueue_t *queue)
{
	assert(NULL != queue);
	
	
	return HeapPeek(queue->pq_ptr);
}


/*=================================================*/
int PQIsEmpty(const pqueue_t *queue)
{
	assert(NULL != queue);	
	
	return HeapIsEmpty(queue->pq_ptr);
}


/*=================================================*/
size_t PQSize(const pqueue_t *queue)
{
	assert(NULL != queue);	
		
	return HeapGetSize(queue->pq_ptr);
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
	/*sorted_list_iter_t find_if_res = {0};
	void *poped = {0};*/
	assert(NULL != queue);
	
	return HeapRemove(queue->pq_ptr, rhs,is_match_func);
		
}
