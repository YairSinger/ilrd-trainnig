/***********************************************************
*PROJECT: 
*
*WRITER: Yair Singer
*
*REVIEWER: Lior Nachmias
*
*STATUS: Approved
*
*DATE: 25/07/2023
***********************************************************/
#ifndef __WS10_H__
#define __WS10_H__

#include <stddef.h> /*size_t */
#include <stdint.h> /*uint16_t*/

#define IS_LITTLE_ENDIAN (*(uint16_t *) "\0\x11" == 0x1100)


char* IntToString(int num, char *str, int base);
/*
* converts int value to string in reprasentation of the value in 
* desigered base. 
*
* @params:
*	 num to convert,
*	 char pointer with 32 bits,
*	 base to convert between 2-36/
* @return: no of chars written
*
*/


int StringToInt(const char *str, int base);
 /*converts string reprasentation of the value in known base to int.
*  
* @params:
*	 char pointer with 32 bits,
*	 base to convert between 2-36.

* @return: the converted int
*/

void PrintLettersFrom2StrOnly( unsigned char *str1, size_t size1,unsigned char *str2, size_t size2, unsigned char *str3, size_t size3);
/*gets 3 strings and prints the letters that appear in st1 and str2  but not in str3. 
*
*@return: none.
*/

int IsLittelEndian(void);
/*
test if machine is little endian or not.
* @return:1 if true, 0 if false.
*/

#endif /*__WS10__*/

