
#include <stdio.h>
#include <string.h>
#include "simple_logger.h"


char *logger_name = NULL;

void LogSetLogName(char *log_name)
{
	logger_name = log_name;
}

void Log(char* writer_name, const char *message, va_list message_args)
{
	FILE *file = fopen(logger_name, "a+");
	pid_t self = getpid();

	time_t t;
    struct tm *tm_info;
    char *log_entry = NULL;
    char timestamp[20]; 
	char pid_str[20] = {'\0'};
	sprintf(pid_str,"PROCESS %s \0",self);
    time(&t);
    tm_info = localtime(&t);

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    if (NULL == file)
    {
        fprintf(stderr, "File open error\n");
        return FAIL;
    }


    log_entry = (char *)malloc(strlen(pid_str) + (writer_name) + (timestamp) + strlen(message) + 3);
    if (NULL == log_entry)
    {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return FAIL;
    }
    sprintf(log_entry, "%s:%s, %s %s\n", timestamp, pid_str, message);

    if (1 != fwrite(log_entry, strlen(log_entry), 1, file))
    {
        fprintf(stderr, "Error writing to file\n");
    }

    free(log_entry);
    log_entry = NULL;
    
    if (-1 == fclose(file))
    {
        fprintf(stderr, "Error closing file\n");
        return FAIL;
    }

    return SUCCESS;


}

