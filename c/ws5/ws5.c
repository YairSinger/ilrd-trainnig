/***********************************************************
*PROJECT: Files
*
*WRITER: Yair Singer
*
*REVIEWER: Avi Gueta
*
*STATUS: Approved
*
*DATE: 16.7.23
***********************************************************/
#include "ws5.h"
#include <stdio.h> 	/* printf */
#include <string.h> /*strcmp */

#define BUFFER_SIZE 100
#define ESC 27



enum status 
{
	before_perform = 1, 
	Success = 0, 
	init_fail = -3,
	OpenFileError =-4,
	DeleteFileError = -5,
	ExitCall = -6
};

typedef void (*print_int)(int);
typedef int (*compare_p)(const char *s1, const char *s2);
typedef int (*operator_p)(char* file_name, char * str);

typedef struct p_print_me
{
	int content;
	print_int p;
}print_me_t;

int ReturnZero(const char *s1, const char *s2)
{
	enum status st = Success;
	UNUSED(s1);
	UNUSED(s2);
	return st;
}
int  CountLinesInFile(char* file_name, char * str)
{
	enum status st = Success;
	FILE *fp;
	int count = 0;
	char c = '\0'; 
	UNUSED(str);
	
    fp = fopen(file_name, "r");
 
    if (fp == NULL)
    {
    	st = OpenFileError;
		return st;
	}
	
	for(c = fgetc(fp); EOF != c; c = fgetc(fp))
	{
		if ('\n' == c)
		{
			++count;
		}
	}
	
	printf("The file %s contains %d lines of data\n", file_name, count);
	fclose(fp);
	return st;
}

int RemoveFile(char* file_name, char * str)
{
	enum status st = Success;
	int result = 1; 
	UNUSED(str);
	result = remove(file_name);
	 if (0 == result)
	 {
	 	printf("Removed successfully!\n");
	 	return st;
	 }
	 else
	 {
	 	st = DeleteFileError;
	 	return st;
	 }
}
int CompChr(const char *s1, const char *s2)
{
	return (*s1-*s2);
}

int ExitLogger (char* file_name, char * str)
{
	enum status st = Success;
	UNUSED (file_name);
	UNUSED (str);
	st = ExitCall;
	return st;
}
	
typedef struct logger_flags
{
	char *str;
	compare_p cmp;
	operator_p op_p;
}log_flag_t;

void Print(int n)
{
	printf("%d\n", n);
}


void Print10Structs()
{
	int i = 0;
	print_me_t ptint_arr[10] = {0};	


	
	for (i = 0; i < 10 ; i++)
	{
		 ptint_arr[i].content = i;
		 ptint_arr[i].p = &Print;
	}
	
	for (i = 0; i < 10 ; i++)
	{
		 ptint_arr[i].p(ptint_arr[i].content);
		 
	}
	
}

	
	
 

int AppendStringToLogger(char* file_name, char * str)
{
	FILE * fp;
	enum status st = Success;		
	fp = fopen(file_name, "a");
	if (NULL == fp)
	{
		st = OpenFileError;	
		return st;
	}
		
	fputs(str,fp);
	printf("A string was appended to Logger\n");
	fclose(fp);
		
	return st;
}

int PrependStringToLooger(char* file_name, char * str)
{
	enum status st = Success;
	char *temp = "temp file";
	char c = '\0';

	FILE * fp;
	FILE * temp_p;
	
	++str; /*skipping "<" char */
	AppendStringToLogger(temp, str);
	fp = fopen(file_name, "r");
	
	if (NULL == fp)
	{
		rename(temp, file_name);	
		return st;
	}
	
	temp_p = fopen(temp, "a");
	
	if (NULL == temp_p)
	{	
		st = OpenFileError;	
		return st;
		
	}
	c = fgetc(fp);
	
	for(; c != EOF;)
		{
			fputc(c, temp_p);
			c = fgetc(fp);
		}
		
	fclose(fp);
	fclose(temp_p);
	rename(temp, file_name);
	return st;
}

int InitFlags(struct logger_flags log_f[5])
{
	log_f[0].str = "-remove\n";
	log_f[0].cmp = &strcmp;
	log_f[0].op_p = &RemoveFile;
	
	log_f[1].str = "-count\n";
	log_f[1].cmp = &strcmp;
	log_f[1].op_p = &CountLinesInFile;
	
	log_f[2].str = "-exit\n";
	log_f[2].cmp = &strcmp;
	log_f[2].op_p = &ExitLogger;
	
	log_f[3].str = "<";
	log_f[3].cmp = &CompChr;
	log_f[3].op_p = &PrependStringToLooger; 
	
	log_f[4].str =  "\n";
	log_f[4].cmp = &ReturnZero;
	log_f[4].op_p = &AppendStringToLogger;
	
	return 0;
}
int InputManeger(char* file_name, char *input)
{
	enum status st = Success;
	enum status result = before_perform;
	int i = 0;	
	static log_flag_t log_f[5] = {0};
	static int is_flags_init = 0;
	
	if (is_flags_init == 0)
	{
		if (0 != InitFlags(log_f) )
		{
			st = init_fail;
			return st;
		}
		is_flags_init = 1;
	}	
	
	for (i = 0, result = before_perform ; i < 5 && before_perform == result; ++i)
	{
		if (0 == log_f[i].cmp(log_f[i].str, input))
		{
			result = log_f[i].op_p(file_name, input);
		}
	}
	
	if (before_perform != result)
	{	
		return result;
	}
	else
	{
		return st;
	}
}


void Logger(char* file_name)
{
	
	char input[BUFFER_SIZE] = {0};
	int result = 0;
	if (NULL == file_name)
	{
		printf("Please enter a file name with program\n");
	}
	
	
	while (0 == result)
	{
		printf("enter string\n");
		fgets(input, BUFFER_SIZE, stdin);
		result = InputManeger(file_name, input);
	}
	 
	 switch(result)
	 {
	 	case init_fail:
	 	printf("could not initialize flags\n"); 
	 	break;
	 	case OpenFileError:
	 	printf("file name could not open\n"); 
	 	break;
	 	case DeleteFileError:
	 	printf("failed to delete file\n"); 
	 	break;
	 	case ExitCall:
	 	printf("exit logger\n"); 
	 	return;
	 	
	 }
}

	

	
