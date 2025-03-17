
/* ----------------------------------------------------------
 * Filename:    scheduler_test.c
 * Author:      Shahar Molina
 * Reviewer:    Yael Hava
 * Date:        28.09.2023
 * Course:      OL-149
 * Description:	Test unit for scheduler library
 * ----------------------------------------------------------
 */

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcmp */
#include <unistd.h> /* sleep */

#include "scheduler.h"    /* API for scheduler */
#include "testing_unit.h" /* API for testing unit */
#include "uid.h"          /* API for uid */

/*---Macros---*/
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

/* -------------------Functions Declerations-------------------- */
static void CreateDestroyTests(void);
static void AddTest(void);
static void RunTest(void);
static void SizeIsEmptyTest(void);
static void StopTest(void);
static void ClearTest(void);
static void FileTest(void);
static void RemoveTest(void);

static void TaskAddTaskTest(void);
static void TaskUsingMallocTest(void);
static void TaskRemoveTaskTest(void);
static void TaskRemoveItselfTest(void);

static int Print(void *str);
static int Stop(void *sched);
static int Clear(void *sched);
static int Add(void *add_params);
static int Malloc(void *param);
static void Free(void *param);
static int Remove(void *remove_params);
static int PrintCounter(void *interval_until_params);
static int ResetFile(void);
static int ActionChangeFileToStop(void *act_params);

/* -------------------Structs-------------------- */
typedef struct task_params
{
	size_t interval;
	time_t time_to_run;
	int (*action_func)(void *param);
	void *act_params;
	void (*cleanup_func)(void *param_cleanup);
	void *cleanup_params;
} task_params_t;

typedef struct add_params
{
	task_params_t add_params;
	scheduler_t *sched;
} add_params_t;

typedef struct remove_params
{
	ilrd_uid_t task_id;
	scheduler_t *sched;
} remove_params_t;

typedef struct interval_until_params
{
	void *params;
	const ilrd_uid_t *task_id;
	scheduler_t *sched;
} interval_until_params_t;

/* -------------------Program-------------------- */
int main(void)
{
	CreateDestroyTests();
	AddTest();
	RunTest();
	SizeIsEmptyTest();
	ClearTest();
	RemoveTest();
	StopTest();
	FileTest();

	TaskAddTaskTest();
	TaskUsingMallocTest();
	TaskRemoveTaskTest();
	TaskRemoveItselfTest();

	return 0;
}

/* -------------------Tests Defeinitions-------------------- */
static void CreateDestroyTests(void)
{
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: Create and Destroy - FAILED!\n" RESET);
	}

	SchedDestroy(sched);
	printf(GREEN "Test: Create and Destroy - PASSED!\n" RESET);
	printf("\n");
}

static void AddTest(void)
{
	char *str = "Hello World";
	ilrd_uid_t uid = bad_uid;
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: Add - FAILED!\n" RESET);
	}

	TestExpected("Add1", SchedIsEmpty(sched), 1);
	uid = SchedAdd(sched, 0, time(NULL), Print, str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: Add - FAILED!\n" RESET);
	}

	TestExpected("Add2", SchedIsEmpty(sched), 0);

	SchedDestroy(sched);
	printf("\n");
}

static void RunTest(void)
{
	char *str = "hello world";
	ilrd_uid_t uid = bad_uid;
	int result = 0;
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: Run - FAILED!\n" RESET);
	}

	str = "now + 1";
	uid = SchedAdd(sched, 0, 1, Print, str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: Run - FAILED!\n" RESET);
	}

	str = "now";
	uid = SchedAdd(sched, 0, 0, Print, str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: Run - FAILED!\n" RESET);
	}

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: Run - FAILED!\n" RESET);
	}

	SchedDestroy(sched);
	printf(GREEN "Test: Run - PASSED!\n" RESET);
	printf("\n");
}

static void StopTest(void)
{
	char *str = "hello world";
	ilrd_uid_t uid = bad_uid;
	int result = 0;
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: Stop - FAILED!\n" RESET);
	}

	uid = SchedAdd(sched, 1, 0, Print, str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: Stop - FAILED!\n" RESET);
	}

	uid = SchedAdd(sched, 0, 5, Stop, sched, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: Stop - FAILED!\n" RESET);
	}

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: Stop - FAILED!\n" RESET);
	}

	printf(GREEN "Test: Stop - PASSED!\n" RESET);
	SchedDestroy(sched);
	printf("\n");
}

