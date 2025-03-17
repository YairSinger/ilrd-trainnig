/*********************************
* Group: OL 149	 		 		 *
* Project: simple_logger       	 *
* Version: 1.0.0   		 		 *
* Student: Yair singer   		 *
* Reviewer: 	 				 *
* Status:   			 		 *
*						 		 *
* Date: 	              		 *
**********************************/


#ifndef __SIMPLE_LOGGER_H__
#define __SIMPLE_LOGGER_H__

#include <stddef.h> /* size_t */
#include<stdarg.h> /*va_list*/

void LogSetLogName(char *log_name);

void Log(char* writer_name, const char *message, va_list message_args);





#endif /*__SIMPLE_LOGGER_H__*/
