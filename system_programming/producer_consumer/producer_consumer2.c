/*********************************
* Group: OL 149	 		 		 *
* Project: producer_consumer     *
* Version: 1.0.0   		 		 *
* Student: Yair singer   		 *
* Reviewer: 	 				 *
* Status:   			 		 *
*						 		 *
* Date: 	5.12.23      		 *
**********************************/
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
#include <assert.h>

#include "producer_consumer.h"
#include "sll.h"
#include "stack.h"



#define NUM_OF_RUNS 10
#define NUM_OF_PRODUCERS 20
#define NUM_OF_CONSUMERS 20
#define BUFFER_CAPACITY 50

struct fsq
{
    size_t enqueue_inx;
    size_t dequeue_inx;
    size_t capacity;
    pthread_mutex_t enqueue_mutex;
    pthread_mutex_t dequeue_mutex;
    sem_t *enqueu_semaphore;
    sem_t *dequeu_semaphore;    
    size_t buffer[1];
};

/*ex6 globals*/
sem_t *semaphore_ex6 = NULL;
pthread_mutex_t mutex_ex6 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond;
size_t version_counter;


/*ex_4 globals*/
sem_t *free_space_semaphore = NULL;
sem_t *full_space_semaphore = NULL;
pthread_mutex_t mutex_ex4 = PTHREAD_MUTEX_INITIALIZER;
stack_t *bounded_buffer = NULL;

/*ex_3 globals*/
sem_t *produced_semaphore = NULL;
pthread_mutex_t mutex_ex3 = PTHREAD_MUTEX_INITIALIZER;

/*ex_2 globals*/
pthread_mutex_t mutex_ex2 = PTHREAD_MUTEX_INITIALIZER;
sll_t *buffer_list = NULL; 


/*ex_1 global*/
volatile sig_atomic_t num_produced = 0;
volatile sig_atomic_t products_counter = 0;


static void *PreducerFunc(void *data)
{
    size_t i = 0;
    (int *)data;
    for (i = 0; i < NUM_OF_RUNS; ++i)
    {
        while(num_produced);/*busy wait untill product is consumed*/
        
        ++products_counter; 
        num_produced = 1;        
    }
    return NULL;
}

static void *ConsumerFunc(void *data)
{
    size_t i = 0;
    (int *)data;
    for (i = 0; i < NUM_OF_RUNS; ++i)
    {
        while(!num_produced);/*busy wait untill product is produced*/
        
        printf("products cointer: %d\n", products_counter); 
        num_produced = 0;        
    }

    return NULL;

}

void Ex1(void)
{
	pthread_t producer = 0;
    pthread_t consumer = 0;
	int status = 0;
	

    while (0 != (status = pthread_create(&producer, NULL, PreducerFunc, NULL)));
    while (0 != (status = pthread_create(&consumer, NULL, ConsumerFunc, NULL)));

	while (0 != (status = pthread_join(producer, NULL)))
    {
        printf("pthread_join returned %d\n", status);
    }
    while (0 != (status = pthread_join(consumer, NULL)))
    {
        printf("pthread_join returned %d\n", status);
    }
}

static void *PreducerFuncEx2(void *data)
{
    size_t p_thread_inx = *(size_t *)data;
    size_t i = 0;

    for (i = 0; i < NUM_OF_RUNS; ++i)
    {
       if (!pthread_mutex_lock(&mutex_ex2))
       {
           SllInsert(buffer_list, SllEnd(buffer_list), (const void *)data);
       }

       pthread_mutex_unlock(&mutex_ex2);      
    }
    return NULL;
}

static void *ConsumerFuncEx2(void *data)
{
    size_t p_thread_inx = *(size_t *)data;
    size_t i = 0;
    size_t value_to_consume = 0;

    for (i = 0; i < NUM_OF_RUNS; ++i)
    {

       while (!SllIsEmpty(buffer_list))
       {
        if (!pthread_mutex_lock(&mutex_ex2))
        {
            if(!SllIsEmpty(buffer_list))
            {
               value_to_consume = *((size_t *)SllGetData(SllBegin(buffer_list)));
               SllRemove(buffer_list, SllBegin(buffer_list));
            }
        }

        pthread_mutex_unlock(&mutex_ex2); 

        printf("producer %lu, consumer %lu\n", value_to_consume, p_thread_inx);
       }     
    }
    return NULL;
}




