#include <stdio.h>  /*printf*/
#include "ws4.h"
void print_n(int n);


typedef char chr;
typedef unsigned int un_int;
typedef long int l_int;
typedef void (*printer_t)(int);
typedef int Array[5];



int main()
{
	
	int i = 5;
	chr c_test = 'k';
	l_int num = 2000000000;
	printer_t p = &print_n;
	Array id_num = {1, 2, 3, 4, 5};
	
	p(i);
	
	printf("%c\n", c_test);
	printf("%lu\n", num);
	printf("%d\n", id_num[2]);
	
	
	ATPrintingIfElse();
	printf("\nend of if else option\n");
	ATPrintingSwitchCase();
	printf("\nend of switch case option\n");
	ATPrintingLut();
  	printf("\nend of LUT option\n");
  	return 0;
}




void print_n(int n)
{
    printf("%d\n", n);
}


