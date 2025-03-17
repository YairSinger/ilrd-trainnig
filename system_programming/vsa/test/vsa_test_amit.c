#include <stdio.h>
#include <stdlib.h>
#include "vsa.h"

#define WHITEBOLD "\033[0;37;1m"
#define CLOSETEXT "\033[0m"
#define WHITE printf("\033[0;37;1m")
#define GREEN printf("\033[32;7m")
#define RED printf("\033[31;7m")
#define DEFAULT printf("\033[0m")

void test_vsa_senity();
void test_vsa_alloc_edge_cases();
void test_vsa_free_edge_cases();
void test_vsa_stress_test();
void test_word_alignment_of_alloc();

int main() 
{
	printf("\n%s***** Test: VSA Init And Senity ******%s\n", WHITEBOLD, CLOSETEXT);
	test_vsa_senity();

	printf("\n%s***** Test: VSA Allocation - Edge Cases ******%s\n", WHITEBOLD, CLOSETEXT);
	test_vsa_alloc_edge_cases();

	printf("\n%s***** Test: VSA Freeing - Edge Cases ******%s\n", WHITEBOLD, CLOSETEXT);
	test_vsa_free_edge_cases();

	printf("\n%s***** Test: VSA Stress ******%s\n", WHITEBOLD, CLOSETEXT);
	test_vsa_stress_test();
	
	printf("\n%s***** Test: VSA Alignment ******%s\n", WHITEBOLD, CLOSETEXT);
	test_word_alignment_of_alloc();
    
    	return 0;
} 

