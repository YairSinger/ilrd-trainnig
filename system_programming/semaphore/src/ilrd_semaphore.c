/*********************************
* Group: OL 149	 		 		 *
* Project: Semaphore			 *
* Version: 1.0.0   		 		 *
* Student: Yair singer   		 *
* Reviewer: 	 				 *
* Status:   			 		 *
*						 		 *
* Date: 	4.12.23      		 *
**********************************/



#include <stdlib.h> /*malloc, strtod*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h> /* strstr, strcmp */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include "ilrd_semaphore.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"


static void ReciveInput(char *chr, int *num_to_change, int *is_undo);
static void ExitSemaphore(sem_t *sem, int undo_counter);


/**************************  API FUNCTIONS ******************************/

int ManipulateSemaphore(int argc, char **argv)
{
	char input_chr = '\0';
	int value = 0;
	int undo_counter = 0;
	int is_undo = 0;
	int sem_value = 0;
	sem_t *sem = NULL;
	
	sem = sem_open(argv[1], O_CREAT, 0666, 3);
	if (SEM_FAILED == sem)
	{
		printf("Error  sem_open\n");
		return -1;
	} 
		
	while ('X' !=  input_chr && 'T' != input_chr )
	{
		ReciveInput(&input_chr, &value, &is_undo);
				
		switch (input_chr)
		{
			case 'D':

				while (0 < value)
				{
					if (0 != sem_wait(sem))
					{
						printf("error decrease\n");
						sem_close(sem);
						return -1;
					}
					--value;
					if (is_undo)
					{
						++undo_counter;		
					}	
				}

				break;
			
			case 'I':
				while (0 < value)
				{
					if (0 != sem_post(sem))
					{
						printf("error increasing\n");
						sem_close(sem);
						return -1;
					}
					--value;
					if (is_undo)
					{
						--undo_counter;				
					}
				}

				break;
			
			case 'V':
				if (0 != sem_getvalue(sem, &sem_value))
				{
					printf("error semaphore getvalue\n");					
				}
				printf("Samphore value: %d\n", sem_value);
				break;
			default :
				printf("Invalid input\n");
			 	break;
		}
		
	}

	if('T' == input_chr)
	{
		if(0 != sem_unlink(argv[1]))
		{
			printf("error unlink\n");
		}
		else
		{
			printf("unlinking..\n");
		}
	}

	ExitSemaphore(sem, undo_counter);
	return 0;	
}



/**************************  STATIC FUNCTIONSS******************************/
static void ReciveInput(char *chr, int *num_to_change, int *is_undo)
{
	char input[20] = {'\0'};
	*chr = '\0';
	*num_to_change = 0;
	*is_undo = 0;
	
		printf("Enter  mode D, I, V, X ,T, num and [undo]\n");
		fgets(input,sizeof(char)*20, stdin);
		*(strchr(input, '\n')) = '\0';

		*chr = *input;
		if('D' == *chr || 'I' == *chr)
		{
			if (1 != sscanf(input + 1,"%d", num_to_change))
			{
				printf("error sscanf\n");
			}
			if (NULL != strstr(input,"undo"))
			{
				*is_undo = 1;
			}
		}
		else
		{
				*is_undo = 0;
		}
}



static void ExitSemaphore(sem_t *sem, int undo_counter)
{
	if(0 < undo_counter)
	{
		while (0 < undo_counter)
				{
					if (0 != sem_post(sem))
					{
						printf("error increasing\n");
						sem_close(sem);
						return;
					}
					--undo_counter;
				}

	}
	else if (0 > undo_counter)
	{
		while (0 < undo_counter)
				{
					if (0 != sem_wait(sem))
					{
						printf("error decrease\n");
						sem_close(sem);
						return;
					}
					--undo_counter;
				}
	}
	
	if (0 != sem_close(sem))
	{
		printf("failed to close\n"); 
		return;
	}
}
