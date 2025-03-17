
/* ----------------------------------------------------------
 * Filename:    task.c
 * Author:      Shahar Molina
 * Reviewer:    Yael Hava
 * Date:        28.09.2023
 * Course:      OL-149
 * Description: Implementation of task library
 * ----------------------------------------------------------
 */

/* -------------------Includes-------------------- */
#include <stddef.h> /* size_t */
#include <time.h> /* time_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "uid.h" /* API for uid */
#include "task.h" /* API for task */

/* -------------------Functions Definitions-------------------- */
task_t *TaskCreate(size_t interval, time_t time_to_run,
					int (*action_func)(void *act_params), void *act_params,
					void (*cleanup_func)(void *cleanup_params),
					void *cleanup_params, ilrd_uid_t uid)
{
	task_t *task = NULL;

	assert(NULL != action_func);

	task = (task_t *)malloc(sizeof(task_t));
	if (NULL == task)
	{
		return NULL;
	}

	task->interval = interval;
	task->time_to_run = time_to_run;
	task->action_func = action_func;
	task->act_params = act_params;
	task->cleanup_func = cleanup_func;
	task->cleanup_params = cleanup_params;
	task->uid = uid;

	return task;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);

	free(task);
	task = NULL;
}

int TaskRun(task_t *task)
{
	int status = 0;

	assert(NULL != task);

	status = task->action_func(task->act_params);
	if(0 == status && NULL != task->cleanup_func)
	{
		task->cleanup_func(task->cleanup_params);
	}

	return status;
}

void TaskUpdateTime(task_t *task, time_t started_to_run)
{
	assert(NULL != task);

	task->time_to_run = time(NULL) - started_to_run + task->interval;
}

