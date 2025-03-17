/***************************************************************
*PROJECT: ws4 functions
*WRITER: Yair Singer
*REVIEWER: Adi Telem
*DATE: 9/7/23
*STATUS: send to review
*
****************************************************************/


#include "ws4.h"
#include <stdlib.h> /* exsit()*/
#include <stdio.h> /*printf */

typedef void (*LUT_printer)(void);

void ATPrintingIfElse()
{
	int user_input = 0;
	
	system("stty -icanon -echo");
	
	while (user_input != 27) /* exit when input is esc*/
	{
		user_input = getchar();
		
		if('A' == user_input || 'a' == user_input)
		{
			printf("A-pressed\n");
		}
		else if('T' == user_input || 't' == user_input)
		{
			printf("T-pressed\n");
		}
	}

	system("stty icanon echo");

	return;
}
	
void ATPrintingSwitchCase()
{

	int user_input = 0;
	system("stty -icanon -echo");
	
	while (27 != user_input)
	{
		user_input = getchar();

		switch (user_input) /* exit when input is esc*/
		{
		
			case 'A':
				printf("A-pressed\n");
				break;
			case 'a':
				printf("A-pressed\n");
				break;
			case 'T':
				printf("T-pressed\n");
				break;
			case 't':
				printf("T-pressed\n");
				break;			
		}
	}
	
	system("stty icanon echo");
	return;
}

void PrintA()
{
    printf("A-pressed\n");
}

void PrintT()
{
    printf("T-pressed\n");
}



void VoidFunc()
{
	return;
}


void ATPrintingLut()
{
	int user_input = 0, i = 0;
	
	LUT_printer lut_ascii[256] = {NULL};
	
	for (i = 0; i < 256 ;i++)
	{
		lut_ascii[i] = &VoidFunc;
	}
	
	lut_ascii['A'] = &PrintA;
	lut_ascii['T'] = &PrintT;
	lut_ascii['a'] = &PrintA;
	lut_ascii['t'] = &PrintT;
	
	system("stty -icanon -echo");
	while (user_input != 27)
	{
		user_input = getchar();
		lut_ascii[user_input]();
	}
	system("stty -icanon -echo");
	return;
}



