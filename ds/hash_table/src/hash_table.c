/***********************************************************
*PROJECT:Hashtable
*
*WRITER: Yair Singer
*
*REVIEWER: Liad Atsmon
*
*STATUS: Approved
*
*DATE: 1/10/23
***********************************************************/



#include <assert.h> /*assert */
#include <stdlib.h> /*strtod */
#include <string.h> /*strlen */
#include "hash_table.h" /*API functions */
#include "dll.h" /*	*/

#define UNUSED(x) (void)x

struct hashtable
{
	size_t m_num_of_buckets;
	size_t (*m_hash_func)(const void *key);
	int (*m_is_key_match)(const void *lhs, const void *rhs);
	dll_t **m_hashtable;
};

typedef struct is_match_wrapper
{
	void *user_key;
	hashtable_t *hashtable;
}is_match_wrapper_t;

typedef struct action_wrapper
{
	void *action_param;
	action_func ac_func;
}action_wrapper_t;


typedef struct key_value_pair
{
	void *m_key;
	void *m_value;
}key_value_pair_t;


/***************** static functions ****************************/

static int FreePair(void *key_value_pair, void *param)
{
	UNUSED(param);
	free(key_value_pair);
	return 0;
}

static int IsMatchWrapper(const void *data, const void *param)
{
	void *user_key = ((is_match_wrapper_t *)param)->user_key;
	void *node_key = ((key_value_pair_t*)data)->m_key;
	hashtable_t *hash = ((is_match_wrapper_t *)param)->hashtable;
	
	return hash->m_is_key_match(node_key,user_key);
}

static int ActionWrapper(void *data, void *param)
{
	void *action_param = ((action_wrapper_t *)param)->action_param;
	void *node_data = ((key_value_pair_t*)data)->m_value;
	action_func action_func = ((action_wrapper_t *)param)->ac_func;
	
	return action_func(node_data,action_param);
}



/**======================   API FUNCTIONS   ===============================**/

/*******   HashtableCreate   ***********/


hashtable_t *HashtableCreate(size_t (*hash_func)(const void *key),
                              int (*is_key_match)(const void *lhs, const void *rhs),
                              size_t num_of_buckets)
{
	hashtable_t *hashtable = (hashtable_t *)malloc(sizeof(hashtable_t));
	int bucket_i = 0;
	
	assert(NULL != hash_func);
	assert(NULL != is_key_match);
	assert(0 != num_of_buckets);
	
	if (NULL == hashtable)
	{
		return NULL;
	}
	
	hashtable->m_num_of_buckets = num_of_buckets;
	hashtable->m_hash_func = hash_func;
	hashtable->m_is_key_match = is_key_match;
	hashtable->m_hashtable = (dll_t **)malloc(sizeof(dll_t *) * num_of_buckets);
	
	if (NULL == hashtable->m_hashtable)
	{
		free(hashtable);
		return NULL;
	}
	for (bucket_i = 0; bucket_i < (int)num_of_buckets; ++bucket_i)
	{
		hashtable->m_hashtable[bucket_i] = DllCreate();
		if (NULL == hashtable->m_hashtable[bucket_i])
		{
			break;
		}
	}
	
	if (bucket_i != (int)num_of_buckets)
	{
		for (bucket_i = 0; bucket_i < (int)num_of_buckets; ++bucket_i)
		{
			DllDestroy(hashtable->m_hashtable[bucket_i]);
		}
		
		free(hashtable->m_hashtable);
		free(hashtable);
		return NULL;
	}
	
	return hashtable;
}



/*******   HashtableDestroy   ***********/
				
				
void HashtableDestroy(hashtable_t *hashtable)
{
	size_t bucket_i = 0;
	void *param = NULL;
	
	assert(NULL != hashtable);
	
	for (bucket_i = 0; bucket_i < hashtable->m_num_of_buckets; ++bucket_i)
	{
		/*free key_value_pair in list first */
		DllForEach(DllBegin(hashtable->m_hashtable[bucket_i]), 
							DllEnd(hashtable->m_hashtable[bucket_i]), 
							FreePair, param);
		DllDestroy(hashtable->m_hashtable[bucket_i]);
		hashtable->m_hashtable[bucket_i] = NULL;
	}
	
	free(hashtable->m_hashtable);
	memset(hashtable, 0, sizeof(hashtable_t));
	free(hashtable);
	hashtable = NULL;
}


/*******   HashtableInsert   ***********/

