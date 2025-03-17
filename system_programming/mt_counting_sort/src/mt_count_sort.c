/*********************************
* Group: OL 149	 		 	            	 *
* Project: multi threaded counting sort      *
* Version: 1.0.0   		             		 *
* Student: Yair singer                 		 *
* Reviewer: Shahr Molina            		 *
* Status:   Approved	             		 *
*						             		 *
* Date: 	21.12.23      	            	 *
**********************************/
#define _POSIX_C_SOURCE 199309L /*pid_t*/
#include <stdlib.h> /*malloc, */
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h> /* strstr, strcmp */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>
#include "mt_count_sort.h"


#define NUM_OF_THREADS 3
#define CHARS_IN_ASCII 256
#define ABS_MIN_CHAR_VALUE 128


static int *arr_input = NULL;
static int *arrays_sizes = NULL;
static char *arr_input_char = NULL;

/*typedef struct sorting_input
{
    size_t *arr_ptr;
    size_t length;
    size_t *sorted_arr;
    size_t thread_inx;
    pthread_t tid
}sorting_input_t;*/

typedef struct thread_data
{
    pthread_t tid;
    size_t thread_inx;
    size_t start_inx;/* data */
    size_t end_inx;    
    int *thread_sorted;
}thread_data_t;

typedef struct thread_data_comp
{
    pthread_t tid;
    size_t **arr_ptr; /*pointer to words*/
    size_t thread_inx;
    size_t start_inx;/* data */
    size_t end_inx;    
}thread_data_comp_t;


typedef struct thread_data_char
{
    pthread_t tid;
    size_t thread_inx;
    size_t start_inx;/* data */
    size_t end_inx;    
    size_t *thread_count;
    char *thread_sorted;
}thread_data_char_t;

static void *CountingSort(void *thread_data);
static int FindMinAndMax(int *arr, size_t size, int *min,int *max);
static int* Merge(int* arr1, size_t size1, int* arr2, size_t size2);
static int* MergeMultiple(int** arrays, int* sizes, int num_arrays); 
static void SetHistogramandComulative(int *count, thread_data_t *data , int min, int range);
static void *InsertionSort(void *thread_data);
int CompWords(size_t *word1, size_t *word2);


static void *CountingSortChar(void *thread_data);

static char* MergeChar(char* arr1, size_t size1, char* arr2, size_t size2); 
static void *CountingSortChar(void *thread_data);
static char* MergeMultipleChar(char** arrays, size_t* sizes, int num_arrays);
static void *CountingSort(void *thread_data);

void JoinHistograms(thread_data_t **thread_data, size_t num_of_threads, int *main_histogram);




/************************** API functions **************/

int MultiThreadsCompSort(size_t **arr, size_t size, size_t num_of_threads)
{
	size_t i = 0;
    thread_data_comp_t *thread_data = (thread_data_comp_t *)malloc(sizeof(thread_data_comp_t) * num_of_threads);
	int status = 0;
    size_t **threads_arrays = NULL;
	
    int *sorted = NULL;

    assert(NULL != arr);
    
    if (NULL == thread_data)
    {
        return -1;
    }
    threads_arrays = (size_t **)malloc(sizeof(size_t *) * num_of_threads);
    if (NULL == threads_arrays)
    {
        free(thread_data);
        return -1;
    }
    arrays_sizes = (int *)malloc(sizeof(int) * num_of_threads);
    if(NULL == arrays_sizes)
    {
        free(threads_arrays);
        free(thread_data);
        return -1;
    }
	
	for (i = 0; i < num_of_threads; ++i)
	{
		
        thread_data[i].thread_inx = i;
        thread_data[i].start_inx = i * (size / num_of_threads);
        thread_data[i].end_inx = (1 + i) * (size / num_of_threads);  
        thread_data[i].arr_ptr = arr;
        
		if (0 != (status = pthread_create(&(thread_data[i].tid), NULL, InsertionSort, &thread_data[i])))
        {
            return -1;
            /*print error*/
        }
        threads_arrays[i] = thread_data[i].arr_ptr[thread_data[i].start_inx];
        arrays_sizes[i] = thread_data[i].end_inx - thread_data[i].start_inx;			
	}



	for (i = 0; i < num_of_threads; ++i)
	{
		pthread_join(thread_data[i].tid, NULL); /*TODO status check*/
	}

	/*merging all sorted elements*/
  
   /*sorted = MergeMultiple(threads_arrays, arrays_sizes, num_of_threads);*/
    free(threads_arrays);
    free(thread_data);
    free(arrays_sizes);
    return 0;
}


