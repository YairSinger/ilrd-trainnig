#include <stdio.h>
#include <stdlib.h> /*abs*/
#include "knight_tour2.h" /*api functions*/
#include "bit_array.h" /*print lut*/
#include <time.h> 	/*clock_t, clock() */


#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"


void TestKnightTour(void (*knightTour_func)(pos_t start, pos_t *path), char *func_name);
static int IsMovesValid(size_t *moves);
static int IsValidKnightStep(size_t position_1, size_t position_2);
static void ConvertToSizeT(pos_t *path, size_t *moves);
static pos_t SizeTToPosT(size_t index);

int main() 
{
	TestKnightTour(KnightTour, "KnightTour");
	TestKnightTour(KnightTourByWarnsdorff, "KnightTourByWarnsdorff");
	
   	return 0;
}	

void TestKnightTour(void (*knightTour_func)(pos_t start, pos_t *path), char *func_name)
{
	size_t moves[64];
	size_t i = 0;
	size_t first_step_pos = 0;
	int fails = 0;
	double total_time = 0;
	pos_t path[64] = {0};
	time_t t_start, t_end;
	
	t_start = time(NULL);
	for (first_step_pos = 0; first_step_pos < 64; ++first_step_pos)
	{
		knightTour_func(SizeTToPosT(first_step_pos), path);
		ConvertToSizeT(path, moves);
	
		if (!IsMovesValid(moves))
		{
			++fails;
			printf(RED"%s FAILED.idx [%lu] resulted moves are not valid\n"RESET_COLOR, func_name, first_step_pos);
			/*	
			for(i = 0 ; i < 64; ++i)
			{
				printf("move[%lu]",i);
				printf(RED"%lu, "RESET_COLOR, moves[i]);
			}*/
		}
	}
	
	t_end = time(NULL);
	total_time = (double) (t_end - t_start);
	if(0 == fails)
	{
		printf(GREEN"%s PASSED\n"RESET_COLOR, func_name);
		printf(GREEN"Total time for all positions results %f [sec]\n"RESET_COLOR, total_time);
	}

}
 
/************    STATIC FUNCTIONS      ***********/

static void ConvertToSizeT(pos_t *path, size_t *moves)
{
	size_t i = 0;
	for (i = 0; i < 64; ++i)
	{
		moves[i] = path[i].h * 8 + path[i].v;
	}
}


static int IsMovesValid(size_t *moves)
{
	size_t i = 1; 
	size_t res = moves[0];
	size_t expceted = 0;
	
	
	for (i = 1; i < 64 && IsValidKnightStep(moves[i], moves[i - 1]); ++i)
	{
		res += moves[i];
		expceted += i;
	}
	
	return (64 == i) && (expceted == res);
}

static pos_t SizeTToPosT(size_t index)
{
	pos_t pos = {0};
	pos.h = index / 8;
	pos.v = index % 8;
	return pos;
}

static int IsValidKnightStep(size_t position_1, size_t position_2)
{
	int x1 = (int)position_1 / 8;
	int y1 = (int)position_1 % 8;
	
	int x2 = (int)position_2 / 8;
	int y2 = (int)position_2 % 8;
	
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	
	
	return (2 == dx && 1 == dy) || ( 1 == dx && 2 == dy);
}

