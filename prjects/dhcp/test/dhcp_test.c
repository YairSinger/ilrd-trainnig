#include <stdio.h> 	/* printf, size_t		*/
#include <string.h> /* memcmp 				*/
#include <stdlib.h> /* malloc , free, rand, srand			*/
#include <time.h>   /* time , clock */
#include <sys/types.h> /* ssize_t*/
#include <assert.h> /* assert */

#include "dhcp.h"
/*#include "trie.h"*/

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red 	  */
#define GREEN   "\033[32m"      /* Green */
#define BLUE 	"\033[34m"      /* Blue   */

#define WORD_SIZE sizeof(size_t)
#define MAX_RANGE  1000
#define MIN_RANGE  0
#define PRINT 1
#define PRINT_ERR 1
#define GLOBAL_ARR_SIZE 2500

#define MASK_SIZE 15
#define NET_ID_SIZE 15
#define EQUAL  (1)
#define NOT_EQUAL  (0)

typedef void (*callback_t)(unsigned int exp_bin,unsigned int res_ip);

static void InsertErrCallback(unsigned int exp_bin, unsigned int res_bin);
static void SortArr(int arr[], int out_arr[], size_t size);
static void InitIntArrRandomSpec(int arr[], size_t size, int min, int max);
static int ArrMax(int arr[], size_t size);
static int CompareResults(
	void *expected, void *result, size_t element_size, int line);
static void InitIntArrRandom(int arr[], size_t size);
static void ShowResetStatus(void);
static void PrintName(const char *name ,int line);
static void PrintLine(int line);
static void PrintSizeT(size_t t);
static size_t SizeAllignedToWordSize(size_t size);
static void PrintIntArrs(int *exp_arr ,int *result_arr, size_t size);
static int CompareSsizeT(ssize_t expected, ssize_t result, int line);
static ssize_t SlowAndSteadySearch(int arr[], size_t size, int target);
static int CmpInt(int expected, int result, char *err_msg, int line);
static void InitIntArr(int arr[], size_t from, size_t to);
static int ArrMin(int arr[], size_t size);
static int CmpSize(size_t expected, size_t result, char *msg, int line );
static int ActionFunc1(void *data, void *param);
static int ActionFunc2(void *data, void *param);
static void InitArrRandomEven(int arr[], size_t from, size_t to);
static int CmpUnsignedInt(unsigned int expected, unsigned int result, char *err_msg, int line);
static int CmpUnsignedWithCallback(unsigned int expected, unsigned int result,
							   	          callback_t err_callback, int line);

size_t error = 0, test_num = 0;

typedef struct test
{
	int priority;
	char task[100];
	char owner[50];
} test_t;



static void InitTestArr(test_t test_arr[], int int_arr[], size_t size);
static void InitTestArrSpec(test_t test_arr[], int int_arr[], size_t size);


#define BIT_GROUPS 4
#define CHAR_BIT 8

unsigned int IPToBin(const char *ip_str)
{
	unsigned int bin = 0, groups[BIT_GROUPS] = {0};
	size_t i = 0;
	
	sscanf(ip_str, "%u.%u.%u.%u", &groups[0], &groups[1], &groups[2], &groups[3]);
	for (i = 0; i < BIT_GROUPS; ++i)
	{
		bin <<= CHAR_BIT;
		bin |= groups[i];
	}
	
	return bin;
}

char *BinToIP(int bin, char *ip_str)
{
    unsigned char octets[4] = {0};
    octets[0] = (bin >> 24) & 0xFF;
    octets[1] = (bin >> 16) & 0xFF;
    octets[2] = (bin >> 8) & 0xFF;
    octets[3] = bin & 0xFF;

    sprintf(
	ip_str, "%d.%d.%d.%d", octets[0], octets[1], octets[2], octets[3]);
	return ip_str;
}



static char *BitArrToString(unsigned int arr, char *str)
{
	size_t i = 0;
	/* string representation of 4 bits, values 0 - 15 */
	char *bits_strings[16] = {"0000", "0001", "0010", "0011",
							  "0100", "0101", "0110", "0111",
							  "1000", "1001", "1010", "1011",
							  "1100", "1101", "1110", "1111"};
	assert(NULL != str);
	for (i = 0; i < 8; ++i)
	{
		strncpy((str+28-i*4), bits_strings[arr & 0x0000000F], 4);
		arr >>=4;
	}				
	
	str[32] = '\0';

	return str;			  
}


