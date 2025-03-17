#ifndef __WS3_H__
#define __WS3_H__

void SumMatrixRows(int **matrix,int row_num, int col_num, int row_results[]);
/**************************************
SumMatrixRows PARAMETERS:
	A.int **matrix[] ; 
	B. int row_num num of matrix rows;
	C.
	B.int row_results[] an array with the same size of rows in Matrix. 
DESCRIPTION:
the function sums the matrix rows and insert the result to the relevant index in the row_results[].
*/
int lastOneStanding(int n);
int Josephus (int n);
void PrintAllEnv(char **envp);


#endif /*__WS3_H__*/

