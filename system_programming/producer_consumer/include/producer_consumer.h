
/*********************************
* Group: OL 149	 		 		 *
* Project: watchdog         	 *
* Version: 1.0.0   		 		 *
* Student: Yair singer   		 *
* Reviewer: 	 				 *
* Status:   			 		 *
*						 		 *
* Date: 	12.12.23      		 *
**********************************/


#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include <stddef.h> /* size_t */
/*
*
* Watchdog capabilites:
*                        1. crashes handeling
* watchdog process requirements: 
*                        1. SIGUSR1 & SIGUSER2 should be handler free for all of the watchdog operation
*
*
**/



/**
 * @details starts watchdog operation, process crashes fault tolerance
 * @param path modified argv array where path[0] shold hold executable full path
 *        logger_filename a filename for the watchdog logger.
 * @return status 0 if succeded
 *                1 if failed to init watchdog action
 */
int WDStart(const char **path, const char *logger_filename);


/**
 * @details stops watchdog oparation
 * @param timeout waiting time to kill watchdog befure rusuming to program.
 * @return non
void WDStop(size_t timeout);





#endif /*__WATCHDOG_H__*/
