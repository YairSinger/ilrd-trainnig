#define _POSIX_C_SOURCE 199309L /*pid_t*/
#include <stdlib.h> /*malloc, strtod*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h> /* strstr, strcmp */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include "producer_consumer.h"
#include "sll.h"
#include "stack.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

#define NUM_OF_ENQUEUE 15
#define NUM_OF_DEQUEUE 15
#define NUM_OF_PRODUCERS 5
#define NUM_OF_CONSUMERS 5

typedef struct fsq_input
{
    fsq_t *fsq;
    size_t data;
} fsq_input_t;

void TestFSQ();


int main(int argc, char **argv)
{
	/*printf("**************Ex1******************************\n ");

	Ex1();
	printf("**************Ex2******************************\n ");
	Ex2();
	printf("**************Ex3******************************\n ");
	Ex3();
	printf("**************Ex4******************************\n ");
	Ex4();*/
	printf("**************Ex5******************************\n ");
	TestFSQ();
	/*printf("**************Ex6******************************\n ");
	Ex6();*/
	
	return 0;
}



void *FSQProducer(void *input)
{
	fsq_t *fsq = ((fsq_input_t *)input)->fsq;
	size_t data = ((fsq_input_t *)input)->data;
	size_t i = 0;

	for (i = 0; i < NUM_OF_ENQUEUE ; ++i)
	{
		FSQEnqueue(fsq, &i);
	}
	return NULL;
}

void *FSQConsumer(void *input)
{
	fsq_t *fsq = ((fsq_input_t *)input)->fsq;
	size_t data = ((fsq_input_t *)input)->data;
	int status = 0;
	size_t i = 0;

	for (i = 0;!status && i < NUM_OF_DEQUEUE ; ++i)
	{
		status = FSQDequeue(fsq);
	}

		return NULL;
}


void TestFSQ()
{
	fsq_input_t input = {0};
	pthread_t producer_tid[NUM_OF_PRODUCERS] = {0};
    pthread_t consumer_tid[NUM_OF_CONSUMERS] = {0};
    size_t producers_inx[NUM_OF_PRODUCERS] = {0};
    size_t consumers_inx[NUM_OF_CONSUMERS] = {0};
	int status = 0;
    size_t i = 0;


	input.fsq = FSQCreate(20);
	/*creating producers*/
    for(i = 0; i < NUM_OF_PRODUCERS; ++i)
    {
        producers_inx[i] = i;
        while (0 != (status = pthread_create(&producer_tid[i], NULL, FSQProducer, &input)))
        {
            fprintf(stderr, "pthread_create failed, error - %s\n", strerror(errno));
        }
    }

	/*creating consumers*/
   for(i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        consumers_inx[i] = i;
        while (0 != (status = pthread_create(&consumer_tid[i], NULL, FSQConsumer, &input)))
        {
            fprintf(stderr, "pthread_create failed, error - %s\n", strerror(errno));
        }
    }

	/*joinning producers*/
    for(i = 0; i < NUM_OF_PRODUCERS; ++i)
    {
        while (0 != (status = pthread_join(producer_tid[i], NULL)))
        {
            printf("pthread_join returned %d\n", status);
        }
    }
    /*joinning consumers*/	
    for(i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        while (0 != (status = pthread_join(consumer_tid[i], NULL)))
        {
            printf("pthread_join returned %d\n", status);
        }
    }

	FSQDestroy(input.fsq);
}




