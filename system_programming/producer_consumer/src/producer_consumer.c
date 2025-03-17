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


#define NUM_OF_RUNS 15




volatile sig_atomic_t is_produced = 0;
volatile sig_atomic_t products_counter = 0;


static void *PreducerFunc(void *data)
{
    size_t i = 0;
    (int *)data;
    for (i = 0; i < NUM_OF_RUNS; ++i)
    {
        while(is_produced);/*busy wait untill product is consumed*/*/
        
        ++products_counter; 
        is_produced = 1;        
    }
}

static void *ConsumerFunc(void *data)
{
    size_t i = 0;
    (int *)data;
    for (i = 0; i < NUM_OF_RUNS; ++i)
    {
        while(!is_produced);/*busy wait untill product is produced*/*/
        
        printf("products cointer: %d\n", products_counter); 
        is_produced = 0;        
    }
}

void Ex1(void)
{
	pthread_t producer = 0;
    pthread_t consumer = 0;
	int status = 0;
	

    while (0 != (status = pthread_create(&producer, NULL, PreducerFunc, NULL)));
    while (0 != (status = pthread_create(&consumer, NULL, ConsumerFunc, NULL)));

	while (0 != status = pthread_join(producer, NULL))
    {
        printf("pthread_join returned %d\n", status);
    }
    while (0 != status = pthread_join(consumer, NULL))
    {
        printf("pthread_join returned %d\n", status);
    }

}




