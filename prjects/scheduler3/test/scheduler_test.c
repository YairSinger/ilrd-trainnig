#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include "scheduler.h"


#define PULSE_INTERVAL 4

int wd_proc_pulse = 0;


static int SendPulseTaskFunc(void *params)
{
	/*kill(pid, SIGUSR1)*/
	printf("pulse\n");
	return 0;
}



static int CheckFlagFunc(void * params)
{
	/*check flag*/
	printf("flag checked\n");
	return 0;
}



int WatchdogProcessFunc(void *param)
{
	/*struct sigaction sa = {0};*/
	scheduler_t *user_proc_sched = NULL;
	ilrd_uid_t send_pulse_uid = {0};
	ilrd_uid_t check_flag_uid = {0};
	int thread_status = 1;
	size_t i = 0;

	user_proc_sched = SchedCreate();

	if (NULL == user_proc_sched)
	{
		return -1;
	}

	send_pulse_uid = SchedAdd(user_proc_sched, PULSE_INTERVAL, 0,
                   SendPulseTaskFunc, NULL, NULL, NULL);
    if (UIDIsSame(send_pulse_uid, bad_uid))
	{
		printf("taskAdd failed\n");
	}

	check_flag_uid = SchedAdd(user_proc_sched, PULSE_INTERVAL, 2,
                   CheckFlagFunc, NULL, NULL, NULL);
    if (UIDIsSame(check_flag_uid, bad_uid))
	{
		printf("taskAdd failed\n");
	}

	SchedRun(user_proc_sched);
	
	return 0;
}



int main()
{
	void *test = NULL;
	WatchdogProcessFunc(test);
	return 0;
}
