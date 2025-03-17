#include <stdio.h> 	/* printf */
#include <string.h> /* memcmp */
#include "c_buffer.h"


#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

struct overlap_struct
{
	int x;
	char y;
	size_t z;
};

void TestCBufCreate();
void TestCBufWrite();
void TestCBufRead();

int main()
{
	TestCBufCreate();
	TestCBufWrite();
	TestCBufRead();
	
	return 0;
}

/********************/
void TestCBufCreate()
{
	int fails = 0;
	c_buffer_t * buffer = CBufCreate(10);
	if (NULL == buffer || 0 == sizeof(buffer) )
	{
		++fails;
		printf(RED"buffer CREATE FAILED\n"RESET_COLOR);
	}
			
	
	if (10 != CBufFreeSpace(buffer) && 0 != CBufBufsiz(buffer) && !CBufIsEmpty(buffer))
	{
		++fails;
		printf(RED"buffer CREATE FAILED metadata not set right\n"RESET_COLOR);
	}
	
	if (0 == fails)
	{
		printf(GREEN"buffer CREATE PASSED\n"RESET_COLOR);
	}
	printf(GREEN"test valgrind for full memory release test\n\n"RESET_COLOR);
	CBufDestroy(buffer);
}

/***********************************/


void TestCBufWrite()
{
	int fails = 0;
	char src[15] = {0};
	char dest[15] = {0};
	
	c_buffer_t * buffer = CBufCreate(10);
	
	/*write from empty more than capacity*/
	memset(src, 'C', 15);
	if (10 != CBufWrite(buffer, (const void *) src, 14))
	{
		++fails;
		printf(RED"Test 1 c_buffer write FAILED more than capacity\n"RESET_COLOR);
	}
	
	/*write all free space */
	CBufRead(buffer, (void *)dest, 5);
	if (5 != CBufWrite(buffer, (const void *) src, 14))
	{
		++fails;
		printf(RED"Test 2 c_buffer write FAILED more than free space\n"RESET_COLOR);
	}
	CBufRead(buffer, (void *)dest, 8);
	if (8 != CBufWrite(buffer, (const void *) src, 14))
	{
		++fails;
		printf(RED"Test 3 c_buffer write FAILED more than free space\n over end of buffer\n"RESET_COLOR);
	}
	
	/*write in empty buffer less than capacity */
	CBufRead(buffer, (void *)dest, 5);

	if (2 != CBufWrite(buffer, (const void *) src, 2))
	{
		++fails;
		printf(RED"Test 4 c_buffer write FAILED less than space to end\n"RESET_COLOR);
	}
	/*finish at end of buffer to test circularity */
	CBufWrite(buffer, (const void *) src, 2);
	if (1 != CBufWrite(buffer, (const void *) src, 4))
	{
		++fails;
		printf(RED"Test 5 c_buffer write FAILED writing over buffer end\n"RESET_COLOR);
	}
	/*test writing count = 0 */
	CBufRead(buffer, (void *)dest, 10);
	if (0 != CBufWrite(buffer, (const void *) src, 0))
	{
		++fails;
		printf(RED"Test 6 c_buffer write FAILED writing count = 0 \n"RESET_COLOR);
	}

	
	if (0 == fails)
	{
		printf(GREEN"c_buffer write PASSED\n"RESET_COLOR);
	}
	
	CBufDestroy(buffer);
}

/**************************************************/

void TestCBufRead()
{
	int fails = 0;
	char src_a[15] = {0};
	char src_b[15] = {0};
	char dest[15] = {0};
	size_t read_num = 0;
	c_buffer_t * buffer = CBufCreate(10);
	c_buffer_t * buffer_struct = CBufCreate(20);
	struct overlap_struct test_struct = {50, 'A', 505050};
	struct overlap_struct test_struct_res = {5,'j',5};
	memset(src_a, 'A', 15);
	memset(src_b, 'B', 15);
	
	/*reading empty buffer */
	if (0 != (read_num = CBufRead(buffer, (void *)dest, 10)))
	{
		++fails;
		printf(RED"Test 1 c_buffer read FAILED reading empty buffer %lu\n"RESET_COLOR, read_num);
	}
	
	/*reading full*/
	CBufWrite(buffer, (const void *) src_a, 5);
	CBufWrite(buffer, (const void *) src_b, 5);
	if (10 != CBufRead(buffer, (void *)dest, 10) 
	&& !memcmp((const void *) dest , "AAAAABBBBB",10))
	{
		++fails;
		printf(RED"Test 2 c_buffer read FAILED reading full buffer \n"RESET_COLOR);
	}
	
	/*reading over end*/
	CBufWrite(buffer, (const void *) src_a, 5);
	CBufWrite(buffer, (const void *) src_b, 5);
	CBufRead(buffer, (void *)dest, 4);
	CBufWrite(buffer, (const void *) src_a, 2);
	if (8 != CBufRead(buffer, (void *)dest, 8) 
	&& !memcmp((const void *) dest , "BBBBBAAA",8))
	{
		++fails;
		printf(RED"Test 3 c_buffer read FAILED reading over end \n"RESET_COLOR);
	}
	/*reading a struct across buffer end */
	CBufWrite(buffer_struct, (const void *) src_a, 14);
	CBufRead(buffer_struct, (void *)dest, 14);
	
	CBufWrite(buffer_struct, (const void *) &test_struct, sizeof(struct overlap_struct));
	CBufRead(buffer_struct, (void *)&test_struct_res, sizeof(struct overlap_struct));
	/*if ( memcmp((const void *) &test_struct_res, (const void *) &test_struct, sizeof(struct overlap_struct)))
	{
		++fails;
		printf(RED"Test 4 c_buffer read FAILED reading a struct across buffer end \n"RESET_COLOR);
		printf(RED"Test 4 struct x %d vs expected %d\n"RESET_COLOR, test_struct_res.x,  test_struct.x );
		printf(RED"Test 4 struct x %c vs expected %c\n"RESET_COLOR, test_struct_res.y,  test_struct.y );
		printf(RED"Test 4 struct x %lu vs expected %lu\n"RESET_COLOR, test_struct_res.z,  test_struct.z );
		
	}
	*/
	if (0 == fails)
	{
		printf(GREEN"c_buffer read PASSED\n"RESET_COLOR);
	}
	
		CBufDestroy(buffer_struct);		
		CBufDestroy(buffer);
}