static void ClearTest(void)
{
	char *str = "hello world";
	ilrd_uid_t uid = bad_uid;
	int result = 0;
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: Clear - FAILED!\n" RESET);
	}

	str = "now + 2 (After Clear)";
	uid = SchedAdd(sched, 0, 2, Print, str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: Clear - FAILED!\n" RESET);
	}

	uid = SchedAdd(sched, 0, 1, Clear, sched, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: Clear - FAILED!\n" RESET);
	}

	str = "now (Before Clear)";
	uid = SchedAdd(sched, 0, 0, Print, str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: Clear - FAILED!\n" RESET);
	}

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: Clear - FAILED!\n" RESET);
	}

	TestExpected("Clear", SchedIsEmpty(sched), 1);

	if (NULL != sched)
	{
		SchedDestroy(sched);
	}
	printf("\n");
}

static void FileTest(void)
{
	const char *str = "hello world";
	ilrd_uid_t uid = bad_uid;
	int result = 0;
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: File - FAILED!\n" RESET);
	}

	str = "now + 2";
	uid = SchedAdd(sched, 0, 2, Print, (void *)str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: File - FAILED!\n" RESET);
	}

	str = "now";
	uid = SchedAdd(sched, 1, 0, Print, (void *)str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: File - FAILED!\n" RESET);
	}

	uid = SchedAdd(sched, 0, 5, ActionChangeFileToStop, NULL, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: File - FAILED!\n" RESET);
	}

	if (0 != ResetFile())
	{
		printf(RED "Test: File - FAILED!\n" RESET);
	}

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: File - FAILED!\n" RESET);
	}

	if (0 != ResetFile())
	{
		printf(RED "Test: File - FAILED!\n" RESET);
	}

	if (NULL != sched)
	{
		SchedDestroy(sched);
	}
}

static void SizeIsEmptyTest(void)
{
	char *str = "hello world";
	ilrd_uid_t uid = bad_uid;
	int result = 0;
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: SizeIsEmpty - FAILED!\n" RESET);
	}

	TestExpected("IsEmpty1", SchedIsEmpty(sched), 1);
	TestExpected("Size1", SchedCount(sched), 0);
	str = "now + 1";
	uid = SchedAdd(sched, 0, 1, Print, str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: SizeIsEmpty - FAILED!\n" RESET);
	}

	str = "now";
	uid = SchedAdd(sched, 0, 0, Print, str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: SizeIsEmpty - FAILED!\n" RESET);
	}
	TestExpected("IsEmpty2", SchedIsEmpty(sched), 0);
	TestExpected("Size2", SchedCount(sched), 2);

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: SizeIsEmpty - FAILED!\n" RESET);
	}

	TestExpected("IsEmpty3", SchedIsEmpty(sched), 1);
	TestExpected("Size3", SchedCount(sched), 0);

	SchedDestroy(sched);
	printf("\n");
}

static void RemoveTest(void)
{
	char *str = "hello world";
	ilrd_uid_t uid = bad_uid;
	int result = 0;
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: Remove - FAILED!\n" RESET);
	}

	uid = SchedAdd(sched, 0, 0, Print, str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: Remove - FAILED!\n" RESET);
	}

	TestExpected("Remove1", SchedCount(sched), 1);
	SchedRemove(sched, uid);
	TestExpected("Remove2", SchedCount(sched), 0);

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: Remove - FAILED!\n" RESET);
	}

	SchedDestroy(sched);
	printf("\n");
}

static void TaskAddTaskTest(void)
{
	const char *str = "hello world";
	ilrd_uid_t uid = bad_uid;
	int result = 0;
	add_params_t add_params = {0};
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: TaskAddTask - FAILED!\n" RESET);
	}

	add_params.add_params.interval = 0;
	add_params.add_params.time_to_run = 1;
	add_params.add_params.action_func = Print;
	add_params.add_params.act_params = (void *)str;
	add_params.add_params.cleanup_func = NULL;
	add_params.add_params.cleanup_params = NULL;
	add_params.sched = sched;

	uid = SchedAdd(sched, 0, 0, Add, &add_params, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: TaskAddTask - FAILED!\n" RESET);
	}

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: TaskAddTask - FAILED!\n" RESET);
	}

	TestExpected("TaskAddTask", SchedIsEmpty(sched), 1);

	if (NULL != sched)
	{
		SchedDestroy(sched);
	}
	printf("\n");
}

static void TaskUsingMallocTest(void)
{
	char *str = "Hello World!";
	ilrd_uid_t uid = bad_uid;
	int result = 0;
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: UsingMalloc - FAILED!\n" RESET);
	}

	uid = SchedAdd(sched, 0, 0, Malloc, &str, Free, &str);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: UsingMalloc - FAILED!\n" RESET);
	}

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: UsingMalloc - FAILED!\n" RESET);
	}

	TestExpected("UsingMalloc", SchedIsEmpty(sched), 1);
	SchedDestroy(sched);
	printf("\n");
}

