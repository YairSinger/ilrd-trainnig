#include <stdio.h>  /*printf*/

#include "ws5.h"



int main(int argc, char **argv)
{
	
	Print10Structs();
	if (NULL ==argv[1])
	{
		return 1;
	}
	if (argc < 2)
	{
		printf("missing file name to run logger\n");
		return 0;
	}
	Logger(argv[1]);
	
  
  
  	return 0;
}

