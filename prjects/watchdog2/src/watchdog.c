#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h> /*pthread create*/
#include <assert.h>
#include <string.h> /*strcmp*/
#include <time.h>
#include "watchdog.h"
#include "watchdog_util.h"



/************ global variables ***********************************************/
int wd_proc_pulse = 0;
pthread_t wd_thread = 0;
/*char *new_argv[4] = {NULL};*/
wd_argv_t new_argv = {0};
/*sem_t *sigaction_wd_process_semaphore = NULL;
sem_t *sigaction_user_process_semaphore = NULL;*/



/************* static variables ***********************************************/

static watchdog_util_data_t user_process_data = {0};



/************* static functions **********************************************/
static void SignalHandler(int signum);
static void *WatchdogThreadFunc(void *sched_ptr);
void SetWDUtilsInitSemaphores(void);
int SigActionSetUp(struct sigaction *sa);


/************ API function *****************************************************/

int WDStart(const char **path)
{
	size_t i = 0;
	int thread_status = 1;
	struct sigaction sa = {0};
	wd_sched_create_status_t sched_status = SCHED_CREATE_SUCCESS;
	pid_t self = getpid();
	char *time_string = NULL;
	
	WriteToLogger(USER_PROCESS, "%d - WDStart started by %d\n", self, getppid());	

	 
	
	SetWDUtilsInitSemaphores();

	/*AddWDProcessToArgv((char **)path, &new_argv);*/
	if (NULL == getenv(ENV_VAR_NAME)) 
    {
		printf("user init watchdog\n");
		WriteToLogger(USER_PROCESS, "%d user process is forking\n", self);
		ForcAndExec(&user_process_data);	
	    
    }
	else
	{
		user_process_data.pid_for_signals = getppid();
		printf("watchdog init user\n");
	}  


	
	if (SigActionSetUp(&sa))
	{
		return -1;
	}
	
	WriteToLogger(USER_PROCESS, "%d user process is forking\n", self);
	
	if (-1 == sem_post( user_process_data.sigaction_user_process_semaphore)) /*update wd_proc that sigaction is set*/ /*** move to before sem wait */
	{
		WriteToLogger(USER_ERROR, "pid %d  sem post failed, error - %s\n", self, strerror(errno));
		return -1;
	}

	if (SCHED_CREATE_SUCCESS !=  (sched_status = CreateSchedWithTask(&user_process_data)))
	{
		WriteToLogger(USER_ERROR, "pid %d  sem post failed, error - %s\n", self, strerror(errno));
		return -1;
	}
	
	thread_status = pthread_create(&wd_thread, NULL, WatchdogThreadFunc, (void *)&user_process_data);
	if(0 != thread_status)
	{
		WriteToLogger(USER_ERROR, "pid %d  user pthread_create failed, error - %s \n", self, strerror(errno));
		return -1;
	}
	
	return 0;
}


void WDStop(size_t timeout)
{
	clock_t start_time = clock();
    clock_t end_time = start_time + timeout * CLOCKS_PER_SEC;
	int status = 0;
	pid_t self = getpid();
	char *time_string = NULL;

	WriteToLogger(USER_PROCESS, "pid %d  start WDStop\n", self);	

	user_process_data.stop_watchdog_flag = 1;

    while (clock() < end_time)
	{
        kill(user_process_data.pid_for_signals, SIGUSR2);

    }
	WriteToLogger(USER_PROCESS, "pid %d SIGUSR2 timeout ended\n", self);

	SchedulerStop(user_process_data.sched); /*** can remove stop task cover it */
	WriteToLogger(USER_PROCESS, "pid %d  user scheduler stoped\n", self);	
	
	status = pthread_join(wd_thread, NULL);
	WriteToLogger(USER_PROCESS, "pid %d  watchdog thread pthread_join returned %d \n", self, status);
	
	if(0 != sem_close(user_process_data.sigaction_wd_process_semaphore))
	{
		WriteToLogger(USER_PROCESS, "pid %d sem close failed %s \n", self, strerror(errno));
	}
	if(0 != sem_close(user_process_data.sigaction_user_process_semaphore))
	{
		WriteToLogger(USER_PROCESS, "pid %d sem close failed %s \n", self, strerror(errno));
	}
	
	/*remove(logger_path);*/
	
}



static void SignalHandler(int signum)
{
	if(SIGUSR1 == signum)
	{
		user_process_data.time_from_last_signal = time(NULL);
	}

	else if (SIGUSR2 == signum)
	{
		user_process_data.stop_watchdog_flag = 1;
	}
}


static void *WatchdogThreadFunc(void *util_data)
{
	int status = 0;
	scheduler_t *sched = ((watchdog_util_data_t *)util_data)->sched;
	pid_t self = getpid();
	
	WriteToLogger(USER_PROCESS, "pid %d user process Watchdog thread started \n", self);	

	sem_wait(user_process_data.sigaction_wd_process_semaphore); /*wait for wd_process to set sigaction*/
	
	status = SchedulerRun(sched);
	WriteToLogger(USER_PROCESS, "pid %d user process Watchdog scheduler run returned %d\n", self, status);
	
	SchedulerDestroy(sched);
	WriteToLogger(USER_PROCESS, "pid %d user  Watchdog scheduler destroyed\n", self);
	return NULL;
}




void SetWDUtilsInitSemaphores(void) /***split two funcs */
{
	pid_t self = getpid();	

	
	user_process_data.who_am_i = forked_by_user;
	user_process_data.identity = USER_PROCESS;
	user_process_data.exe_full_path = WD_PROC_PATH;
	user_process_data.args = new_argv.new_argv;
	user_process_data.pid_for_signals = -1;
	user_process_data.time_from_last_signal = time(NULL);
	user_process_data.stop_watchdog_flag = 0;
	user_process_data.sched = NULL; 
	
	user_process_data.sigaction_wd_process_semaphore = sem_open("sigaction_wd_process_semaphore", O_CREAT, 0666, 0);
	if (SEM_FAILED == user_process_data.sigaction_wd_process_semaphore)
	{
		WriteToLogger(USER_ERROR, "pid %d  sem_open failed, error - %s\n", self, strerror(errno));
		return;
	} 

	user_process_data.sigaction_user_process_semaphore = sem_open("sigaction_user_process_semaphore", O_CREAT, 0666, 0);
	if (SEM_FAILED == user_process_data.sigaction_user_process_semaphore )
	{
		WriteToLogger(USER_ERROR, "pid %d  sem_open failed, error - %s\n", self, strerror(errno));
		return;
		}
		
}


int SigActionSetUp(struct sigaction *sa)
{
	pid_t self = getpid();

	sa->sa_handler = SignalHandler;
	sa->sa_flags = 0;

	if (-1 == sigaction(SIGUSR1, sa, NULL)) /*set pulse signal*/
	{
		WriteToLogger(USER_ERROR, "pid %d  Sigaction failed, error - %s\n", self, strerror(errno));
		return -1;
	}

	if (-1 == sigaction(SIGUSR2, sa, NULL)) /*set stop signal*/
	{
		WriteToLogger(USER_ERROR, "pid %d  Sigaction failed, error - %s\n", self, strerror(errno));
		return -1;
	}
	WriteToLogger(USER_PROCESS, "pid %d  user process sigactions is set\n", self, strerror(errno));
	
	return 0;
}