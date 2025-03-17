#include <stdio>
#include "stack.h"

typedef struct queue
{
	stack_t *stack1;
	stack_t *stack2;
}queue_t;


int Enqueue(queue_t *queue, void *data)
{
	if (StackCapacity(queue->stack1) > StackSize(queue->stack1))
	{
		StackPush(queue->stack1, data);
		return 0;
	}
	return 1;
}

void *Dequeue(queue_t *queue)
{
	void *temp = NULL;
	void *res = NULL;
	if (StackIsEmpty(queue->stack1))
	{
		return NULL;
	}
	
	while (!StackIsEmpty(queue->stack1))
	{
		StackPop(queue->stack1, temp);
		StackPush(queue->stack2, temp);
	}
	
	StackPop(queue->stack2, res);
	
	while (!StackIsEmpty(queue->stack2))
	{
		StackPop(queue->stack2, temp);
		StackPush(queue->stack1, temp);
	}
	
	return res;
}