int main()
{
	size_t element_size = 0, exp = 0, result = 0, i = 0, j = 0,
		   size = 0, size_1 = 0, size_2 = 0, i_flag = 0, loops = 0,
		   loops2 = 0, i_2 = 0, arr_size = 0;
	int int_res = 0, int_exp = 0, param = 0, status = 0, line = 0,
		is_sorted = 0, is_found = 0, min = 0, ip_bin_1 = 0;
	void *result_ptr = NULL, *expected_ptr = NULL;
	void *element_1 = (void *)malloc(100);
	void *element_2 = (void *)malloc(100);
	void *element_3 = (void *)malloc(100);
	void *element_4 = (void *)malloc(100);
	int *l_arr = NULL, *r_arr = NULL;
	
	
	test_t test_arr[1000] = {0};
	test_t *test_e_1 = NULL;
	test_t *test_e_2 = NULL;
	int int_arr_1[1000] = {0};
	int int_arr_2[1000] = {0};
	char bit_str[32] = {0};
	char req_ip[32] = {0};
	char res_ip[32] = {0};
	static char ip_arr[66000][16];

	clock_t begin = clock();	
	clock_t end = clock();	
	

	(void)element_size;
	(void)bit_str;
	(void)req_ip;
	(void)i;
	(void)result;
	(void)exp;
	(void)test_num;
	(void)error;
	(void)element_1;
	(void)element_2;
	(void)PrintName;
	(void)ShowResetStatus;
	(void)CompareResults;
	(void)result_ptr;
	(void)PrintSizeT;
	(void)SizeAllignedToWordSize;
	(void)CompareSsizeT;
	(void)size;
	(void)size_1;
	(void)size_2;
	(void)i_flag;
	(void)int_res;
	(void)int_exp;
	(void)param;
	(void)expected_ptr;
	(void)status;
	(void)CmpInt;
	(void)CmpUnsignedInt;
	(void)PrintIntArrs;
	(void)line;
	(void)end;
	(void)begin;
	(void)r_arr;
	(void)l_arr;
	(void)is_sorted;
	(void)SlowAndSteadySearch;
	(void)ArrMax;
	(void)ArrMin;
	(void)is_found;
	(void)i_2;
	(void)loops2;
	(void)loops;
	(void)j;
	(void)CmpSize;
	(void)ActionFunc1;
	(void)ActionFunc2;
	(void)InitIntArr;
	(void)InitIntArrRandom;
	(void)InitArrRandomEven;
	(void)arr_size;
	(void)ip_bin_1;
	(void)test_arr;
	(void)int_arr_1;
	(void)int_arr_2;
	(void)test_e_1;
	(void)test_e_2;
	(void)min;
	(void)InitTestArrSpec;
	(void)InitTestArr;
	(void)SortArr;
	(void)BitArrToString;
	(void)ip_arr;
	srand(time(NULL));	
	

	
	/* DISCLAIMER */
	
	printf("\n\n---------------------------------------------------------\n\n");
	printf("IMPORTANT!\n");
	printf("These tests assumes you have a fine DHCPGetCountFree\
 function.\nIf many tests fail, check this function first.\n\
Each insertion session has an attached time stamp. You may use\n\
it to compare performances with the other students.\n\n\
DONT FORGET TO VLG!!\n\n\n\n");

	/* Create */
	PrintName("Create", __LINE__);
	result_ptr = DHCPCreate("192.168.0.0", "255.255.0.0");
	CmpInt(NOT_EQUAL, NULL == result_ptr, "Create returned NULL.", __LINE__);
	
	size_1 = DHCPCountFreeIP(result_ptr);
	size_2 = 1<<16;
	CmpSize(size_1 + 3, size_2, "Initial addresses were not allocated", __LINE__);
	DHCPDestroy(result_ptr);	
	
	
	
	result_ptr = DHCPCreate("131.230.100.120", "255.255.255.248");
	CmpInt(NOT_EQUAL, NULL == result_ptr, "Create returned NULL.", __LINE__);
	
	size_1 = DHCPCountFreeIP(result_ptr);
	size_2 = 1<<3;
	CmpSize(size_1 + 3, size_2, "Initial addresses were not allocated", __LINE__);
	
	DHCPDestroy(result_ptr);
	ShowResetStatus();
	
	
	
	
	
	
	/* Alloc */
	/* test count after insertion */
	PrintName("Insert", __LINE__);
	result_ptr = DHCPCreate("192.168.0.0", "255.255.0.0");
	status = DHCP_ALLOC_SUCCESS;
	int_res = 0;
	begin = clock();
	while (DHCP_IS_FULL_ERR != status && DHCP_ALLOC_FAIL != status && !int_res)
	{
		size_1 = DHCPCountFreeIP(result_ptr);
		status = DHCPAllocIP(result_ptr, "192.168.0.0", res_ip);
		size_2 = DHCPCountFreeIP(result_ptr);
		if (DHCP_IS_FULL_ERR == status && DHCP_ALLOC_FAIL == status )
		{
			continue;
		}
		int_res = CmpSize(
		size_1 * (size_2 != 0),
		(size_2 + 1) * (size_2 != 0),
		"Count after insertion is not right", __LINE__);
	}
	end = clock();
	printf("1st insertion session time stamp (line %d): %ld\n" , __LINE__, (end - begin));
	DHCPDestroy(result_ptr);
	
	/* test returned ip */
	result_ptr = DHCPCreate("192.168.0.0", "255.255.0.0");
	status = DHCP_ALLOC_SUCCESS;
	int_res = 0;
	DHCPAllocIP(result_ptr, "192.168.0.0", res_ip);
	begin = clock();
	while (DHCP_IS_FULL_ERR != status && DHCP_ALLOC_FAIL != status && !int_res)
	{
		unsigned int prev_binary = 0;
		
		prev_binary = IPToBin(res_ip);
		status = DHCPAllocIP(result_ptr, "192.168.0.0", res_ip);
		IPToBin(res_ip);
		if (DHCP_IS_FULL_ERR == status || DHCP_ALLOC_FAIL == status )
		{
			continue;
		}
		
		int_res = CmpUnsignedWithCallback(
				  prev_binary + 1, IPToBin(res_ip) , &InsertErrCallback, __LINE__);
	}
	end = clock();
	printf("2nd insertion session time stamp (line %d) : %ld\n" ,__LINE__, (end - begin));
	DHCPDestroy(result_ptr);
	
	/* test count after insertion - different mask and different net id */
	result_ptr = DHCPCreate("131.230.100.120", "255.255.255.248");
	status = DHCP_ALLOC_SUCCESS;
	int_res = 0;
	begin = clock();
	while (DHCP_IS_FULL_ERR != status && DHCP_ALLOC_FAIL != status && !int_res)
	{
		size_1 = DHCPCountFreeIP(result_ptr);
		status = DHCPAllocIP(result_ptr, "131.230.100.120", res_ip);
		size_2 = DHCPCountFreeIP(result_ptr);
		if (DHCP_IS_FULL_ERR == status && DHCP_ALLOC_FAIL == status )
		{
			continue;
		}
		int_res = CmpSize(
		size_1 * (size_2 != 0),
		(size_2 + 1) * (size_2 != 0),
		"Count after insertion is not right", __LINE__);
	}
	end = clock();
	printf("3rd insertion session time stamp (line %d) : %ld\n" ,__LINE__, (end - begin));
	DHCPDestroy(result_ptr);
	
	/* test returned ip */
	result_ptr = DHCPCreate("131.230.100.120", "255.255.255.248");
	status = DHCP_ALLOC_SUCCESS;
	int_res = 0;
	DHCPAllocIP(result_ptr, "131.230.100.120", res_ip);
	begin = clock();
	while (DHCP_IS_FULL_ERR != status && DHCP_ALLOC_FAIL != status && !int_res)
	{
		unsigned int prev_binary = 0;
		prev_binary = IPToBin(res_ip);
		status = DHCPAllocIP(result_ptr, "131.230.100.120", res_ip);
		IPToBin(res_ip);
		if (DHCP_IS_FULL_ERR == status || DHCP_ALLOC_FAIL == status )
		{
			continue;
		}
		
		int_res = CmpUnsignedWithCallback(
				  prev_binary + 1, IPToBin(res_ip) , &InsertErrCallback, __LINE__);
	}
	end = clock();
	printf("4th insertion session time stamp (line %d) : %ld\n" ,__LINE__, (end - begin));	
	
	DHCPDestroy(result_ptr);
	ShowResetStatus();
	




	
	
	/* Free */
	/* test count after release */
	PrintName("free", __LINE__);
	result_ptr = DHCPCreate("158.3.120.0", "255.255.255.0");
	status = DHCP_ALLOC_SUCCESS;
	int_res = 0, i = 0;
	/* fill up DHCP */
	while (DHCP_IS_FULL_ERR != status && DHCP_ALLOC_FAIL != status && !int_res)
	{
		status = DHCPAllocIP(result_ptr, "158.3.120.0", res_ip);
		if (DHCP_IS_FULL_ERR == status && DHCP_ALLOC_FAIL == status )
		{
			continue;
		}
		strcpy(&ip_arr[i][0], res_ip);
		++i;	
	}
	status = 0;
	size_1 = DHCPCountFreeIP(result_ptr);
	i = 0;
	begin = clock();
	/* Free all*/
	while (!status && DHCPFreeIP(result_ptr, ip_arr[i]) != DHCP_ALLOC_DOUBLE_FREE)
	{
		size_2 = DHCPCountFreeIP(result_ptr);
		status = CmpSize(size_2, size_1 + 1, "Count After freeing is wrong", __LINE__);
		size_1 = size_2, ++i;
	}
	end = clock();
	printf("1st freeing session time stamp (line %d) : %ld\n" ,__LINE__, (end - begin));

	DHCPAllocIP(result_ptr, "158.3.120.1", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.3", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.7", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.15", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.31", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.63", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.127", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.127", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.127", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.127", res_ip);
	printf("\n **** %s ****\n", res_ip);
	DHCPAllocIP(result_ptr, "158.3.120.127", res_ip);
/*	DHCPAllocIP(result_ptr, "158.3.120.255");*/
	
	
	
	/* Try to insert again all freed addresses */
	i = 0;
	while (DHCP_IS_FULL_ERR != status && DHCP_ALLOC_FAIL != status && !int_res)
	{
		status = DHCPAllocIP(result_ptr, "158.3.120.0", res_ip);
		if (DHCP_IS_FULL_ERR == status && DHCP_ALLOC_FAIL == status )
		{
			continue;
		}
		strcpy(&ip_arr[i][0], res_ip);
		++i;	
	}
	CmpSize(
	0, DHCPCountFreeIP(result_ptr),
   "Could not allocate all addresses after they've been already freed" , __LINE__);
	
	DHCPDestroy(result_ptr);
	
	/*  different mask and different net id */
	result_ptr = DHCPCreate("131.230.100.120", "255.255.255.248");
	status = DHCP_ALLOC_SUCCESS;
	int_res = 0, i = 0; /* fill up dhcp */
	while (DHCP_IS_FULL_ERR != status && DHCP_ALLOC_FAIL != status && !int_res)
	{
		status = DHCPAllocIP(result_ptr, "131.230.100.120", res_ip);
		if (DHCP_IS_FULL_ERR == status && DHCP_ALLOC_FAIL == status )
		{
			continue;
		}
		strcpy(&ip_arr[i][0], res_ip);
		++i;	
	}
	status = 0;
	size_1 = DHCPCountFreeIP(result_ptr), i = 0; /* free all */
	begin = clock();
	while (!status && DHCPFreeIP(result_ptr, ip_arr[i]) != DHCP_ALLOC_DOUBLE_FREE)
	{
		size_2 = DHCPCountFreeIP(result_ptr);
		status = CmpSize(size_2, size_1 + 1, "Count After freeing is wrong", __LINE__);
		size_1 = size_2, ++i;
	}
	end = clock();
	printf("2nd freeing session time stamp (line %d) : %ld\n" ,__LINE__, (end - begin));


	/* Try to insert again all freed addresses */
	i = 0;
	while (DHCP_IS_FULL_ERR != status && DHCP_ALLOC_FAIL != status && !int_res)
	{
		status = DHCPAllocIP(result_ptr, "131.230.100.120", res_ip);
		if (DHCP_IS_FULL_ERR == status && DHCP_ALLOC_FAIL == status )
		{
			continue;
		}
		strcpy(&ip_arr[i][0], res_ip);
		++i;	
	}
	CmpSize(
	0, DHCPCountFreeIP(result_ptr),
   "Could not allocate all addresses after they've been already freed" , __LINE__);



	DHCPDestroy(result_ptr);
	ShowResetStatus();
	
	
	
	printf("---------------------------------------------------------\n\n");
	printf("End\n");
	printf("---------------------------------------------------------\n\n");
	printf("READ DISCLAIMER AT THE TOP OF THE TEST.\n\n\n\n");
	
	free(element_1);
	free(element_2);
	free(element_3);
	free(element_4);
	
	return 0;
}



static void InsertErrCallback(unsigned int exp_bin, unsigned int res_bin)
{
	char exp_ip[32] = {0}, res_ip[32] = {0};
	printf(RED "expected : %s, got : %s\n" RESET ,
		   BinToIP(exp_bin, exp_ip), BinToIP(res_bin, res_ip));
}


static void SortArr(int arr[], int out_arr[], size_t size)
{
	int is_sorted = 0;
	size_t i = 0;
	int tmp = 0;
	
	memcpy(out_arr, arr, size * sizeof(int));
	
	while (!is_sorted)
	{
		i = 0, is_sorted = 1;
		while (i < (size - 1))
		{
			if (out_arr[i] > out_arr[i + 1])
			{
				tmp = out_arr[i];
				out_arr[i] = out_arr[i+1];
				out_arr[i+1] = tmp;
				is_sorted = 0;				
			}
			++i;	
		}
	}
}


static void InitTestArr(test_t test_arr[], int int_arr[], size_t size)
{
	size_t i = 0;
	
	InitIntArrRandom(int_arr, size);
	
	for (i = 0; i < size; ++i)
	{
		(test_arr[i]).priority = int_arr[i];
		strcpy(test_arr[i].task , "Make global peace");	
		strcpy(test_arr[i].owner , "Lior Nachmias");	
	}
	
	return;
}

static void InitTestArrSpec(test_t test_arr[], int int_arr[], size_t size)
{
	size_t i = 0;
	
	InitIntArrRandomSpec(int_arr, size, 0 , (int)size);
	
	for (i = 0; i < size; ++i)
	{
		(test_arr[i]).priority = int_arr[i];
		strcpy(test_arr[i].task , "Make global peace");	
		strcpy(test_arr[i].owner , "Lior Nachmias");	
	}
	
	return;
}

static int ActionFunc1(void *data, void *param)
{
	if(NULL == data)
	{
		return 1;
	}
	
	*(int *)data += *(int *)param;
	
	return 0;	
}

static int ActionFunc2(void *data, void *param)
{
	(void)data, (void)param;
	return 1;
}

static int ArrMin(int arr[], size_t size)
{
	size_t i = 0;
	int min_value = arr[0];
	
	for (i = 1; i < size; ++i)
	{
		min_value = arr[i] < min_value ? arr[i] : min_value; 
	}
	
	return min_value;
}

static int ArrMax(int arr[], size_t size)
{
	size_t i = 0;
	int max_value = arr[0];
	
	for (i = 1; i < size; ++i)
	{
		max_value = arr[i] > max_value ? arr[i] : max_value; 
	}
	
	return max_value;
}

static void InitIntArrRandom(int arr[], size_t size)
{
	size_t i = 0;
	int lut[MAX_RANGE - MIN_RANGE] = {0};
	
	for (i = 0; i < size; ++i)
	{	
		arr[i] = (rand() % (MAX_RANGE - MIN_RANGE )) + MIN_RANGE;
		while (1 == (lut[arr[i] - MIN_RANGE]))
		{
			arr[i] = (rand() % (MAX_RANGE - MIN_RANGE )) + MIN_RANGE;
		}
		lut[arr[i] - MIN_RANGE] = 1;	
	}
}


static void InitIntArrRandomSpec(int arr[], size_t size, int min, int max)
{
	size_t i = 0;
	int lut[MAX_RANGE - MIN_RANGE] = {0};
	
	for (i = 0; i < size; ++i)
	{	
		arr[i] = (rand() % (max - min )) + min;
		while (1 == (lut[arr[i] - min]))
		{
			arr[i] = (rand() % (max - min)) + min;
		}
		lut[arr[i] - min] = 1;	
	}
}

static void InitArrRandomEven(int arr[], size_t from, size_t to)
{
	size_t i = 0;
	int lut[MAX_RANGE - MIN_RANGE] = {0};
	
	for (i = from; i < to; ++i)
	{	
		arr[i] = (((rand() % (MAX_RANGE - MIN_RANGE )) + MIN_RANGE) / 2) * 2;
		while (1 == lut[arr[i] - MIN_RANGE])
		{
			arr[i] = (rand() % (MAX_RANGE - MIN_RANGE )) + MIN_RANGE;
		}
		lut[arr[i] - MIN_RANGE] = 1;	
	}
}

static void InitIntArr(int arr[], size_t from, size_t to)
{
	size_t i = 0;
	for (i = from; i <= to; ++i)
	{
		arr[i] = (int)i;
	}
}

/*static int CmpFunc(const void *lhs,const void *rhs)*/
/*{*/
/*	return *(int *)lhs - *(int *)rhs;*/
/*}*/


static void PrintIntArrs(int *exp_arr ,int *result_arr, size_t size)
{
	size_t i = 0;
	
	printf(BLUE "expected:\n" RESET);
	for (i = 0; i < size; ++i)
	{
		printf(BLUE " %d, " RESET , exp_arr[i] );	
	}
	
	printf(BLUE "\ngot:\n" RESET);
	for (i = 0; i < size; ++i)
	{
		printf(BLUE " %d, " RESET , result_arr[i] );	
	}
	
	printf("\n");
}


static int CmpInt(int expected, int result, char *err_msg, int line)
{
	size_t err = 0;
	
	test_num += 1;
	if (0 == test_num)
	{
		test_num = 1;
	}
		
	err = (expected != result);
	
	if (err)
	{	
		++(error);
		printf(RED "%s\n in test %lu , line: %d\n" RESET, err_msg, test_num , line);
		printf(RED "expected: %d , result: %d\n"
			   RESET, expected, result);
		return err;	
	}
	
	return 0;
}

static int CmpUnsignedInt(unsigned int expected, unsigned int result, char *err_msg, int line)
{
	size_t err = 0;
	
	test_num += 1;
	if (0 == test_num)
	{
		test_num = 1;
	}
		
	err = (expected != result);
	
	if (err)
	{	
		++(error);
		printf(RED "%s\n in test %lu , line: %d\n" RESET, err_msg, test_num , line);
		printf(RED "expected: %u , result: %u\n"
			   RESET, expected, result);
		return err;	
	}
	
	return 0;
}

static int CmpSize(size_t expected, size_t result, char *msg, int line)
{
	size_t err = 0;
	int status = 0;
	test_num += 1;
		
	err = expected != result;
	
	if (err)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
		printf("%s\n", msg);
		printf(RED "expected: %lu , result: %lu\n"
			   RESET, expected, result);
		status = 1;
	}
	
	return status;
}



