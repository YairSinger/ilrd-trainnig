#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scheduler.h"
#include "uid.h"

#define GOOD "\033[1;30m\033[102m"
#define BAD "\033[1;37m\033[41m"
#define REG "\033[1;0m""\n"
#define HEAD "\033[1;30m\033[47m"
#define SUB_HEAD "\033[1;30m\033[43m"

#define UNUSED(x) (void)(x)

int was_errors = 0;

char string[100] = {0};

scheduler_t *SchedulerCreateTEST(void);

ilrd_uid_t SchedulerAddTaskTEST(scheduler_t *scheduler,
					   int (*op_func)(void *), 
					   const void *params,
					   const size_t time_to_execute,
					   const size_t frequency);

void SchedulerClearTEST(void);

void SchedulerRemoveTaskTEST(void);

/***********************************************************/

int PrintS(void *params)
{
	UNUSED(params);
	
	printf("S\n");
	strcat(string, "S");
	
	return 0;
}

int PrintU(void *params)

{
	UNUSED(params);
	
	printf("U\n");
	strcat(string, "U");
	
	return 0;
}

int PrintC(void *params)
{
	UNUSED(params);
	
	printf("C\n");
	strcat(string, "C");
	
	return 0;
}

int PrintE(void *params)
{
	UNUSED(params);
	
	printf("E\n");
	strcat(string, "E");
	
	return 0;
}

int RepFunc(void *params)
{
	UNUSED(params);
	
	printf("[Repeat]\n");
	strcat(string, "[Repeat]");
	
	return 1;
}

int StopFunc(void *scheduler)
{
	SchedulerStop(scheduler);

	return 0;
}

int GhostFunc(void *params)
{
	UNUSED(params);
	
	printf(BAD"you shouldn't see me. removal error."REG);
	strcat(string, "*");
	
	was_errors = 1;
	
	return 0;
}

int SilentFunc(void *params)
{
	UNUSED(params);
	return 0;
}

int SilentStopFunc(void *scheduler)
{
	SchedulerStop(scheduler);
	return 0;
}

int SilentRepFunc(void *params)
{
	UNUSED(params);
	return 1;
}

int GoodJob_1(void *params)
{
	UNUSED(params);
	printf("░██████╗░░█████╗░░█████╗░██████╗░  ░░░░░██╗░█████╗░██████╗░██╗\n");
	return 0;
}

int GoodJob_2(void *params)
{
	UNUSED(params);
	printf("██╔════╝░██╔══██╗██╔══██╗██╔══██╗  ░░░░░██║██╔══██╗██╔══██╗██║\n");
	return 0;
}

int GoodJob_3(void *params)
{
	UNUSED(params);
	printf("██║░░██╗░██║░░██║██║░░██║██║░░██║  ░░░░░██║██║░░██║██████╦╝██║\n");
	return 0;
}

int GoodJob_4(void *params)
{
	UNUSED(params);
	printf("██║░░╚██╗██║░░██║██║░░██║██║░░██║  ██╗░░██║██║░░██║██╔══██╗╚═╝\n");
	return 0;
}


int GoodJob_5(void *params)
{
	UNUSED(params);
	printf("╚██████╔╝╚█████╔╝╚█████╔╝██████╔╝  ╚█████╔╝╚█████╔╝██████╦╝██╗\n");
	return 0;
}

int GoodJob_6(void *params)
{
	UNUSED(params);
	printf("░╚═════╝░░╚════╝░░╚════╝░╚═════╝░  ░╚════╝░░╚════╝░╚═════╝░╚═╝\n\n");
	return 0;
}

