#include <stdio.h>
#include <errno.h> 
#include <signal.h>
#include <sys/types.h>
#include <string.h> /*strerror*/
#include <unistd.h>
#include <assert.h>
#include "watchdog_util.h"
#include "uid.h"



 wd_sched_create_status_t CreateSchedWithTask(watchdog_util_data_t *tasks_data)
{
    scheduler_t *scheduler = SchedulerCreate();
    ilrd_uid_t bad_uid = GenerateBadUID();
    ilrd_uid_t task_uid = {0};
    wd_sched_create_status_t status = SCHED_CREATE_SUCCESS;
    FILE * wd_logger;
	pid_t self = getpid();
	char *time_string = NULL;

    wd_logger = fopen(logger_path,"w");
	if (NULL == wd_logger)
	{
		fprintf(stderr, "logger creation failed, error - %s\n", strerror(errno));
		return -1;
	} 

    if (NULL == scheduler)
    {
        fprintf(wd_logger, "%s\t\t pid %d  sched creation failed\n", PrintTime(time_string), self);
        status = SCHED_CREATE_ALLOC_FAIL;
    }

    task_uid = SchedulerAddTask(scheduler, SendPulseTaskFunc, (void *)tasks_data, 0,PULSE_INTERVAL);
    if (IsSameUID(task_uid, bad_uid))
    {
        fprintf(wd_logger, "%s\t\t pid %d  taskAdd failed\n", PrintTime(time_string), self);
        status = SCHED_CREATE_TASKS_INSERT_FAIL;
    }
    task_uid = SchedulerAddTask(scheduler, CheckTimeFromLastSignal, (void*)tasks_data, 7, MAX_TIME_FROM_LAST_SIGNAL);
    if (IsSameUID(task_uid, bad_uid))
    {
        fprintf(wd_logger, "%s\t\t pid %d  taskAdd failed\n", PrintTime(time_string), self);
        status = SCHED_CREATE_TASKS_INSERT_FAIL;
    }
    task_uid = SchedulerAddTask(scheduler, CheckStopFromOtherProcess, (void *)tasks_data, 5,CHECK_STOP);
    if (IsSameUID(task_uid, bad_uid))
    {
        fprintf(wd_logger, "%s\t\t pid %d  taskAdd failed\n", PrintTime(time_string), self);
        status = SCHED_CREATE_TASKS_INSERT_FAIL;
    }
       
	tasks_data->sched = scheduler;
    fclose(wd_logger);
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
        printf("forking from %s while argc is %s\n", utils->who_am_i, utils->args[2]);
        ForcAndExec(utils);
        while (time_from_last_signal == utils->time_from_last_signal); /*waiting for first signal from forked process*/      
        printf("%s process continue to run after fork\n", utils->who_am_i);
    }
    else
    {
        printf("last signal from pid %d %lu[sec] ago\n", pid ,time(NULL)- time_from_last_signal);
    }
    return 1; /*for repeating task*/
}

int CheckStopFromOtherProcess(void *tasks_data)
{
	watchdog_util_data_t *util_data = (watchdog_util_data_t *)tasks_data;
    pid_t pid = util_data->pid_for_signals;
    FILE * wd_logger;
	pid_t self = getpid();
	char *time_string = NULL;

    wd_logger = fopen(logger_path,"a");
	if (NULL == wd_logger)
	{
		fprintf(stderr, "logger creation failed, error - %s\n", strerror(errno));
		return -1;
	} 

    if (0 != util_data->stop_watchdog_flag)
    {
        fprintf(wd_logger, "%s\t\t pid %d  stop flag is %d,changed by pid %d\n", PrintTime(time_string), 
                                        self, util_data->stop_watchdog_flag,  util_data->pid_for_signals);
        SchedulerStop(util_data->sched);
        kill(pid, SIGUSR2);
    }
    fclose(wd_logger);
	return 1; /*for repeating task*/
}

void ForcAndExec(watchdog_util_data_t *tasks_data)
{
    pid_t child_pid = fork();
    FILE * wd_logger;
	pid_t self = getpid();
	char *time_string = NULL;

     wd_logger = fopen(logger_path,"a");
	if (NULL == wd_logger)
	{
		fprintf(stderr, "logger creation failed, error - %s\n", strerror(errno));
		return;
	} 
    
    if (child_pid < 0)
	{
		  fprintf(wd_logger, "%s\t\t pid %d  fork failed\n", PrintTime(time_string), self);
		return;
	}
	else if (0 == child_pid) /*the code the child process will see*/
	{
		printf("path %s, arg[0] %s arg[1] %s, args[2] %s end \n", tasks_data->exe_full_path,tasks_data->args[0], tasks_data->args[1], tasks_data->args[2]);
        execv(tasks_data->exe_full_path, tasks_data->args);
		fprintf(wd_logger, "%s\t\t pid %d  execv failed returned %s\n", PrintTime(time_string), self, strerror(errno));
	}
    else
    {
        tasks_data->pid_for_signals = child_pid;
    }
    fclose(wd_logger);
}

char *PrintTime(char *time_string)
{
    time_t current_time;
   
    /* Obtain current time. */
    current_time = time(NULL);

    if (current_time == ((time_t)-1)) {
        fprintf(stderr, "Failure to obtain the current time.\n");
        return NULL;
    }

    /* Convert to local time format. */
    time_string = ctime(&current_time);

    if (time_string == NULL) {
        fprintf(stderr, "Failure to convert the current time.\n");
        return NULL;
    }
    return time_string;
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
