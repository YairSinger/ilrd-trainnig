
/* ----------------------------------------------------------
 * Filename:    scheduler.c
 * Author:      Shahar Molina
 * Reviewer:	Yael Hava
 * Date:        28.09.2023
 * Course:      OL-149
 * Description: Implementation of scheduler
 * ----------------------------------------------------------
 */

#ifndef __ILRD_OL149_SCHEDULER_H__
#define __ILRD_OL149_SCHEDULER_H__

#include "uid.h" /* UID API */

/*
    This API represents A scheduler which provides a framework for managing
    and executing tasks at specified intervals and times by the order of their
    time. It allows you to create, remove, manage, and execute tasks.

*/

typedef struct scheduler scheduler_t;

/**
 * @description Creates a new scheduler.
 * @return A handle to the newly created scheduler, or NULL on failure.
 * @complexity Time: O(1), Space: O(1)
 */
scheduler_t *SchedCreate(void);

/**
 * @description Destroys a scheduler and frees its resources.
 * @param sched The scheduler to destroy.
 * @complexity Time: O(1), Space: O(1)
 */
void SchedDestroy(scheduler_t *sched);

/**
 * @description Adds a new task to the scheduler.
 * @param sched The scheduler to which the task is added.
 * @param interval The time interval (in seconds) between task executions.
 * @param time_to_run The reletive time in seconds to the start of run at which
 *			the task should run.
 * @param action_func A function to be executed by the task.
 * @param act_params Parameters to be passed to the action function.
 * @param cleanup_func A function to clean up resources in case i'ts needed
 *		after task execution (can be NULL).
 * @param cleanup_params Parameters to be passed to the cleanup function
 *			(can be NULL).
 * @return A UID of the added task, or bad_uid on failure.
 * @complexity Time: O(1), Space: O(1)
 */
ilrd_uid_t SchedAdd(scheduler_t *sched, size_t interval, time_t time_to_run,
                    int (*action_func)(void *act_params), void *act_params,
                    void (*cleanup_func)(void *cleanup_params),
                    void *cleanup_params);

/**
 * @description Runs the scheduler, executing scheduled tasks.
 * @param sched The scheduler to run.
 * @return 0 on success, non zero on failure.
 * @note Stops running in case of choosing to stop, if the task falied or there
 * 			are no more tasks to perform
 * @complexity Time: O(n), Space: O(1)
 */
int SchedRun(scheduler_t *sched);

/**
 * @description Removes a task from the scheduler.
 * @param sched The scheduler from which to remove the task.
 * @param task_id The UID of the task to remove.
 * @complexity Time: O(n), Space: O(1)
 */
void SchedRemove(scheduler_t *sched, ilrd_uid_t task_id);

/**
 * @description Retrieves the number of tasks in the scheduler.
 * @param sched The scheduler to query.
 * @return The number of tasks in the scheduler.
 * @complexity Time: O(n), Space: O(1)
 */
size_t SchedCount(scheduler_t *sched);

/**
 * @description Checks if the scheduler is empty (contains no tasks).
 * @param sched The scheduler to check.
 * @return 1 if the scheduler is empty, 0 if it contains tasks.
 * @complexity Time: O(1), Space: O(1)
 */
int SchedIsEmpty(scheduler_t *sched);

/**
 * @description Stops the scheduler, preventing further task execution.
 * @param sched The scheduler to stop.
 * @complexity Time: O(1), Space: O(1)
 */
void SchedStop(scheduler_t *sched);

/**
 * @description Clears all tasks from the scheduler.
 * @param sched The scheduler to clear.
 * @complexity Time: O(n), Space: O(1)
 */
void SchedClear(scheduler_t *sched);

#endif /* __ILRD_OL149_SCHEDULER_H__ */
