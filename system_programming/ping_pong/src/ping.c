
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
	pid_t child_pid = -1;
	struct sigaction sa = {0};
	char *path = "/home/yair/git2/yair.singer/system_programming/ping_pong/bin/debug/pong.out";
	char* argv[] = {"/home/yair/git2/yair.singer/system_programming/ping_pong/bin/debug/pong.out", NULL};
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

	child_pid = fork();

	if (child_pid < 0)
	{
		fprintf(stderr, "Fork failed, error - %s\n", strerror(errno));
		return 1;
	}
	else if (child_pid == 0)
	{
		if (-1 == execvp(path, argv))
		{
			printf("Execution Failed\n");
			return 1;	
		}
	}
	else
	{
			sleep(1);
		while (counter < 5)
		{
			kill(child_pid, SIGUSR1);

			while (!flag)
			{
				pause();
			}

			printf("Parent received SIGUSR2 - Pong %d\n", counter);
			flag = 0;
			++counter;
		}
		kill(child_pid, SIGTERM);
        waitpid(child_pid, &status, 0);
        printf("Child process exited with: %d\n", status);
	}

	return 0;
}

int main()
{
	printf("Ping have been called.\n");
	Ping();
	return 0;
}


