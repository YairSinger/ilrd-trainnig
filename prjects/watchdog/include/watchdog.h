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

* This Watchdog Library is a powerful tool designed to ensure the smooth operation of your system’s processes.  
* One of the key features of the Watchdog Library API is its fault tolerance. 
* It constantly monitors the state of your processes and can handle crashes seamlessly, maintaining the stability of your system. 
* In the event of a process crash or Watchdog crash , the API takes restars the crushing process.
* Moreover, the Watchdog Library API comes with embedded logger, self erased after succsessful run. 
* This feature records the library’s operations, providing valuable insights into system performance and aiding in troubleshooting. 
*
* Watchdog capabilites:
*                        1. crash handeling.
                         2. thread safe.
* Watchdog process requirements: 
*                        1. SIGUSR1 & SIGUSER2 should not be used by the process while watchdog operation is active.
*
*
**/



/**
 * @description: Initiates watchdog monitoring. From this point forward, the process is equipped to handle and recover from crashes.
 * @param path NULL terminated array of strings. First argument is excecutable full path, add argv arguments at the next array arguments.   
 * @return status 0 if succeeded initiat monitoring.
 *                none zero if failed to init watchdog action.
 */
int WDStart(const char **path);


/**
 * @details Stops watchdog oparation/
 * @param timeout waiting time to kill watchdog befure rusuming to program.
 * @return */
void WDStop(size_t timeout);





#endif /*__WATCHDOG_H__*/
