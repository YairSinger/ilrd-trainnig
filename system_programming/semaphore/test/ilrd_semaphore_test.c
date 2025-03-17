#include <stdlib.h> /*malloc*/
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include "semaphore.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"



int main(int argc, char **argv)
{
	
	
	ManipulateSemaphore(argc, argv);
	return 0;
}



