
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> /*wait*/
#include <errno.h>

static volatile sig_atomic_t flag = 0;

void handler(int signum)
{
	if (SIGUSR1 == signum)
	{
		flag = 1;
		(void)signum;
	}
}

int Ping()
{
	pid_t self = -1;
	pid_t pong = -1;
	struct sigaction sa = {0};
	
	int counter = 0;
	int status = 0;
	

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
	self = getpid();
	printf("Ping PID is: %d\n", self);
	printf("Please type Pong PID\n");
	scanf("%d",&pong);
	printf("Recieved Pong PID is: %d\n",pong);
	sleep(10);
	
	while (counter < 100)
	{
		while (!flag)
		{
			pause();
		}
		printf("Child received SIGUSR1 - Ping %d\n", counter);
		flag = 0;

		kill(pong, SIGUSR2);

		++counter;
	}
	kill(pong, SIGTERM);
	return 0;
}

int main()
{
	printf("Ping have been called.\n");
	Ping();
	return 0;
}


