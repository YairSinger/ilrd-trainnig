
#ifndef __CALC_H__
#define __CALC_H__

typedef enum calc_status
{
    CALC_SUCCESS,
    CALC_SYNTEX_ERROR,
    CALC_MATH_ERROR,
    CALC_ALLOC_FAILED
} calc_status_t;

/*
 * Calculate the result of a mathematical expression represented as a C-style string.
 * 
 * @param exp The mathematical expression to be evaluated. This should be a
 *            null-terminated string containing valid mathematical operations
 *            and operands.
 * @param res A pointer to a double variable where the result of the evaluation
 *            will be stored. The caller should allocate memory for `res`.
 * 
 * @return - `SUCCESS`: The expression was successfully evaluated, and the result
 *                      is stored in `res`.
 *         - `SYNTAX_ERROR`: There was a syntax error in the expression, making
 *                          it invalid for evaluation.
 *         - `MATH_ERROR`: An error occurred during the mathematical computation,
 *                        such as division by zero.
 *         - `ALLOC_FAILED`: Memory allocation for evaluation failed. 
 */
calc_status_t Calc(const char *exp, double *res);


#endif /* __CALC_H__ */
