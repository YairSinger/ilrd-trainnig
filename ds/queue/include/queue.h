
/***********************************************************
* PROJECT: Queue
* Group: OL 147-148      
* API Version: 
* API Date   
* WRITER: Yair sllSinger
* REVIEWER: Zayd Abu Sneineh
* STATUS: Approved
* DATE: 7/8/23
***********************************************************/
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>



typedef struct queue queue_t;



/* O(1)*/
queue_t *QueueCreate(void);



/* O(n)*/
void QueueDestroy(queue_t *queue);


/*return from start O(1)*/
void *QueuePeek(const queue_t *queue);


/*inserting to end O(1)*/
int QueueEnqueue(queue_t *queue, const void *data);

/*remove from start O(1)*/
void QueueDequeue(queue_t *queue);

/*O(n)*/
size_t QueueCount(const queue_t *queue);

/* O(1)*/
int QueueIsEmpty(const queue_t *queue);

/* move elements from src to dest O(1)*/
void QueueAppend(queue_t *dest, queue_t *src);


/* #########add in sll.h#################


@Description:   Appends src's nodes to the end of dest's nodes.
                After append src is empty valid list.
	dest		- Pointer to the destination sll.
	src			- Pointer to the source sll.
@Return value: None.
@Time Complexity: O(1).
@Undefined Behavior: dest is NULL, src is NULL.
*/
void SllAppend(sll_t *dest, sll_t *src); 



#endif /* __QUEUE_H__ */
