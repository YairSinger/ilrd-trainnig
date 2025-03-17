#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heap_scheduler.h"
#include "ilrd_uid.h"

#define GOOD "\033[1;30m\033[102m"
#define BAD "\033[1;37m\033[41m"
#define REG "\033[1;0m""\n"
#define HEAD "\033[1;30m\033[47m"
#define SUB_HEAD "\033[1;30m\033[43m"

#define UNUSED(x) (void)(x)

int was_errors = 0;

char string[100] = {0};

heap_scheduler_t *HeapSchedulerCreateTEST(void);

ilrd_uid_t HeapSchedulerAddTaskTEST(heap_scheduler_t *scheduler,
					   int (*op_func)(void *), 
					   const void *params,
					   const size_t time_to_execute,
					   const size_t frequency);

void HeapSchedulerClearTEST(void);

void HeapSchedulerRemoveTaskTEST(void);

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
	HeapSchedulerStop(scheduler);

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
	HeapSchedulerStop(scheduler);
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
		
	heap_scheduler_t *scheduler = NULL;
	
	UNUSED(uid1);UNUSED(uid2);UNUSED(uid3);UNUSED(uid4);UNUSED(uid5);UNUSED(uid6);
	UNUSED(uid7);UNUSED(uid8);UNUSED(uid9);UNUSED(uid10);UNUSED(uid11);UNUSED(uid12);
	
	printf("\n"HEAD"     Flow Test (utilizes most of the functions)      "REG);
	printf    (HEAD"    (without repeating and stop-signaling tasks)     "REG);

	printf(SUB_HEAD"                 creating a new list                 "REG);
	scheduler = HeapSchedulerCreateTEST();
	
	printf(SUB_HEAD"                     adding tasks                    "REG);
	
	uid2 = HeapSchedulerAddTaskTEST(scheduler, PrintC, &some_var, 9, 0);
	
	uid4 = HeapSchedulerAddTaskTEST(scheduler, PrintS, &some_var, 5, 0);
	
	uid5 = HeapSchedulerAddTaskTEST(scheduler, PrintU, &some_var, 7, 0);
	
	uid6 = HeapSchedulerAddTaskTEST(scheduler, PrintC, &some_var, 8, 0);
	
	uid7 = HeapSchedulerAddTaskTEST(scheduler, GhostFunc, &some_var, 2, 0);
	
	uid11 = HeapSchedulerAddTaskTEST(scheduler, PrintS, &some_var, 14, 0);

	uid8 = HeapSchedulerAddTaskTEST(scheduler, GhostFunc, &some_var, 16, 0);
	
	uid9 = HeapSchedulerAddTaskTEST(scheduler, PrintE, &some_var, 11, 0);
	
	uid10 = HeapSchedulerAddTaskTEST(scheduler, PrintS, &some_var, 12, 0);

	printf(SUB_HEAD"      removing tasks (if failed - you'll know)       "REG"\n");
	HeapSchedulerRemoveTask(scheduler, uid7);
	HeapSchedulerRemoveTask(scheduler, uid8);
	
	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (0 == HeapSchedulerIsEmpty(scheduler) && 7 == HeapSchedulerSize(scheduler))
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
	HeapSchedulerRun(scheduler);
	
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
	if (1 == HeapSchedulerIsEmpty(scheduler) && 0 == HeapSchedulerSize(scheduler))
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
	
	uid1 = HeapSchedulerAddTaskTEST(scheduler, StopFunc, scheduler, 22, 0);
	
	uid2 = HeapSchedulerAddTaskTEST(scheduler, PrintC, &some_var, 9, 0);
	
	uid3 = HeapSchedulerAddTaskTEST(scheduler, RepFunc, &some_var, 6, 5);
	
	uid4 = HeapSchedulerAddTaskTEST(scheduler, PrintS, &some_var, 5, 0);
	
	uid11 = HeapSchedulerAddTaskTEST(scheduler, PrintS, &some_var, 13, 0);
	
	uid5 = HeapSchedulerAddTaskTEST(scheduler, PrintU, &some_var, 7, 0);
	
	uid6 = HeapSchedulerAddTaskTEST(scheduler, PrintC, &some_var, 8, 0);
	
	uid10 = HeapSchedulerAddTaskTEST(scheduler, PrintE, &some_var, 10, 0);
	
	uid7 = HeapSchedulerAddTaskTEST(scheduler, GhostFunc, &some_var, 2, 0);

	uid8 = HeapSchedulerAddTaskTEST(scheduler, GhostFunc, &some_var, 15, 0);
	
	uid12 = HeapSchedulerAddTaskTEST(scheduler, PrintS, &some_var, 12, 0);

	printf(SUB_HEAD"       removing tasks (if failed - you'll know)      "REG"\n");
	HeapSchedulerRemoveTask(scheduler, uid7);
	HeapSchedulerRemoveTask(scheduler, uid8);
	
	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (0 == HeapSchedulerIsEmpty(scheduler) && 9 == HeapSchedulerSize(scheduler))
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
	
	HeapSchedulerRun(scheduler);

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
	if (0 == HeapSchedulerIsEmpty(scheduler) && 1 == HeapSchedulerSize(scheduler))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	
	
	HeapSchedulerRemoveTaskTEST();
	

	
	if (0 == was_errors)
	{
		HeapSchedulerClear(scheduler);
		
		HeapSchedulerAddTask(scheduler, GoodJob_1, &some_var, 1, 0);
		HeapSchedulerAddTask(scheduler, GoodJob_2, &some_var, 2, 0);
		HeapSchedulerAddTask(scheduler, GoodJob_3, &some_var, 3, 0);
		HeapSchedulerAddTask(scheduler, GoodJob_4, &some_var, 4, 0);
		HeapSchedulerAddTask(scheduler, GoodJob_5, &some_var, 5, 0);
		HeapSchedulerAddTask(scheduler, GoodJob_6, &some_var, 6, 0);

		HeapSchedulerRun(scheduler);
	}
	
	HeapSchedulerDestroy(scheduler);
	
	
		HeapSchedulerClearTEST();
	return 0;
} 

