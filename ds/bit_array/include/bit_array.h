/***********************************************************
*PROJECT: Bit Array
*
*WRITER: Yair Singer
*
*REVIEWER: Noam Lazar
*
*STATUS: Approved
*
*DATE: 26/07/2023
***********************************************************/
#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h> /*size_t */

typedef size_t bit_arr_t;

/*
@Description: set a specific bit to 1.
@Parameters:
			 1. [arr] - a pointer to the bit array.
			 2. [bit_index] - the index of the bit to be set to 1.
@Return value: the modified number.
*/
bit_arr_t BitArrSetOn(bit_arr_t arr,size_t bit_index);

/*
@Description: set a specific bit to 0.
@Parameters:
			 1. [arr] - the bit array.
			 2. [bit_index] - the index of the bit to be set to 0.
@Return value: the modified number.
*/
bit_arr_t BitArrSetoff(bit_arr_t arr,size_t bit_index);

/*
@Description: set a specific bit to the value sent as an argument.
@Parameters:
			 1. [arr] - the bit array.
			 2. [bit_index] - the index of the bit to be set to value.
			 3. [bool] - the value of the bit. can be either 0 or 1.
@Return value: the modified number.
*/
bit_arr_t BitArrSetBit(bit_arr_t arr, size_t bit_index, unsigned int bool);

/*
@Description: set all bits to 1.
@Parameters: the bit array.
@Return value: bit array full of 1's.
*/
bit_arr_t BitArrSetAll(bit_arr_t arr);

/*
@Description: set all bits to 0.
@Parameters: the bit array.
@Return value: bit array full of 0's.
*/
bit_arr_t BitArrResetAll(bit_arr_t arr);

/*
@Description: return the value of the bit in bit_index position (0 or 1).
@Parameters:
			 1. [arr] - the bit array.
			 2. [bit_index] - the index of the bit to be set to value.
@Return value: the value of the bit in bit_index position (0 or 1).
*/
unsigned int BitArrGetVal(bit_arr_t arr, size_t bit_index);

/*
@Description: filps the bit in bit_index position.
@Parameters: the bit array.
@Return value: the modified array.
*/
bit_arr_t BitArrFlip(bit_arr_t arr, size_t bit_index);

/*
@Description: reverse the order of the bits in the array.
@Parameters: the bit array.
@Return value: the modified array.
*/
bit_arr_t BitArrMirror(bit_arr_t arr);

/*
@Description: ratote the all bits to the right n times circularly.
@Parameters:
			 1. [arr] - the bit array.
			 2. [n] - the number of right rotations to be performed.
@Return value: the modified array.
*/
bit_arr_t BitArrRotateRight(bit_arr_t arr, size_t n);

/*
@Description: rotate the all bits to the left n times circularly.
@Parameters:
			 1. [arr] - the bit array.
			 2. [n] - the number of left rotations to be performed.
@Return value: the modified array.
*/
bit_arr_t BitArrRotateLeft(bit_arr_t arr, size_t n);

/*
@Description: count the number of set bits.
@Parameters: the bit array.
@Return value: number of set bits.
*/
size_t BitArrCountOn(bit_arr_t arr);

/*
@Description: count the number of off bits
@Parameters: the bit array.
@Return value: number of off bits.
*/
size_t BitArrCountOff(bit_arr_t arr);

/*
@Description: make a string of the binary representation of the array.
@Parameters:
			 1. [arr] - the bit array.
			 2. [str] - the memory block allocated for the string.
@Return value: the string of the binary representation of the array.
*/
char* BitArrToString(bit_arr_t  arr, char *str);

/*
@Description: reverse the order of the bits in the array.
@Parameters: the bit array.
@Return value: the modified array.
*/
bit_arr_t ReadMirrorLut(const bit_arr_t value_to_mirror);

/*
@Description: writes the reversed bits to a LUT file. 
@Parameters: non.
@Return value: 0 for success, -1 for failure.
*/
int WriteMirrorLut();

#endif /*__BIT_ARRAY_H__*/
