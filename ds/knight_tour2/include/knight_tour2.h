/* -------------------------------------------------------------------------- *
 * FILE:        KNIGHT_TOUR.H 		                                          *
 * AUTHOR:      TAL ZAIF                                                      *
 * REVIEWER:    			                                                  *
 * DATE:        22.11.2023                                                    *
 * LAB:         OL-149                                                        *
 * DESCRIPTION: API KNIGHT TOUR                                               *
 * -------------------------------------------------------------------------- */

/* ------------------------- Preprocessor Directives ------------------------ */

#ifndef __ILRD_OL149_H_KNIGHT_TOUR__
#define __ILRD_OL149_H_KNIGHT_TOUR__

#include <stddef.h> /* size_t */

/* ---------------------------- Type Definitions ---------------------------- */

typedef struct position
{
	size_t h;	/* horizontal */
	size_t v;	/* vertical */
} pos_t;

/* -------------------------- Function Declarations ------------------------- */
/*
@Description:
                Receiving a starting index for a knight on
                a standard chess board, this function will
                record the knight journey along the board,
                keeping two basic rules:
                
                1. All of the squares must be visited by
                   the knight.
                2. Each square has to be visited exactly
                   once.
                
                The knight's journey  will be recorded into
                a buffer given as an argument,   where each 
                index describes the move number,   and each
                value describes the sqaure to be visited in
                that move.
    
@Parameters:
    start - the position on the board where the knight
                  will start its journey.
    path       - buffer to record the knights's
                  journey's positions.
@Return: 
   
@Time Complexity: 
    0(8 ^ (n^2)) - Backtracking
    O(n^2 log n) - Warnsdorff
@Space Complexity: 
    O(n^2)
*/
void KnightTour(pos_t start, pos_t *path);

void KnightTourByWarnsdorff(pos_t start, pos_t *path);

#endif /* __ILRD_OL149_H_KNIGHT_TOUR__ */