static int CmpUnsignedWithCallback(unsigned int expected, unsigned int result,
							   	          callback_t err_callback, int line)
{
	size_t err = 0;
	int status = 0;
	test_num += 1;
		
	err = expected != result;
	
	if (err)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
		err_callback(expected, result);
		status = 1;
	}
	
	return status;
}

static int CompareSsizeT(ssize_t expected, ssize_t result, int line)
{
	size_t err = 0;
	int status = 0;
	test_num += 1;
		
	err = expected != result;
	
	if (err)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
		printf(RED "expected: %ld , result: %ld\n"
			   RESET, expected, result);
		status = 1;
	}
	
	return status;
}

static int CompareResults(void *expected, void *result, size_t element_size, int line)
{
	size_t err = 0;
	int status = 0;
	
	test_num += 1;
	if (test_num == 0)
	{
		test_num = 1;
	}
		
	if (NULL == expected || NULL == result)
	{
		err = (expected != result);
	}
		
	else
	{
		err = memcmp(expected, result, element_size);
	}
	if (err)
	{	
		++(error);
		printf(RED "Error in test %ld , line: %d\n" RESET, test_num , line);		
	}
	expected = element_size + (char *)expected;
	result =   element_size + (char *)	result;	
	
	err ? (status = 1) : (status = 0);
	
	return status; 
}


static void ShowResetStatus()
{
	if (error)
	{
		printf( RED "%ld errors in %ld tests\n\n" RESET , error, test_num);
		error = 0;
	}
	else
	{
		printf( GREEN "Success in %ld out of %ld tests\n\n" RESET , test_num, test_num);
		test_num = 0;
	}
}

static ssize_t SlowAndSteadySearch(int arr[], size_t size, int target)
{
	size_t i = 0;
	
	for (i = 0; i < size && arr[i] != target; ++i)
	{
		;
	}
	
	return (arr[i] == target) ? (ssize_t)(i) : (ssize_t)(-1);
}

static void PrintName(const char *name ,int line)
{
	PrintLine(line);
	printf("%s:\n" ,name);
}

static void PrintLine(int line)
{
	printf(BLUE "line %d\n" RESET ,line);
}

static void PrintSizeT(size_t t)
{
	printf("%lu\n" , t);
}

static size_t SizeAllignedToWordSize(size_t size)
{
	return (size % WORD_SIZE == 0) ? size 	 :  
	( size + (WORD_SIZE - (size % WORD_SIZE)) );
}

