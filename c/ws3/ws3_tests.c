#include <stdio.h>  /*printf*/
#include <stdlib.h>
#include "ws3.h"



void SumMatrixRowsTest();
void lastOneStandingTest();
void PrintTypes();
void CopyEnvLocalTest(char **envp);
void JosephusTest();

int main(int argc, char **argv, char **envp)
{
	
  /*	SumMatrixRowsTest();
	lastOneStandingTest();*/
	JosephusTest();
/*	PrintTypes();
	CopyEnvLocalTest(envp);*/
  
  	return 0;
}




void SumMatrixRowsTest()
{
	int *arr[4] = {0};
	int results[4] = {0};
	int i, j;
	
	for (i = 0; 4 > i; i++)
	{
		arr[i] =(int *)calloc(4, sizeof(int));
		for (j = 0; 4 > j ;j++)
		{
			*(*(arr+i)+j) = (i + j/2);
		}
	}
	
	for (i = 0; 4 > i; i++)
	{
		for (j = 0; 4 > j ;j++)
		{
			printf(" %d ", *(arr[i]+j));
		}
		
		printf("\n");
	}
		
	SumMatrixRows(arr, 4, 4, results);
	
	
	for (i = 0; 4 > i; i++)
	{
		printf("first row sum %d\n" , results[i]);
		free(arr[i]);
		arr[i] = 0;
	}
}

void lastOneStandingTest()
{
	int soldires = 26;
	
	printf("from %d soldiers,starting at the first soldier,\nthe  index of the last soldier is %d\n", soldires, lastOneStanding(soldires));
	

}

void JosephusTest()
{
	int soldiers[4] = {5, 10, 26, 40};
	int exp_results[4] = {4, 6, 22, 18};
	int cal_results[4] = {0};
	size_t i = 0;
	int fails = 0;
	
	for (i = 0; i < 4; ++i)
	{
		cal_results[i] = Josephus(soldiers[i]);
		if(exp_results[i] != cal_results[i])
		{
			++fails;
			printf("Failed in %d soldiers %d vs %d expected.\n", soldiers[i],cal_results[i],exp_results[i]);
		}
	}
	
	if(0 == fails)
	{
		printf("Josephus Passed\n");
	}
}

void PrintTypes()
{
 
	 printf("size of  char is %lu\n", sizeof(char));
	 printf("size of  signed char is %lu\n", sizeof(signed char));
	 printf("size of  unsigned char is %lu\n", sizeof(unsigned char));
	 printf("size of  short int is %lu\n", sizeof(short int));
	 printf("size of  int is %lu\n", sizeof(int));
	 printf("size of  long int is %lu\n", sizeof(long int));
	 printf("size of  signed short int is %lu\n", sizeof(signed short int));
	 printf("size of  unsigned short int is %lu\n", sizeof(unsigned short int));
	 printf("size of  signed int is %lu\n", sizeof(signed int));
	 printf("size of  unsigned int is %lu\n", sizeof(unsigned int));
	 printf("size of  signed long int is %lu\n", sizeof(signed long int));
	 printf("size of  unsigned long int is %lu\n", sizeof(unsigned long int));
	 
 	
 }
 
 void CopyEnvLocalTest(char **envp)
 {
 	PrintAllEnv(envp);
 	
 }