int HashtableInsert(hashtable_t *hashtable, const void *key, void* data)
{
	size_t bucket_i = 0;
	
	dll_iter_t insert_iter = {0};
	key_value_pair_t *new_pair = NULL;
	
	assert(NULL != hashtable);
	assert(NULL != key);
	
	new_pair = (key_value_pair_t *)malloc(sizeof(key_value_pair_t));

	if (NULL == new_pair)
	{
		return 1;
	}
		
	new_pair->m_key = (void *)key;
	new_pair->m_value = data;
	
	bucket_i = hashtable->m_hash_func(key);
	insert_iter = DllPushFront(hashtable->m_hashtable[bucket_i], (const void *)new_pair);
	if (DllIsSameIter(insert_iter, DllEnd(hashtable->m_hashtable[bucket_i])))
	{
		free(new_pair);
		return 1;
	}
	
	return 0;	
}


/*******   HashtableRemove   ***********/


void HashtableRemove(hashtable_t *hashtable, const void *key)
{
	dll_iter_t from = {0};
	dll_iter_t to = {0};
	is_match_wrapper_t wrapped = {0};
	size_t bucket_i = 0;
		
	assert(NULL != hashtable);
	assert(NULL != key);
	
	bucket_i = hashtable->m_hash_func(key);
	from = DllBegin(hashtable->m_hashtable[bucket_i]);
	to = DllEnd(hashtable->m_hashtable[bucket_i]);
	
	wrapped.user_key = (void *)key;
	wrapped.hashtable = (hashtable_t *)hashtable;
	
	from = DllFind(from, to, IsMatchWrapper, (void *)&wrapped);
	
	if (!DllIsSameIter(from,to))
	{
		FreePair(DllGetData(from), (void *)bucket_i);		
		DllRemove(from);
	}
}
	


/*******   HashtableIsEmpty   ***********/
				

int HashtableIsEmpty(const hashtable_t *hashtable)
{
	size_t bucket_i = 0;
	
	assert(NULL != hashtable);
	
	for (bucket_i = 0; (bucket_i < hashtable->m_num_of_buckets) && 
								(DllIsEmpty(hashtable->m_hashtable[bucket_i])); ++bucket_i)
	{
		/*empty loop*/
	}
	
	return bucket_i == hashtable->m_num_of_buckets;
}

/*******   HashtableCountSize   ***********/
				
size_t HashtableCountSize(const hashtable_t *hashtable)
{
	size_t count = 0;
	size_t bucket_i = 0;
	
	assert(NULL != hashtable);
	
	for (bucket_i = 0; bucket_i < hashtable->m_num_of_buckets; ++bucket_i)
	{
		count += DllSize(hashtable->m_hashtable[bucket_i]);
	}
	
	return count;
}


/*******   HashtableFind   ***********/
				
				
void *HashtableFind(const hashtable_t *hashtable, const void *key)
{
	dll_iter_t from = {0};
	dll_iter_t to = {0};
	is_match_wrapper_t wrapped = {0};
	size_t bucket_i = 0;
		
	assert(NULL != hashtable);
	assert(NULL != key);
	
	bucket_i = hashtable->m_hash_func(key);
	from = DllBegin(hashtable->m_hashtable[bucket_i]);
	to = DllEnd(hashtable->m_hashtable[bucket_i]);
	
	wrapped.user_key = (void *)key;
	wrapped.hashtable = (hashtable_t *)hashtable;
	
	from = DllFind(from, to, IsMatchWrapper, (void *) &wrapped);	
	if (!DllIsSameIter(from,to))
	{
		return ((key_value_pair_t *)(DllGetData(from)))->m_value; 
	}
	else
	{
		return NULL;
	}	
}

/*******   HashtableForEach   ***********/


int HashtableForEach(hashtable_t *hashtable, 
					int (*action_func)(void *data, void *param), 
					void *action_param)
{
	size_t bucket_i = 0;
	int status = 0;
	dll_iter_t runner = {0};
	dll_iter_t end = {0};
	action_wrapper_t ac_wrap = {0};
	
	assert(NULL != hashtable);
	assert(NULL != action_func);
	
	ac_wrap.action_param = action_param;
	ac_wrap.ac_func = action_func;
	
	for (bucket_i = 0; 0 == status && bucket_i < hashtable->m_num_of_buckets; ++bucket_i)
	{
		runner = DllBegin(hashtable->m_hashtable[bucket_i]);
		end = DllEnd(hashtable->m_hashtable[bucket_i]);
		
		status = DllForEach(runner,end, &ActionWrapper, (const void *)&ac_wrap);
	}
	
	return status;
}

