
/* ----------------------------------------------------------
 * Filename:    task.h
 * Author:      Shahar Molina
 * Reviewer:	Yael Hava
 * Date:        28.09.2023
 * Course:      OL-149
 * Description: Library API for task
 * ----------------------------------------------------------
 */

#ifndef __ILRD_OL149_TASK_H__
#define __ILRD_OL149_TASK_H__

/* -------------------Includes-------------------- */
#include <stddef.h> /* size_t */
#include <time.h> /* time_t */

#include "uid.h" /* API for uid */

/* -------------------Struct Definition-------------------- */
typedef struct task
{
    size_t interval;
    time_t time_to_run;
    int (*action_func)(void *param);
    void *act_params;
    void (*cleanup_func)(void *param_cleanup);
    void *cleanup_params;
    ilrd_uid_t uid;
} task_t;

/* -------------------Functions Decleration-------------------- */
/**
 * @description Creates a new task with specified properties.
 * @param interval The task's execution interval in seconds.
 * @param time_to_run The initial reletive  time at which the task should run.
 * @param action_func A pointer to the task's action function.
 * @param act_params Parameters to pass to the action function.
 * @param cleanup_func A pointer to the task's cleanup function (optional).
 * @param cleanup_params Parameters to pass to the cleanup function (optional).
 * @param uid A UID for the task.
 * @return A handle to the created task.
 * @complexity Time: O(1), Space: O(1)
 */
task_t *TaskCreate(size_t interval, time_t time_to_run,
					int (*action_func)(void *act_params), void *act_params,
					void (*cleanup_func)(void *cleanup_params),
					void *cleanup_params, ilrd_uid_t uid);
/**
 * @description Destroys a given task.
 * @param task The task to destroy.
 * @complexity Time: O(1), Space: O(1)
 */
void TaskDestroy(task_t *task);

/**
 * @description Runs the task's action function.
 * @param task The task to execute.
 * @return 0 on success, non zero on failure.
 * @complexity Time: O(1), Space: O(1)
 */
int TaskRun(task_t *task);

/**
 * @description Updates the task's internal time tracking based on the
 *				 current time.
 * @param task The task to update.
 * @param curr_time The current time value.
 * @complexity Time: O(1), Space: O(1)
 */
void TaskUpdateTime(task_t *task, time_t started_to_run);

#endif /* __ILRD_OL149_TASK_H__ */


