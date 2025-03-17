#include <stdio.h>		/* printf */
#include <stdlib.h>
#include <assert.h>
#include <string.h>		/* STRCMP */

#include "heap_pqueue.h"


#define GOOD "\033[1;30m\033[102m"
#define BAD "\033[1;37m\033[41m"
#define REG "\033[1;0m""\n"
#define HEAD "\033[1;30m\033[47m"

#define NUM_OF_BUCKETS 11
#define WORD_SIZE 30
#define SPELL_NUM_BUCKETS 1000
#define KEY_SIZE 104334

#define UNUSED(x) (void)x



void TestPushPop();
void TestRemove();

int main(void)
{
    TestPushPop();
    TestRemove();


    return 0;
}


int MatchFunc(const void *lhs, const void *rhs)
{
	return *(int *)lhs == *(int *)rhs;
}


int PriorityCmpFunc(const void *lhs, const void *rhs)
{
	
	return  *(int*)lhs - *(int*)rhs ;
}



/**************************************************************/ 

void TestPushPop()
{ 
	int data[] = {10,12,9,14};
	int control_data[] = {10,12,12,14};
	int remove_data[] = {14,12,10,9};
	size_t size = 4;
	
	size_t i = 0;

	pqueue_t *heap = NULL;
	
	size_t  error_count = 0;
	
	printf(HEAD"TestPushPop"REG);
	printf("\n");

/***************************************************************/
	heap = PQCreate(PriorityCmpFunc);
	if (NULL == heap)
	{
		printf(BAD"FAILURE - failed allocating block"REG);
		++error_count;
	}
	
	
	if(!PQIsEmpty(heap))
    {
        printf(BAD"FAIL - heap not empty in init"REG);
        ++error_count;
    }
   
    if(0 != PQSize(heap))
    {
        printf(BAD"FAIL - size not 0 in init"REG);
        ++error_count;
    }

	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}
/***************************************************************/
	error_count = 0;
	size = 4;
	
	for (i = 0; i < size; ++i)
	{
		
		if (1 == PQEnqueue(heap, &data[i]))
		{
			printf(BAD"FAILURE - failed allocating block - data = %d "REG, data[i]);
			++error_count;
		}
		
		
		
		if(i + 1 != PQSize(heap))
    	{
      		printf(BAD" EXPECTED: %lu RECIEVED: %lu "REG , i + 1, PQSize(heap));
        	++error_count;
    	}
    	
    	if(control_data[i] != *(int*)PQPeek(heap))
    	{
      		printf(BAD" EXPECTED: %d RECIEVED: %d "REG , control_data[i], 
      												*(int*)PQPeek(heap));
        	++error_count;
    	}
	}
	
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}
	
/***************************************************************/	
	error_count = 0;
	
	for (i = 0; i < size; ++i)
	{	
		if(remove_data[i] != *(int*)PQPeek(heap))
    	{
      		printf(BAD" EXPECTED: %d RECIEVED: %d "REG , remove_data[i], 
      												*(int*)PQPeek(heap));
        	++error_count;
    	}
    	
    	PQDequeue(heap);
		
		if(size - i - 1 != PQSize(heap))
    	{
      		printf(BAD" EXPECTED: %lu RECIEVED: %lu "REG ,size - i - 1, 
      													PQSize(heap));
       		 ++error_count;
    	}
		
	}	

    
    if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}
	
	PQDestroy(heap);
	
}

/***************************************************************/



void TestRemove()
{ 
	int data[] = {100,50,60,20,40,45,30};
	int control_data[] = {100};

	size_t size = 7;
	
	
	
	
	
	size_t i = 0;

	pqueue_t *heap = NULL;
	
	size_t  error_count = 0;
	
	printf(" userdata = %d\n", data[6]);
	printf(" useradress = %p\n",(void *)&data[6]);
		
	printf(HEAD"TestRemove"REG);
	printf("\n");

/***************************************************************/
	heap = PQCreate(PriorityCmpFunc);
	if (NULL == heap)
	{
		printf(BAD"FAILURE - failed allocating block"REG);
		++error_count;
	}
	
	
	if(!PQIsEmpty(heap))
    {
        printf(BAD"FAIL - heap not empty in init"REG);
        ++error_count;
    }
   
    if(0 != PQSize(heap))
    {
        printf(BAD"FAIL - size not 0 in init"REG);
        ++error_count;
    }

	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}
/***************************************************************/
	error_count = 0;
	
	for (i = 0; i < size; ++i)
	{
		
		if (1 == PQEnqueue(heap, &data[i]))
		{
			printf(BAD"FAILURE - failed allocating block - data = %d "REG, data[i]);
			++error_count;
		}
		
		
		
		if(i +1 != PQSize(heap))
    	{
      		printf(BAD" EXPECTED: %lu RECIEVED: %lu "REG , i + 1, PQSize(heap));
        	++error_count;
    	}
    	
    	if(control_data[0] != *(int*)PQPeek(heap))
    	{
      		printf(BAD" EXPECTED: %d RECIEVED: %d "REG , control_data[i], 
      												*(int*)PQPeek(heap));
        	++error_count;
    	}
	}
	
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}


/***************************************************************/	
	error_count = 0;
	
	
	
	/*remove = PQErase(heap, &remove_param, MatchFunc);
	
	
	
	if (NULL != remove)
	{
	
		if(control_remove != *(int*)remove)
    		{
      			printf(BAD" EXPECTED: %d RECIEVED: %d "REG , control_remove, 
      												*(int*)remove);
        		++error_count;
    		}
	}
	*/
	/*remove = PQErase(heap, &remove_param1, MatchFunc);
		
	PQEnqueue(heap, &x);

	if (NULL != remove)
	{
		if(control_remove1 != *(int*)remove)
    		{
      			printf(BAD" EXPECTED: %d RECIEVED: %d "REG , control_remove1, 
      												*(int*)remove);
        		++error_count;
    		}
	}
*/
		
	 if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}

	
	PQDestroy(heap);

}

/***************************************************************/