void Ex2(void)
{

    pthread_t producer_tid[NUM_OF_PRODUCERS] = {0};
    pthread_t consumer_tid[NUM_OF_CONSUMERS] = {0};
    size_t producers_inx[NUM_OF_PRODUCERS] = {0};
    size_t consumers_inx[NUM_OF_CONSUMERS] = {0};
	int status = 0;
    size_t i = 0;

    buffer_list = SllCreate();
    if (NULL == buffer_list)
    {
        printf("Faild creating buffer\n");
        return;
    }


    pthread_mutex_init(&mutex_ex2, NULL);
	
    /*creating producers*/
    for(i = 0; i < NUM_OF_PRODUCERS; ++i)
    {
        producers_inx[i] = i;
        while (0 != (status = pthread_create(&producer_tid[i], NULL, PreducerFuncEx2, &producers_inx[i])))
        {
            fprintf(stderr, "pthread_create failed, error - %s\n", strerror(errno));
        }
    }
   
   /*creating consumers*/
   for(i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        consumers_inx[i] = i;
        while (0 != (status = pthread_create(&consumer_tid[i], NULL, ConsumerFuncEx2, &consumers_inx[i])))
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

    SllDestroy(buffer_list);
}


static void *PreducerFuncEx3(void *data)
{
    size_t p_thread_inx = *(size_t *)data;
    size_t i = 0;

    for (i = 0; i < NUM_OF_RUNS; ++i)
    {
       if (!pthread_mutex_lock(&mutex_ex3))
       {
           SllInsert(buffer_list, SllEnd(buffer_list), (const void *)data);
       }

       pthread_mutex_unlock(&mutex_ex3); 

        if (0 != sem_post(produced_semaphore))
        {
            fprintf(stderr, "sem_post failed, error - %s\n", strerror(errno));
		    return NULL;
        }     
    }
    return NULL;
}

static void *ConsumerFuncEx3(void *data)
{
    size_t p_thread_inx = *(size_t *)data;
    size_t i = 0;
    size_t value_to_consume = 0;

    for (i = 0; i < NUM_OF_RUNS; ++i)
    {

        if (0 != sem_wait(produced_semaphore))
        {
            fprintf(stderr, "sem_wait failed, error - %s\n", strerror(errno));
		    return NULL;
        }

        if (!pthread_mutex_lock(&mutex_ex3))
        {
            if(!SllIsEmpty(buffer_list))
            {
               value_to_consume = *((size_t *)SllGetData(SllBegin(buffer_list)));
               SllRemove(buffer_list, SllBegin(buffer_list));
            }
        }

        pthread_mutex_unlock(&mutex_ex3); 

        printf("producer %lu, consumer %lu\n", value_to_consume, p_thread_inx);
            
    }
    return NULL;
}



void Ex3(void)
{
    pthread_t producer_tid[NUM_OF_PRODUCERS] = {0};
    pthread_t consumer_tid[NUM_OF_CONSUMERS] = {0};
    size_t producers_inx[NUM_OF_PRODUCERS] = {0};
    size_t consumers_inx[NUM_OF_CONSUMERS] = {0};
	int status = 0;
    size_t i = 0;

    buffer_list = SllCreate();
    if (NULL == buffer_list)
    {
        printf("Faild creating buffer\n");
        return;
    }

    produced_semaphore = sem_open("produced_semaphore", O_CREAT, 0666, 3);
	if (SEM_FAILED == produced_semaphore)
	{
		 fprintf(stderr, "sem_open failed, error - %s\n", strerror(errno));
		return;
	} 

    pthread_mutex_init(&mutex_ex3, NULL);
	
    /*creating producers*/
    for(i = 0; i < NUM_OF_PRODUCERS; ++i)
    {
        producers_inx[i] = i;
        while (0 != (status = pthread_create(&producer_tid[i], NULL, PreducerFuncEx3, &producers_inx[i])))
        {
            fprintf(stderr, "pthread_create failed, error - %s\n", strerror(errno));
        }
    }
   
   /*creating consumers*/
   for(i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        consumers_inx[i] = i;
        while (0 != (status = pthread_create(&consumer_tid[i], NULL, ConsumerFuncEx3, &consumers_inx[i])))
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

    SllDestroy(buffer_list);
    pthread_mutex_destroy(&mutex_ex3);
    sem_close(produced_semaphore);
    sem_unlink("produced_semaphore");
}


static void *PreducerFuncEx4(void *data)
{
    size_t p_thread_inx = *(size_t *)data;
    size_t i = 0;
    int semaphor_val = 0;
    for (i = 0; i < NUM_OF_RUNS; ++i)
    {
        /*printf("free space semaphore: %d\n", sem_getvalue(free_space_semaphore, &semaphor_val));*/

      /*  if (0 != )
        {
            fprintf(stderr, "sem_wait failed, error - %s\n", strerror(errno));
		    return NULL;
        }*/
        sem_wait(free_space_semaphore);
        pthread_mutex_lock(&mutex_ex4);       
        StackPush(bounded_buffer, (const void *)data);
        pthread_mutex_unlock(&mutex_ex4); 
        sem_post(full_space_semaphore);
            
    }
    return NULL;
}

static void *ConsumerFuncEx4(void *data)
{
    size_t p_thread_inx = *(size_t *)data;
    size_t i = 0;
    size_t value_to_consume = 0;

    for (i = 0; i < NUM_OF_RUNS; ++i)
    {

        /*if (0 != )
        {
            fprintf(stderr, "sem_wait failed, error - %s\n", strerror(errno));
		    return NULL;
        }*/
        sem_wait(full_space_semaphore);
        pthread_mutex_lock(&mutex_ex4);        
        StackPeek(bounded_buffer, &value_to_consume);
        StackPop(bounded_buffer);
        pthread_mutex_unlock(&mutex_ex4); 
        sem_post(free_space_semaphore);
        
        printf("producer %lu, consumer %lu\n", value_to_consume, p_thread_inx);

         /*if (0 != )
        {
            fprintf(stderr, "sem_post failed, error - %s\n", strerror(errno));
		    return NULL;
        }*/
            
    }
    return NULL;
}

void Ex4(void)
{
    pthread_t producer_tid[NUM_OF_PRODUCERS] = {0};
    pthread_t consumer_tid[NUM_OF_CONSUMERS] = {0};
    size_t producers_inx[NUM_OF_PRODUCERS] = {0};
    size_t consumers_inx[NUM_OF_CONSUMERS] = {0};
	int status = 0;
    size_t i = 0;
    

    bounded_buffer = StackCreate(BUFFER_CAPACITY, sizeof(size_t));
    if (NULL == bounded_buffer)
    {
        printf("Faild creating BUFFER_CAPACITY\n");
        return;
    }

    free_space_semaphore = sem_open("free_space_semaphore", O_CREAT, 0666, BUFFER_CAPACITY);
	if (SEM_FAILED == free_space_semaphore)
	{
		 fprintf(stderr, "sem_open failed, error - %s\n", strerror(errno));
		return;
	}
   
    full_space_semaphore = sem_open("full_space_semaphore", O_CREAT, 0666, 0);
	if (SEM_FAILED == full_space_semaphore)
	{
		 fprintf(stderr, "sem_open failed, error - %s\n", strerror(errno));
		return;
	} 

    pthread_mutex_init(&mutex_ex4, NULL);
	
    /*creating producers*/
    for(i = 0; i < NUM_OF_PRODUCERS; ++i)
    {
        producers_inx[i] = i;
        while (0 != (status = pthread_create(&producer_tid[i], NULL, PreducerFuncEx4, &producers_inx[i])))
        {
            fprintf(stderr, "pthread_create failed, error - %s\n", strerror(errno));
        }
    }
   
   /*creating consumers*/
   for(i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        consumers_inx[i] = i;
        while (0 != (status = pthread_create(&consumer_tid[i], NULL, ConsumerFuncEx4, &consumers_inx[i])))
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

    pthread_mutex_destroy(&mutex_ex4);
    sem_close(free_space_semaphore);
    sem_close(full_space_semaphore);
    StackDestroy(bounded_buffer);
}

void FSQEnqueue(fsq_t *fsq, size_t *data)
{
       
    assert(NULL != fsq);

    sem_wait(fsq->enqueu_semaphore);
    pthread_mutex_lock(&fsq->enqueue_mutex); 

    fsq->buffer[fsq->enqueue_inx] = fsq->enqueue_inx;
    fsq->enqueue_inx = (fsq->enqueue_inx + 1 % fsq->capacity);
    pthread_mutex_unlock(&fsq->enqueue_mutex); 

    sem_post(fsq->dequeu_semaphore);
    
}

size_t FSQDequeue(fsq_t *fsq)
{
    size_t consumer_inx = 0;
    size_t read_data = 0;     
    assert(NULL != fsq);

    sem_wait(fsq->dequeu_semaphore);
    pthread_mutex_lock(&fsq->dequeue_mutex); 

    read_data =  fsq->buffer[fsq->dequeue_inx];
    consumer_inx = fsq->dequeue_inx;
    fsq->buffer[fsq->dequeue_inx] = 0;
    fsq->dequeue_inx = (fsq->dequeue_inx + 1 % fsq->capacity);

    pthread_mutex_unlock(&fsq->dequeue_mutex); 
    sem_post(fsq->enqueu_semaphore);

    printf("porducer [%d] \t\t consumer [%lu]\n", read_data, consumer_inx); /*remove after tests*/

    return read_data;
}

fsq_t *FSQCreate(size_t capacity)
{
    fsq_t *fsq = NULL;

    assert (capacity != 0);

    fsq = (fsq_t *)malloc(offsetof(fsq_t,buffer) + capacity * sizeof(size_t));
    if (NULL == fsq)
    {
        return NULL;
    }

    /*fsq->dequeue_mutex = PTHREAD_MUTEX_INITIALIZER;*/
    pthread_mutex_init(&(fsq->dequeue_mutex), NULL);

    /*fsq->enqueue_mutex = PTHREAD_MUTEX_INITIALIZER;*/
    pthread_mutex_init(&(fsq->enqueue_mutex), NULL);

    fsq->dequeue_inx = 0;
    fsq->enqueue_inx = 0;

    fsq->enqueu_semaphore = sem_open("enqueu_semaphore", O_CREAT, 0666, capacity); /*to lock all enqueue threads untill create return*/
    if (SEM_FAILED == fsq->enqueu_semaphore)
	{
		fprintf(stderr, "sem_open failed, error - %s\n", strerror(errno));
        sem_close(fsq->dequeu_semaphore);
        free(fsq);
		return;
	} 
    fsq->dequeu_semaphore = sem_open("dequeu_semaphore", O_CREAT, 0666, 0);
    if (SEM_FAILED == fsq->dequeu_semaphore)
	{
		fprintf(stderr, "sem_open failed, error - %s\n", strerror(errno));
        free(fsq);
		return NULL;
	}


    return fsq;
}

void FSQDestroy(fsq_t *fsq)
{
    assert(NULL != fsq);

    pthread_mutex_destroy(&fsq->enqueue_mutex);
    pthread_mutex_destroy(&fsq->dequeue_mutex);
    sem_close(fsq->dequeu_semaphore);
    sem_close(fsq->enqueu_semaphore);
    sem_unlink("dequeu_semaphore");
    sem_unlink("enqueu_semaphore");

    memset(fsq, 0, sizeof(fsq_t));
    free(fsq);    
}

static void *PreducerFuncEx6(void *data)
{
    size_t p_thread_inx = *(size_t *)data;
    size_t i = 0, j = 0;
    size_t version_num = 0;
    int semaphor_val = 0;
    for (i = 0; i < NUM_OF_RUNS; ++i)
    {
        ++version_num; /*produce*/
        pthread_mutex_lock(&mutex_ex6);
        version_counter = version_num;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex_ex6); 
        for (j = 0; j < NUM_OF_CONSUMERS; ++j)
        {
            sem_wait(semaphore_ex6);
        }
             
    }
    return NULL;
}

static void *ConsumerFuncEx6(void *data)
{
    size_t p_thread_inx = *(size_t *)data;
    size_t i = 0, j = 0;
    size_t cur_version = 0;
    

    int semaphor_val = 0;
    for (i = 0; i < NUM_OF_RUNS; ++i)
    {
        pthread_mutex_lock(&mutex_ex6);
        while(version_counter <= cur_version)
        {
            pthread_cond_wait(&cond, &mutex_ex6);
        }
        cur_version = version_counter; /*updating version*/
        printf("recieved version %lu\n",cur_version);         
        pthread_mutex_unlock(&mutex_ex6); 
        sem_post(semaphore_ex6); 
    }
    return NULL;


}

void Ex6(void)
{
    pthread_t producer_tid = 0;
    pthread_t consumer_tid[NUM_OF_CONSUMERS] = {0};
    size_t producers_inx = 0;
    size_t consumers_inx[NUM_OF_CONSUMERS] = {0};
    size_t i = 0;
	int status = 0;
    static int version_num = 0;
    pthread_cond_init(&cond, NULL);
    
  
    semaphore_ex6 = sem_open("semaphore_ex6", O_CREAT, 0666, 0);
	if (SEM_FAILED == semaphore_ex6)
	{
		 fprintf(stderr, "sem_open failed, error - %s\n", strerror(errno));
		return;
	} 

    pthread_mutex_init(&mutex_ex6, NULL);
	
    /*creating producer*/     
    while (0 != (status = pthread_create(&producer_tid, NULL, PreducerFuncEx6, &producers_inx)))
    {
        fprintf(stderr, "pthread_create failed, error - %s\n", strerror(errno));
    }
   
   /*creating consumers*/
   for(i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        consumers_inx[i] = i;
        while (0 != (status = pthread_create(&consumer_tid[i], NULL, ConsumerFuncEx6, &consumers_inx[i])))
        {
            fprintf(stderr, "pthread_create failed, error - %s\n", strerror(errno));
        }
    }

    /*joinning producer*/
    while (0 != (status = pthread_join(producer_tid, NULL)))
    {
        printf("pthread_join returned %d\n", status);
    }
    
    /*joinning consumers*/	
    for(i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        while (0 != (status = pthread_join(consumer_tid[i], NULL)))
        {
            printf("pthread_join returned %d\n", status);
        }
    }

    pthread_mutex_destroy(&mutex_ex6);
    sem_close(semaphore_ex6);
    sem_unlink("semaphore_ex6");
    pthread_cond_destroy(&cond);
}