static void TaskRemoveTaskTest(void)
{
	const char *str = NULL;
	ilrd_uid_t uid = bad_uid;
	int result = 0;
	remove_params_t remove_params = {0};
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: TaskRemoveTask - FAILED!\n" RESET);
	}

	str = "Remove me";
	uid = SchedAdd(sched, 1, 0, Print, (void *)str, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: TaskRemoveTask - FAILED!\n" RESET);
	}

	remove_params.task_id = uid;
	remove_params.sched = sched;

	uid = SchedAdd(sched, 0, 2, Remove, &remove_params, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: TaskRemoveTask - FAILED!\n" RESET);
	}

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: TaskRemoveTask - FAILED!\n" RESET);
	}

	TestExpected("TaskRemoveTask", SchedIsEmpty(sched), 1);
	if (NULL != sched)
	{
		SchedDestroy(sched);
	}
	printf("\n");
}

static void TaskRemoveItselfTest(void)
{
	char *str = "hello world";
	ilrd_uid_t uid = bad_uid;
	ilrd_uid_t *ptr_uid = &uid;
	int result = 0;
	interval_until_params_t params = {0};
	scheduler_t *sched = SchedCreate();
	if (NULL == sched)
	{
		printf(RED "Test: TaskRemoveItself - FAILED!\n" RESET);
	}

	params.sched = sched;
	params.params = str;
	params.task_id = ptr_uid;
	uid = SchedAdd(sched, 1, 0, PrintCounter, &params, NULL, NULL);
	if (UIDIsSame(uid, bad_uid))
	{
		printf(RED "Test: TaskRemoveItself - FAILED!\n" RESET);
	}

	result = SchedRun(sched);
	if (0 != result)
	{
		printf(RED "Test: TaskRemoveItself - FAILED!\n" RESET);
	}

	TestExpected("TaskRemoveItself", SchedIsEmpty(sched), 1);
	SchedDestroy(sched);
}

/* -------------------Service Functions-------------------- */
static int Print(void *str)
{
	printf("%s\n", (char *)str);
	return 0;
}

static int Stop(void *sched)
{
	SchedStop((scheduler_t *)sched);
	return 0;
}

static int Clear(void *sched)
{
	SchedClear((scheduler_t *)sched);
	return 0;
}

static int Add(void *add_params)
{
	add_params_t *params = (add_params_t *)add_params;

	ilrd_uid_t uid =
	    SchedAdd(params->sched, params->add_params.interval,
	             params->add_params.time_to_run, params->add_params.action_func,
	             params->add_params.act_params, params->add_params.cleanup_func,
	             params->add_params.cleanup_params);
	if (UIDIsSame(uid, bad_uid))
	{
		return -1;
	}
	return 0;
}

static int Malloc(void *param)
{
	char **my_param = (char **)param;
	*my_param = (char *)malloc(sizeof(char) * 13);
	if (NULL == my_param)
	{
		return -1;
	}
	printf("used Malloc.\n");
	return 0;
}

static void Free(void *param)
{
	free(*(char **)param);
	param = NULL;
	printf("freed Malloc.\n");
}

static int PrintCounter(void *interval_until_params)
{
	static int counter = 5;
	interval_until_params_t *params =
	    (interval_until_params_t *)interval_until_params;
	while (counter > 0)
	{
		printf("%s\n", (char *)params->params);
		--counter;
		return 0;
	}
	SchedRemove(params->sched, *(ilrd_uid_t *)params->task_id);
	return 0;
}

static int Remove(void *remove_params)
{
	remove_params_t *params = (remove_params_t *)remove_params;
	SchedRemove(params->sched, params->task_id);
	return 0;
}

static int ResetFile(void)
{
	char *run = "run";
	FILE *file = fopen("filecontroller.txt", "wb");
	if (NULL == file)
	{
		fprintf(stderr, "File open error\n");
		return -1;
	}

	if (1 != fwrite(run, sizeof(char) * 4, 1, file))
	{
		fprintf(stderr, "Error writing to file\n");
		return -1;
	}

	if (-1 == fclose(file))
	{
		fprintf(stderr, "Error closing file\n");
		return -1;
	}

	return 0;
}

static int ActionChangeFileToStop(void *act_params)
{
	char *stop = "stop";
	FILE *file = fopen("filecontroller.txt", "wb");
	if (NULL == file)
	{
		fprintf(stderr, "File open error\n");
		return -1;
	}

	if (1 != fwrite(stop, sizeof(char) * 5, 1, file))
	{
		fprintf(stderr, "Error writing from file\n");
		fclose(file);
		return -1;
	}

	if (-1 == fclose(file))
	{
		fprintf(stderr, "Error closing file\n");
		return -1;
	}
	(void)act_params;
	return 0;
}
