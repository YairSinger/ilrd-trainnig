/*********************************
* Group: OL 149	 		 		 
* Project: multi thread count sort  	
* Version: 1.0.0   		 	
* Student: Yair singer   		
* Reviewer: Shahar Molina	 				 
* Status:   Approved			 		 
*						 		 
* Date: 	22.12.23      		 
**********************************/


#ifndef __MT_COUNT_SORT_H__
#define __MT_COUNT_SORT_H__

#include <stddef.h> /* size_t */



int MultiThreadsCountingSort(int *arr, size_t size, size_t num_of_threads);


/*int MultiThreadsCountingSort2(int *arr, size_t size, size_t num_of_threads);*/


int MultiThreadsCountingSortChars(char *arr, size_t size, size_t num_of_threads);


#endif /*__MT_COUNT_SORT_H__*/





