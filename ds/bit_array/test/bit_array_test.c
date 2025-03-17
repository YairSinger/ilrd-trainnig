#include <stdio.h>
#include <string.h> /*strcmp */
#include "../include/bit_array.h"

void TestBitArrSetBit();
void TestBitArrSetAll();
void TestBitArrResetAll();
void TestBitArrGetVal();
void TestBitArrToString();
void TestBitArrMirror();
void TestBitArrCountOn();
void TestBitArrRotateRight();
void TestBitArrRotateLeft();
void TestBitArrFlip();
void TestBitArrCountOff();
void TestReadMirrorLut();


int main(void)
{
	bit_arr_t a1 = 250;
	if (242 == BitArrSetoff(a1,3))
	{
		printf("BitArrSetoff PASSED\n");
	}
	else 
	{
		printf("BitArrSetoff FAILED\n");
	}
	
	if (250 == BitArrSetOn(a1,3))
	{	
		printf("BitArrSetOn PASSED\n");
	}
	else 
	{
		printf("BitArrSetOn FAILED\n");
	}
	
	
	TestBitArrSetBit();
	TestBitArrSetAll();
	TestBitArrResetAll();
	TestBitArrGetVal();
	TestBitArrToString();
	TestBitArrMirror();
	TestBitArrCountOn();
	TestBitArrCountOff();
	TestBitArrRotateRight();
	TestBitArrRotateLeft();
	TestBitArrFlip();
	WriteMirrorLut();
	TestReadMirrorLut();
	return 0;
}


void TestBitArrSetBit() 
{
	bit_arr_t tests_values[5] = {250, 242 , 0,0, 0xffffffffffffffff};
	size_t tes_index_input[5] = {3, 3, 0, 0,63};
	unsigned int tes_bit_bool[5]   = {0, 1, 0,1,0};
	bit_arr_t tests_result[5] = {242, 250, 0,1,0x7fffffffffffffff};
	size_t i = 0;
	size_t fails = 0;
	
	for (;i < 5; ++i)
	{
		if (tests_result[i] != BitArrSetBit(tests_values[i], tes_index_input[i],tes_bit_bool[i]))
		{
			++fails;		
			printf("BitArrSetBit FAILED test No %lu\n", i+1);
		}
	}
	printf("BitArrSetBit PASSED %lu / 5 tests\n\n", 5-fails);
}

void TestBitArrSetAll()
{
	bit_arr_t tests_values[5] = {-200, 0, -1 , 0xffffffffffffff0, 0x7fffffffffffffff};
	bit_arr_t tests_result[5] = {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,0xffffffffffffffff};
	size_t i = 0;
	size_t fails = 0;
	
	for (;i < 5; ++i)
	{
		if (tests_result[i] != BitArrSetAll(tests_values[i]))
		{
			++fails;		
			printf("BitArrSetAll FAILED test No %lu\n", i+1);
		}
	}
	printf("BitArrSetAll PASSED %lu / 5 tests\n\n", 5-fails);
}


void TestBitArrResetAll()
{
	bit_arr_t tests_values[5] = {-200, 0, -1 , 0xffffffffffffff0, 0x7fffffffffffffff};
	bit_arr_t tests_result[5] = {0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,0x0000000000000000};
	size_t i = 0;
	size_t fails = 0;
	
	for (;i < 5; ++i)
	{
		if (tests_result[i] != BitArrResetAll(tests_values[i]))
		{
			++fails;		
			printf("BitArrResetAll FAILED test No %lu\n", i+1);
		}
	}
	printf("BitArrResetAll PASSED %lu / 5 tests\n\n", 5-fails);
}

