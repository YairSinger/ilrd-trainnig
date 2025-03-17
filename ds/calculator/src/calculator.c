/***********************************************************
*PROJECT:Calculator
*
*WRITER: Yair Singer
*
*REVIEWER: Liad Atmon
*
*STATUS: Approved
*
*DATE: 27/09/2023
***********************************************************/



#include <assert.h> /*assert */
#include <stdlib.h> /*strtod */
#include <string.h> /*strlen */
#include "calculator.h" /*API functions */
#include "stack_b.h"	/*for num_stack, op_stack with more convinent StackPeek func*/

#define NUM_OF_OPARERATORS 8
#define UNUSED(x) (void)x
#define ASCII_SIZE 256

typedef enum input_type
{
    INV = 0,
    ZERO,
    NON_ZERO,
    PLUS,
    MINUS,
    MULTI,
    DIVID,
    L_BRACKET,
    R_BRAKET,
    END,
    NUM_OF_INPUT  /*must be last*/   
}input_type_t;

typedef enum state
{
	NUM = 0,
	OP,
	UNARY,
	NON_Z,
	TRAP,
	NUM_OF_STATES /*must be last*/  
}state_t;

typedef struct input_buffer
{
	double input;
	input_type_t input_type;
}input_buffer_t;



typedef void (*parse_func)(char **exp, input_buffer_t *input_buffer);

typedef calc_status_t (*event_handler)(double input, state_t *current_state,
						stack_t *num_stack, stack_t *op_stack);

typedef double (*evaluate_func)(double first, double second);



/*********************** Parsing functions ********************/
void Parsing(char **exp, input_buffer_t *input);

static void ParseNum(char **exp, input_buffer_t *input_buffer)
{
	input_type_t num_lut[2]= {NON_ZERO, ZERO};
	double num = strtod(*exp, exp);
	 
	input_buffer->input = num;
	input_buffer->input_type = num_lut[0 == input_buffer->input];
}



static void ParseInv(char **exp, input_buffer_t *input_buffer)
{
	input_buffer->input_type = INV;
	*exp += 1;
}

static void ParseSpace(char **exp, input_buffer_t *input_buffer)
{
	*exp += 1;
	Parsing(exp, input_buffer);
}

static void ParseOperator(char **exp, input_buffer_t *input_buffer)
{
	static input_type_t input_LUT[ASCII_SIZE] = 
	{
 		END, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, L_BRACKET, 
 		R_BRAKET, MULTI, PLUS, INV, MINUS, INV, DIVID, ZERO, NON_ZERO, 
 		NON_ZERO, NON_ZERO, NON_ZERO, NON_ZERO, NON_ZERO, NON_ZERO, NON_ZERO, 
 		NON_ZERO, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, INV, 
 		INV, INV, INV, INV
 	};
 	
 	
 	*((double *)&input_buffer->input) = **exp;
 	input_buffer->input_type = input_LUT[(int)(*((char*)*exp))];
	*exp += 1;
}

void Parsing(char **exp, input_buffer_t *input)
{
 	static parse_func ParseLut[ASCII_SIZE] = 
 	{
 		ParseOperator, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseSpace, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseOperator, ParseOperator, ParseOperator, ParseOperator, ParseInv, 
 		ParseOperator, ParseInv, ParseOperator, ParseNum, ParseNum, ParseNum, 
 		ParseNum, ParseNum, ParseNum, ParseNum, ParseNum, ParseNum, ParseNum, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, ParseInv, 
 		ParseInv, ParseInv
 	};
 			
	ParseLut[(int)**exp](exp, input);
}

/*********************** operation functions for StackEveluate *************/


/*===================== Empty ============================*/
static double Empty(double first, double second)
{
	UNUSED(first);
	UNUSED(second);
    return -1;
}

/*===================== Add ============================*/
static double Add(double first, double second)
{
    return (first + second);
}

/*===================== Sub ============================*/
static double Sub(double first, double second)
{
    return (first - second);
}

/*===================== Multi ============================*/
static double Multi(double first, double second)
{
    return (first * second);
}

/*===================== Div ============================*/
static double Div(double first, double second)
{
    return (first / second);
}