heap_scheduler_t *HeapSchedulerCreateTEST(void)
{
	size_t error_count = 0;
	
	heap_scheduler_t *scheduler = HeapSchedulerCreate();
	
	if (NULL == scheduler)
	{
		printf(BAD"allocation failed"REG);
		++error_count;
	}

	
	if (0 == HeapSchedulerIsEmpty(scheduler))
	{
		printf(BAD"new scheduler isn't empty"REG);
		++error_count;
	}
	
	if (0 != HeapSchedulerSize(scheduler))
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


ilrd_uid_t HeapSchedulerAddTaskTEST(heap_scheduler_t *scheduler,
					   int (*op_func)(void *), 
					   const void *params,
					   const size_t time_to_execute,
					   const size_t frequency)
{
	size_t error_count = 0;
	
	size_t old_scheduler_size = HeapSchedulerSize(scheduler);
	
	ilrd_uid_t uid = HeapSchedulerAddTask(scheduler, op_func, params, time_to_execute, frequency);
	
	if (1 == IsSameUID(uid, GenerateBadUID()))
	{
		printf(BAD"uid == bad_uid\n");
		return uid;
	}
	
	if (1 == HeapSchedulerIsEmpty(scheduler))
	{
		printf(BAD"scheduler is empty after adding test"REG);
		++error_count;
	}
	
	if (old_scheduler_size + 1 != HeapSchedulerSize(scheduler))
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


void HeapSchedulerClearTEST(void)
{
	size_t error_count = 0;
	
	heap_scheduler_t *scheduler = HeapSchedulerCreate();
	
	int some_var = 1;
	
	ilrd_uid_t first_uid = {0};
	ilrd_uid_t mid_uid = {0};
	ilrd_uid_t last_uid = {0};
	
	printf("\n"HEAD"           Edge cases for 'HeapSchedulerClear'           "REG);
	
	/* trying to clear a brand new scheduler */
	HeapSchedulerClear(scheduler);
	
	HeapSchedulerAddTask(scheduler, StopFunc, scheduler, 16, 0);
	HeapSchedulerAddTask(scheduler, PrintE, &some_var, 9, 0);
	HeapSchedulerAddTask(scheduler, RepFunc, &some_var, 6, 4);
	HeapSchedulerAddTask(scheduler, PrintS, &some_var, 5, 0);
	HeapSchedulerAddTask(scheduler, PrintU, &some_var, 7, 0);
	HeapSchedulerAddTask(scheduler, PrintC, &some_var, 7, 0);
	HeapSchedulerAddTask(scheduler, GhostFunc, &some_var, 2, 0);
	HeapSchedulerAddTask(scheduler, GhostFunc, &some_var, 12, 0);
	HeapSchedulerAddTask(scheduler, PrintE, &some_var, 11, 0);
	
	if (9 != HeapSchedulerSize(scheduler))
	{
		printf(BAD"error inserting tasks"REG);
		++error_count;
	}
	
	HeapSchedulerClear(scheduler);
	
	if (0 == HeapSchedulerIsEmpty(scheduler))
	{
		printf(BAD"scheduler isn't empty after Clear"REG);
		++error_count;
	}
	
	if (0 != HeapSchedulerSize(scheduler))
	{
		printf(BAD"scheduler size isn't 0 after Clear"REG);
		++error_count;
	}

	if (0 == error_count)
	{	
		/* trying to clear an empty scheduler */
		HeapSchedulerClear(scheduler);
	}
	
	if (0 == HeapSchedulerIsEmpty(scheduler))
	{
		printf(BAD"scheduler isn't empty after Clear"REG);
		++error_count;
	}
	
	if (0 != HeapSchedulerSize(scheduler))
	{
		printf(BAD"scheduler size isn't 0 Clear"REG);
		++error_count;
	}
	
	HeapSchedulerAddTask(scheduler, SilentStopFunc, scheduler, 4, 0);
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 3, 0);
	HeapSchedulerAddTask(scheduler, SilentRepFunc, &some_var, 1, 1);
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 5, 0);
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 2, 0);
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 1, 0);
	
	first_uid = HeapSchedulerAddTask(scheduler, GhostFunc, &some_var, 0, 0);
	last_uid = HeapSchedulerAddTask(scheduler, GhostFunc, &some_var, 6, 0);
	
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 5, 0);

	HeapSchedulerRemoveTask(scheduler, first_uid);
	HeapSchedulerRemoveTask(scheduler, last_uid);
	
	if (7 != HeapSchedulerSize(scheduler))
	{
		printf(BAD"error inserting tasks"REG);
		++error_count;
	}
	
	HeapSchedulerRun(scheduler);
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG"\n");
	}
	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	HeapSchedulerDestroy(scheduler);
}


