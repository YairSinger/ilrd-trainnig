
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h> /* size_t */
#include "uid.h"



typedef struct scheduler scheduler_t;

/*
@Description: Creates scheduler.
@Return value: Pointer to the scheduler, NULL on failure.
@Time Complexity: O(1).
@Notes: None.
*/
scheduler_t *SchedulerCreate();

/*
@Description: Destroys scheduler.
@Parameters:  
            1. [scheduler] - pointer to scheduler.
@Return value: None.
@Time Complexity: O(n).
@Notes: [scheduler] must be valid.
*/
void SchedulerDestroy(scheduler_t *scheduler);

/*
@Description: Schedual a new task based user priority function.
@Parameters:  
            1. [scheduler]  - Pointer to the scheduler.
            2. [op_func]   - Function to execute should return 0 on sucsses, 1 if repeat.   
            3. [params]     - Pointer to func_ptr's argument.
            4. [time_to_execute]   - When to execute Task in seconds.
@Return value: New valid uid of the new task, or Bad uid on failure.
@Time Complexity: O(n).
@Notes: [scheduler] should be a valid.
*/
ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, int(*op_func)(void *) ,const void *params, size_t time_to_execute,const size_t frequency);
 
/*
@Description: Removes Task from scheduler.
@Parameters:  
            1. [scheduler]  - Pointer to the scheduler.
			2. [task_uid]   - uid of the task to be removed.
@Time Complexity: O(n).
@Notes: [scheduler] should be a valid, [task_uid] should be a valid uid.
*/
void SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t task_uid);

/*
@Description: Runs scheduler's loop, stops if a user's function failed or all tasks have been executed or SchedStop was called.
@Parameters:  
            1. [scheduler] - pointer to scheduler.
@Return value: 0 if there is no more tasks left to be executes or last return value of failed function.
@Time Complexity: O(n).
@Notes: [scheduler] should be valid.
*/
int SchedulerRun(scheduler_t *scheduler);

/*
@Description: Stops the scheduler's loop.
@Parameters:  
			 1. [scheduler] - Pointer to the scheduler.
@Return value: None.
@Time Complexity: O(1).
@Notes: [scheduler] should be valid.
*/
void SchedulerStop(scheduler_t *scheduler);

/*
@Description: Returns number of tasks that currently in scheduler's queue.
@Parameters: 
            1. [scheduler] - Pointer to the scheduler. 
@Return Value: [scheduler] size.            
@Time Complexity: O(n).
@Notes: [scheduler] should be valid.
*/
size_t SchedulerSize(const scheduler_t *scheduler);

/*
@Description: Returns whether [scheduler]'s queue is empty.
@Parameters:  
			 1. [scheduler] - Pointer to the scheduler.
@Return value: returns 1 if scheduler's queue is empty or 0 otherwise.
@Time Complexity: O(1).
@Notes: [scheduler] should be valid.
*/
int SchedulerIsEmpty(const scheduler_t *scheduler);

/*
@Description: Clears scheduler's elements.
@Parameters:  
			 1. [scheduler] - Pointer to the scheduler.
@Return value: None.
@Time Complexity: O(n).
@Notes: [scheduler] should be valid.
*/
void SchedulerClear(scheduler_t *scheduler);

#endif /* __SCHEDULER_H__ */

