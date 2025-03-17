#include <stdio.h>
#include <errno.h> 
#include <signal.h>
#include <sys/types.h>
#include <string.h> /*strerror*/
#include <unistd.h>
#include <assert.h>
#include <stdarg.h>
#include "watchdog_util.h"
#include "uid.h"

#define RESET "\x1B[0m"
#define BLUE "\x1B[34m"
#define PURPLE "\x1B[35m"
#define RED "\x1B[31m"

 wd_sched_create_status_t CreateSchedWithTask(watchdog_util_data_t *tasks_data)
{
    scheduler_t *scheduler = SchedulerCreate(); /*** add destroy sched if somthing fail*/
    ilrd_uid_t bad_uid = GenerateBadUID();
    ilrd_uid_t task_uid = {0};
    wd_sched_create_status_t status = SCHED_CREATE_SUCCESS;
  	pid_t self = getpid();
    who_am_i_t valid_identity = USER_PROCESS;
    who_am_i_t error_identity = USER_ERROR;

    if (tasks_data->identity == WATCHDOG_PROCESS)
    {
        valid_identity = WATCHDOG_PROCESS;
        error_identity = WATCHDOG_ERROR;
    }
	
    if (NULL == scheduler)
    {
        WriteToLogger(error_identity, "pid %d  sched creation failed\n", self);
        status = SCHED_CREATE_ALLOC_FAIL;
    }

    task_uid = SchedulerAddTask(scheduler, SendPulseTaskFunc, (void *)tasks_data, 0,PULSE_INTERVAL);
    if (IsSameUID(task_uid, bad_uid))
    {
        WriteToLogger(error_identity, "pid %d  taskAdd failed\n", self);
        status = SCHED_CREATE_TASKS_INSERT_FAIL;
    }
    task_uid = SchedulerAddTask(scheduler, CheckTimeFromLastSignal, (void*)tasks_data, 7, MAX_TIME_FROM_LAST_SIGNAL);
    if (IsSameUID(task_uid, bad_uid))
    {
        WriteToLogger(error_identity, "pid %d  taskAdd failed\n", self);
        status = SCHED_CREATE_TASKS_INSERT_FAIL;
    }
    task_uid = SchedulerAddTask(scheduler, CheckStopFromOtherProcess, (void *)tasks_data, 5,CHECK_STOP);
    if (IsSameUID(task_uid, bad_uid))
    {
        WriteToLogger(error_identity, "pid %d  taskAdd failed\n", self);
        status = SCHED_CREATE_TASKS_INSERT_FAIL;
    }
      
	tasks_data->sched = scheduler;
    return status;
}

int SendPulseTaskFunc(void *tasks_data)
{
    pid_t pid = ((watchdog_util_data_t *)tasks_data)->pid_for_signals;
	kill(pid, SIGUSR1);
	return 1; /*for repeating task*/
}

int CheckTimeFromLastSignal(void *tasks_data)
{
    watchdog_util_data_t *utils = (watchdog_util_data_t *)tasks_data;
    time_t time_from_last_signal = utils->time_from_last_signal;
    pid_t pid = utils->pid_for_signals;
    pid_t self = getpid();
    who_am_i_t valid_identity = USER_PROCESS;
    who_am_i_t error_identity = USER_ERROR;

    if (utils->identity == WATCHDOG_PROCESS)
    {
        valid_identity = WATCHDOG_PROCESS;
        error_identity = WATCHDOG_ERROR;
    }

    if((time(NULL)- time_from_last_signal) > MAX_TIME_FROM_LAST_SIGNAL)
    {
        if (0 == strcmp(forked_by_user, utils->who_am_i))
        {
            sem_post(utils->sigaction_user_process_semaphore);
            *(utils->args[2]) = '0';
        }
        else
        {
            sem_post(utils->sigaction_wd_process_semaphore);
            *(utils->args[2]) = '1';
        }

        ForcAndExec(utils); /*** if fork failes... */
        WriteToLogger(valid_identity, "pid %d  forked %d\n", self, utils->pid_for_signals);
        while (time_from_last_signal == utils->time_from_last_signal); /*waiting for first signal from forked process*/      
    }
    else
    {
        /*printf("last signal from pid %d %lu[sec] ago\n", pid ,time(NULL)- time_from_last_signal);*/
    }
    return 1; /*for repeating task*/
}