void HeapSchedulerRemoveTaskTEST(void)
{
	size_t error_count = 0;
	
	
	size_t old_scheduler_size = 0;
	
	heap_scheduler_t *scheduler = HeapSchedulerCreate();
	
	ilrd_uid_t first_uid = {0};
	ilrd_uid_t mid_uid = {0};
	ilrd_uid_t last_uid = {0};

	ilrd_uid_t dummy_uid = GenerateUID();
	ilrd_uid_t bad_uid = GenerateBadUID();
	ilrd_uid_t blank_uid = {0};
	
	int some_var = 1;
	
	printf("\n"HEAD"        Edge cases for 'HeapSchedulerRemoveTask'         "REG);

	HeapSchedulerAddTask(scheduler, SilentStopFunc, scheduler, 4, 0);
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 6, 0);
	HeapSchedulerAddTask(scheduler, SilentRepFunc, &some_var, 1, 1);
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 5, 0);
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 2, 0);
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 1, 0);
	
	first_uid = HeapSchedulerAddTask(scheduler, GhostFunc, &some_var, 0, 0);
	mid_uid = HeapSchedulerAddTask(scheduler, GhostFunc, &some_var, 3, 0);
	last_uid = HeapSchedulerAddTask(scheduler, GhostFunc, &some_var, 7, 0);
	
	HeapSchedulerAddTask(scheduler, SilentFunc, &some_var, 5, 0);
	

	if (10 != HeapSchedulerSize(scheduler))
	{
		printf(BAD"error inserting tasks"REG);
		++error_count;
	}
	
	old_scheduler_size = HeapSchedulerSize(scheduler);
	HeapSchedulerRemoveTask(scheduler, mid_uid);

	if (old_scheduler_size != HeapSchedulerSize(scheduler) + 1)
	{
		printf(BAD"error removing tasks from the middle"REG);
		++error_count;
	}
	
	old_scheduler_size = HeapSchedulerSize(scheduler);
	HeapSchedulerRemoveTask(scheduler, last_uid);
	
	if (old_scheduler_size != HeapSchedulerSize(scheduler) + 1)
	{
		printf(BAD"error removing the last task"REG);
		++error_count;
	}
	
	old_scheduler_size = HeapSchedulerSize(scheduler);
	HeapSchedulerRemoveTask(scheduler, first_uid);
	
	if (old_scheduler_size != HeapSchedulerSize(scheduler) + 1)
	{
		printf(BAD"error removing the first task"REG);
		++error_count;
	}
	
	old_scheduler_size = HeapSchedulerSize(scheduler);
	
	/* attempting to remove nonexisting tasks */
	HeapSchedulerRemoveTask(scheduler, first_uid);
	HeapSchedulerRemoveTask(scheduler, mid_uid);
	HeapSchedulerRemoveTask(scheduler, last_uid);
	
	
	if (old_scheduler_size != HeapSchedulerSize(scheduler))
	{
		printf(BAD"the size changed after attempting to remove nonexisting tasks"REG);
		++error_count;
	}
	
	/* trying to run the scheduler after several removals and removal-attempts */
	HeapSchedulerRun(scheduler);
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}
	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	HeapSchedulerDestroy(scheduler);
}
