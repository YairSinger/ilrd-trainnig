#include <stdio.h>
#include <stdlib.h> /*abs*/
#include <time.h> 	/*clock_t, clock() */
#include "watchdog.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

#define UNUSED (void)

void UserSpendTimeFunc(int duration);





int main(int argc, char **argv) 
{
	argv[0] = "/home/yair/git2/yair.singer/prjects/watchdog/bin/debug/watchdog_test";
	UNUSED argc;
	WDStart((const char **)argv);
	UserSpendTimeFunc(40);
	WDStop(2);
	printf("ended wachdog\n");
	
	
   	return 0;
}	



/**********************************************************************************/




void UserSpendTimeFunc(int duration)
{
  
    size_t counter = 0;
    clock_t start_time = clock();
    clock_t end_time = start_time + duration * CLOCKS_PER_SEC;

    while (clock() < end_time) {
        counter++;
    }

    printf("User Program ended Performed %lu computations in %d seconds\n", counter, duration);
}

