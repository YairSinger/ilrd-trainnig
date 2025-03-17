
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
	if (SIGUSR2 == signum)
	{
		flag = 1;
		(void)signum;
	}
}

int Ping()
{
	pid_t self = -1;
	pid_t ping = -1;
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

	if (-1 == sigaction(SIGUSR2, &sa, NULL))
	{
		fprintf(stderr, "Sigaction failed, error - %s\n", strerror(errno));
		return 1;
	}
	
	self = getpid();
	printf("Pong PID is: %d\n", self);
	printf("Please type Ping PID\n");
	scanf("%d",&ping);
	printf("Recieved Ping PID is: %d\n",ping);
	sleep(10);
	while (counter < 100)
	{
		kill(ping, SIGUSR1);
		while (!flag)
		{
			pause();
		}
		printf("Child received SIGUSR2 - Pong %d\n", counter);
		flag = 0;
		++counter;
	}
	kill(ping, SIGTERM);
    waitpid(ping, &status, 0);
    printf("ping process exited with: %d\n", status);
	

	return 0;
}

int main()
{
	printf("Pong have been called.\n");
	Ping();
	return 0;
}


