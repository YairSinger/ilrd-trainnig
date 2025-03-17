/*written by Amit */

#include <stdio.h>

#include "pqueue.h"

#define WHITEBOLD "\033[0;37;1m"
#define CLOSETEXT "\033[0m"
#define WHITE printf("\033[0;37;1m")
#define GREEN printf("\033[32;7m")
#define RED printf("\033[31;7m")
#define DEFULT printf("\033[0m")

void test_p_queue_essentials();
void test_p_queue_dequeue();
void test_p_queue_clear();
void test_p_queue_stable();


int main() 
{
	printf("\n%s***** Test1: create + Enqueue + peek  ******%s\n", WHITEBOLD, CLOSETEXT);
    	test_p_queue_essentials();
    	
    	printf("\n%s***** Test2: Dequeue + peek + isEmpty + Size  ******%s\n", WHITEBOLD, CLOSETEXT);
    	test_p_queue_dequeue();
    	
    	printf("\n%s***** Test3: Clear + Erase  ******%s\n", WHITEBOLD, CLOSETEXT);
    	test_p_queue_clear();
    	
    	printf("\n%s***** Test4: Is stable  ******%s\n", WHITEBOLD, CLOSETEXT);
    	test_p_queue_stable();
    	
    	
    	
   	return 0;
} 


int CmpFunc(const void *list_data, const void *user_data)
{
	
	return  *((size_t *)user_data) - (*(size_t *)list_data);
}

int FindMatch(const void *data, const void *param)
{
	
	return (*(size_t *)data == *(size_t *)param);
}


