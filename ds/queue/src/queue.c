#include <assert.h>
#include <stdlib.h> /* malloc  */
#include <stddef.h> /* size_t  */
#include "sll.h"
#include "queue.h"

struct queue
{
	sll_t *sll;
};

queue_t *QueueCreate(void)
{
	queue_t *queue_ptr = (queue_t *) malloc(sizeof(queue_t));
	if (NULL == queue_ptr)
	{
		return NULL;
	}
	
	queue_ptr->sll = SllCreate();
	if (NULL == queue_ptr->sll)
	{
		free(queue_ptr);
		return NULL;
	}
	
	return queue_ptr;
}

void QueueDestroy(queue_t *queue)
{
	
	assert(NULL != queue);
	SllDestroy(queue->sll);
	queue->sll = NULL;
	
	free(queue);
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	return (SllGetData(SllBegin((const sll_t *)queue->sll)));
}

int QueueEnqueue(queue_t *queue, const void *data)
{
	sll_iter_t iter = NULL;
	
	assert(NULL != queue);
	assert(NULL != data);
	
		
	iter = SllInsert(queue->sll, SllEnd(queue->sll),data);
	return NULL == iter;  
}

void QueueDequeue(queue_t *queue)
{
	assert(NULL != queue);
	SllRemove(queue->sll, SllBegin(queue->sll));
}

size_t QueueCount(const queue_t *queue)
{
	assert(NULL != queue);
	return SllCount((const sll_t *)queue->sll);
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	return (SllBegin(queue->sll) == SllEnd(queue->sll));
}

void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	SllAppend(dest->sll, src->sll);
} 


