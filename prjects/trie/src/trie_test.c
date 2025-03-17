#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "trie.h"


#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

void TestTrieCreate();
void TestTrieCreatePathCountLeafs();
static const char* GetTrieStatus(trie_status_t status)
{
	switch (status)
	{
		case TRIE_SUCCESS: return "TRIE_SUCCESS";
		case TRIE_ALLOCATION_FAIL: return "TRIE_ALLOCATION_FAIL";
		case TRIE_IS_FULL: return "TRIE_IS_FULL";
		case TRIE_PATH_IS_ALLOCATED: return "TRIE_PATH_IS_ALLOCATED";
		case TRIE_PATH_IS_FULL: return "TRIE_PATH_IS_FULL";
		case TRIE_DOUBLE_FREE: return "TRIE_DOUBLE_FREE";
		case TRIE_INVALID_INPUT: return "TRIE_INVALID_INPUT";
	}

}
void PrintBits(unsigned int *ptr)
{
	size_t size = 4;
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}


int main()
{
	TestTrieCreate();
	TestTrieCreatePathCountLeafs();
	return 0;
}


void TestTrieCreate()
{
	trie_t *trie = TrieCreate(2);
	int fails = 0;
	
	if(NULL == trie)
	{
		++fails;
		printf("TrieCreate failed,returned NULL\n");
	}
	
	if(4 != TrieCountFreeLeafs(trie))
	{
		++fails;
		printf("TrieCreate failed. Height 2 resulted %lu free leafs\n", TrieCountFreeLeafs(trie));
	}
	
	TrieDestroy(trie);
	
	trie = TrieCreate(5);
	
	if(32 != TrieCountFreeLeafs(trie))
	{
		++fails;
		printf("TrieCreate failed. Height 2 resulted %lu free leafs\n", TrieCountFreeLeafs(trie));
	}
	if(0 == fails)
	{
		printf("TrieCreate PASSED\n");
	}
	
	TrieDestroy(trie);
}

void TestTrieCreatePathCountLeafs()
{
	trie_t *trie = TrieCreate(2);
	int fails = 0;
	int is_full = 0;
	unsigned int path1 = (unsigned int)0x77000000;
	unsigned int path2 = (unsigned int)0x77000001;
	unsigned int path3 = (unsigned int)0x77000002;
	unsigned int path4 = (unsigned int)0x77000003;
	unsigned int givven_path = 0;
	trie_status_t status = TRIE_SUCCESS;
	
	status = TrieCreatePath(trie, path1, &givven_path);
	if(givven_path == 0)
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. didnt update givven path\n"RESET_COLOR);	
	}
	
	if(status != TRIE_SUCCESS)
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. return status is %s\n"RESET_COLOR, GetTrieStatus(status));	
	}
	
	if(3 != TrieCountFreeLeafs(trie))
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. Free leafs are %lu vs 3 expected\n"RESET_COLOR, TrieCountFreeLeafs(trie));	
	}
	
	
	
	status = TrieCreatePath(trie, path1, &givven_path);
	if(givven_path == path1)
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. didnt update givven path when path is allocated\n"RESET_COLOR);	
	}
	if(givven_path != path2)
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. givven path is:\n");
		PrintBits(&givven_path);
		printf(RED"vs expected:\n");
		PrintBits(&path2);
		printf("not next free path\n"RESET_COLOR);	
	}
	if(2 != TrieCountFreeLeafs(trie))
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. Free leafs are %lu vs 2 expected\n"RESET_COLOR, TrieCountFreeLeafs(trie));	
	}
	
	status = TrieCreatePath(trie, path4, &givven_path);
	
	if(status != TRIE_SUCCESS)
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. return status is %s\n"RESET_COLOR, GetTrieStatus(status));	
	}
	if(givven_path != path4)
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. givven path is:\n");
		PrintBits(&givven_path);
		printf(RED"vs expected:\n");
		PrintBits(&path4);
		printf("not next free path\n"RESET_COLOR);	
	}
	if(1 != TrieCountFreeLeafs(trie))
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. Free leafs are %lu vs 1 expected\n"RESET_COLOR, TrieCountFreeLeafs(trie));	
	}
	is_full = TrieIsFull(trie);
	if(1 == is_full)
	{
		++fails;
		printf(RED"TrieIsFull FAILED. resulted full when Free leafs are %lu\n"RESET_COLOR, TrieCountFreeLeafs(trie));	
	}
	status = TrieCreatePath(trie, path4, &givven_path);
	
	if(status != TRIE_SUCCESS)
	{
		++fails;
		printf(RED"test 4 TrieCreatePath FAILED. return status is %s\n"RESET_COLOR, GetTrieStatus(status));	
	}
	if(givven_path != path3)
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. givven path is:\n");
		PrintBits(&givven_path);
		printf(RED"vs expected:\n");
		PrintBits(&path4);
		printf("not next free path\n"RESET_COLOR);	
	}
	if(0 != TrieCountFreeLeafs(trie))
	{
		++fails;
		printf(RED"TrieCreatePath FAILED. Free leafs are %lu vs 0 expected\n"RESET_COLOR, TrieCountFreeLeafs(trie));	
	}
	is_full = TrieIsFull(trie);
	if(0 == is_full)
	{
		++fails;
		printf(RED"TrieIsFull FAILED. resulted not full when Free leafs are %lu\n"RESET_COLOR, TrieCountFreeLeafs(trie));	
	}
	
	if(0 == fails)
	{
		printf(GREEN"{TrieCreatePath, TrieCountFreeLeafs, TrieIsFull} PASSED\n"RESET_COLOR);
	}
	
	fails = 0;
	status = TrieRemovePath(trie, path1);
	if(TRIE_SUCCESS != status)
	{
		++fails;
		printf(RED"TrieRemovePath FAILED. return status is %s\n vs TRIE_SUCCESS expected"RESET_COLOR, GetTrieStatus(status));		
	}
	
	if(1 != TrieCountFreeLeafs(trie))
	{
		++fails;
		printf(RED"TrieRemovePath FAILED. Free leafs are %lu vs 1 expected\n"RESET_COLOR, TrieCountFreeLeafs(trie));
	}
	status = TrieRemovePath(trie, path1);
	if(TRIE_DOUBLE_FREE != status)
	{
		++fails;
		printf(RED"TrieRemovePath FAILED. return status is %s\n vs TRIE_DOUBLE_FREE expected"RESET_COLOR, GetTrieStatus(status));		
	}
	if(1 != TrieCountFreeLeafs(trie))
	{
		++fails;
		printf(RED"TrieRemovePath FAILED. Free leafs are %lu vs 1 expected\n"RESET_COLOR, TrieCountFreeLeafs(trie));
	}
	status = TrieRemovePath(trie, path2);
	status = TrieRemovePath(trie, path3);
	status = TrieRemovePath(trie, path4);
	if(TRIE_SUCCESS != status)
	{
		++fails;
		printf(RED"TrieRemovePath FAILED. return status is %s\n vs TRIE_SUCCESS expected"RESET_COLOR, GetTrieStatus(status));		
	}
	if(4 != TrieCountFreeLeafs(trie))
	{
		++fails;
		printf(RED"TrieRemovePath FAILED. Free leafs are %lu vs 2 expected\n"RESET_COLOR, TrieCountFreeLeafs(trie));
	}
	if(0 == fails)
	{
		printf(GREEN"TrieRemovePath PASSED\n"RESET_COLOR);
	}
	TrieDestroy(trie);
}

