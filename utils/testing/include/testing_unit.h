#ifndef __TESTING_UNIT_H__
#define __TESTING_UNIT_H__

/*---Macro---*/
#define FIRST_NAME_SIZE 100
#define LAST_NAME_SIZE 100

/*---typedef---*/
typedef struct student_t
{
	char first_name[FIRST_NAME_SIZE];
	char last_name[LAST_NAME_SIZE];
} student_t;


/*---Declerations---*/
void TestExpected(const char *test_name, int actual, int expected);
void TestIsEqual(const char *test_name, const void *actual, const void *expected);
void PrintTestResults(void);

#endif /*__TESTING_UNIT_H__*/