void test_p_queue_essentials()
{
	size_t success_counter = 0;
	size_t num_tests=0;
	size_t test[4] = {10, 17, 3, 9};
	size_t expect[4] = {10,10,3,3};
	size_t res = 0;
	size_t i = 0;
	
	pqueue_t *pq_ptr = PQCreate(CmpFunc);
	WHITE;
	printf("Create + INSERT + Peek");
	DEFULT;
	
	++num_tests;
	if(pq_ptr == NULL)
	{
		printf("\nError in creation\n");
	}
	else
	{
		++success_counter;
	}
	
	for (i = 0 ; i < 4 ; ++i)
	{
		++num_tests;
		if(1 == PQEnqueue(pq_ptr, &test[i]))
		{
			printf("\nError in Enqueue\n");
		}
		else
		{
			++success_counter;
		}
		
		res = *(size_t *)PQPeek(pq_ptr);
		++num_tests;
		if(expect[i] != res)
		{
			printf("\nError in Peek expected %ld, got %ld\n",expect[i], res );
		}
		else
		{
			++success_counter;
		}
	}
	
	
	PQDestroy(pq_ptr);
	
	(success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n",success_counter,num_tests );
	DEFULT;
	
}

void test_p_queue_dequeue()
{
	size_t success_counter = 0;
	size_t num_tests=0;
	size_t test[4] = {10, 17, 3, 9};
	size_t expect[4] = {3, 9, 10, 17};
	size_t res = 0;
	size_t i = 0;
	
	pqueue_t *pq_ptr = PQCreate(CmpFunc);
	WHITE;
	printf("Dequeue + Peek + isEmpy + Size");
	DEFULT;
	
	++num_tests;
	if(1 != PQIsEmpty(pq_ptr))
	{
		printf("\nError in is Empty" );
	}
	else
	{
		++success_counter;
	}
	
	++num_tests;
	if(0 != PQSize(pq_ptr))
	{
		printf("\nError in Size" );
	}
	else
	{
		++success_counter;
	}
	
	/* poplating the list */
	for (i = 0 ; i< 4 ; ++i)
	{
		PQEnqueue(pq_ptr, &test[i]);
	}
	
	++num_tests;
	if(0 != PQIsEmpty(pq_ptr))
	{
		printf("\nError in is Empty" );
	}
	else
	{
		++success_counter;
	}
	
	++num_tests;
	if(4 != PQSize(pq_ptr))
	{
		printf("\nError in Size" );
	}
	else
	{
		++success_counter;
	}
	
	for (i = 0 ; i < 4 ; ++i)
	{
		
		
		res = *(size_t *)PQPeek(pq_ptr);
		++num_tests;
		if(expect[i] != res)
		{
			printf("\nError in Dequeue expected %ld, got %ld\n",expect[i], res );
		}
		else
		{
			++success_counter;
		}
		PQDequeue(pq_ptr);
	}
	
	
	PQDestroy(pq_ptr);
	
	(success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n",success_counter,num_tests );
	DEFULT;
}

void test_p_queue_clear()
{
	size_t success_counter = 0;
	size_t num_tests=0;
	size_t test[4] = {10, 17, 3, 9};
	size_t expect[4] = {3, 9, 10, 17};
	size_t res = 0;
	size_t i = 0;
	
	pqueue_t *pq_ptr = PQCreate(CmpFunc);
	WHITE;
	printf("Clear");
	DEFULT;
	
	/* poplating the list */
	for (i = 0 ; i< 4 ; ++i)
	{
		PQEnqueue(pq_ptr, &test[i]);
	}
	
	++num_tests;
	if(0 != PQIsEmpty(pq_ptr))
	{
		printf("\nError in is Empty" );
	}
	else
	{
		++success_counter;
	}
	
	++num_tests;
	if(4 != PQSize(pq_ptr))
	{
		printf("\nError in Size" );
	}
	else
	{
		++success_counter;
	}
	
	PQClear(pq_ptr);
	
	++num_tests;
	if(1 != PQIsEmpty(pq_ptr))
	{
		printf("\nError in is Empty" );
	}
	else
	{
		++success_counter;
	}
	
	++num_tests;
	if(0 != PQSize(pq_ptr))
	{
		printf("\nError in Size" );
	}
	else
	{
		++success_counter;
	}

	
	(success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n",success_counter,num_tests );
	DEFULT;
	
	
	WHITE;
	printf("Erase");
	DEFULT;
	
	success_counter = 0;
	num_tests=0;
	
	/* poplating the list */
	for (i = 0 ; i< 4 ; ++i)
	{
		PQEnqueue(pq_ptr, &test[i]);
	}
	
	PQErase(pq_ptr, FindMatch, &test[2]);
	
	++num_tests;
	if(0 != PQIsEmpty(pq_ptr))
	{
		printf("\nError in is Empty" );
	}
	else
	{
		++success_counter;
	}
	
	++num_tests;
	if(3 != PQSize(pq_ptr))
	{
		printf("\nError in Size" );
	}
	else
	{
		++success_counter;
	}
	
	i = 1;
	res = *(size_t *)PQPeek(pq_ptr);
	++num_tests;
	if(expect[i] != res)
	{
		printf("\nError in Dequeue expected %ld, got %ld\n",expect[i], res );
	}
	else
	{
		++success_counter;
	}
	
	PQErase(pq_ptr, FindMatch, &test[3]);
	
	++num_tests;
	if(0 != PQIsEmpty(pq_ptr))
	{
		printf("\nError in is Empty" );
	}
	else
	{
		++success_counter;
	}
	
	++num_tests;
	if(2 != PQSize(pq_ptr))
	{
		printf("\nError in Size" );
	}
	else
	{
		++success_counter;
	}
	
	i = 2;
	res = *(size_t *)PQPeek(pq_ptr);
	++num_tests;
	if(expect[i] != res)
	{
		printf("\nError in Dequeue expected %ld, got %ld\n",expect[i], res );
	}
	else
	{
		++success_counter;
	}
	
	PQDestroy(pq_ptr);
	
	(success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n",success_counter,num_tests );
	DEFULT;
}


int CmpFunc2(const void *list_data, const void *user_data)
{
	
	return (((*(size_t *)list_data % 10) - (*(size_t *)user_data) % 10));
}

void test_p_queue_stable()
{
	size_t success_counter = 0;
	size_t num_tests=0;
	size_t test[4] = {22, 8, 12, 23};
	size_t expect[4] = {22, 12, 23, 8};
	size_t res = 0;
	size_t i = 0;
	
	pqueue_t *pq_ptr = PQCreate(CmpFunc2);
	
	WHITE;
	printf("Is stable");
	DEFULT;
	
	for (i = 0 ; i< 4 ; ++i)
	{
		PQEnqueue(pq_ptr, &test[i]);
	}
	
	for (i = 0 ; i< 4 ; ++i)
	{
		res = *(size_t *)PQPeek(pq_ptr);
		++num_tests;
		if(expect[i] != res)
		{
			printf("\nList is not Stable: expected %ld, got %ld\n",expect[i], res );
		}
		else
		{
			++success_counter;
		}
		
		PQDequeue(pq_ptr);
	}
	
	PQDestroy(pq_ptr);
	
	(success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n",success_counter,num_tests );
	DEFULT;
}
