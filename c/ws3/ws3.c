/***************************************************************
*PROJECT: ws3 pointers
*WRITER: Yair Singer
*REVIEWER: Yizhar Dahan
*DATE: 9/7/23
*STATUS: approved
*
****************************************************************/

#include "ws3.h"
#include <stddef.h> /* NULL*/
#include <assert.h>
#include <stdlib.h> /*malloc*/
#include <string.h> /*tolower */
#include <ctype.h>/*tolower */
#include <stdio.h> /*printf*/

void SumMatrixRows(int **matrix,int row_num, int col_num, int row_results[])
{
	int i = 0, j = 0;
	
	for (i = 0; row_num > i; i++)
	{
		for (j = 0 ;col_num >j ; j++)
		{
			row_results[i] += *(*(matrix+i)+j);
		}
	
	}
	
}


int lastOneStanding(int n)
{
	int *sword = (int*)malloc(sizeof(int)*n);
	int killed = 0;
	int i = 0; 
	int flag = 1; /* 1 = kill, 0 = pass*/
	
	for (i = 0; i < n; i++)
	{
		sword[i] = 1;
	}

	i= 1 ;
	while (killed < n-1)
	{
		
			if (1 == flag && 1 == sword[i])
			{
				sword[i] = 0;
				killed++;
				flag = 0;
			}
			else if (0 == flag && 1 == sword[i])
			{
				flag = 1;				
			}
		
		i = (i+1) % n;
	}
	
	


	
	for (i = 0; 0 == sword[i]; i++)
	{
		/* finds return index*/
	}
	free(sword);
	
	return i;
}

int CountEnvElemnts(char **envp)
{
	int count = 0;
	assert(NULL != envp);
	
	for (count = 0;NULL != envp[count]; ++count)
	{
	/*empty loop */
	}
	return count;
	
}

int Josephus (int n)
{
	int *circle = (int *)malloc(sizeof(int) * n);
	int i = 0;
	int sword_i = 0;
	
	for (i = 0; i < n ; ++i) 
	{
		circle[i] = i + 1;		
	}
	
	circle[i] = 0;
	
	while (circle[sword_i] != sword_i)
	{
		circle[sword_i] = circle[circle[sword_i]];
		sword_i = circle[sword_i];
	}
	
	free(circle);
	return sword_i;
}

int CountChars(char *str)
{
	int count = 0;
	assert(NULL != str);
	
	for (count = 0;'\0' != str[count]; count++)
	{
	/*empty loop*/
	}
	return count;
}



void PrintAllEnv(char **envp)
{
	int num_of_env_var = 0;
	int i = 0, j = 0;
	int num_of_chars = 0;
	char ** lowered_env;
	
	assert(NULL != envp);
	
 	num_of_env_var = CountEnvElemnts(envp);
 	printf("%d\n" ,num_of_env_var);
	lowered_env = (char**) malloc((sizeof(char*) * num_of_env_var+1));
	if(NULL == lowered_env)
			{
				return;
			}
	
	
	
	for (i = 0; i < num_of_env_var ; ++i)
	{
		num_of_chars = (strlen(envp[i])+1);
		
		lowered_env[i] = (char *) malloc((sizeof(char) * num_of_chars)+1); 
			
			if(NULL == lowered_env[i])
			{
				return;
			}
		strcpy(lowered_env[i],envp[i]);
			for (j = 0; '\0' != envp[i][j]; j++)
			{
				lowered_env[i][j] = tolower(lowered_env[i][j]);
			}
			
			lowered_env[i][j] = '\0';
			
	}
	
	for (i = 0; i < num_of_env_var; i++)
	{
		printf("\n%s\n" , lowered_env[i]);
		free(lowered_env[i]);
	}
}
/*
	
			*/



	
	
	
	
	
	
	
	
	
	
	
	
	