static double StackEveluate(stack_t *num_stack, stack_t *op_stack)
{
	double first = 0;
	double second = 0;
	double res = 0;
	char op = '\0';
	static evaluate_func op_lut[NUM_OF_OPARERATORS] = 
									{Empty,Empty,Multi,Add,Empty,Sub,Empty,Div};
	
	
	second = *((double *)StackPeek(num_stack));
	StackPop(num_stack);
	
	first = *((double *)StackPeek(num_stack));
	StackPop(num_stack);
	
	op = *((char *)StackPeek(op_stack)) - '(';	/*first oparator ASCII*/
	StackPop(op_stack);
	
	res = (op_lut[(int)op](first, second));
	StackPush(num_stack,(const void *) &res);
	return res;
}




static calc_status_t DummyHandler(double input, state_t *current_state, 
									stack_t *num_stack, stack_t *op_stack)
{
	UNUSED(input);
	UNUSED(current_state);
	UNUSED(num_stack);
	UNUSED(op_stack);
	
	return CALC_SUCCESS;
}



static calc_status_t ValidNum(double input, state_t *current_state, 
										stack_t *num_stack, stack_t *op_stack)
{
	UNUSED(op_stack);	
	StackPush(num_stack, (const void *)&input);
	
	*current_state = OP;
	return CALC_SUCCESS;
}




static calc_status_t Math(double input, state_t *current_state, 
								stack_t *num_stack, stack_t *op_stack)
{
	UNUSED(input);
	UNUSED(num_stack);
	UNUSED(op_stack);
	
	*current_state = TRAP;
	return CALC_MATH_ERROR;
}

static calc_status_t Syntax(double input, state_t *current_state, 
								stack_t *num_stack, stack_t *op_stack)
{
	UNUSED(input);
	UNUSED(num_stack);
	UNUSED(op_stack);	
			
	*current_state = TRAP;
	return CALC_SYNTEX_ERROR;
}

static calc_status_t ValidUnary(double input, state_t *current_state, 
									stack_t *num_stack, stack_t *op_stack)
{
	char char_input = (char) input;
	double zero = 0;
	
	StackPush(op_stack, (const void *)&char_input); /*highest precedence */
	StackPush(num_stack, (const void *)&zero);
		
	*current_state = UNARY;
	return CALC_SUCCESS;
}

static calc_status_t ValidLeftBracket(double input, state_t *current_state, 
										stack_t *num_stack, stack_t *op_stack)
{
	char char_input = (char) input;
	char multi = '*';
	
	UNUSED(num_stack);
	StackPush(op_stack, (const void *)&multi);
	StackPush(op_stack, (const void *)&char_input);	
	
	*current_state = NUM;
	return CALC_SUCCESS;
}
	
/*evaluates after  end '\0'*/
static calc_status_t EvaluateEnd(double input, state_t *current_state, 
									stack_t *num_stack, stack_t *op_stack)
{	
	char op = *((char *)StackPeek(op_stack));
	calc_status_t stat_lut[2] = {CALC_SUCCESS, CALC_SYNTEX_ERROR};
	state_t state_lut[2] = {OP, TRAP};
	
	UNUSED(input);
	
	while (!StackIsEmpty(op_stack)  && op != '(')
	{
		StackEveluate(num_stack, op_stack);
		op = *((char *)StackPeek(op_stack));
	}
	
	*current_state = state_lut['(' == op];
	return stat_lut['(' == op];	
}





/*evaluates after right bracket*/
static calc_status_t EvaluateBrackets(double input, state_t *current_state, 
									stack_t *num_stack, stack_t *op_stack)
{
	calc_status_t stat_lut[2] = {CALC_SUCCESS, CALC_MATH_ERROR};
	state_t state_lut[2] = {OP, TRAP};	
	char op = *((char *)StackPeek(op_stack));
	double num_stack_top = *((double *)StackPeek(num_stack));;
	
	UNUSED(input);
	
	/** '0' != num_stack_top to detect MATH_ERROR after brackets are removed*/
	while ('(' != op && !StackIsEmpty(op_stack) && '0' != num_stack_top)
	{
		 num_stack_top = StackEveluate(num_stack, op_stack);
		 op = *((char *)StackPeek(op_stack));
	}
	
	if (StackIsEmpty(op_stack))
	{
		*current_state = TRAP;
		return CALC_SYNTEX_ERROR;
	}
	
	StackPop(op_stack); /*popping '(' */
	op = *((char *)StackPeek(op_stack));
	
	*current_state = state_lut[0 == num_stack_top && '/' == op];
	return stat_lut[0 == num_stack_top && '/' == op];
}