int CheckStopFromOtherProcess(void *tasks_data)
{
	watchdog_util_data_t *util_data = (watchdog_util_data_t *)tasks_data;
    pid_t pid = util_data->pid_for_signals;
	pid_t self = getpid();
    who_am_i_t valid_identity = USER_PROCESS;
    who_am_i_t error_identity = USER_ERROR;

    if (util_data->identity == WATCHDOG_PROCESS)
    {
        valid_identity = WATCHDOG_PROCESS;
        error_identity = WATCHDOG_ERROR;
    }
	
    if (0 != util_data->stop_watchdog_flag)
    {
        WriteToLogger(valid_identity, " pid %d  stop flag has changed to %d\n", self, util_data->stop_watchdog_flag);        
        SchedulerStop(util_data->sched);
        kill(pid, SIGUSR2); /*** do wait_stop semphore*/
    }
   
	return 1; /*for repeating task*/
}

void ForcAndExec(watchdog_util_data_t *tasks_data) /*** what if fork fails?*/
{
    pid_t child_pid = fork();
	pid_t self = getpid();
	who_am_i_t valid_identity = USER_PROCESS;
    who_am_i_t error_identity = USER_ERROR;

    if (tasks_data->identity == WATCHDOG_PROCESS)
    {
        valid_identity = WATCHDOG_PROCESS;
        error_identity = WATCHDOG_ERROR;
    }

    if (child_pid < 0)
	{
	    WriteToLogger(error_identity, " pid %d  fork failed\n", self);   
        return;
	}
	else if (0 == child_pid) /*the code the child process will see*/
	{
        execv(tasks_data->exe_full_path, tasks_data->args);
		WriteToLogger(error_identity, " pid %d  execv failed returned %s\n", self, strerror(errno));
	}
    else
    {
        tasks_data->pid_for_signals = child_pid;
    }
}

void AddWDProcessToArgv(char **argv, wd_argv_t *new_argv)
{
	size_t len = 0;
	assert(NULL != argv);
	
	
		len = strlen(argv[0]);
		strncpy(new_argv->user_path,argv[0],len);
		new_argv->user_path[len] = '\0';
		new_argv->new_argv[0] = new_argv->user_path;

		len = strlen(WD_PROC_PATH);
		strncpy(new_argv->wd_path,WD_PROC_PATH,len);
		new_argv->wd_path[len] = '\0';
		new_argv->new_argv[1] = new_argv->wd_path;

	if ( '1' == *argv[2])
	{
		new_argv->new_argv[2] = new_argv->is_wd_parent;
        *new_argv->is_wd_parent = '1';	
	}
    else
    {
        new_argv->new_argv[2] = new_argv->is_wd_parent;
        *new_argv->is_wd_parent = '0';
    }
		

		new_argv->new_argv[3] = NULL;		
	
}


int WriteToLogger(int identity, const char *text, ...)
{
	va_list args;
	char buffer[256] = {'\0'};

	FILE *file = fopen(LOGGER_PATH, "a");
	if (NULL == file)
	{
		fprintf(stderr, "File open error\n");
		return -1;
	}

	va_start(args, text);
	vsprintf(buffer, text, args);

	if (identity == 0)
	{
		fprintf(file, BLUE "%s" RESET, buffer); /*User column in blue*/
	}
	else if (identity == 1)
	{
		fprintf(file, "\t\t\t\t\t\t\t\t" PURPLE "%s" RESET, buffer); /*Watchdog column in purple*/
	}
	else if (identity == 2)
	{
		fprintf(file, RED "%s" RESET, buffer); /*User error - user column in red*/
	}
	else if (identity == 3)
	{
		fprintf(file, "\t\t\t\t\t\t\t\t" RED "%s" RESET, buffer); /*Watchdog error - watchdog column in red*/
	}
	else
	{
		fprintf(file, "%s", buffer); /*Default column*/
	}

	va_end(args);

	if (-1 == fclose(file))
	{
		fprintf(stderr, "Error closing file\n");
		return -1;
	}
	return 0;
}