int main()
{
	int some_var = 1;
	
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	ilrd_uid_t uid3 = {0};
	ilrd_uid_t uid4 = {0};
	ilrd_uid_t uid5 = {0};
	ilrd_uid_t uid6 = {0};
	ilrd_uid_t uid7 = {0};
	ilrd_uid_t uid8 = {0};
	ilrd_uid_t uid9 = {0};
	ilrd_uid_t uid10 = {0};
	ilrd_uid_t uid11 = {0};
	ilrd_uid_t uid12 = {0};
		
	scheduler_t *scheduler = NULL;
	
	UNUSED(uid1);UNUSED(uid2);UNUSED(uid3);UNUSED(uid4);UNUSED(uid5);UNUSED(uid6);
	UNUSED(uid7);UNUSED(uid8);UNUSED(uid9);UNUSED(uid10);UNUSED(uid11);UNUSED(uid12);
	
	printf("\n"HEAD"     Flow Test (utilizes most of the functions)      "REG);
	printf    (HEAD"    (without repeating and stop-signaling tasks)     "REG);

	printf(SUB_HEAD"                 creating a new list                 "REG);
	scheduler = SchedulerCreateTEST();
	
	printf(SUB_HEAD"                     adding tasks                    "REG);
	
	uid2 = SchedulerAddTaskTEST(scheduler, PrintC, &some_var, 9, 0);
	
	uid4 = SchedulerAddTaskTEST(scheduler, PrintS, &some_var, 5, 0);
	
	uid5 = SchedulerAddTaskTEST(scheduler, PrintU, &some_var, 7, 0);
	
	uid6 = SchedulerAddTaskTEST(scheduler, PrintC, &some_var, 7, 0);
	
	uid7 = SchedulerAddTaskTEST(scheduler, GhostFunc, &some_var, 2, 0);
	
	uid11 = SchedulerAddTaskTEST(scheduler, PrintS, &some_var, 14, 0);

	uid8 = SchedulerAddTaskTEST(scheduler, GhostFunc, &some_var, 16, 0);
	
	uid9 = SchedulerAddTaskTEST(scheduler, PrintE, &some_var, 11, 0);
	
	uid10 = SchedulerAddTaskTEST(scheduler, PrintS, &some_var, 12, 0);

	printf(SUB_HEAD"      removing tasks (if failed - you'll know)       "REG"\n");
	SchedulerRemoveTask(scheduler, uid7);
	SchedulerRemoveTask(scheduler, uid8);
	
	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (0 == SchedulerIsEmpty(scheduler) && 7 == SchedulerSize(scheduler))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	
	printf(SUB_HEAD"                  running scheduler                  "REG);
	printf(SUB_HEAD"          should print \"SUCCESS\" vertically          "REG);
	SchedulerRun(scheduler);
	
	printf(SUB_HEAD"                veryfing print output                "REG);
	if (0 == strcmp("SUCCESS", string))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	
	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (1 == SchedulerIsEmpty(scheduler) && 0 == SchedulerSize(scheduler))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	

	
	printf("\n"HEAD"      Flow Test (utilizes most of the functions)     "REG);
	printf    (HEAD"  (with a repeating task and a stop-signaling task)  "REG);
	
	printf(SUB_HEAD"                    adding tasks                     "REG);
	
	uid1 = SchedulerAddTaskTEST(scheduler, StopFunc, scheduler, 20, 0);
	
	uid2 = SchedulerAddTaskTEST(scheduler, PrintC, &some_var, 9, 0);
	
	uid3 = SchedulerAddTaskTEST(scheduler, RepFunc, &some_var, 6, 4);
	
	uid4 = SchedulerAddTaskTEST(scheduler, PrintS, &some_var, 5, 0);
	
	uid11 = SchedulerAddTaskTEST(scheduler, PrintS, &some_var, 13, 0);
	
	uid5 = SchedulerAddTaskTEST(scheduler, PrintU, &some_var, 7, 0);
	
	uid6 = SchedulerAddTaskTEST(scheduler, PrintC, &some_var, 7, 0);
	
	uid10 = SchedulerAddTaskTEST(scheduler, PrintE, &some_var, 9, 0);
	
	uid7 = SchedulerAddTaskTEST(scheduler, GhostFunc, &some_var, 2, 0);

	uid8 = SchedulerAddTaskTEST(scheduler, GhostFunc, &some_var, 15, 0);
	
	uid12 = SchedulerAddTaskTEST(scheduler, PrintS, &some_var, 11, 0);

	printf(SUB_HEAD"       removing tasks (if failed - you'll know)      "REG"\n");
	SchedulerRemoveTask(scheduler, uid7);
	SchedulerRemoveTask(scheduler, uid8);
	
	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (0 == SchedulerIsEmpty(scheduler) && 9 == SchedulerSize(scheduler))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	
	printf(SUB_HEAD"                  running scheduler                  "REG);
	printf(SUB_HEAD"    should print the following string vertically:    "REG);
	printf(SUB_HEAD"       S[Repeat]UCCE[Repeat]SS[Repeat][Repeat]       "REG);
	
	SchedulerRun(scheduler);

	printf(SUB_HEAD"                veryfing print output                "REG);
	if (0 == strcmp("SUCCESSS[Repeat]UCCE[Repeat]SS[Repeat][Repeat]", string))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}

	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (0 == SchedulerIsEmpty(scheduler) && 1 == SchedulerSize(scheduler))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	
	
	SchedulerRemoveTaskTEST();
	
	SchedulerClearTEST();
	
	if (0 == was_errors)
	{
		SchedulerClear(scheduler);
		
		SchedulerAddTask(scheduler, GoodJob_1, &some_var, 1, 0);
		SchedulerAddTask(scheduler, GoodJob_2, &some_var, 2, 0);
		SchedulerAddTask(scheduler, GoodJob_3, &some_var, 3, 0);
		SchedulerAddTask(scheduler, GoodJob_4, &some_var, 4, 0);
		SchedulerAddTask(scheduler, GoodJob_5, &some_var, 5, 0);
		SchedulerAddTask(scheduler, GoodJob_6, &some_var, 6, 0);

		SchedulerRun(scheduler);
	}
	
	SchedulerDestroy(scheduler);
	
	return 0;
}

