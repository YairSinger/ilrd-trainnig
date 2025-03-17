#include <assert.h>
#include <stdlib.h> /*frre malloc*/
#include "task.h"

struct task
{
	ilrd_uid_t uid;
	op_func op_func1;
	const void *params;
	size_t time_to_execute;
	size_t freqency;
};



task_t *TaskCreate(int(*op_func)(void *),const void *params,const size_t time_to_execute,const size_t frequency)
{
	task_t *task = (task_t *) malloc(sizeof(task_t));

	assert(NULL != op_func);
	if (NULL == task)
	{
		return NULL;
	}
	
	task->uid = GenerateUID();
	if (1 == IsSameUID(task->uid, GenerateBadUID()))
	{
		TaskDestroy(task);
		return NULL;	
	}
	
	task->op_func1 = op_func;
	task->params = params;
	task->time_to_execute = time_to_execute;
	task->freqency = frequency;
	
	return task;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	task->op_func1 = NULL;
	task->params = NULL;
	task->time_to_execute = 0;
	task->freqency = 0;
	
	free(task);
	task = NULL;

}


int TaskRun(task_t *task)
{
    
	int status = 0;
	
	assert(NULL != task);
	
	status = task->op_func1((void *)task->params);
	return status;

}
	
ilrd_uid_t TaskGetUid(const task_t *task)
{
    
	assert(NULL != task);
	
	return task->uid;
}

void TaskUpdateRepeatingTask(task_t *task)
{
	assert(NULL != task);
	
	task->time_to_execute += task->freqency ;
}
	
int TaskIsUidSame(const task_t *task, const ilrd_uid_t *uid)
{
	assert(NULL!= task);
	
	return IsSameUID(TaskGetUid(task),*uid);
}	

size_t TaskGetTimeToExceute(task_t *task)
{
    
	assert(NULL != task);
	return (task->time_to_execute);
}

int TaskPriorityTimeToExe(const task_t *lsv, const task_t *rsv)
{
	assert(NULL != lsv);
	assert (NULL != rsv);	
	
	return ((lsv->time_to_execute) - (rsv->time_to_execute));
}