void test_vsa_senity()
{
	size_t success_counter = 0;
	size_t num_tests=0;
	size_t res = 0;
	size_t expect = 0;
	char test[100] = {0};
	char test2[4] = {0};
	void *alloc = NULL;
	void *alloc2 = NULL;
	vsa_t *vsa_ptr = NULL;
	vsa_t *vsa_ptr2 = NULL;
	
	WHITE;
	printf("VSA senity");
	DEFAULT;
	
	vsa_ptr = VsaInit(test, 100);
	res = VsaLargestBlock(vsa_ptr);
	expect = 80;
	++num_tests;
	if(expect != res)
	{
		printf("\n num of Block: expected %ld, got %ld\n", expect, res);
	}
	else
	{
		++success_counter;
	}
	
	/* init pool size lower then minimum */
	vsa_ptr2 = VsaInit(test2, 4);
	++num_tests;
	if(NULL != vsa_ptr2)
	{
		printf("Requested Pool size lower the Mangment struct Shuld return NULL");
	}
	else
	{
		++success_counter;
	}
	
	alloc = VsaAlloc(vsa_ptr, 24);
	res = VsaLargestBlock(vsa_ptr);
	expect = 48;
	++num_tests;
	if(expect != res)
	{
		printf("\n num of Block: expected %ld, got %ld\n", expect, res);
	}
	else
	{
		++success_counter;
	}
	
	VsaFree(alloc);
	res = VsaLargestBlock(vsa_ptr);
	expect = 80;
	++num_tests;
	if(expect != res)
	{
		printf("\n num of Block: expected %ld, got %ld\n", expect, res);
	}
	else
	{
		++success_counter;
	}
	
	alloc = VsaAlloc(vsa_ptr, 20);
	res = VsaLargestBlock(vsa_ptr);
	expect = 48;
	++num_tests;
	if(expect != res)
	{
		printf("\n num of Block: expected %ld, got %ld\n", expect, res);
	}
	else
	{
		++success_counter;
	}
	
	alloc2 = VsaAlloc(vsa_ptr, 50);
	++num_tests;
	if(NULL != alloc2)
	{
		printf("\n alloc shuld return NULL");
	}
	else
	{
		++success_counter;
	}
	
	res = VsaLargestBlock(vsa_ptr);
	expect = 48;
	++num_tests;
	if(expect != res)
	{
		printf("\n num of Block: expected %ld, got %ld\n", expect, res);
	}
	else
	{
		++success_counter;
	}
	
	alloc2 = VsaAlloc(vsa_ptr, 30);
	res = VsaLargestBlock(vsa_ptr);
	expect = 8;
	++num_tests;
	if(expect != res)
	{
		printf("\n num of Block: expected %ld, got %ld\n", expect, res);
	}
	else
	{
		++success_counter;
	}
	
	VsaFree(alloc);
	res = VsaLargestBlock(vsa_ptr);
	expect = 24;
	++num_tests;
	if(expect != res)
	{
		printf("\n num of Block: expected %ld, got %ld\n", expect, res);
	}
	else
	{
		++success_counter;
	}
	
	(success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n",success_counter,num_tests );
	DEFAULT;
	
}

void test_vsa_alloc_edge_cases()
{
	size_t success_counter = 0;
	size_t num_tests = 0;
	char *test = calloc(100, sizeof(char));
	void *alloc = NULL;
	vsa_t *vsa_ptr = VsaInit(test, 100);
	
	int i = 0;

	WHITE; printf("VSA Alloc Edge Cases"); DEFAULT;

	/* Pool size is 0 */
	alloc = VsaAlloc(vsa_ptr, 0);
	++num_tests;
	if (NULL != alloc)
	{
		printf("\n Allocation with size 0 should return NULL");
	}
	else
	{
		++success_counter;
	}

	/* alloc size larger than pool*/
	alloc = VsaAlloc(vsa_ptr, 200);
	++num_tests;
	if (NULL != alloc)
	{
		printf("\n Allocation larger than pool should return NULL.");
	}
	else
	{
		++success_counter;
	}

	/* Multiple small allocations to empty the pool*/
	for (i = 0; i < 3; ++i)
	{
		/* Shuld be Full after 3 insertion */
		alloc = VsaAlloc(vsa_ptr, 10);
	}
	++num_tests;

	/* Checking if pool is fully used*/
	alloc = VsaAlloc(vsa_ptr, 10);
	if (NULL != alloc)
	{
		printf("\n Pool should be unevalable after 3 allocations of size 10.");
	}
	else
	{
		++success_counter;
	}

	(success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n", success_counter, num_tests);
	DEFAULT;
	
	free(test);
}

void test_vsa_free_edge_cases()
{
	size_t success_counter = 0;
	size_t num_tests = 0;
	char test[100] = {0};
	void *alloc1, *alloc2 = NULL;
	vsa_t *vsa_ptr = VsaInit(test, 100);

	WHITE; printf("VSA Free Edge Cases"); DEFAULT;

	/* Freeing NULL*/
	VsaFree(NULL);
	++num_tests;
	if (VsaLargestBlock(vsa_ptr) != 80) 
	{
		printf("\n Freeing NULL shouldn't change pool state.");
	}
	else
	{
		++success_counter;
	}

	alloc1 = VsaAlloc(vsa_ptr, 10);
	alloc2 = VsaAlloc(vsa_ptr, 10);
	VsaFree(alloc2);
	VsaFree(alloc1);
	++num_tests;
	if (VsaLargestBlock(vsa_ptr) != 80) 
	{
		printf("\n Order of free shouldn't matter, blocks should merge.");
	}
	else
	{
		++success_counter;
	}

	(success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n", success_counter, num_tests);
	DEFAULT;
}

void test_vsa_stress_test()
{
	size_t success_counter = 0;
	size_t num_tests = 0;
	
	char pool[10000] = {0};
	vsa_t *vsa_ptr = VsaInit(pool, 10000);
	void *allocs[1000] = {0};
	int i = 0;
	int choice = 0 ;
	size_t largest = 0;
	int rand(void);

	WHITE; printf("VSA Stress Test\n"); DEFAULT;
	++num_tests;
	
	for (i = 0; i < 1000; ++i)
	{
		allocs[i] = VsaAlloc(vsa_ptr, (rand() % 8) + 16);
	}

	for (i = 0; i < 1000; ++i)
	{
		choice = rand() % 2;
		
		if (choice)
		{
		    VsaFree(allocs[i]);
		    allocs[i] = NULL;
		}
	}

	for (i = 0; i < 1000; ++i)
	{
		if (allocs[i] == NULL)
		{
			
		    	allocs[i] = VsaAlloc(vsa_ptr, (rand() % 8) + 16);
		}
	}

	largest = VsaLargestBlock(vsa_ptr);
	++success_counter;
	WHITE; printf("Largest Free Block After Stress Test: %ld\n", largest); DEFAULT;
	
	(success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n", success_counter, num_tests);
	DEFAULT;
}

int IsWordAligned(void *ptr)
{
        return (size_t)ptr % sizeof(size_t) == 0;	
}

void test_word_alignment_of_alloc()
{
        size_t success_counter = 0;
        size_t num_tests = 0;
        char pool[2000] = {0};
        vsa_t *vsa_ptr = NULL;
        void *alloc = NULL;
        size_t i = 1;

        vsa_ptr = VsaInit(pool, 2000);

        WHITE; printf("VSA Alignment test"); DEFAULT;
        
        for (i = 16; i < 200; i += 5)
        {
                alloc = VsaAlloc(vsa_ptr, i);
                num_tests++;
                if (IsWordAligned(alloc))
                {
                        success_counter++;
                }
                else
                {
                        printf("Allocation of %ld bytes is not word-aligned. Address: %p\n", i, alloc);
                }
              
        }

        (success_counter == num_tests) ? GREEN : RED;
	printf("\n	Success in:  %10ld / %ld\n\n", success_counter, num_tests);
	DEFAULT;
}


