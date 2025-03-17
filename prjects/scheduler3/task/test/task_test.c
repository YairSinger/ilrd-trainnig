
/* ----------------------------------------------------------
 * Filename:    task_test.c
 * Author:      Shahar Molina
 * Reviewer:	Yael hava
 * Date:        28.09.2023
 * Course:      OL-149
 * Description:	Test unit for task library
 * ----------------------------------------------------------
 */

#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <time.h> /* time_t */

#include "uid.h" /* API for uid */
#include "task.h" /* API for task */
/* -------------------Functions Declerations-------------------- */
static void PrintTest(void);

static int PrintAction(void *params);

/* -------------------Program-------------------- */
int main(void)
{
    PrintTest();

    return 0;
}

/* -------------------Test Definitions-------------------- */
static void PrintTest(void)
{
    task_t *task1;
    task_t *task2;

    task1 = TaskCreate(0, 0, PrintAction, "Task 1", NULL, NULL,  UIDGet());
    task2 = TaskCreate(0, 0, PrintAction, "Task 2", NULL, NULL, UIDGet());

    if (task1 == NULL || task2 == NULL)
    {
        fprintf(stderr, "Failed to create tasks.\n");
    }

    printf("Tasks created.\n");

    TaskRun(task1);
    TaskRun(task2);
	printf("Tasks runned.\n");

    TaskUpdateTime(task1, time(NULL));
    TaskUpdateTime(task2, time(NULL));
    printf("Tasks updated.\n");

    TaskDestroy(task1);
    TaskDestroy(task2);
    printf("Tasks destroyed.\n");
}

/* -------------------Service Functions-------------------- */
static int PrintAction(void *params)
{
    printf("Task executed with params: %s\n", (char *)params);
    return 0;
}

