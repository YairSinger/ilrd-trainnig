#include <assert.h>
#include <stddef.h> 	/* size_t 			*/
#include <stdlib.h> 	/* malloc 			*/
#include <assert.h> 
#include "sorted_list.h"

typedef int (*cmp_f)(const void *list_data, const void *user_data);

struct sorted_list
{
	dll_t *dll;
	cmp_f cmp;
};

#define SRT_ITER_LIST(srt_iter) srt_iter.srt_list
#define SRT_ITR_DLL_ITR(srt_iter) srt_iter.iter
#define IS_VALID_ITER_DEBUG(srt_iter) \
							!DllIsSameIter(srt_iter.iter, \
							DllEnd(srt_iter.srt_list->dll))\

/* ==============================================*/

sorted_list_t *SortedListCreate(int (*cmp_func)(const void *list_data, const void *user_data))
{
		sorted_list_t *sorted =(sorted_list_t *) malloc (sizeof(sorted_list_t));  
		if (NULL == sorted) 
		{
			return NULL;
		}
		
		sorted->dll = DllCreate();
		if (NULL == sorted->dll)
		{
			free(sorted);
			return NULL;
		}
		
		sorted->cmp = cmp_func;
		return sorted;
}
/* ==============================================*/

void SortedListDestroy(sorted_list_t *sorted_list)
{
	DllDestroy(sorted_list->dll);
	sorted_list->cmp = NULL;
	free(sorted_list);
}


/* ==============================================*/
sorted_list_iter_t SortedListInsert
								(sorted_list_t *sorted_list, const void *data)
{
		sorted_list_iter_t new = {0};
		new = SortedListFind((const sorted_list_t *)sorted_list, 
							SortedListBegin(sorted_list), 
							SortedListEnd(sorted_list), 
							data); 
		
		new.iter = DllInsert(sorted_list->dll, new.iter, data); /* הייתי מפרידה לשני איטרים, אחד לאיזה מיקום להכניס ואחד שהוא האיטר החדש..מבחינה לוגית */
		#ifndef NDEBUG
    	SRT_ITER_LIST(new) = sorted_list;
    	#endif
    	
		return new;
}
/* ==============================================*/

sorted_list_iter_t SortedListRemove(sorted_list_iter_t who)
{
	assert(IS_VALID_ITER_DEBUG(who));
	
	SRT_ITR_DLL_ITR(who) = DllRemove(SRT_ITR_DLL_ITR(who));
	return who;
}

/* ==============================================*/

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list); 
	return DllPopFront(sorted_list->dll);
}

/* ==============================================*/

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	return DllPopBack(sorted_list->dll);
}

/* ==============================================*/

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list); 
	return DllSize(sorted_list->dll);
}
/* ==============================================*/

void *SortedListGetData(const sorted_list_iter_t iter) 
{
	assert(IS_VALID_ITER_DEBUG(iter));
	
	return DllGetData(SRT_ITR_DLL_ITR(iter));
}

/* ==============================================*/

sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t begin = {0};
		
	assert(NULL != sorted_list);
	SRT_ITR_DLL_ITR(begin) = DllBegin(sorted_list->dll); 
	
	#ifndef NDEBUG
	 SRT_ITER_LIST(begin) = (sorted_list_t *) sorted_list;
	#endif
	
	return begin;
}
/* ==============================================*/
sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t end = {0};
		
	assert(NULL != sorted_list);
	
	SRT_ITR_DLL_ITR(end) = DllEnd(sorted_list->dll);
	
	#ifndef NDEBUG
	SRT_ITER_LIST(end) = (sorted_list_t *) sorted_list;
	#endif
	
	return end;
}
/* ==============================================*/
sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	sorted_list_iter_t prev = {0};
		
	assert(NULL != SRT_ITR_DLL_ITR(iter));
	
	SRT_ITR_DLL_ITR(prev) = DllPrev(SRT_ITR_DLL_ITR(iter)); 
	
	#ifndef NDEBUG
	SRT_ITER_LIST(prev) = SRT_ITER_LIST(iter);
	#endif
	
	return prev;
}
/* ==============================================*/	

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	sorted_list_iter_t next = {0};
		
	assert(IS_VALID_ITER_DEBUG(iter));
	
	SRT_ITR_DLL_ITR(next) = DllNext(SRT_ITR_DLL_ITR(iter));
	
	#ifndef NDEBUG
	SRT_ITER_LIST(next) = SRT_ITER_LIST(iter);
	#endif
	
	return next;

}	

