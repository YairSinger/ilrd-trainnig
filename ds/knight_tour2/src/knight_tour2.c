
/* -------------------------------------------------------------------------- *
 * FILE:        KNIGHT_TOUR.H 		                                          *
 * AUTHOR:      YAIR SINGER                                                   *
 * REVIEWER:    TAL ZAIF			                                          *
 * DATE:        26.11.2023 													  * 
 * STATUS: 		APPROVED	                                                  *
 * LAB:         OL-149                                                        *
 * DESCRIPTION: API KNIGHT TOUR                                               *
 * -------------------------------------------------------------------------- */

#include <assert.h> /*assert */
#include <string.h> /*strlen */
#include <stdio.h> /*printf in PrintLut*/
#include <time.h> 	/*clock_t, clock() */
#include "knight_tour2.h" 
#include "bit_array.h"

#define BOARD_SIZE 64
#define MAX_MOVMENTS_OP 8
#define ROW_COL_SIZE 8
#define NO_STEP_AVAILABLE 65
#define TIME_LIMIT 5

#define UNUSED(var) (void)var
#define SUCCSESS 0
#define FAIL 1

typedef size_t (*find_func)(bit_arr_t *steps_lut,bit_arr_t untested_steps, 
							bit_arr_t board);

static int IsValidStep(int x, int y);
static void InitStepsLut(bit_arr_t *lut);
static int KnightTourRec(bit_arr_t board, bit_arr_t *steps_lut, size_t *moves, 
				size_t position_i, clock_t start_time, find_func find_next_i);
static size_t FindNextStepWalsdrof(bit_arr_t *steps_lut,
				bit_arr_t untested_steps, bit_arr_t board);
static size_t FindFirstBitOn(bit_arr_t *steps_lut,
				bit_arr_t untested_steps, bit_arr_t board);
static void IdxToPos(pos_t *path, size_t *moves);

/******************	API FUNCTIONS 	*************/

void KnightTour(pos_t start, pos_t *path)
{
	bit_arr_t board = ~0; /*set bits are valid un-visited positions*/
	bit_arr_t steps_lut[BOARD_SIZE] = {0};
	clock_t start_time;
	size_t moves[BOARD_SIZE] = {0};
	size_t start_index = 0; 
	int status = 0;
	size_t i = 0;
	
	assert(BOARD_SIZE > start_index); 
	assert(NULL != path);
	
	start_index = 8 * start.h + start.v;
	InitStepsLut(steps_lut); /*set bits are valid steps per position*/
	start_time = clock();
	status = KnightTourRec(board, steps_lut, moves, 
							start_index, start_time, FindFirstBitOn);
	if (0 == status)
	{
		IdxToPos(path, moves);
	}
}


void KnightTourByWarnsdorff(pos_t start, pos_t *path)
{
	bit_arr_t board = ~0; /*set bits are valid un-visited positions*/
	bit_arr_t steps_lut[BOARD_SIZE] = {0};
	clock_t start_time;
	size_t moves[BOARD_SIZE] = {0};
	size_t start_index = 8 * start.h + start.v;
	int status = 0;
	size_t i = 0;
	
	assert(BOARD_SIZE > start_index); 
	assert(NULL != path);
	
	InitStepsLut(steps_lut); /*set bits are valid steps per position*/
	start_time = clock();
	status = KnightTourRec(board, steps_lut, moves, 
							start_index, start_time, FindNextStepWalsdrof);
	if (0 == status)
	{
		IdxToPos(path, moves);
	}
}




/************    STATIC FUNCTIONS      ***********/
static int KnightTourRec(bit_arr_t board, bit_arr_t *steps_lut, size_t *moves, 
				size_t position_i, clock_t start_time, find_func find_next_i)
{
	size_t next_step = 0;
	bit_arr_t valid_steps = 0;
	bit_arr_t untested_steps = 0;
	int option_status = 1;
	
	if(TIME_LIMIT < ((double)clock()- start_time)/ CLOCKS_PER_SEC)
	{
		return FAIL;
	}
		
	board = BitArrSetoff(board,position_i);
	*moves = position_i;
	valid_steps = steps_lut[position_i] & board;
	untested_steps = valid_steps; 
	
	if (0 != board)
	{
		while(0 != option_status)
		{
			next_step = find_next_i(steps_lut, untested_steps, board);
			if (NO_STEP_AVAILABLE == next_step)
			{
				return FAIL;
				
			}
			
			option_status = KnightTourRec(board, steps_lut, moves + 1, 
											next_step, start_time, find_next_i);
			untested_steps = BitArrSetoff(untested_steps,next_step); 
								/* remove tested option from untested bit arr*/	
		}
	}
	
	return SUCCSESS;
}	


static size_t FindFirstBitOn(bit_arr_t *steps_lut,bit_arr_t untested_steps, 
								bit_arr_t board)
{
	size_t i = 0;
	
	UNUSED(steps_lut);
	UNUSED(board);
	for (i = 0; i < BOARD_SIZE && 0 != untested_steps; ++i)
	{
		if (BitArrGetVal(untested_steps, i))
		{
			return i;
		}
	}
	
	return NO_STEP_AVAILABLE;
}

static void IdxToPos(pos_t *path, size_t *moves)
{
	size_t i = 0;
	
	for (i = 0; i < BOARD_SIZE; ++i)
	{
		path[i].h = moves[i] / ROW_COL_SIZE;
		path[i].v = moves[i] % ROW_COL_SIZE;
	}
}



static size_t FindNextStepWalsdrof(bit_arr_t *steps_lut, 
									bit_arr_t untested_steps, bit_arr_t board)
{
	size_t min_i = NO_STEP_AVAILABLE;
	size_t min_steps = MAX_MOVMENTS_OP + 1;
	size_t temp = MAX_MOVMENTS_OP + 1;
	size_t i = 0;
	
	for (i = 0; i < BOARD_SIZE && 0 != untested_steps; ++i)
	{
		if (BitArrGetVal(untested_steps, i) &&
			 min_steps > (temp = BitArrCountOn(steps_lut[i] & board)))
		{
			min_steps = temp;
			min_i = i; 
		}
	}
	
	return min_i;
}




static int IsValidStep(int x, int y)
{
	return (0 <= x && x < ROW_COL_SIZE && 0 <= y && y < ROW_COL_SIZE);
}


static void InitStepsLut(bit_arr_t *lut)
{
	size_t position = 0;
	size_t movment_i = 0;
	
	int row[MAX_MOVMENTS_OP] = {2, 1, -1, -2, -2, -1, 1, 2};
	int col[MAX_MOVMENTS_OP] = {1 ,2 , 2, 1, -1, -2, -2, -1};
	
	int x = 0;
	int y = 0;
	size_t bit_to_set = 0;
	
	assert(NULL != lut);
		
	for (position = 0; position < BOARD_SIZE; ++position)
	{
		lut[position] = BitArrResetAll(lut[position]);
		x = (int)position / ROW_COL_SIZE;
		y = (int)position % ROW_COL_SIZE;
		for(movment_i = 0; movment_i < MAX_MOVMENTS_OP; ++movment_i)
		{
			if(IsValidStep(x + row[movment_i], y + col[movment_i]))
			{
				bit_to_set = ROW_COL_SIZE * (x + row[movment_i]) + 
							y + col[movment_i];
				lut[position] = BitArrSetOn(lut[position], bit_to_set);
			}
		}
	}		
}

