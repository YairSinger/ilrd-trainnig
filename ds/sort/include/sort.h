/***********************************************************
*PROJECT: sorting algorithems
*
*WRITER: Yair Singer
*
*REVIEWER: Zayd Abu Sneineh
*
*STATUS: resent
*
*DATE: 13/09/2023
***********************************************************/
/******************
* Version: 1.1 	  *
*******************/
#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>
#include "stack.h" /*stack_sort */
/*
@Description: Bubble sort implementation. 
@Parameters: 
             1. [arr] - Array to sort.
             2. [length] - Size of Array.
@Time Complexity: 
                    Best O(n)
                    Worst O(n^2)
*/
void BubbleSort(int arr[], size_t length);

/*
@Description: Generic Bubble sort implementation. 
@Parameters: 
             1. [arr] - Array of void Pointers.
             2. [elem_size] - Element SIze.
             3. [length] - Size of Array.
             4. [cmp_func] - cmp function for sorting. 
@Time Complexity: 
                    Best O(n)
                    Worst O(n^2)
*/
void GenericBubbleSort(void *arr, size_t elem_size, size_t length, int (*cmp_func)(const void *lhs, const void *rhs));

/*
@Description: Selection sort implementation. 
@Parameters: 
             1. [arr] - Array to sort.
             2. [length] - Size of Array.
@Time Complexity: 
                    Best O(n^2)
                    Worst O(n^2)
*/
void SelectionSort(int arr[], size_t length);

/*
@Description: Insertion sort implementation. 
@Parameters: 
             1. [arr] - Array to sort.
             2. [length] - Size of Array.
@Time Complexity: 
                    Best O(n)
                    Worst O(n^2)
*/
void InsertionSort(int arr[], size_t length);

/*
@Description: Counting sort implementation. 
@Parameters: 
             1. [arr] - Array to sort.
             2. [length] - Size of Array.
@Time Complexity: 
                    Best O(n+k) where k is the maximum value in arr.
                    Worst O(n+k) where k is the maximum value in arr.
*/
int CountingSort(int arr[], size_t length);

/*
@Description: Radix sort implementation. 
@Parameters: 
             1. [arr] - Array to sort.
             2. [length] - Size of Array.
@Time Complexity: 
                    Best O(n*d) where d is number of digits of the largest number in arr.
                    Worst O(n*d) where d is number of digits of the largest number in arr.
*/
int RadixSort(int arr[], size_t length);

/*
@Description: Merge sort implementation. 
@Parameters: 
             1. [arr_to_sort] - Array to sort.
             2. [num_elements] - Size of Array.
@Return value: 0 on success, 1 on failure (failed to allocate addition required space).             
@Time Complexity: 
                    Best O(nlog n)
                    Worst O(nlog n)
*/
int MergeSort(int *arr_to_sort, size_t num_elements);


/*
@Description: Sort an array using the Quicksort algorithm.
@Parameters: 
    1. [base] - Pointer to the first element of the array to be sorted.
    2. [nmemb] - Number of elements in the array.
    3. [size] Size in bytes of each element in the array.
    4. [compar] -   Pointer to a comparison function that takes two const void pointers as arguments and
                    returns an integer value less than, equal to, or greater than zero to indicate the
                    relative order of the two elements.
@Note: The `compar` function should be implemented such that it returns:
       - a negative value if the first element is less than the second element,
       - zero if the elements are equal, and
       - a positive value if the first element is greater than the second element.
@Time Complexity:   average and best-case O(n*log(n)), where 'n' is the number of elements.
                    worst case O(n^2).
@Space Complexity: O(log(n)).
*/
void QSort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

stack_t *SortStack(stack_t *unsorted);

/*
@Description: Heap sort implementation. 
@Parameters: 
             1. [arr] - Array to sort.
             2. [length] - Size of Array.
@Time Complexity: 
                    Best O(n * log(n))
                    Worst O(n * log(n))
*/

void HeapSort(int arr[], size_t length);
void QuickSortQuize(int *arr, size_t size);

#endif /* __SORT_H__ */
