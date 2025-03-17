#include <stdio.h> 	/* printf */
#include <string.h> /* memcmp */
#include "sll.h"
#include "queue.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"


void TestCreateDestroy();
void TestQueueEnqueue();
void TestQueueCount();
void TestQueueIsEmpty();
void TestQueueDequeue();
void TestQueuePeek();
void TestQueueAppend();

int main()
{
	TestCreateDestroy();
	TestQueueEnqueue();
	TestQueueDequeue();
	TestQueueCount();	
	TestQueueIsEmpty();
	TestQueuePeek();
	TestQueueAppend();
	
	return 0;
}

/********************/
void TestCreateDestroy()
{
	queue_t *queue = QueueCreate();
	if (NULL != queue && 0 != sizeof(queue))
	{
		printf(GREEN"QUEUE CREATE PASSED\n"RESET_COLOR);
	}
	else
	{
		printf(RED"QUEUE CREATE FAILED\n"RESET_COLOR);
	}		
	
	QueueDestroy(queue);	
	printf(GREEN"test valgrind for full memory release test\n\n"RESET_COLOR);
}

/***********************************/

void TestQueueEnqueue() 
{
	queue_t *queue = QueueCreate();
	int arr[5] = {5,7,0,0,0};
	size_t i = 0;
	int fails_counter = 0;
	
	for(i = 0; i < 5; ++i)
	{
		if(1 == QueueEnqueue(queue, (const void *) &arr[i]))
		{
			++fails_counter ;
			printf(RED"Test 1 TestQueueEnqueue FAILED to insert int\n"RESET_COLOR);
		}
	}
	
	if (0 == fails_counter && 5 == QueueCount((const queue_t *) queue))
	{
		printf(GREEN"Test TestQueueEnqueue PASSED\n"RESET_COLOR);
	}
	QueueDestroy(queue);
}

/***************************************/	
void TestQueueCount()
{
	queue_t *queue = QueueCreate();
	int arr[5] = {5,7,0,0,0};
	
	size_t i = 0;
	int fails_counter = 0;
	
	if (0 != QueueCount((const queue_t *) queue))
		{
			++fails_counter ;
			printf(RED"Test 1 TestQueueCount FAILED when count is 0 \n"RESET_COLOR);
		}
	
	for(i = 0; i < 5; ++i)
	{
		QueueEnqueue(queue, (const void *) &arr[i]);
		if ((i+1)!= QueueCount((const queue_t *) queue))
		{
			++fails_counter ;
			printf(RED"Test 2 TestQueueCount FAILED when Enqueue ints \n"RESET_COLOR);
		}
			
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test TestQueueCount PASSED\n"RESET_COLOR);
	}
	QueueDestroy(queue);
}

/******************************************/
void TestQueueIsEmpty()
{
	queue_t *queue = QueueCreate();
	int arr[5] = {5,7,0,0,0};
	
	size_t i = 0;
	int fails_counter = 0;
	if (1 != QueueIsEmpty((const queue_t *) queue))
	{
		++fails_counter ;
		printf(RED"Test 1 TestQueueIsEmpty FAILED when empty\n"RESET_COLOR);
	}
	QueueEnqueue(queue, (const void *) &arr[i]);
	
	if (0 != QueueIsEmpty((const queue_t *) queue))
	{
		++fails_counter ;
		printf(RED"Test 2 TestQueueIsEmpty FAILED when not empty\n"RESET_COLOR);
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test TestQueueIsEmpty PASSED\n"RESET_COLOR);
	}
	QueueDestroy(queue);
}

/*******************************************/

void TestQueueDequeue()
{
	queue_t *queue = QueueCreate();
	int arr[5] = {5,7,0,0,0};
	size_t i = 0;
	int fails_counter = 0;
	
	for(i = 0; i < 5; ++i)
	{
		QueueEnqueue(queue, (const void *) &arr[i]);
	}
	for(i = 0; i < 5; ++i)
	{
		QueueDequeue(queue);
		if (4-i != QueueCount((const queue_t *) queue))
		{
			++fails_counter ;
			printf(RED"Test 1 TestQueueDequeue FAILED when not empty\n"RESET_COLOR);
		}	
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test TestQueueDequeue PASSED\n"RESET_COLOR);
	}
	QueueDestroy(queue);
}

/***********************************************/

void TestQueuePeek()
{
	queue_t *queue_int = QueueCreate();
	queue_t *queue_char = QueueCreate();
	int arr[5] = {5,7,0,0,0};
	char str[5] = {'a','b','d','t','0'};
	size_t i = 0;
	int fails_counter = 0;
	
	for(i = 0; i < 5; ++i)
	{
		QueueEnqueue(queue_int, (const void *) &arr[i]);
		QueueEnqueue(queue_char, (const void *) &str[i]);
	}
	
	for(i = 0; i < 5; ++i)
	{
		if (arr[i] != *((int *) QueuePeek((const queue_t *)queue_int))
		&& str[i]!= *((char *) QueuePeek((const queue_t *)queue_char)))
		{
			++fails_counter;
			printf(RED"Test 1 TestQueuePeek FAILED \n"RESET_COLOR);
		}
		
		QueueDequeue(queue_int);	
		QueueDequeue(queue_char);
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test TestQueuePeek PASSED\n"RESET_COLOR);
	}
	QueueDestroy(queue_int);
	QueueDestroy(queue_char);
}

/**********************************************/
void TestQueueAppend()
{
	queue_t *queue1 = QueueCreate();
	queue_t *queue2 = QueueCreate();
	int arr[5] = {1,2,3,4,5};
	int arr2[5] = {6,7,8,9,10};
	int res[10] = {1,2,3,4,5,6,7,8,9,10};
	size_t i = 0;
	int fails_counter = 0;
	
	for(i = 0; i < 5; ++i)
	{
		QueueEnqueue(queue1, (const void *) &arr[i]);
		QueueEnqueue(queue2, (const void *) &arr2[i]);
	}
	
	QueueAppend(queue1, queue2);
	if (0 != QueueCount((const queue_t *) queue2) && 10 != QueueCount((const queue_t *) queue1))
	{
		++fails_counter;
		printf(RED"Test 1 TestQueueAppend FAILED \nsrc length  %lu vs 0 expected \n dest length %lu vs 10 expected\n "RESET_COLOR, QueueCount((const queue_t *) queue2), QueueCount((const queue_t *) queue1));
	}
	for(i = 0; i < 10; ++i)
	{
		if (res[i] != *((int *) QueuePeek((const queue_t *) queue1)))
		{
			++fails_counter;
		printf(RED"Test 2 TestQueueAppend FAILED \ndest   %d vs %d expected \n"RESET_COLOR,*((int *) QueuePeek((const queue_t *) queue1)) ,res[i] );
		}
		QueueDequeue(queue1);
	}
	if (0 == fails_counter)
	{
		printf(GREEN"Test TestQueueAppend PASSED\n"RESET_COLOR);
	}
	QueueDestroy(queue1);
	QueueDestroy(queue2);		
}
	
