#include <stdio.h> 	/* printf */
#include <pthread.h> /*thread save test*/
#include<unistd.h> /*sleep*/
#include "uid.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

#define UNUSED (void)
ilrd_uid_t ids[10] = {0}; 

void TestBadUid()
{
	ilrd_uid_t first = GenerateBadUID();
	ilrd_uid_t sec = GenerateBadUID();
	
	int fails_counter = 0;
	if (0 == sizeof(first))
	{
		++fails_counter ;
		printf(RED"Test 1 GenerateBadUID FAILED to return value\n"RESET_COLOR);
	}
	
	if (!IsSameUID(first, sec))
	{
		++fails_counter ;
		printf(RED"Test 2 GenerateBadUID FAILED not consistant bad values\n"RESET_COLOR);
	}
	if (0 == fails_counter)
	{
		printf(GREEN"Test GenerateBadUID PASSED\n"RESET_COLOR);
	}
}

void TestGenerateUIDIsSame()
{
	int fails_counter = 0;
	ilrd_uid_t bad =  GenerateBadUID();
	ilrd_uid_t first = GenerateUID();
	ilrd_uid_t sec = GenerateUID();
	
	if (IsSameUID(first, bad) || IsSameUID(sec ,bad))
	{
		++fails_counter ;
		printf(RED"Test 1 GenerateUID FAILED retured bad uid\n"RESET_COLOR);
	}
	
	if (IsSameUID(first, sec))
	{
		++fails_counter ;
		printf(RED"Test 2 GenerateUID FAILED uid's are not unique\n"RESET_COLOR);
	
	}
	
	if (first.counter ==  sec.counter)
	{
		++fails_counter ;
		printf(RED"Test 3 GenerateUID FAILED counter members isnt updating\n"RESET_COLOR);
	
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test GenerateUID & IsSame PASSED\n"RESET_COLOR);
	}

}


static void *PreducerFunc(void *data)
{
    size_t i = 0;
    UNUSED data;
    for (i = 0; i < 5; ++i)
    {
        ids[i] = GenerateUID();
		sleep(2);                
    }
    return NULL;
}

static void *PreducerFunc2(void *data)
{
    size_t i = 0;
    UNUSED data;
    for (i = 5; i < 10; ++i)
    {
        ids[i] = GenerateUID();
		sleep(2);              
    }
    return NULL;
}


void TestForThreadSafe(void)
{
	/*ilrd_uid_t bad =  GenerateBadUID();*/
	pthread_t producer = 0;
    pthread_t consumer = 0;
	int status = 0;
	size_t i = 0, j = 0;
	int fails_counter = 0;
	

    while (0 != (status = pthread_create(&producer, NULL, PreducerFunc, NULL)))
    {
    	/*empty loop*/
    }
    while (0 != (status = pthread_create(&consumer, NULL, PreducerFunc2, NULL)))
    {
    	/*empty loop*/
    }

	while (0 != (status = pthread_join(producer, NULL)))
    {
    	printf("pthread_join returned %d\n", status);
    }
    
    while (0 != (status = pthread_join(consumer, NULL)))
    {
        printf("pthread_join returned %d\n", status);
    }

	for (i = 0; i < 10; ++i)
	{
		for (j = 0; j < 10; ++j)
		{
			if (j != i)
			{
				if (IsSameUID(ids[i], ids[j]))
				{
					++fails_counter ;
					printf(RED"thread safe  GenerateUID FAILED retured same uid\n"RESET_COLOR);
				}
			}		
		}
	}
		
	
	

	if (0 == fails_counter)
	{
		printf(GREEN"thread safe PASSED GenerateUID \n"RESET_COLOR);
	}
}


int main()
{
	TestBadUid();
	TestGenerateUIDIsSame();
	TestForThreadSafe();


	return 0;
}