scheduler_t *SchedulerCreateTEST(void)
{
	size_t error_count = 0;
	
	scheduler_t *scheduler = SchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf(BAD"allocation failed"REG);
		++error_count;
	}

	
	if (0 == SchedulerIsEmpty(scheduler))
	{
		printf(BAD"new scheduler isn't empty"REG);
		++error_count;
	}
	
	if (0 != SchedulerSize(scheduler))
	{
		printf(BAD"new scheduler size isn't 0"REG);
		++error_count;
	}
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}

	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	return scheduler;
}


ilrd_uid_t SchedulerAddTaskTEST(scheduler_t *scheduler,
					   int (*op_func)(void *), 
					   const void *params,
					   const size_t time_to_execute,
					   const size_t frequency)
{
	size_t error_count = 0;
	
	size_t old_scheduler_size = SchedulerSize(scheduler);
	
	ilrd_uid_t uid = SchedulerAddTask(scheduler, op_func, params, time_to_execute, frequency);
	
	if (1 == IsSameUID(uid, GenerateBadUID()))
	{
		printf(BAD"uid == bad_uid\n");
		return uid;
	}
	
	if (1 == SchedulerIsEmpty(scheduler))
	{
		printf(BAD"scheduler is empty after adding test"REG);
		++error_count;
	}
	
	if (old_scheduler_size + 1 != SchedulerSize(scheduler))
	{
		printf(BAD"scheduler size is incorrect"REG);
		++error_count;
	}
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}
	
	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	return uid;
}


void SchedulerClearTEST(void)
{
	size_t error_count = 0;
	
	scheduler_t *scheduler = SchedulerCreate();
	
	int some_var = 1;
	
	ilrd_uid_t first_uid = {0};
	ilrd_uid_t mid_uid = {0};
	ilrd_uid_t last_uid = {0};
	
	printf("\n"HEAD"           Edge cases for 'SchedulerClear'           "REG);
	
	/* trying to clear a brand new scheduler */
	SchedulerClear(scheduler);
	if (0 != SchedulerSize(scheduler))
	{
		printf(BAD"error clear tasks"REG);
		++error_count;
	}
	SchedulerAddTask(scheduler, StopFunc, scheduler, 16, 0);
	SchedulerAddTask(scheduler, PrintE, &some_var, 9, 0);
	SchedulerAddTask(scheduler, RepFunc, &some_var, 6, 4);
	SchedulerAddTask(scheduler, PrintS, &some_var, 5, 0);
	SchedulerAddTask(scheduler, PrintU, &some_var, 7, 0);
	SchedulerAddTask(scheduler, PrintC, &some_var, 7, 0);
	SchedulerAddTask(scheduler, GhostFunc, &some_var, 2, 0);
	SchedulerAddTask(scheduler, GhostFunc, &some_var, 12, 0);
	SchedulerAddTask(scheduler, PrintE, &some_var, 11, 0);
	
	if (9 != SchedulerSize(scheduler))
	{
		printf(BAD"error inserting tasks"REG);
		++error_count;
	}
	
	SchedulerClear(scheduler);
	
	if (0 == SchedulerIsEmpty(scheduler))
	{
		printf(BAD"scheduler isn't empty after Clear"REG);
		++error_count;
	}
	
	if (0 != SchedulerSize(scheduler))
	{
		printf(BAD"scheduler size isn't 0 after Clear"REG);
		++error_count;
	}

	if (0 == error_count)
	{	
		/* trying to clear an empty scheduler */
		SchedulerClear(scheduler);
	}
	
	if (0 == SchedulerIsEmpty(scheduler))
	{
		printf(BAD"scheduler isn't empty after Clear"REG);
		++error_count;
	}
	
	if (0 != SchedulerSize(scheduler))
	{
		printf(BAD"scheduler size isn't 0 Clear"REG);
		++error_count;
	}
	
	SchedulerAddTask(scheduler, SilentStopFunc, scheduler, 4, 0);
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 3, 0);
	SchedulerAddTask(scheduler, SilentRepFunc, &some_var, 1, 1);
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 5, 0);
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 2, 0);
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 1, 0);
	
	first_uid = SchedulerAddTask(scheduler, GhostFunc, &some_var, 0, 0);
	mid_uid = SchedulerAddTask(scheduler, GhostFunc, &some_var, 3, 0);
	last_uid = SchedulerAddTask(scheduler, GhostFunc, &some_var, 6, 0);
	
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 5, 0);

	SchedulerRemoveTask(scheduler, first_uid);
	SchedulerRemoveTask(scheduler, mid_uid);
	SchedulerRemoveTask(scheduler, last_uid);
	
	if (7 != SchedulerSize(scheduler))
	{
		printf(BAD"error inserting tasks"REG);
		++error_count;
	}
	
	SchedulerRun(scheduler);
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG"\n");
	}
	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	SchedulerDestroy(scheduler);
}