void TestBitArrGetVal()
{
	bit_arr_t tests_values[7] = {0, 0,1,0xffffffffffffff0 , 0xffffffffff7fff,0xffffffffff7fff,0xffffffffff7fff};
	bit_arr_t result_holder = 0;
	char str_print_res[65] ={'\0'};
	char str_print_exp[65] ={'\0'};
	size_t tes_index_input[7] = {0, 64, 0, 4,15,14,16};
	unsigned int tests_result[7] = {0,0 , 1, 1,0,1,1};
	size_t i = 0;
	size_t fails = 0;
	
	for (;i < 7; ++i)
	{
		if (tests_result[i] != (result_holder = BitArrGetVal(tests_values[i],tes_index_input[i])))
		{
			++fails;		
			printf("BitArrGetVal FAILED test No %lu\n", i+1);
			printf(" %s\n %s expected\n", BitArrToString(result_holder,str_print_res),BitArrToString(tests_result[i],str_print_exp));
		}
	}
	printf("BitArrGetVal PASSED %lu / 7 tests\n\n", 7-fails);
}

void TestBitArrToString()
{
	bit_arr_t tests_values[4] = {0,1,0xfffffffffffffff0 , 0xffffffffffff7fff};
	char tests_result_res[4][65] = {'\0'};
	char tests_result_exp[4][65] = {
	{"0000000000000000000000000000000000000000000000000000000000000000"},
	{"0000000000000000000000000000000000000000000000000000000000000001"},
	{"1111111111111111111111111111111111111111111111111111111111110000"},
	{"1111111111111111111111111111111111111111111111110111111111111111"}};
	size_t i = 0;
	size_t fails = 0;
	
	
	for (;i < 4; ++i)
	{
		if (0 != (strcmp(tests_result_exp[i] , BitArrToString(tests_values[i],tests_result_res[i]))))
		{
			++fails;		
			printf("BitArrToString FAILED test No %lu\n", i+1);
		}
	}
	printf("BitArrToString PASSED %lu / 4 tests\n\n", 4-fails);
}

void TestBitArrMirror()
{
	bit_arr_t tests_values[4] = 
	{0x0000000000000000, 0x0000000000000001, 0x7fffffffffffffff,0x7fffffffffffff0f};
	bit_arr_t tests_result[4] = 
	{0x0000000000000000, 0x8000000000000000, 0xfffffffffffffffe,0xf0fffffffffffffe};
	bit_arr_t result_holder = 0;
	char str_print_res[65] ={'\0'};
	char str_print_exp[65] ={'\0'};
	size_t i = 0;
	size_t fails = 0;
	
	for (i = 0;i < 4; ++i)
	{
		if (tests_result[i] != (result_holder = BitArrMirror(tests_values[i])))
		{
			++fails;		
			printf("BitArrMirror FAILED test No %lu\n", i + 1);

			printf(" %s\n %s expected\n", BitArrToString(result_holder,str_print_res),BitArrToString(tests_result[i],str_print_exp));
		}
	}
	printf("BitArrMirror PASSED %lu / 4 tests\n\n", 4-fails);
}


void TestBitArrCountOn()
{
	bit_arr_t tests_values[5] = 
	{0x0000000000000000, 0x0000000000000001, 0x7fffffffffffffff,0x7fffffffffffff0f,0x7fffffbbffffff0f};
	bit_arr_t tests_result[5] = 
	{0, 1, 63, 59, 57};
	bit_arr_t result_holder = 0;
	
	size_t i = 0;
	size_t fails = 0;
	
	for (i = 0;i < 5; ++i)
	{
		if (tests_result[i] != (result_holder = BitArrCountOn(tests_values[i])))
		{
			++fails;		
			printf("BitArrCountOn FAILED test No %lu\n", i + 1);

			printf(" %lu\n %lu expected\n", result_holder, tests_result[i]);
		}
	}
	printf("BitArrCountOn PASSED %lu / 5 tests\n\n", 5-fails);
}

void TestBitArrCountOff()
{
	bit_arr_t tests_values[5] = 
	{0x0000000000000000, 0x0000000000000001, 0x7fffffffffffffff,0x7fffffffffffff0f,0x7fffffbbffffff0f};
	bit_arr_t tests_result[5] = 
	{64, 63, 1, 5, 7};
	bit_arr_t result_holder = 0;
	
	size_t i = 0;
	size_t fails = 0;
	
	for (i = 0;i < 5; ++i)
	{
		if (tests_result[i] != (result_holder = BitArrCountOff(tests_values[i])))
		{
			++fails;		
			printf("BitArrCountOff FAILED test No %lu\n", i + 1);

			printf(" %lu\n %lu expected\n", result_holder, tests_result[i]);
		}
	}
	printf("BitArrCountOff PASSED %lu / 5 tests\n\n", 5-fails);
}


