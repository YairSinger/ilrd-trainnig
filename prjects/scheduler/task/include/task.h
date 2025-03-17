#include "uid.h"

#ifndef __TASK_H__
#define __TASK_H__



typedef struct task task_t;
typedef int (*op_func)(void *);




/*
@Description: Creates new task dynamiclly and returns a task_t pointer.
@Parameters: 
            1. [op_func]   			- Function to execute should return 0 on sucsses, 1 if repeat.   
            2. [params]     		- Pointer to func_ptr's argument.
            3. [time_to_execute]    - When to execute Task in seconds .
            4. [frequency]          - Time to next execution when task is repeating.
@Return Value: task_t *ptr to new task null.            
@Time Complexity: O(1).
@Notes: 
*/
task_t *TaskCreate(int(*op_func)(void *),const void *params,const size_t time_to_execute,const size_t frequency);


/*
@Description: Destroyes one task.
@Parameters: 
            1. [task]   - Task pointer to destroy.  
@Return Value: non.            
@Time Complexity: O(1).
@Notes: [task] should be valid.
*/
void TaskDestroy(task_t *task);


/*
@Description: Runs one task when time_to_execute passed.
@Parameters: 
            1. [task]   - Task pointer to destroy.  
@Return Value: int as in function to execute (op_func) set in task.          
@Time Complexity: O(n).
@Notes: [task] should be valid.
*/
int TaskRun(task_t *task);

/*
@Description: Gets UID in the task
@Parameters: 
            1. [task]   - Task pointer.  
@Return Value: uid of the task.          
@Time Complexity: O(1).
@Notes: [task] should be valid.
*/
ilrd_uid_t TaskGetUid(const task_t *task);

/*
@Description: Changing [time_to_execute] to now() + execute_interval
@Parameters: 
            1. [task]   - Task pointer to destroy.  
@Return Value: non.          
@Time Complexity: O(n).
@Notes: [task] should be valid.
*/
void TaskUpdateRepeatingTask(task_t *task);


int TaskIsUidSame(const task_t *task, const ilrd_uid_t *uid);
 
size_t TaskGetTimeToExceute(task_t *task); 

int TaskPriorityTimeToExe(const task_t *lsv, const task_t *rsv);

#endif /*__TASK_H__*/
