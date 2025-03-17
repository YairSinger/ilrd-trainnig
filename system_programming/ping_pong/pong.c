
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

static volatile sig_atomic_t flag = 0;


static void handler(int signum)
{
	flag = 1;
	(void)signum;
}

static int Pong()
{
	
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

	while (counter < 5)
	{
		while (!flag)
		{
			pause();
		}
		printf("Child received SIGUSR1 - Ping %d\n", counter);
		flag = 0;

		kill(getppid(), SIGUSR2);

		++counter;
	}
	
	return 0;
}


int main()
{
	printf("Pong returned status is: %d\n", Pong());
	return 0;
}

