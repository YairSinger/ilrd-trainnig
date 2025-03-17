#include <stdlib.h> /*free, malloc*/
#include <assert.h>
#include <stddef.h> /* NULL */
#include <time.h>   /*time_t , time()*/
#include<unistd.h> /* sleep */
#include "task.h"
#include "pqueue.h"
#include "heap_scheduler.h"






struct heap_scheduler
{
	pqueue_t *queue;
	int running_status;
};


static int PriorityTimeToExe(const void *list_task, const void *new_task)
{
	task_t *left = (task_t *)list_task;
	task_t *right = (task_t *)new_task;
	
	return TaskGetTimeToExceute(left) < TaskGetTimeToExceute(right);	
}

static int CompUidFromTask(const void *task, const void *uid)
{
	 return TaskIsUidSame((const task_t *)task, (const ilrd_uid_t *)uid);
}

heap_scheduler_t *HeapSchedulerCreate()
{
	heap_scheduler_t *scheduler = (heap_scheduler_t *) malloc (sizeof(heap_scheduler_t));
	 
	if (NULL == scheduler)
	{
		return NULL;
	}
	
	
	scheduler->queue = PQCreate(PriorityTimeToExe);
	if(NULL == scheduler->queue)
	{
		free(scheduler);
		return NULL;	
	}
	
	scheduler->running_status = 0;
	
	return scheduler;
}

void HeapSchedulerDestroy(heap_scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	HeapSchedulerClear(scheduler);
	PQDestroy(scheduler->queue);
	scheduler->queue = NULL;
	scheduler->running_status = 0;
	
	free(scheduler);
	scheduler = NULL;
}


ilrd_uid_t HeapSchedulerAddTask(heap_scheduler_t *scheduler, 
							 int(*op_func)(void *), 
							 const void *params, 
							 const size_t time_to_execute, 
							 const size_t frequency)

{
  	ilrd_uid_t bad_uid = GenerateBadUID();
	task_t *new_task = TaskCreate(op_func, params, time_to_execute,frequency);
	
	if (NULL == new_task) /*malloc of TaskCreate failed*/
	{
		return bad_uid;
	}
	                           
	if (TaskIsUidSame(new_task, &bad_uid)) /*new task with bad uid*/
	{
		TaskDestroy(new_task);
		return bad_uid;
	}
	
	if (1 == PQEnqueue(scheduler->queue, (const void *) new_task)) /*failed to enqueue*/
	{
		TaskDestroy(new_task);
		return bad_uid;	
	}
	
	return TaskGetUid(new_task);
}



void HeapSchedulerRemoveTask(heap_scheduler_t *scheduler, ilrd_uid_t task_uid)
{
    ilrd_uid_t uid_to_remove = task_uid;
	task_t *task_to_remove = NULL;
	
	assert(NULL != scheduler);
			
	task_to_remove = (task_t *) PQErase(scheduler->queue, CompUidFromTask, (void *) &uid_to_remove);
	if (NULL != task_to_remove)
	{
		TaskDestroy(task_to_remove);	
	}
}




size_t HeapSchedulerSize(const heap_scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	return PQSize(scheduler->queue);

}

int HeapSchedulerIsEmpty(const heap_scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	return PQIsEmpty(scheduler->queue);	
}

void HeapSchedulerClear(heap_scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	while (!HeapSchedulerIsEmpty(scheduler))
	{
		 TaskDestroy((task_t *) PQPeek(scheduler->queue));
		 PQDequeue(scheduler->queue);
	}
}


int HeapSchedulerRun(heap_scheduler_t *scheduler)
{
    
	int status = 0; 				/* op_func result */
	int enqueue_status = 1;
		
	time_t run_start_time = time(NULL);
	time_t sleep_time = 0;
	
	
	task_t *current_task_ptr = NULL;
	
	assert(NULL != scheduler);
		
	scheduler->running_status = 1;
	
	while ((!HeapSchedulerIsEmpty(scheduler)) && (0 == status || 1 == status ) && scheduler->running_status == 1)
	{
		/*prepare to run task */
		current_task_ptr = (task_t *) PQPeek(scheduler->queue);
		PQDequeue(scheduler->queue);
		
		sleep_time = (time_t)TaskGetTimeToExceute(current_task_ptr) - (time(NULL) - run_start_time) ;
		if (0 < sleep_time) 
		{	
			sleep(sleep_time);
		}
		
		/***************************/
		status = TaskRun(current_task_ptr);
		if (1 != status)
		{
			TaskDestroy(current_task_ptr);
		}
		
		if (1 != status && 0 != status) 		/*exit loop when op_func fails */
		{
			HeapSchedulerStop(scheduler);
		}
		else if (1 == status) 				/*current task is repeating task  */
		{
			TaskUpdateRepeatingTask(current_task_ptr);		
			enqueue_status = PQEnqueue(scheduler->queue, (const void *) current_task_ptr);
			
			if (0 != enqueue_status)
			{
				TaskDestroy(current_task_ptr);	
				return 1;			
			}
		}
	}
	return status;
}

void HeapSchedulerStop(heap_scheduler_t *scheduler)
{
	scheduler->running_status = 0;
}
