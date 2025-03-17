#include <stdio.h>  /*printf, printf*/
#include <string.h> /*strcmp*/

#include "testing_unit.h" /*header of this testing library*/

/*---Macros---*/
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

/*---Global Variable---*/
static size_t tests_passed = 0;
static size_t tests_failed = 0;

/*----Tests Functions---*/
void TestExpected(const char *test_name, int actual, int expected)
{
	if (actual == expected)
	{
		printf(GREEN "Test: '%s' - PASSED!\n" RESET, test_name);
		++tests_passed;
	}
	else
	{
		fprintf(stderr,
		        RED "Test '%s' - FAILED (Expected: %d, Actual: %d)\n" RESET,
		        test_name, expected, actual);
		++tests_failed;
	}
}

void TestIsEqual(const char *test_name, const void *actual, const void *expected)
{
	if (0 == strcmp((char *)actual, (char *)expected))
	{
		printf(GREEN "Test: '%s' - PASSED!\n" RESET, test_name);
		++tests_passed;
	}
	else
	{
		fprintf(stderr,
		        RED "Test '%s' - FAILED (Expected: %s, Actual: %s)\n" RESET,
		        test_name, (char *)expected, (char *)actual);
		++tests_failed;
	}
}

void PrintTestResults(void)
{
	size_t total_tests = tests_passed + tests_failed;
	printf("\n*** Test Results ***\n");
	printf(GREEN "Tests Passed: %lu/%lu\n" RESET, tests_passed, total_tests);
	printf(RED "Tests Failed: %lu/%lu\n" RESET, tests_failed, total_tests);
}

