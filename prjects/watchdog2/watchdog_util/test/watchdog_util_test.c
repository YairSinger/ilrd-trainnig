
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>

#include "watchdog_util.h"
#define UNUSED (void)



wd_argv_t new_argv = {0};
static watchdog_util_data_t wd_process_data = {0};
char *new_arg[4] = {NULL};

static void SignalHandler(int signum)
{
	if(SIGUSR1 == signum)
	{
		wd_process_data.time_from_last_signal = time(NULL);
	}
	else if (SIGUSR2 == signum)
	{
		wd_process_data.stop_watchdog_flag = 1;
		kill(wd_process_data.pid_for_signals, SIGUSR2);
	}
}

static int AddEnvVar(void);


int main(int argc, char **argv)
{
	wd_sched_create_status_t sched_status = SCHED_CREATE_SUCCESS;
	pid_t self = getpid();
	int status = 0;
	struct sigaction sa = {0};
	
	UNUSED(argc);
	WriteToLogger(WATCHDOG_PROCESS, "pid %d  watchdog process started\n", self);
	AddWDProcessToArgv(argv, &new_argv);
	if (0 != AddEnvVar())
	{
		WriteToLogger(WATCHDOG_PROCESS, "pid %d  AddEnvVar failed. %S\n", self, strerror(errno));
	}
	
	wd_process_data.identity = WATCHDOG_PROCESS;
	wd_process_data.who_am_i = forked_by_wd;
	wd_process_data.time_from_last_signal = time(NULL);
	wd_process_data.pid_for_signals = getppid();
	wd_process_data.exe_full_path = argv[0];/*new_argv.new_argv[0];*/
	wd_process_data.args = argv;/*new_argv.new_argv;*/
	wd_process_data.time_from_last_signal = time(NULL);
	wd_process_data.stop_watchdog_flag = 0;
	wd_process_data.sigaction_wd_process_semaphore = sem_open("sigaction_wd_process_semaphore", O_CREAT, 0666, 0);

	
	if (SEM_FAILED == wd_process_data.sigaction_wd_process_semaphore)
	{
		WriteToLogger(WATCHDOG_ERROR, "pid %d  watchdog process sem_open failed, error - %s\n", self, strerror(errno));
		return -1;
	} 

	wd_process_data.sigaction_user_process_semaphore = sem_open("sigaction_user_process_semaphore", O_CREAT, 0666, 0);
	if (SEM_FAILED == wd_process_data.sigaction_user_process_semaphore)
	{
		WriteToLogger(WATCHDOG_ERROR, "pid %d  watchdog process sem_open failed, error - %s\n", self, strerror(errno));
		return -1;
	} 
	
	if (SCHED_CREATE_SUCCESS != (sched_status = CreateSchedWithTask(&wd_process_data)))
	{
		WriteToLogger(WATCHDOG_ERROR, "pid %d  watchdog process CreateSchedWithTask failed returned %d\n", self, sched_status);
		return -1;
	}

	sa.sa_handler = SignalHandler;
	sa.sa_flags = 0;

	if (-1 == sigaction(SIGUSR1, &sa, NULL))
	{
		WriteToLogger(WATCHDOG_ERROR, "pid %d  watchdog process Sigaction failed, error - %s\n", self, strerror(errno));
		return -1;
	}
	if (-1 == sigaction(SIGUSR2, &sa, NULL))
	{
		WriteToLogger(WATCHDOG_ERROR, "pid %d  watchdog process Sigaction failed, error - %s\n", self, strerror(errno));
		return -1;
	}
	WriteToLogger(WATCHDOG_PROCESS, "pid %d watchdog process sigaction is set\n", self);
	sem_post(wd_process_data.sigaction_wd_process_semaphore);
	sem_wait(wd_process_data.sigaction_user_process_semaphore);/*waiting for user process to set his signal hendler*/
	
	WriteToLogger(WATCHDOG_PROCESS, "pid %d watchdog process Schedrun starts\n", self);
	status = SchedulerRun(wd_process_data.sched);
	WriteToLogger(WATCHDOG_PROCESS, "pid %d  watchdog process SchedulerRun returned %d\n", self, status);
	SchedulerDestroy(wd_process_data.sched);
	WriteToLogger(WATCHDOG_PROCESS, "pid %d  watchdog process scheduler destroyed %d\n", self);

	return 0;
}

static int AddEnvVar(void)
{
    char pid_str[20];

    snprintf(pid_str, sizeof(pid_str), "%d", getpid());

    return setenv(ENV_VAR_NAME, pid_str, 1);
}




