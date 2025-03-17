
/* ----------------------------------------------------------
 * Filename:    scheduler.c
 * Author:      Shahar Molina
 * Reviewer:	Yael Hava
 * Date:        28.09.2023
 * Course:      OL-149
 * Description: Implementation of
 * ----------------------------------------------------------
 */

/* -------------------Includes-------------------- */
#include <stddef.h> /* size_t */
#include <stdio.h> /* size_t */
#include <time.h> /* time_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* sleep */
#include <string.h> /* strstr */

#include "heap_pq.h" /* API for pqueue */
#include "uid.h" /* API for uid */
#include "task.h" /* API for task */
#include "scheduler.h" /* API for scheduler */

#define COMMAND_SIZE 32
/* -------------------Struct-------------------- */
struct scheduler
{
	pqueue_t *pq;
	task_t *curr_task;
	int is_running;
};

/* -------------------Function Decleration-------------------- */
static int CmpByTimeToRun(const void *target, const void *source);
static int IsUIDMatch(const void *uid1, void *uid2);
static int StopIfRequested(scheduler_t *sched);

/* -------------------Functions Definition-------------------- */
scheduler_t *SchedCreate(void)
{
	scheduler_t *sched = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == sched)
	{
		return NULL;
	}

	sched->pq = PQCreate(CmpByTimeToRun);
	if (NULL == sched->pq)
	{
		free(sched);
		sched = NULL;

		return NULL;
	}

	sched->curr_task = NULL;
	sched->is_running = 0;

	return sched;
}

void SchedDestroy(scheduler_t *sched)
{
	assert(NULL != sched);

	SchedClear(sched);

	if (sched->curr_task)
	{
		TaskDestroy(sched->curr_task);
	}

	PQDestroy(sched->pq);
	sched->pq = NULL;

	free(sched);
	sched = NULL;
}

ilrd_uid_t SchedAdd(scheduler_t *sched, size_t interval, time_t time_to_run,
                    int (*action_func)(void *act_params), void *act_params,
                    void (*cleanup_func)(void *cleanup_params),
                    void *cleanup_params)
{
	task_t *task = NULL;
	ilrd_uid_t uid = bad_uid;

	assert(NULL != sched);
	assert(NULL != action_func);

	uid = UIDGet();
	if (1 == UIDIsSame(uid, bad_uid))
	{
		return bad_uid;
	}

	task = TaskCreate(interval, time_to_run, action_func, act_params,
	                          cleanup_func, cleanup_params, uid);
	if (NULL == task)
	{
		return bad_uid;
	}


	if (0 != PQEnqueue(sched->pq, task))
	{
		TaskDestroy(task);

		return bad_uid;
	}

	return task->uid;
}

int SchedRun(scheduler_t *sched)
{
	int action_status = 0;
	int enqueue_status = 0;
	time_t started_to_run = 0;

	assert(NULL != sched);

	sched->is_running = 1;
	started_to_run = time(NULL);

	while (!PQIsEmpty(sched->pq) && sched->is_running)
	{
		task_t *task = NULL;

		task = (task_t *)PQDequeue(sched->pq);
		sched->curr_task = task;

		while (task->time_to_run > (time(NULL) - started_to_run))
		{
			sleep(task->time_to_run - (time(NULL) - started_to_run));
		}

		action_status = TaskRun(task);
		if (0 != action_status)
		{
			TaskDestroy(task);
			sched->curr_task = NULL;

			return action_status;
		}

		if (task->interval > 0)
		{
			TaskUpdateTime(task, started_to_run);
			enqueue_status = PQEnqueue(sched->pq, task);
			if (0 != enqueue_status)
			{
				TaskDestroy(task);
				sched->curr_task = NULL;

				return enqueue_status;
			}

			task = NULL;
			sched->curr_task = NULL;
		}

		if (NULL != task)
		{
			TaskDestroy(task);
			sched->curr_task = NULL;
		}

		if (0 != StopIfRequested(sched))
		{
			return -1;
		}
	}
	return 0;
}

void SchedRemove(scheduler_t *sched, ilrd_uid_t task_id)
{
	ilrd_uid_t *uid_ptr = NULL;
	task_t * task = NULL;

	assert(NULL != sched);

	uid_ptr = &task_id;

	if (sched->curr_task && UIDIsSame(sched->curr_task->uid, task_id))
	{
		sched->curr_task->interval = 0;
	}

	task = (task_t *)PQErase(sched->pq, IsUIDMatch, (void *)uid_ptr);
	if (task)
	{
		TaskDestroy(task);
	}
}

size_t SchedCount(scheduler_t *sched)
{
	return PQSize(sched->pq) + (NULL != sched->curr_task);
}

int SchedIsEmpty(scheduler_t *sched)
{
	assert(NULL != sched);

	return (PQIsEmpty(sched->pq) && (NULL == sched->curr_task));
}

void SchedStop(scheduler_t *sched)
{
	assert(NULL != sched);

	sched->is_running = 0;
}

void SchedClear(scheduler_t *sched)
{
	assert(NULL != sched);

	while (!PQIsEmpty(sched->pq))
	{
		task_t *task = (task_t *)PQDequeue(sched->pq);
		TaskDestroy(task);
	}
}

/* -------------------Service Functions-------------------- */
static int CmpByTimeToRun(const void *target, const void *source)
{
	assert(NULL != target);
	assert(NULL != source);

	return ((task_t *)target)->time_to_run - ((task_t *)source)->time_to_run;
}

static int IsUIDMatch(const void *task, void *uid_to_find)
{
	assert(NULL != task);
	assert(NULL != uid_to_find);

	return UIDIsSame(((task_t *)task)->uid, *(const ilrd_uid_t *)uid_to_find);
}

static int StopIfRequested(scheduler_t *sched)
{
	char command[COMMAND_SIZE] = {0};
	FILE *file = fopen("filecontroller.txt", "rb");
	if (NULL == file)
	{
		fprintf(stderr, "File open error\n");
		return -1;
	}

	if (0 == fread(command, 1, sizeof(command) - 1, file))
	{
		fprintf(stderr, "Error reading from file\n");
		fclose(file);
		return -1;
	}

	if (-1 == fclose(file))
	{
		fprintf(stderr, "Error closing file\n");
		return -1;
	}

	if (command == strstr(command, "stop"))
	{
		SchedStop(sched);
	}
	return 0;
}
