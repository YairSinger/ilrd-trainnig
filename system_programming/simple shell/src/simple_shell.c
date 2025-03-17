#include <stddef.h>
#include <stdio.h>
#include <string.h> /*strncpy, strcmp */
#include <stdlib.h> /*malloc, free */
#include <sys/types.h> /*pid_t*/
#include <sys/wait.h> /*wait*/
#include <unistd.h>	/*fork*/

/*typedef int pid_t;*/

int RunSystemModeCommand(void)
{
	int status = 0;
	char command[100] ={'\0'};
	char *end = NULL;
	
	fgets(command, 100, stdin);
	end = strchr(command, '\n');
	*end = '\0';
	
	while(0 != strcmp(command,"exit") && -1 != status)
	{
		status = system(command);
		printf("System call exited with status %d\n", status);
		printf("please type desired shell command\n");
		fgets(command, 100, stdin);
		end = strchr(command, '\n');
		*end = '\0';
	}
	
	
	return status;
}

int RunForkModeCommand(void)
{
	pid_t pid = 0;
	int status = 0;
	char command[100] ={'\0'};
	char *end = NULL;
		
	fgets(command, 100, stdin);
	end = strchr(command, '\n');
	*end = '\0';
	
	while(0 != strcmp(command,"exit"))
	{
		pid = fork();
		printf("%s\n", command);
		
		if (-1 == pid)
		{
			printf("failed to fork\n");
			status = 1;
		}
				
		else if (0 == pid) /*the code the child process will see*/
		{
			execlp("/bin/sh", "sh", "-c", command, NULL);
			printf("Execution Failed\n");
			status = 1;
		}
		
		else /*parent process*/
		{
			waitpid(pid,&status, 0);
			printf("Child process exited with status %d\n", status);
		}
		
		printf("please type desired shell command\n");
		fgets(command, 100, stdin);
		end = strchr(command, '\n');
		*end = '\0';
	}
	return status;
}

int SimpleShell(int argc, char **argv)
{
	char mod[10] = {'\0'};
	int status = 0;
		
	if (NULL == argv[1])
	{
		
		return 1;
	}
	else
	{
		strncpy(mod, argv[1],10);	
	}

	printf("please type desired shell command\n");
	if (0 == strcmp(mod, "system"))
	{
		status = RunSystemModeCommand();
	}
	
	else if (0 == strcmp(mod, "fork"))
	{
		status = RunForkModeCommand();
	}
	
	 
  	return status;
}



int main(int argc, char **argv)
{
	
	return SimpleShell(argc, argv);	  
}