int MultiThreadsCountingSort(int *arr, size_t size, size_t num_of_threads)
{
	size_t i = 0;
    thread_data_t *thread_data = (thread_data_t *)malloc(sizeof(thread_data_t) * num_of_threads);
	int status = 0;
    int **threads_arrays = NULL;
	
    int *sorted = NULL;

    assert(NULL != arr);
    arr_input = arr;
    if (NULL == thread_data)
    {
        return -1;
    }
    threads_arrays = (int **)malloc(sizeof(int *) * num_of_threads);
    if (NULL == threads_arrays)
    {
        free(thread_data);
        return -1;
    }
    arrays_sizes = (int *)malloc(sizeof(int) * num_of_threads);
    if(NULL == arrays_sizes)
    {
        free(threads_arrays);
        free(thread_data);
        return -1;
    }
	
	for (i = 0; i < num_of_threads; ++i)
	{
		
        thread_data[i].thread_inx = i;
        thread_data[i].start_inx = i * (size / num_of_threads);
        thread_data[i].end_inx = (1 + i) * (size / num_of_threads);  
        
        thread_data[i].thread_sorted = (int *)malloc((thread_data[i].end_inx -  thread_data[i].start_inx + 1) * sizeof(int));    
        if (NULL == thread_data[i].thread_sorted)
        {
            return -1;
            /*print error*/
        }

		if (0 != (status = pthread_create(&(thread_data[i].tid), NULL, CountingSort, &thread_data[i])))
        {
            return -1;
            /*print error*/
        }
        threads_arrays[i] = arr_input + thread_data[i].start_inx;
        arrays_sizes[i] = thread_data[i].end_inx - thread_data[i].start_inx;			
	}



	for (i = 0; i < num_of_threads; ++i)
	{
		pthread_join(thread_data[i].tid, NULL); /*TODO status check*/
	}

	/*merging all sorted elements*/
  
   sorted = MergeMultiple(threads_arrays, arrays_sizes, num_of_threads);
    free(threads_arrays);
    free(thread_data);
    free(arrays_sizes);
    return NULL == sorted;
}


int MultiThreadsCountingSortChars(char *arr, size_t size, size_t num_of_threads)
{
    size_t i = 0;
    thread_data_char_t *thread_data = (thread_data_char_t *)malloc(sizeof(thread_data_char_t) * num_of_threads);
	int status = 0;
    char **threads_arrays = NULL;
	size_t *sizes = NULL;
    char *sorted = NULL;

    assert(NULL != arr);
    arr_input_char = arr;
    if (NULL == thread_data)
    {
        return -1;
    }
    threads_arrays = (char **)malloc(sizeof(char *) * num_of_threads);
    if (NULL == threads_arrays)
    {
        free(thread_data);
        return -1;
    }
    sizes = (size_t *)malloc(sizeof(size_t) * num_of_threads);
    if(NULL == sizes)
    {
        free(threads_arrays);
        free(thread_data);
        return -1;
    }
	
	for (i = 0; i < num_of_threads; ++i)
	{
		
        thread_data[i].thread_inx = i;
        thread_data[i].start_inx = i * (size / num_of_threads);
        if (num_of_threads - 1 == i)
        {
            thread_data[i].end_inx = size;    
        }
        else
        {
            thread_data[i].end_inx = (1 + i) * (size / num_of_threads);
        }
        thread_data[i].thread_count = NULL;
        thread_data[i].thread_sorted = NULL;
        threads_arrays[i] = arr_input_char + thread_data[i].start_inx;
        sizes[i] = thread_data[i].end_inx - thread_data[i].start_inx;
		if (0 != (status = pthread_create(&(thread_data[i].tid), NULL, CountingSortChar, &thread_data[i])))
        {
            return -1;
            /*print error*/
        }
    }


	for (i = 0; i < num_of_threads; ++i)
	{
		pthread_join(thread_data[i].tid, NULL); /*TODO status check*/
	}

	/*merging all sorted elements*/
  
   sorted = MergeMultipleChar(threads_arrays, sizes, num_of_threads);
    free(threads_arrays);
    free(thread_data);
    free(sizes);
    return NULL == sorted;
}

