/***********************************************************
*PROJECT: Serialize Struckts
*
*WRITER: Yair Singer
*
*REVIEWER: Shai Labbel
*
*STATUS: Approved
*
*DATE:19.7.23 
***********************************************************/
#include "ws9.h"
#include <stdio.h> /* FILE * */
#include <stddef.h> /* NULL */
#include <string.h> /*strcmp */
    

                      
	


int SaveStudentToBinaryFile(student_t *student, char * file_name)
{
	FILE * f = fopen(file_name,"w+");
	
	
	if (NULL == f)
	{
		fputs("failed to open file", stderr);
		return 1;
	}
		
	if (fwrite( &(student->first_name), sizeof(char),NAME_SIZE, f) != NAME_SIZE) 		
	{																													
		fputs("failed to write first name\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fwrite( &(student->last_name), sizeof(char),NAME_SIZE, f) != NAME_SIZE) 		
	{																													
		fputs("failed to write last name\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fwrite( &(student->stu_grades.human_g.bible), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to write grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fwrite( &(student->stu_grades.human_g.history), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to write history grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fwrite( &(student->stu_grades.real_g.math), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to write math grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fwrite( &(student->stu_grades.real_g.physics), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to write physics grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fwrite( &(student->stu_grades.real_g.biology), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to write biology grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fwrite( &(student->stu_grades.sport_grade), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to write sport grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (EOF == fclose(f))
	{
		fputs("Failed to close file\n" , stderr);
	}
	
	return 0;
}

int LoadFileToStudentStruct(student_t *student, char * file_name)
{
FILE * f = fopen(file_name,"r");

	
	if (NULL == f)
	{
		fputs("failed to open file", stderr);
		return 1;
	}
		
	if (fread( &(student->first_name), sizeof(char),NAME_SIZE, f) != NAME_SIZE) 		
	{																													
		fputs("failed to read first name\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fread( &(student->last_name), sizeof(char),NAME_SIZE, f) != NAME_SIZE) 		
	{																													
		fputs("failed to read last name\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fread( &(student->stu_grades.human_g.bible), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to read grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fread( &(student->stu_grades.human_g.history), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to read history grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fread( &(student->stu_grades.real_g.math), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to read math grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fread( &(student->stu_grades.real_g.physics), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to read physics grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fread( &(student->stu_grades.real_g.biology), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to read biology grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (fread( &(student->stu_grades.sport_grade), sizeof(float),1, f) != 1) 		
	{																													
		fputs("failed to read sport grade\n", stderr);			
		fclose(f);		
		return 1;		
	}
	
	if (EOF == fclose(f))
	{
		fputs("Failed to close file\n" , stderr);
	}
	
	return 0;
}

int IsStudentsEquals(student_t *s1,student_t *s2)
{
	int result = 1;
	

	
	if ((strcmp(s1->first_name, s2->first_name)))
	{
	 	printf("first not equal\n");
	 	result = 0;
	}
	 
	if ((strcmp(s1->last_name, s2->last_name)))
	{
	 	printf("last not equal\n");
	 	result = 0;
	}
	  
	if (!(s1->stu_grades.human_g.bible == s2->stu_grades.human_g.bible))
	{
	 	printf("bible not equal\n");
	 	result = 0;
	}
	 
	if (!(s1->stu_grades.human_g.history == s2->stu_grades.human_g.history))
	{
	 	printf("history not equal\n");
	 	result = 0;
	} 
	
	if (!(s1->stu_grades.real_g.math == s2->stu_grades.real_g.math))
	{
	 	printf("history not equal\n");
	 	result = 0;
	} 
	
	if (!(s1->stu_grades.real_g.physics == s2->stu_grades.real_g.physics))
	{
	 	printf("history not equal\n");
	 	result = 0;
	}
	 
	if (!(s1->stu_grades.real_g.biology == s2->stu_grades.real_g.biology))
	{
	 	printf("history not equal\n");
	 	result = 0;
	}
	 
	if (!(s1->stu_grades.sport_grade == s2->stu_grades.sport_grade))
	{
	 	printf("history not equal\n");
	 	result = 0;
	}
	 
	return result;
}

