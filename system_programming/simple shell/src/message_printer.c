#include <unistd.h>
#include <stdlib.h>	/*exit*/
#include <stdio.h>

int main()
{
	printf("This program should exit in 5 seconds.\n");
	sleep(5);
	exit(0);
	return 0;
}
