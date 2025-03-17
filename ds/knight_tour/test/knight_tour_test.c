#include <stdio.h>
#include <stdlib.h> /*abs*/
#include "knight_tour.h" /*api functions*/
#include "bit_array.h" /*print lut*/


#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"



static int IsMovesValid(size_t *moves);
static int IsValidKnightStep(size_t position_1, size_t position_2);

int main() 
{
	size_t moves[64];
	size_t i = 0;
	size_t first_step_pos = 0;
	int fails = 0;
	int res = 0;
	
	for (first_step_pos = 0; first_step_pos < 64; ++first_step_pos)
	{
		res = KnightTour(first_step_pos, moves);
		if (0 != res)
		{
			++fails;
			printf(RED"\n%lu Start position KnightTour FAILED"RESET_COLOR,first_step_pos);
			printf(RED"KnightTour FAILED. returned status is %d vs 0 expected\n"RESET_COLOR,res);
		}
		
		if (!IsMovesValid(moves))
		{
			++fails;
			printf(RED"\n%lu Start position KnightTour FAILED"RESET_COLOR,first_step_pos);
			printf(RED"KnightTour FAILED. resulted moves are not valid\n"RESET_COLOR);
		
			
			for(i = 0 ; i < 64; ++i)
			{
				printf("move[%lu]",i);
				printf(RED"%lu, "RESET_COLOR, moves[i]);
			}
		}
	}
		
	if(0 == fails)
	{
		printf(GREEN"KnightTour PASSED\n"RESET_COLOR);
	} 
	  
   	return 0;
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
