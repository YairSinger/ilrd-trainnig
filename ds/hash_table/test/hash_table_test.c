#include <stdio.h> 	/* printf */
#include <math.h> /*floor*/
#include "hash_table.h"
#include <string.h> /* stcpy, strdup*/
#include <stdlib.h> /*malloc*/ 

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"


#define HASH_FACROT 0.73
#define NUM_OF_KEYS 700
#define NUM_OF_BUCKETS 20000
#define NUM_OF_WORDS 104334
#define NUM_OF_WORDS_BUCKETS 100000


void TestSpellChaecker();

static size_t HashFunc(const void *key)
{
	size_t size = NUM_OF_BUCKETS;
	float factor = HASH_FACROT;
	int key_num = *((int *)key);
	return (size_t)key_num % size;
	/*return (size_t)(size * (modf(key_num * factor, &i)));*/
	
}

static size_t WordsHash(const void *key)
{
	char word[100] = {'\0'};
	char *head = word;
	int c;
	size_t hash = 5381;
   
	strcpy(word,(const char *)key);
	while ((c = *head))
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		++head;
	}
    return hash % NUM_OF_WORDS_BUCKETS;
}



static size_t HashFunc2(const void *key)
{
	return (size_t)(*((int *)key));
}



static int IsWordKeyMatch(const void *key1, const void *key2)
{
	char word1[100] = {'\0'};
	char word2[100] = {'\0'};
	
	strcpy(word1,(const char *)key1);
	strcpy(word2,(const char *)key2);
	
	return (!strcmp(word1, word2));
}


static int IsKeyMatch(const void *key1, const void *key2)
{
	return (int *)key1 == (int *)key2;
}

void TestHashtableCreate();
void TestHashtableInsertSizeEmpty();



int main()
{
	/*TestHashFunc();
	TestHashtableCreate();
	TestHashtableInsertSizeEmpty();*/
	TestSpellChaecker();
	
	return 0;
}


void TestHashtableCreate()
{
	int fails = 0;
	hashtable_t *hash = HashtableCreate(HashFunc, IsKeyMatch, NUM_OF_BUCKETS);
	
	if (NULL == hash)
	{
		++fails;
		printf(RED"HashtableCreate FAILD\n"RESET_COLOR);
	}
	
	if (!HashtableIsEmpty(hash))
	{
		++fails;
		printf(RED"HashtableCreate FAILD, not empty\n"RESET_COLOR);
	}
	
	if (0 != HashtableCountSize(hash))
	{
		++fails;
		printf(RED"HashtableCreate FAILD, count is %lu vs 0 expected\n"RESET_COLOR, HashtableCountSize(hash));
	}
		
	if (0 == fails)
	{
		printf(GREEN"HashtableCreate PASSED\nCheck valgrind for destroy approval\n"RESET_COLOR);
	}
	
	HashtableDestroy(hash);
	
}

void TestHashtableInsertSizeEmpty()
{
	int fails = 0;
	size_t i = 0;
	int status = 0; 
	int arr_data[10] = {50, -4, 25, 8000, 734, 0, 82, -13, 0, 100};
	int keys[10]= {0,1,2,5,6,7,8,15,20,30};
	hashtable_t *hash = HashtableCreate(HashFunc2, IsKeyMatch, NUM_OF_BUCKETS);
	
	if (NULL == hash)
	{
		++fails;
		printf(RED"HashtableCreate FAILD\n"RESET_COLOR);
	}
	
	if (!HashtableIsEmpty(hash))
	{
		++fails;
		printf(RED"HashtableCreate FAILD, not empty\n"RESET_COLOR);
	}
	
	if (0 != HashtableCountSize(hash))
	{
		++fails;
		printf(RED"HashtableCreate FAILD, count is %lu vs 0 expected\n"RESET_COLOR, HashtableCountSize(hash));
	}
	for (i = 0; i < 10; ++i)
	{	
		status = HashtableInsert(hash,(void *)&keys[i], &arr_data[i]);
		
		if (HashtableIsEmpty(hash))
		{
			++fails;
			printf(RED"HashtableInsert/HashtableIsEmpty FAILD, empty after insert\n"RESET_COLOR);
		}
		
		if (i + 1 != HashtableCountSize(hash))
		{
			++fails;
			printf(RED"HashtableInsert/HashtableCountSize FAILD, count is %lu vs %lu expected\n"RESET_COLOR, HashtableCountSize(hash), i);
		}
	}
	
	for (i = 0; i < 10; ++i)
	{		
		if (HashtableFind(hash, (void *)&keys[i]) != (void *) &arr_data[i])
		{
			++fails;
			printf(RED"HashtableInsert/HashtableFind FAILD, different data\n%d vs %d expected\n"RESET_COLOR,*((int *)HashtableFind(hash, (void *)&keys[i])),arr_data[i]);
		}
	}
	
	if (0 == fails)
	{
		printf(GREEN"{HashtableInsert,\nHashtableCountSize,\nHashtableIsEmpty}PASSED\n"RESET_COLOR);
	}
	
	
	fails = 0;
	for (i = 10; i != 0; --i)
	{
		HashtableRemove(hash, &keys[i]);			
		if (i - 1 != HashtableCountSize(hash))
		{
			++fails;
			printf(RED"HashtableRemove FAILD, count is %lu vs %lu expected\n"RESET_COLOR, HashtableCountSize(hash), i - 1);
		}
	}
	
	if (0 == fails)
	{
		printf(GREEN"HashtableRemove PASSED\n"RESET_COLOR);
	}
	
	HashtableDestroy(hash);
	
}
static char *my_strdup(const char *s) {
    char *d = malloc(strlen(s) + 1);   /* Allocate memory*/
    if (d == NULL)
    {
    	return NULL; 
    }         /* Return NULL if malloc failed*/
    strcpy(d,s);                        /* Copy the string*/
    return d;                           /* Return the new string*/
}

void TestSpellChaecker()
{
	int fails = 0;
	int status = 0;
	size_t i = 0, j = 0;
	
	char word[100] = {'\0'};
	char *words[104336] = {NULL};
	size_t len = 0;
	
	hashtable_t *hash = HashtableCreate(WordsHash, IsWordKeyMatch,NUM_OF_WORDS_BUCKETS);
	FILE *fp = fopen("/usr/share/dict/words", "r");
	
	for (j = 0; j < 104336 && 0 == status; ++j)
	{
		for(i = 0, word[i] = fgetc(fp); EOF != word[i] && '\n' != word[i] ; ++i,word[i] = fgetc(fp))
		{
			
		}
		word[i] = '\0';
		/*printf("%s\n", word);*/
		words[j] = my_strdup(word);
		status = HashtableInsert(hash, (const void *)words[j], (void*)words[j]);
	}
	
	if (104336 != HashtableCountSize(hash))
	{
			++fails;
			printf(RED"HashtableInsert FAILD, count is %lu vs 104336 expected\n"RESET_COLOR, HashtableCountSize(hash));
	}
	if (0 == fails)
	{
		printf(GREEN"HashtableRemove PASSED\n"RESET_COLOR);
	}
	
	while (0 != strcmp("quit", word))
	{
		printf("Please insert a word for spell check or type quit to exit\n");
		scanf("%s", word);
		if (NULL != HashtableFind(hash, (const void *)word))
		{
			printf(GREEN"%s exists in dictionary\n"RESET_COLOR, word);
		}
		else
		{
			printf(RED"%s Do not exists in dictionary\n"RESET_COLOR, word);
		}
	}
	
	
	HashtableDestroy(hash);
	for (j = 0; j < 500; ++j)
	{
		free(words[j]);
	}
}
