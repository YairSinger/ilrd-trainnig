
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#include "ping_pong.h"

static volatile sig_atomic_t flag = 0;
static volatile sig_atomic_t flag2 = 0;

void handler(int signum)
{
	flag = 1;
	(void)signum;
}

int PingPong(void)
{
	pid_t child_pid = -1;
	struct sigaction sa = {0};
	int counter = 0;
	
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (-1 == sigemptyset(&sa.sa_mask))
	{
		fprintf(stderr, "Sigemptyset failed, error - %s\n", strerror(errno));
		return 1;
	}

	if (-1 == sigaction(SIGUSR1, &sa, NULL))
	{
		fprintf(stderr, "Sigaction failed, error - %s\n", strerror(errno));
		return 1;
	}

	if (-1 == sigaction(SIGUSR2, &sa, NULL))
	{
		fprintf(stderr, "Sigaction failed, error - %s\n", strerror(errno));
		return 1;
	}

	child_pid = fork();

	if (child_pid < 0)
	{
		fprintf(stderr, "Fork failed, error - %s\n", strerror(errno));
		return 1;
	}
	else if (child_pid == 0)
	{
		
		while (1)/*counter < 3*/
		{
			sleep(3);
			while (!flag)
			{
				pause();
			}
			printf("Child received SIGUSR1 - Ping %d\n", counter);
			flag = 0;

			kill(getppid(), SIGUSR2);

			++counter;
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		int counter = 0;
		while (1) /*counter < 3*/
		{
			printf("PID %d", child_pid);
			sleep(3);
			kill(child_pid, SIGUSR1);

			while (!flag)
			{
				pause();
			}

			printf("Parent received SIGUSR2 - Pong %d\n", counter);
			flag = 0;
			++counter;
		}
	}

	return 0;
}