/************************** Static  functions **************/

int CompWords(size_t *word1, size_t *word2)
{
    return strcmp((char *)word1, (char *) word2);
}

static void *InsertionSort(void *thread_data)
{
    thread_data_comp_t *data = (thread_data_comp_t *)thread_data;
	size_t sorted_size = 1;
    size_t **arr = data->arr_ptr;
    size_t length = data->end_inx - data->start_inx + 1;
	size_t *swap_temp = 0;
	size_t i = 0;

    assert(NULL != thread_data);

	for(sorted_size = 1; sorted_size < length; ++sorted_size)
	{		
		if ( 0 > CompWords(arr[sorted_size], arr[sorted_size - 1]))
		{
			i = (sorted_size - 1);
			swap_temp = arr[sorted_size];
			while(0 > CompWords(arr[i] , swap_temp))
			{
				arr[i + 1] = arr[i];
				--i;
			}
			arr[i + 1] = swap_temp;
		}
	}

}



static void *CountingSortChar(void *thread_data)
{
	thread_data_char_t *data = (thread_data_char_t *)thread_data;
	size_t i = 0;

    assert(NULL != data);

    
    data->thread_count = (size_t *)calloc(CHARS_IN_ASCII + 1, sizeof(size_t));
    if(NULL == data->thread_count)
    {
        return NULL;
    }
    data->thread_sorted = (char *)malloc((data->end_inx -  data->start_inx + 1) * sizeof(char));
    if (NULL == data->thread_sorted)
    {
        return NULL;
        /*print error*/
    }
	
	for(i = data->start_inx; i < data->end_inx; ++i) /*	histogram of values */
	{
		data->thread_count[(int)arr_input_char[i] + ABS_MIN_CHAR_VALUE] += 1;
	}
	
	for(i = 1; i < ((size_t)CHARS_IN_ASCII + 1); ++i) /*	comulative histogram of values */
	{
		data->thread_count[i] += data->thread_count[i - 1] ;
	}
	
	for(i = (data->end_inx - 1); i >= data->start_inx && i < data->end_inx; --i)
	{
		data->thread_sorted[data->thread_count[(int)arr_input_char[i] + ABS_MIN_CHAR_VALUE] - 1] = arr_input_char[i];
		data->thread_count[(size_t)arr_input_char[i] + ABS_MIN_CHAR_VALUE] -= 1;	
	}   
	
	for(i = data->start_inx; i < data->end_inx; ++i)
	{
		arr_input_char[i] = data->thread_sorted[i - data->start_inx];
	}
	
	free(data->thread_sorted);
	data->thread_sorted = NULL;
	
	free(data->thread_count);
    data->thread_count = NULL;
	return NULL;
}

static int FindMinAndMax(int *arr, size_t size, int *min,int *max)
{
    size_t i = 0; 
    *min = arr[0];
    *max = arr[0];
    for (i = 0; i < size; ++i)
    {
        if (arr[i] < *min)
        {
            *min = arr[i]; 
        }
        if (arr[i] > *max)
        {
            *max = arr[i];
        } 
    }
    return *max - *min;
}

