#ifndef __HEAP_SCHEDULER_H__
#define __HEAP_SCHEDULER_H__

#include "ilrd_uid.h"

typedef struct heap_scheduler heap_scheduler_t;


/*****************************************************************************/
/*
@Name: HeapSchedulerCreate
@Description: 
    Initializes and returns a new Heap Scheduler.
@Parameters: 
    None
@Return: 
    - Returns a pointer to the newly created Heap Scheduler or NULL if allocation fails.
@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
*/
heap_scheduler_t *HeapSchedulerCreate(void);


/*****************************************************************************/
/*
@Name: HeapSchedulerDestroy
@Description: 
    Frees all the memory allocated for the Heap Scheduler and its tasks. All scheduled tasks will be lost.
@Parameters: 
    - *scheduler: A valid pointer to the scheduler.
@Return: 
    None
@Time Complexity: 
    O(n) where n is the number of tasks in the scheduler.

@Space Complexity: 
    O(1).
*/
void HeapSchedulerDestroy(heap_scheduler_t *scheduler);


/*****************************************************************************/
/*
@Name: HeapSchedulerAddTask
@Description: 
    Schedules a new task for execution after a certain delay (`time_to_execute`) and, if `frequency` is provided, at regular intervals thereafter.
@Parameters: 
    - *scheduler: A valid pointer to the heap scheduler.
    - *op_func: Operation function pointer that the task should execute.
    - *params: Pointer to parameters that should be passed to the `op_func`.
    - time_to_execute: Delay (in seconds) after which the task should be first executed.
    - frequency: Time interval (in seconds) between consecutive task executions. If set to 0, the task is executed only once.
@Return: 
    - Unique ID of the scheduled task.
@Time Complexity: 
    O(log n) where n is the number of tasks in the scheduler.

@Space Complexity: 
    O(1).
*/
ilrd_uid_t HeapSchedulerAddTask(heap_scheduler_t *scheduler, int (*op_func)(void *), 
					   		const void *params, const size_t time_to_execute, 
					 		const size_t frequency);


/*****************************************************************************/
/*
@Name: HeapSchedulerRemoveTask
@Description: 
    Removes a scheduled task from the Heap Scheduler.
@Parameters: 
    - *scheduler: A valid pointer to the scheduler.
    - uid: Unique ID of the task to be removed.
@Return: 
    - void.
@Time Complexity: 
    O(n) where n is the number of tasks in the scheduler.

@Space Complexity: 
    O(1).
*/
void HeapSchedulerRemoveTask(heap_scheduler_t *scheduler, ilrd_uid_t uid);


/*****************************************************************************/
/*
@Name: HeapSchedulerRun
@Description: 
    Executes tasks in the Heap Scheduler.
@Parameters: 
    - *scheduler: A valid pointer to the scheduler.
@Return: 
    - 0 on success, non-zero on failure.
@Time Complexity: 
    O(n log n) where n is the number of tasks in the scheduler.

@Space Complexity: 
    O(1).
*/
int HeapSchedulerRun(heap_scheduler_t *scheduler);


/*****************************************************************************/
/*
@Name: HeapSchedulerStop
@Description: 
    Stops the execution of tasks in the Heap Scheduler.
@Parameters: 
    - *scheduler: A valid pointer to the scheduler.
@Return: 
    None
@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
*/
void HeapSchedulerStop(heap_scheduler_t *scheduler);


/*****************************************************************************/
/*
@Name: HeapSchedulerGetSize
@Description: 
    Retrieves the number of scheduled tasks in the Heap Scheduler.
@Parameters: 
    - *scheduler: A valid pointer to the scheduler.
@Return: 
    - Number of scheduled tasks.
@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
*/
size_t HeapSchedulerSize(const heap_scheduler_t *scheduler);


/*****************************************************************************/
/*
@Name: HeapSchedulerIsEmpty
@Description: 
    Checks if there are any scheduled tasks in the Heap Scheduler.
@Parameters: 
    - *scheduler: A valid pointer to the scheduler.
@Return: 
    - 1 if empty, 0 otherwise.
@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
*/
int HeapSchedulerIsEmpty(const heap_scheduler_t *scheduler);


/*****************************************************************************/
/*
@Name: HeapSchedulerClear
@Description: 
    Clears all tasks from the scheduler.
@Parameters: 
    - *scheduler: A valid pointer to the scheduler.
@Return: 
    void.
@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
*/
void HeapSchedulerClear(heap_scheduler_t *scheduler);


#endif /* __HEAP_SCHEDULER_H__ */


