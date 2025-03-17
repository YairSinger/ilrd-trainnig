/***********************************************************
*PROJECT: search algorithems
*
*WRITER: Yair Singer
*
*REVIEWER: Noam Lazar
*
*STATUS: Approved
*
*DATE: 1/10/2023
***********************************************************/
/******************
* Version: 1.0 	  *
*******************/
#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stddef.h>     /* size_t */
#include <sys/types.h>  /* ssize_t */

/*
 * Perform iterative binary search in a sorted array.
 *
 * @param arr[] The sorted integer array to search in.
 * @param length The number of elements in the array.
 * @param value_to_search The value to search for within the array.
 *
 * @return If the value is found, the function returns the index of the first occurrence. If not found, it returns -1.
 *
 * @time_complexity O(log(n)), where 'n' is the number of elements.
 *
 * @space_complexity O(1).
 *
 * @note The input array 'arr' must be sorted in ascending order for this function to work correctly.
 */
ssize_t BinarySearch(int arr[], size_t length, int value_to_search);

/*
 * Perform recursive binary search in a sorted array.
 *
 * @param arr[] The sorted integer array to search in.
 * @param length The number of elements in the array.
 * @param value_to_search The value to search for within the array.
 *
 * @return If the value is found, the function returns the index of the first occurrence. If not found, it returns -1.
 *
 * @time_complexity O(log(n)), where 'n' is the number of elements.
 *
 * @space_complexity O(log(n)), where 'n' is the number of elements.
 *
 * @note The input array 'arr' must be sorted in ascending order for this function to work correctly.
 */
ssize_t RecBinarySearch(int arr[], size_t length, int value_to_search);


/*
 * Perform iterative jump search in a sorted array.
 *
 * @param arr[] The sorted integer array to search in.
 * @param length The number of elements in the array.
 * @param value_to_search The value to search for within the array.
 *
 * @return If the value is found, the function returns the index of the first occurrence. If not found, it returns -1.
 *
 * @time_complexity O(sqrt(n)), where 'n' is the number of elements.
 *
 * @space_complexity O(1).
 *
 * @note The input array 'arr' must be sorted in ascending order for this function to work correctly.
 */
ssize_t JumpSearch(int arr[], size_t length, int value_to_search);

/*
 * Perform recursive jump search in a sorted array.
 *
 * @param arr[] The sorted integer array to search in.
 * @param length The number of elements in the array.
 * @param value_to_search The value to search for within the array.
 *
 * @return If the value is found, the function returns the index of the first occurrence. If not found, it returns -1.
 *
 * @time_complexity O(sqrt(n)), where 'n' is the number of elements.
 *
 * @space_complexity O(sqrt(n)), where 'n' is the number of elements.
 *
 * @note The input array 'arr' must be sorted in ascending order for this function to work correctly.
 */
ssize_t RecJumpSearch(int arr[], size_t length, int value_to_search);

#endif /*__SEARCH_H__*/
