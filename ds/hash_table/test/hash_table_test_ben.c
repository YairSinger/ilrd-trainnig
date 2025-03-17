#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hash_table.h"

#define NUM_OF_LETTERS 26
#define MAX_STR_LEN 14
#define STR_ARR_SIZE 500

/******************************/
/*     printing utilities     */
/******************************/
#define GOOD "\033[1;30m\033[102m"
#define BAD "\033[1;37m\033[41m"
#define REG "\033[1;0m""\n"
#define HEAD "\033[1;30m\033[47m"
#define SUB_HEAD "\033[1;30m\033[43m"

#define HEADER_LEN 24

#define PRINT_REG(x) printf("%s"REG, MP(x))
#define PRINT_HEADER(x) printf(HEAD"%s"REG, MP(x))
#define PRINT_SUCCESS printf(GOOD"%s"REG, MP("SUCCESS"))


static char *MP(char *str)
{
	char *spaces = "                                    ";
	size_t num_of_spaces = (HEADER_LEN - strlen(str)) / 2;
	
	static char pretty_str[HEADER_LEN] = {0};
	
	assert(HEADER_LEN > strlen(str));
	
	*pretty_str = '\0';
	
	strncat(pretty_str, spaces, num_of_spaces);
	strncat(pretty_str, str, strlen(str));
	strncat(pretty_str, spaces, num_of_spaces);
	
	if (strlen(pretty_str) < HEADER_LEN)
	{
		strcat(pretty_str, " ");
	}
	
	return pretty_str;
}
/*****************************/
/* end of printing utilities */
/*****************************/



int IsMatchStrings(const void *iter_key, const void *key_to_cmp)
{
	int cmp_status = 0;
	
	cmp_status = strcmp((char *)key_to_cmp, (char *)iter_key);
	
	return (0 == cmp_status) ? (1) : (0);
}

/************/

size_t HashWords(const void *key)
{
	char first_letter = *(char *)key;
	
	return (size_t)(toupper(first_letter) - 'A');
}

/************/

char GetRandomLetter(void)
{
	return 'a' + rand() % NUM_OF_LETTERS;
}

/************/

size_t GetRandomLen(void)
{
	return 1 + rand() % (MAX_STR_LEN - 1);
}

/************/

char *GetRandomString(void)
{
	size_t str_len = GetRandomLen();
	
	char *random_str = (char *)malloc(str_len + 1);
	
	char *str_runner = random_str;
	char *end_address = random_str + str_len;
	
	while (str_runner < end_address)
	{
		*str_runner = GetRandomLetter();
		++str_runner;
	}
	
	*str_runner = '\0';
	
	return random_str;
}

/************/

char **GetRandomStringArr(void)
{
	size_t i = 0;
	size_t j = 0;
	
	char *generated_str = NULL;
	char **str_arr = (char **)malloc(STR_ARR_SIZE * sizeof(char *));
	
	while (i < STR_ARR_SIZE)
	{
		generated_str = GetRandomString();
		
		for (j = 0; j < i; ++j)
		{
			if (0 == strcmp(generated_str, str_arr[j]))
			{
				free(generated_str);
				generated_str = GetRandomString();
				j = 0;
			}
		}
		
		str_arr[i] = generated_str;
		
		++i;
	}
	
	return str_arr;
}

/************/

char *GetUpperCaseStr(char *str)
{
	size_t i = 0;
	
	size_t str_len = strlen(str);
	char *up_str = (char *)malloc((str_len + 1) * sizeof(char));
	
	while (i < str_len)
	{
		up_str[i] = toupper(str[i]);
		++i;
	}
	
	up_str[i] = '\0';
	
	return up_str;
}

/************/

void FreeArrayOfStrings(char **str_arr)
{
	size_t i = 0;
	
	while (i < STR_ARR_SIZE)
	{
		free(str_arr[i]);
		++i;
	}
	
	free(str_arr);
}

/************/

char **GetUpperCaseStringArr(char **str_arr)
{
	size_t i = 0;
	
	char **up_str_arr = (char **)malloc((STR_ARR_SIZE + 1) * sizeof(char *));
	
	while (i < STR_ARR_SIZE)
	{
		up_str_arr[i] = GetUpperCaseStr(str_arr[i]);
		++i;
	}
	
	up_str_arr[i] = '\0';
	
	return up_str_arr;
}

/************/

char *CpyString(char *str)
{
	size_t i = 0;
	
	size_t str_len = strlen(str);
	char *cpy_str = (char *)malloc((str_len + 1) * sizeof(char));
	
	while (i < str_len)
	{
		cpy_str[i] = str[i];
		++i;
	}
	
	cpy_str[i] = '\0';
	
	return cpy_str;
}

/************/

char **CpyStringArr(char **str_arr)
{
	size_t i = 0;
	
	char **cpy_str_arr = (char **)malloc((STR_ARR_SIZE + 1) * sizeof(char *));
	
	while (i < STR_ARR_SIZE)
	{
		cpy_str_arr[i] = CpyString(str_arr[i]);
		++i;
	}
	
	cpy_str_arr[i] = '\0';
	
	return cpy_str_arr;
}

/************/