static void SetHistogramandComulative(int *count, thread_data_t *data , int min, int range)
{
    size_t i = 0;

    for(i = data->start_inx; i < data->end_inx; ++i) /*	histogram of values */ /***move to set_histogram_func*/
	{
		count[arr_input[i] - min] += 1;
	}

    for(i = 1; i < ((size_t)range + 1); ++i) /*	comulative histogram of values */
	{
		count[i] += count[i - 1] ;
	}

}

static void *CountingSort(void *thread_data)
{
	thread_data_t *data = (thread_data_t *)thread_data;
	size_t i = 0;
    int *count = NULL;
    int min = 0, max = 0, range = 0; /*** change range to size_t*/
	assert(NULL != data);

    range = FindMinAndMax(arr_input + data->start_inx,data->end_inx - data->start_inx , &min, &max);
    count = (int *)calloc(range + 1, sizeof(int));
    if(NULL == count)
    {
        return NULL;
    }
    
	
	SetHistogramandComulative(count, data , min, range);
	
	for(i = (data->end_inx - 1); i >= data->start_inx && i < data->end_inx; --i)
	{
		data->thread_sorted[count[arr_input[i] - min] - 1] = arr_input[i];
		count[arr_input[i] - min] -= 1;	
	}   
	
	for(i = data->start_inx; i < data->end_inx; ++i)
	{
		arr_input[i] = data->thread_sorted[i - data->start_inx];
	}
	
	free(data->thread_sorted);
	data->thread_sorted = NULL;
	
	free(count);
	return NULL;
}


static int* Merge(int* arr1, size_t size1, int* arr2, size_t size2) 
{
    int* merged = malloc((size1 + size2) * sizeof(int));
    size_t i = 0, j = 0, k = 0;

    if (NULL == merged)
    {
        return NULL;
    }
    /*Merge arrays*/
    while (i < size1 && j < size2)
    {
        if (arr1[i] < arr2[j]) {
            merged[k++] = arr1[i++];
        }
        else
        {
            merged[k++] = arr2[j++];
        }
    }

    /*Copy remaining elements*/
    while (i < size1) 
    {
        merged[k++] = arr1[i++];
    }
    while (j < size2) 
    {
        merged[k++] = arr2[j++];
    }

    for (i = 0; i < size1 + size2; ++i)
    {
        arr1[i] = merged[i];
    }

    free(merged);
    return arr1;
}

static int* MergeMultiple(int** arrays, int* sizes, int num_arrays) 
{
    int* merged = arrays[0];
    int *new_merged = NULL;
    int merged_size = sizes[0];
    int i = 0;

    for (i = 1; i < num_arrays; i++) {
        new_merged = Merge(merged, merged_size, arrays[i], sizes[i]);
        if (NULL == new_merged)
        {
            return NULL;
        }
        merged = new_merged;
        merged_size += sizes[i];
    }

    return merged;
}

static char* MergeChar(char* arr1, size_t size1, char* arr2, size_t size2) 
{
    char *merged = malloc((size1 + size2) * sizeof(char));
    size_t i = 0, j = 0, k = 0;

    if (NULL == merged)
    {
        return NULL;
    }
    /*Merge arrays*/
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }

    /*Copy remaining elements*/
    while (i < size1) {
        merged[k++] = arr1[i++];
    }
    while (j < size2) {
        merged[k++] = arr2[j++];
    }

    for (i = 0; i < size1 + size2; ++i)
    {
        arr1[i] = merged[i];
    }

    free(merged);
    return arr1;
}

static char* MergeMultipleChar(char** arrays, size_t* sizes, int num_arrays) 
{
    char* merged = arrays[0];
    char *new_merged = NULL;
    int merged_size = sizes[0];
    int i = 0;

    for (i = 1; i < num_arrays; i++) {
        new_merged = MergeChar(merged, merged_size, arrays[i], sizes[i]);
        if (NULL == new_merged)
        {
            return NULL;
        }
        merged = new_merged;
        merged_size += sizes[i];
    }

    return merged;
}