/* ==============================================*/	
int SortedListIsSameIter(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	return DllIsSameIter(SRT_ITR_DLL_ITR(iter1),SRT_ITR_DLL_ITR(iter2));
}
/* ==============================================*/	

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(NULL != sorted_list);
	return DllIsEmpty(sorted_list->dll);
}
/* ==============================================*/	

sorted_list_iter_t SortedListFind(const sorted_list_t *sorted_list, sorted_list_iter_t from, sorted_list_iter_t to, const void *param)
{
	sorted_list_iter_t result = {0};
	
	
	assert(SRT_ITER_LIST(to) == SRT_ITER_LIST(to));
	
	
	
	result = from; 
	while(!SortedListIsSameIter(result , to)
	&& 0 >= (sorted_list->cmp(DllGetData(SRT_ITR_DLL_ITR(result)), param)))
	{
		result = SortedListNext(result);
	}
	
	
	
	return result;	
}

/* ==============================================*/	

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to, int (*is_match_func)(const void *data, const void *param), const void *param)
{ /* ASSERTS */

	assert(SRT_ITER_LIST(to) == SRT_ITER_LIST(from));
	
		
	

	SRT_ITR_DLL_ITR(from) = DllFind(SRT_ITR_DLL_ITR(from), SRT_ITR_DLL_ITR(to), is_match_func, param);
	return from;
}

/* ==============================================*/	

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_list_iter_t splice_where = {0};
	sorted_list_iter_t splice_to   = {0};
	
	splice_where = SortedListBegin(dest);
	while (!SortedListIsEmpty(src))
	{
		/*where to splice in dest */
		splice_where = SortedListFind(dest, splice_where, SortedListEnd(dest),
		SortedListGetData(SortedListBegin(src)));
		
		/*****************************************************
				two cases the second find call is irelevant
		******************************************************/
		
		/*if all src  is spliced after dest*/
		if (SortedListIsSameIter(splice_where, SortedListEnd(dest)))
		{
			DllSplice(SRT_ITR_DLL_ITR(splice_where), 
			SRT_ITR_DLL_ITR((SortedListBegin(src))), 
			SRT_ITR_DLL_ITR((SortedListEnd(src))));
		}
		
		/*if src ends after first valid node*/
		else if (SortedListIsSameIter(SortedListNext(SortedListBegin(src)),SortedListEnd(src)))
		{
			DllSplice(SRT_ITR_DLL_ITR(splice_where), 
			SRT_ITR_DLL_ITR((SortedListBegin(src))), 
			SRT_ITR_DLL_ITR(SortedListEnd(src)));
		}
		
		/* find exclusive node in src for the splice */
		 else
		 {
		 	splice_to = SortedListFind(src, SortedListNext(SortedListBegin(src)), SortedListEnd(src),
			SortedListGetData(splice_where));
		
			DllSplice(SRT_ITR_DLL_ITR(splice_where), 
			SRT_ITR_DLL_ITR(SortedListBegin(src)), 
			SRT_ITR_DLL_ITR(splice_to));
		}
				 
	}
}

int SortedListForEach(sorted_list_iter_t from, 
					  sorted_list_iter_t to, 
					  int (*action_func)(void *data, void *param), 
					  void *param)
{
	int status = 0;
		
	assert(!(SRT_ITER_LIST(to) != SRT_ITER_LIST(from)));	
	
	status = DllForEach(SRT_ITR_DLL_ITR(from), 
						SRT_ITR_DLL_ITR(to), 
						action_func, 
						param);
	return status;
}