void TestInsert(hashtable_t *hashtable, char **value_arr, char **key_arr)
{
	size_t i = 0;
	size_t size_before = 0;
	size_t size_after = 0;
	int was_error = 0;

	char char_buffer[MAX_STR_LEN + 1] = {0};
	char *found_value_str = char_buffer;
	
	PRINT_HEADER("TestInsert");
	
	while (i < STR_ARR_SIZE)
	{
		size_before = HashtableCountSize(hashtable);
		
		if (0 != HashtableInsert(hashtable, key_arr[i], value_arr[i]))
		{
			printf(BAD"[HashtableInsert] returned nonzero status"REG);
			++was_error;
		}
		
		size_after = HashtableCountSize(hashtable);
		
		if (size_before + 1 != size_after)
		{
			printf(BAD"[HashtableCountSize]: size before = %lu | size after = %lu"REG, size_before, size_after);
			++was_error;
		}
		
		found_value_str = (char *)HashtableFind(hashtable, key_arr[i]);
		
		if (0 != strcmp(found_value_str, value_arr[i]))
		{
			printf(BAD"[HashtableFind] wrong value for key"REG);
			printf(BAD"key = %s"REG, key_arr[i]);
			printf(BAD"expected value = %s"REG, value_arr[i]);
			printf(BAD"returned value = %s"REG, found_value_str);
			++was_error;
		}
				
		++i;
	}
	
	if (0 == was_error)
	{
		PRINT_SUCCESS;
	}
}

int ModifyFirstLetter(void *lhs, void *rhs)
{
	char *string = (char *)lhs;
	char new_first_letter = *(char *)rhs;
	
	*string = new_first_letter;
	
	return 0;
}

void TestForEach(hashtable_t *hashtable, char **value_arr, char **key_arr)
{
	size_t i = 0;
	size_t size_before = HashtableCountSize(hashtable);
	size_t size_after = 0;
	
	char **value_arr_cpy = CpyStringArr(value_arr);
	
	char new_first_letter = 'Q';

	int was_error = 0;

	char char_buffer[MAX_STR_LEN + 1] = {0};
	char *found_value_str = char_buffer;
	
	PRINT_HEADER("TestForEach");
	
	for (i = 0; i < MAX_STR_LEN; ++i)
	{
		ModifyFirstLetter(value_arr_cpy[i], &new_first_letter);
	}
	
	HashtableForEach(hashtable, ModifyFirstLetter, &new_first_letter);
	
	size_after = HashtableCountSize(hashtable);
	
	for (i = 0; i < MAX_STR_LEN; ++i)
	{
		if (size_before != size_after)
		{
			printf(BAD"[HashtableCountSize]: size before = %lu | size after = %lu"REG, size_before, size_after);
			++was_error;
		}
		
		found_value_str = (char *)HashtableFind(hashtable, key_arr[i]);
		
		if (0 != strcmp(found_value_str, value_arr_cpy[i]))
		{
			printf(BAD"[HashtableFind] wrong value for key"REG);
			printf(BAD"key = %s"REG, key_arr[i]);
			printf(BAD"expected value = %s"REG, value_arr_cpy[i]);
			printf(BAD"returned value = %s"REG, found_value_str);
			++was_error;
		}
				
		++i;
	}
	
	if (0 == was_error)
	{
		PRINT_SUCCESS;
	}
	
	FreeArrayOfStrings(value_arr_cpy);
}

void TestRemove(hashtable_t *hashtable, char **value_arr, char **key_arr)
{
	size_t i = 0;
	size_t size_before = 0;
	size_t size_after = 0;
	int was_error = 0;

	char char_buffer[MAX_STR_LEN + 1] = {0};
	char *found_value_str = char_buffer;
	
	PRINT_HEADER("TestRemove");
	
	while (0 == HashtableIsEmpty(hashtable))
	{
		size_before = HashtableCountSize(hashtable);
		
		HashtableRemove(hashtable, key_arr[i]);
		
		size_after = HashtableCountSize(hashtable);
		
		if (size_before - 1 != size_after)
		{
			printf(BAD"[HashtableCountSize]: size before = %lu | size after = %lu"REG, size_before, size_after);
			++was_error;
		}
		
		found_value_str = HashtableFind(hashtable, key_arr[i]);
		
		if (NULL != found_value_str)
		{
			printf(BAD"[HashtableFind] wrong value for key"REG);
			printf(BAD"key = %s"REG, key_arr[i]);
			printf(BAD"expected value = %s"REG, value_arr[i]);
			printf(BAD"returned value = %s"REG, found_value_str);
			++was_error;
		}
				
		++i;
	}
	
	if (0 == was_error)
	{
		PRINT_SUCCESS;
	}
}

int main()
{
	char **str_arr = GetRandomStringArr();
	char **up_str_arr = GetUpperCaseStringArr(str_arr);
	
	hashtable_t *hashtable = HashtableCreate(HashWords, IsMatchStrings, NUM_OF_LETTERS);
	
	TestInsert(hashtable, str_arr, up_str_arr);
	TestForEach(hashtable, str_arr, up_str_arr);
	TestRemove(hashtable, str_arr, up_str_arr);
	
	HashtableDestroy(hashtable);
	FreeArrayOfStrings(str_arr);
	FreeArrayOfStrings(up_str_arr);

	return 0;
}