void TestBitArrRotateRight()
{
	bit_arr_t tests_values[5] = {0x0000000000000010,0x7fffffffffffff0f,
	 0x7fffffffffffff0f, 0x0000000000000001,0x0000000000000001};
	size_t input_n_values[5] = {1,0,4,2,66};
	bit_arr_t tests_result[5] =	{0x0000000000000008,0x7fffffffffffff0f,
	 0xf7fffffffffffff0, 0x4000000000000000, 0x4000000000000000};
	bit_arr_t result_holder = 0;
	char str_print_res[65] ={'\0'};
	char str_print_exp[65] ={'\0'};
	
	size_t i = 0;
	size_t fails = 0;
	
	for (i = 0;i < 5; ++i)
	{
		if (tests_result[i] != 
		(result_holder = BitArrRotateRight(tests_values[i],input_n_values[i])))
		{
			++fails;		
			printf("BitArrRotateRight FAILED test No %lu\n", i + 1);

			printf(" %s\n %s expected\n", BitArrToString(result_holder,str_print_res),BitArrToString(tests_result[i],str_print_exp));
		}
	}
	printf("BitArrRotateRight PASSED %lu / 5 tests\n\n", 5-fails);
}


void TestBitArrRotateLeft()
{
	bit_arr_t tests_values[5] = {0x0000000000000010,0x7fffffffffffff0f,
	 0x7fffffffffffff0f, 0x0000000000000001,0x0000000000000001};
	size_t input_n_values[5] = {1,0,4,2,66};
	bit_arr_t tests_result[5] =	{0x0000000000000020,0x7fffffffffffff0f,
	 0xfffffffffffff0f7, 0x0000000000000004, 0x0000000000000004};
	bit_arr_t result_holder = 0;
	char str_print_res[65] ={'\0'};
	char str_print_exp[65] ={'\0'};
	
	size_t i = 0;
	size_t fails = 0;
	
	for (i = 0;i < 5; ++i)
	{
		if (tests_result[i] != 
		(result_holder = BitArrRotateLeft(tests_values[i],input_n_values[i])))
		{
			++fails;		
			printf("BitArrRotateLeft FAILED test No %lu\n", i + 1);

			printf(" %s\n %s expected\n", BitArrToString(result_holder,str_print_res),BitArrToString(tests_result[i],str_print_exp));
		}
	}
	printf("BitArrRotateLeft PASSED %lu / 5 tests\n\n", 5-fails);
}


void TestBitArrFlip() 
{
	bit_arr_t tests_values[3] = {0xffffffffffffffff};
	size_t tes_index_input[3] = {0};
	bit_arr_t tests_result[3] = {0xfffffffffffffffe};
	bit_arr_t result_holder = 0;
	char str_print_res[65] ={'\0'};
	char str_print_exp[65] ={'\0'};
	size_t i = 0;
	size_t fails = 0;
	
	for (;i < 1; ++i)
	{
		if (tests_result[i] != (result_holder = BitArrFlip(tests_values[i], tes_index_input[i])))
		{
			++fails;		
			printf("BitArrFlip FAILED test No %lu\n", i+1);
			printf(" %s\n %s expected\n", BitArrToString(result_holder,str_print_res),BitArrToString(tests_result[i],str_print_exp));
		}
	}
	printf("BitArrFlip PASSED %lu / 1 tests\n\n", 1-fails);
}

void TestReadMirrorLut()
{
	bit_arr_t i = 0; 
	
	for (i = 0; i < 8; ++i)
	{
		printf(" mirror of %lu, is %lu\n", i, ReadMirrorLut(i));
	}
}

