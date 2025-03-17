
/***********************************************************
* PROJECT: Knight Tour
* Group: OL 147-148      
* API Version:  1.0.0
* API Date 18.10.23  
*
***********************************************************/
#ifndef __KNIGHT_TOUR__H
#define __KNIGHT_TOUR__H

#include <stddef.h> /* size_t */
/*@Name: KnightTour
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
    start_index - the index on the board where the knight
                  will start its journey.
    moves       - buffer to record the knights's
                  journey.
@Return: 
    A pointer to the 'moves' buffer given as an
    argument.

@Time Complexity: 
    0(8 ^ (n^2)) - Backtracking
    O(n^2 log n) - Warnsdorff
@Space Complexity: 
    O(n^2)
*/
int KnightTour(size_t start_index, size_t *moves);



#endif /* __KNIGHT_TOUR__H */
