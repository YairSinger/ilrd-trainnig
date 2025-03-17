/*********************************
* Group: OL 149	 		 		 *
* Project: watchdog utils    	 *
* Version: 1.0.0   		 		 *
* Student: Yair singer   		 *
* Reviewer: 	 				 *
* Status:   			 		 *
*						 		 *
* Date: 	12.12.23      		 *
**********************************/


#ifndef __WATCHDOG_UTIL_H__
#define __WATCHDOG_UTIL_H__

#include <stddef.h> /* size_t */
#include <semaphore.h>
#include <time.h>
#include "scheduler.h"
#include "uid.h"

#define PULSE_INTERVAL 1
#define CHECK_STOP 4
#define MAX_TIME_FROM_LAST_SIGNAL 4

#define WD_PROC_PATH "/home/yair/git2/yair.singer/prjects/watchdog/watchdog_util/bin/debug/watchdog_util_test"
#define LOGGER_PATH "/home/yair/git2/yair.singer/prjects/watchdog/watchdog_util/logger.text"


char forked_by_user[] = "user_proc";  
char forked_by_wd[] = "watchdog_proc";
char *logger_path = "/home/yair/git2/yair.singer/prjects/watchdog/watchdog_util/watchdog_logger";

typedef struct wd_argv
{
    char *new_argv[4];
    char user_path[100];
    char wd_path[100];
    char is_wd_parent[1];/*'1' if true*/
}wd_argv_t;

typedef enum wd_sched_create_status
{
    SCHED_CREATE_SUCCESS = 0,
    SCHED_CREATE_ALLOC_FAIL,
    SCHED_CREATE_TASKS_INSERT_FAIL
}wd_sched_create_status_t;

typedef enum who_am_i
{
    USER_PROCESS = 0,
    WATCHDOG_PROCESS,
    USER_ERROR,
    WATCHDOG_ERROR
}who_am_i_t;

typedef struct watchdog_util_data
{
    char *who_am_i;
    who_am_i_t identity;
	const char *exe_full_path;
    char **args;
    pid_t pid_for_signals;
    time_t time_from_last_signal;
    int stop_watchdog_flag;
    scheduler_t *sched; 
    sem_t *sigaction_wd_process_semaphore;
    sem_t *sigaction_user_process_semaphore;
}watchdog_util_data_t;



 wd_sched_create_status_t CreateSchedWithTask(watchdog_util_data_t *tasks_data);

void ForcAndExec(watchdog_util_data_t *tasks_data);

int SendPulseTaskFunc(void * params);

int CheckStopFromOtherProcess(void *tasks_data);


int CheckTimeFromLastSignal(void *params);

int CheckStop(void *tasks_data);

char *PrintTime(char *time_string);

void AddWDProcessToArgv(char **argv, wd_argv_t *new_argv);

int WriteToLogger(int identity, const char *text, ...);



#endif /*__WATCHDOG_UTIL_H__*/





