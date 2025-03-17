#ifndef __WS9_H__
#include <stddef.h> /*size_t */
#define __WS9_H__

#define NAME_SIZE 10
typedef struct human_grades
{
	float bible;
	float history;
	float philosophy;
}human_t;

typedef struct real_grades
{
	float math;
	float physics;
	float biology;
}real_t;

typedef struct grades
{
	human_t human_g;
	real_t real_g;
	float sport_grade;
}grades_t;

typedef struct student
{
	char first_name[NAME_SIZE];
	char last_name[NAME_SIZE];
	grades_t stu_grades;	
}student_t;

int SaveStudentToBinaryFile(student_t *student, char * file_name);
 /*returns the number of students been writen to file.
 -1 if file couldent be open. */ 

int LoadFileToStudentStruct(student_t *student, char * file_name);

int IsStudentsEquals(student_t *s1,student_t *s2);

/*return 1 if equel 0 if students are different. */


#endif /*__WS9__*/

