#ifndef __WS5_H__
#define __WS5_H__

void Print10Structs();

 /* array of 10 structs containing int and a pointer to a printing function. the function print all the array ints. */

void Logger(char* file_name);

/* 
The logger file should be inserted in the argc[1] of the main.
The logger loops for input from the terminal entered by Enter press.
input options:

Default input is appending a string to the end of the logger by pressing Enter.
-remove 	to delete logger.
-count 		to count No of rows in the logger.
<????		prepend ??? at the beggining of logger.
-exit 		exits logger.
*/



#endif /*__WS5_H__*/

