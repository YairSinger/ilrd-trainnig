
/* ----------------------------------------------------------
 * Filename:    heap_pqueue.c
 * Author:      Shahar Molina
 * Reviewer:	Yael Hava
 * Date:        15.11.2023
 * Course:      OL-149
 * Description: Implementation of Priority Queue
 * ----------------------------------------------------------
 */

#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <stdlib.h> /*malloc, free*/

/*#include "heap.h"      /* heap header */*/
#include "heap_pq.h"   /* heap priority queue header */

/*---Struct---*/
struct pqueue
{
	heap_t *pq_heap;
};

/*---Functions Definitions---*/
pqueue_t *PQCreate(cmp_func_t cmp_func)
{
	pqueue_t *pq = NULL;

	assert(NULL != cmp_func);

	pq = (pqueue_t *)malloc(sizeof(pqueue_t));
	if (NULL == pq)
	{
		return NULL;
	}

	pq->pq_heap = HeapCreate(cmp_func);
	if (NULL == pq->pq_heap)
	{
		free(pq);
		return NULL;
	}
	return pq;
}

void PQDestroy(pqueue_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->pq_heap);

	HeapDestroy(pq->pq_heap);
	pq->pq_heap = NULL;

	free(pq);
	pq = NULL;
}

int PQEnqueue(pqueue_t *pq, void *data)
{
	assert(NULL != pq);
	assert(pq->pq_heap);
	assert(NULL != data);

	return HeapPush(pq->pq_heap, data);
}

void *PQDequeue(pqueue_t *pq)
{
	void *element = NULL;
	assert(NULL != pq);
	assert(NULL != pq->pq_heap);
	assert(!HeapIsEmpty(pq->pq_heap));

	element = HeapPeek(pq->pq_heap);
	HeapPop(pq->pq_heap);

	return element;
}

void *PQPeek(const pqueue_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->pq_heap);
	assert(!HeapIsEmpty(pq->pq_heap));

	return HeapPeek(pq->pq_heap);
}

size_t PQSize(const pqueue_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->pq_heap);

	return HeapGetSize(pq->pq_heap);
}

int PQIsEmpty(const pqueue_t *pq)
{
	assert(NULL != pq);
	assert(NULL != pq->pq_heap);

	return HeapIsEmpty(pq->pq_heap);
}

void PQClear(pqueue_t *pq)
{
	assert(NULL != pq);

	while (!HeapIsEmpty(pq->pq_heap))
	{
		PQDequeue(pq);
	}
}

void *PQErase(pqueue_t *pq, match_func_t match_func, void *param)
{
	assert(NULL != pq);
	assert(NULL != pq->pq_heap);
	assert(NULL != match_func);

	return HeapRemove(pq->pq_heap, (match_func_t)match_func, param);
}