static calc_status_t ValidOperator(double input, state_t *current_state, 
										stack_t *num_stack, stack_t *op_stack)
{
	char char_input = (char) input;
	char op = *((char *)StackPeek(op_stack)) - '('; /*for smaller lut*/
	int presedency_lut[NUM_OF_OPARERATORS] = {0,-3,2,1,-3,1,-3,2};
	
	while (!StackIsEmpty(op_stack) && 
					presedency_lut[(int)op] >= presedency_lut[char_input - '('])
	{
		StackEveluate(num_stack, op_stack);
		op = *((char *)StackPeek(op_stack)) - '(';
	}
		
	StackPush(op_stack, (const void *)&char_input);
	
	*current_state = NUM;
	return CALC_SUCCESS;
}




static calc_status_t Go2NonZ(double input, state_t *current_state, 
									stack_t *num_stack, stack_t *op_stack)
{
	char char_input = (char) input;
	char op = *((char *)StackPeek(op_stack)) - '('; /*for smaller lut*/
	int presedency_lut[NUM_OF_OPARERATORS] = {0,-3,2,1,-3,1,-3,2};
			 
	while (!StackIsEmpty(op_stack) && presedency_lut[(int)op] >= presedency_lut[char_input - '('])
	{
		StackEveluate(num_stack, op_stack);
		op = *((char *)StackPeek(op_stack)) - '(';
	}
	
	StackPush(op_stack, (const void *)&char_input);
	
	*current_state = NON_Z;
	return CALC_SUCCESS;
}





static calc_status_t LeftBNum(double input, state_t *current_state, 
									stack_t *num_stack, stack_t *op_stack)
{
	char char_input = (char) input;
	
	UNUSED(num_stack);			
	StackPush(op_stack, (const void *)&char_input);
	
	*current_state = NUM;
	return CALC_SUCCESS;
}




static calc_status_t LeftBNonZ(double input, state_t *current_state, 
									stack_t *num_stack, stack_t *op_stack)
{
	char char_input = (char) input;
	
	UNUSED(num_stack);			
	StackPush(op_stack, (const void *)&char_input);
	
	*current_state = NUM;
	return CALC_SUCCESS;
}



/**********************   API Functions   *************************/

calc_status_t Calc(const char *exp, double *res)
{
	char *head = (char *)exp;	
	input_buffer_t input = {0, NON_ZERO};	
	state_t current_state = NUM;
	calc_status_t status = CALC_SUCCESS;
	
	stack_t *num_stack = StackCreate(strlen(head), sizeof(double));
	stack_t *op_stack = NULL;
		
	
	static event_handler events_lut[NUM_OF_STATES][NUM_OF_INPUT] = 
	{
		{Syntax, ValidNum, ValidNum, ValidUnary, ValidUnary, 
		Syntax, Syntax,LeftBNum,Syntax,Syntax},
		
		{Syntax, Syntax, Syntax, ValidOperator, ValidOperator, 
		ValidOperator, Go2NonZ, ValidLeftBracket, EvaluateBrackets, EvaluateEnd},
		
		{Syntax, ValidNum, ValidNum, Syntax, Syntax, 
		Syntax, Syntax,ValidOperator,Syntax,Syntax},
		
		{Syntax, Math, ValidNum, ValidUnary, ValidUnary, 
		Syntax,Syntax,LeftBNonZ,Syntax,Syntax},
		
		{Syntax, DummyHandler, DummyHandler, DummyHandler, DummyHandler,
		DummyHandler,DummyHandler,DummyHandler,DummyHandler}
	};
	
	if (NULL == num_stack)
	{
		return CALC_ALLOC_FAILED;
	}
	
	op_stack = StackCreate(strlen(head), sizeof(char));
	
	if (NULL == op_stack)
	{
		free(num_stack);
		return CALC_ALLOC_FAILED;
	}
		
	while(END != input.input_type && CALC_SUCCESS == status)
	{
		Parsing(&head, &input);
		status = events_lut[current_state][input.input_type](input.input, &current_state,num_stack, op_stack);
	}
	
	*res = *((double *)StackPeek(num_stack));
	
	StackDestroy(num_stack);
	StackDestroy(op_stack);
	
	return status;
}