void SchedulerRemoveTaskTEST(void)
{
	size_t error_count = 0;
	
	
	size_t old_scheduler_size = 0;
	
	scheduler_t *scheduler = SchedulerCreate();
	
	ilrd_uid_t first_uid = {0};
	ilrd_uid_t mid_uid = {0};
	ilrd_uid_t last_uid = {0};

	ilrd_uid_t dummy_uid = GenerateUID();
	ilrd_uid_t bad_uid = GenerateBadUID();
	ilrd_uid_t blank_uid = {0};
	
	int some_var = 1;
	
	printf("\n"HEAD"        Edge cases for 'SchedulerRemoveTask'         "REG);

	SchedulerAddTask(scheduler, SilentStopFunc, scheduler, 4, 0);
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 3, 0);
	SchedulerAddTask(scheduler, SilentRepFunc, &some_var, 1, 1);
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 5, 0);
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 2, 0);
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 1, 0);
	
	first_uid = SchedulerAddTask(scheduler, GhostFunc, &some_var, 0, 0);
	mid_uid = SchedulerAddTask(scheduler, GhostFunc, &some_var, 3, 0);
	last_uid = SchedulerAddTask(scheduler, GhostFunc, &some_var, 6, 0);
	
	SchedulerAddTask(scheduler, SilentFunc, &some_var, 5, 0);
	

	if (10 != SchedulerSize(scheduler))
	{
		printf(BAD"error inserting tasks"REG);
		++error_count;
	}
	
	old_scheduler_size = SchedulerSize(scheduler);
	SchedulerRemoveTask(scheduler, mid_uid);

	if (old_scheduler_size != SchedulerSize(scheduler) + 1)
	{
		printf(BAD"error removing tasks from the middle"REG);
		++error_count;
	}
	
	old_scheduler_size = SchedulerSize(scheduler);
	SchedulerRemoveTask(scheduler, last_uid);
	
	if (old_scheduler_size != SchedulerSize(scheduler) + 1)
	{
		printf(BAD"error removing the last task"REG);
		++error_count;
	}
	
	old_scheduler_size = SchedulerSize(scheduler);
	SchedulerRemoveTask(scheduler, first_uid);
	
	if (old_scheduler_size != SchedulerSize(scheduler) + 1)
	{
		printf(BAD"error removing the first task"REG);
		++error_count;
	}
	
	old_scheduler_size = SchedulerSize(scheduler);
	
	/* attempting to remove nonexisting tasks */
	SchedulerRemoveTask(scheduler, first_uid);
	SchedulerRemoveTask(scheduler, mid_uid);
	SchedulerRemoveTask(scheduler, last_uid);
	SchedulerRemoveTask(scheduler, dummy_uid);
	SchedulerRemoveTask(scheduler, bad_uid);
	SchedulerRemoveTask(scheduler, blank_uid);
	
	
	if (old_scheduler_size != SchedulerSize(scheduler))
	{
		printf(BAD"the size changed after attempting to remove nonexisting tasks"REG);
		++error_count;
	}
	
	/* trying to run the scheduler after several removals and removal-attempts */
	SchedulerRun(scheduler);
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}
	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	SchedulerDestroy(scheduler);
}
