#include <stdio.h>  /*printf*/

#include "ws9.h"



int main(void)
{
	
  student_t yair = {"Yair", "Singer",{{99,80,81},{80,85,96}, 90}},yair_copy={0};
  char *file_name = "student.b";
  
  if ( SaveStudentToBinaryFile(&yair, file_name) == 0)
  {
  printf("save student passed\n");
  }
  
  if (LoadFileToStudentStruct(&yair_copy, file_name) == 0)
  {
  printf("student  load passed\n");
  }
  
  if (IsStudentsEquals(&yair, &yair_copy))
  {
  printf("students are identical\n");
  }
  else
  {
  	printf("students are unequal\n");
  }
  
  	return 0;
}

