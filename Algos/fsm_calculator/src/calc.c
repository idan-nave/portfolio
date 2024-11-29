/*
  Project: Calculator (State Machine Project)
  Reviewer: Ahmad
  Date: 03/10/2023
  Version: 1.0 - Publication

  Project Overview: API for a Calculator based on State Machine
*/
/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <errno.h>              /* errno */
#include <stdio.h>              /* printf */
#include <stdlib.h>             /* strtod */
#include <stddef.h>             /* size_t */
#include "stack.h"              /* stack_t */
#include "calc.h"               /* stack_t */

/*****************************************************************************/
/********************************* Type Definitions **************************/
/*****************************************************************************/

#define ASCII_SIZE                  256
#define BASE10_SYMBOL_RANGE         10 
#define MIN_OPERANDS_FOR_OP         2 
#define OPEN_P_CHAR                 '('
#define DUMMY_CHAR                  '#'
#define SYMBOL_SIZE                 sizeof(double)
/*#define EXP_MAX_LEN                100*/ 

/******************************** Enumerators *********************************/

typedef enum {FALSE = 0, TRUE} calc_boolean_ty;
typedef enum  { WAIT_OPERAND = 0, WAIT_OPERATOR, ERROR, NUM_OF_STATES } calc_state_ty;
typedef enum  { LUTS_UNINITIALIZED = 0, LUTS_INITIALIZED } lut_state_ty;

typedef enum
    { DUMMY_OP = 0,PLUS, MINUS, DIVIDE, MULTIPLY, OPEN_PARAN, CLOSE_PARAN,NUM_OF_OPERATORS, OPERAND, INVALID,  EOI, NUM_OF_INPUTS} calc_input_ty;
typedef enum
    { DUMMY_OP_P = 0, PARAN_P, PLUS_P, MINUS_P = PLUS_P, DIVIDE_P, MULTIPLY_P = DIVIDE_P} op_precedence_ty;


/******************************** Prototypes *********************************/

/*Function to evaluate a result of current expression, and update it in stack*/
typedef double (*op_func_ty)(double* left_op, double right_op, int *status);

/*Function to cause transitions between calculator states, based on LUT index*/
typedef calc_state_ty (*calc_handler_ty)(int *status, char **input);

/********************************* Objects ***********************************/

typedef struct operator
{
	op_precedence_ty precedence;
	op_func_ty action_func;
}operator_ty;
/*****************************************************************************/
/************************************* Globals *******************************/
/*****************************************************************************/

calc_handler_ty g_handlers_lut[NUM_OF_STATES][NUM_OF_INPUTS];
operator_ty g_operators[NUM_OF_OPERATORS];
calc_input_ty g_inputs[ASCII_SIZE];

stack_t* g_operators_stack = NULL;
stack_t* g_operands_stack = NULL;


/*****************************************************************************/
/********************* Static Functions Declerations *************************/
/*****************************************************************************/

/************ LUT initializers ***********/
static void InitCalcHandlersLUT(void);
static void InitInputsLUT(void);
static void InitCalcOperatorsArray(void);

/************ Transition Handlers ***********/
static calc_state_ty OperandHandler(int *status, char **input);
static calc_state_ty OperatorHandler(int *status, char **input);
static calc_state_ty OpenParanHandler(int *status, char **input);
static calc_state_ty CloseParanHandler(int *status, char **input);
static calc_state_ty ErrorHandler(int *status, char **input);
static calc_state_ty EOIHandler(int *status, char **input);

/************ Calc Evaluators ***********/

static void Eval(int *status);
static double CalcAdd(double* left_op, double right_op, int *status);
static double CalcSub(double* left_op, double right_op, int *status);
static double CalcMul(double* left_op, double right_op, int *status);
static double CalcDiv(double* left_op, double right_op, int *status);


/*****************************************************************************/
/********************* Static Functions Definitions **************************/
/*****************************************************************************/

/*************************** LUT initializers ********************************/

/*{ DUMMY_OP = 0, INVALID, PLUS, MINUS, DIVIDE, MULTIPLY, OPEN_PARAN, CLOSE_PARAN, OPERAND, EOI, NUM_OF_INPUTS } calc_input_ty;*/

/* Function to perform Initializing of transition handlers LUT:*/
static void InitCalcHandlersLUT(void)
{
    g_handlers_lut[WAIT_OPERAND][DUMMY_OP] = ErrorHandler;
    g_handlers_lut[WAIT_OPERAND][INVALID] = ErrorHandler;
    g_handlers_lut[WAIT_OPERAND][PLUS] = OperatorHandler;
    g_handlers_lut[WAIT_OPERAND][MINUS] = OperatorHandler;
    g_handlers_lut[WAIT_OPERAND][DIVIDE] = ErrorHandler;
    g_handlers_lut[WAIT_OPERAND][MULTIPLY] = ErrorHandler;
    g_handlers_lut[WAIT_OPERAND][OPEN_PARAN] = OpenParanHandler;
    g_handlers_lut[WAIT_OPERAND][CLOSE_PARAN] = ErrorHandler;
    g_handlers_lut[WAIT_OPERAND][OPERAND] = OperandHandler;
    g_handlers_lut[WAIT_OPERAND][EOI] = ErrorHandler;
    
    g_handlers_lut[WAIT_OPERATOR][DUMMY_OP] = ErrorHandler;
    g_handlers_lut[WAIT_OPERATOR][INVALID] = ErrorHandler;
    g_handlers_lut[WAIT_OPERATOR][PLUS] = OperatorHandler;
    g_handlers_lut[WAIT_OPERATOR][MINUS] = OperatorHandler;
    g_handlers_lut[WAIT_OPERATOR][DIVIDE] = OperatorHandler;
    g_handlers_lut[WAIT_OPERATOR][MULTIPLY] = OperatorHandler;
    g_handlers_lut[WAIT_OPERATOR][OPEN_PARAN] = ErrorHandler;
    g_handlers_lut[WAIT_OPERATOR][CLOSE_PARAN] = CloseParanHandler;
    g_handlers_lut[WAIT_OPERATOR][OPERAND] = ErrorHandler;
    g_handlers_lut[WAIT_OPERATOR][EOI] = EOIHandler;

    g_handlers_lut[ERROR][DUMMY_OP] = ErrorHandler;
    g_handlers_lut[ERROR][INVALID] = ErrorHandler;
    g_handlers_lut[ERROR][PLUS] = ErrorHandler;
    g_handlers_lut[ERROR][MINUS] = ErrorHandler;
    g_handlers_lut[ERROR][DIVIDE] = ErrorHandler;
    g_handlers_lut[ERROR][MULTIPLY] = ErrorHandler;
    g_handlers_lut[ERROR][OPEN_PARAN] = ErrorHandler;
    g_handlers_lut[ERROR][CLOSE_PARAN] = ErrorHandler;
    g_handlers_lut[ERROR][OPERAND] = ErrorHandler;
    g_handlers_lut[ERROR][EOI] = ErrorHandler;
}

/* Function to perform Initializing of ASCII LUT to mask unsupported symbols */
static void InitInputsLUT(void)
{
    size_t i = 0;

    for (; i < ASCII_SIZE; i++)
    {
        g_inputs[i] = INVALID;
    }

    i = 0;
    for (; i < BASE10_SYMBOL_RANGE; i++)
    {
        g_inputs[(size_t)('0' + i)] = OPERAND;
    }

    g_inputs['('] = OPEN_PARAN;
    g_inputs[')'] = CLOSE_PARAN;
    g_inputs['+'] = PLUS;
    g_inputs['-'] = MINUS;
    g_inputs['/'] = DIVIDE;
    g_inputs['*'] = MULTIPLY;
    g_inputs['\0'] = EOI;
    g_inputs['#'] = DUMMY_OP;
}

/* Function to perform Initializing of Operators array:*/
static void InitCalcOperatorsArray(void)
{
    g_operators[PLUS].precedence = PLUS_P;
    g_operators[PLUS].action_func = CalcAdd;

    g_operators[MINUS].precedence = MINUS_P;
    g_operators[MINUS].action_func = CalcSub;

    g_operators[MULTIPLY].precedence = MULTIPLY_P;
    g_operators[MULTIPLY].action_func = CalcMul;

    g_operators[DIVIDE].precedence = DIVIDE_P;
    g_operators[DIVIDE].action_func = CalcDiv;

    g_operators[DUMMY_OP].precedence = DUMMY_OP_P;
    g_operators[DUMMY_OP].action_func = NULL;

    g_operators[OPEN_PARAN].precedence = PARAN_P;
    g_operators[OPEN_PARAN].action_func = NULL;
}

/***************************** Calc Evaluators **********************************/

/* Calculate addition of top two operands */
static double CalcAdd(double* left_op, double right_op, int *status)
{
    assert(status != NULL);
    assert(left_op != NULL);
    assert(status != NULL);

    *left_op = *left_op + right_op;
    return *left_op ;
}

/* Calculate subtraction of top two operands */
static double CalcSub(double* left_op, double right_op, int *status)
{
    assert(status != NULL);
    assert(left_op != NULL);
    assert(status != NULL);


    *left_op = *left_op - right_op;
    return *left_op;
}

/* Calculate multiplication of top two operands */
static double CalcMul(double* left_op, double right_op, int *status)
{
    assert(status != NULL);
    assert(left_op != NULL);
    assert(status != NULL);


    *left_op = *left_op * right_op;
    return *left_op ;
}

/* Calculate division of top two operands */
static double CalcDiv(double* left_op, double right_op, int *status)
{
    assert(status != NULL);
    assert(left_op != NULL);
    assert(status != NULL);


    if (0 == right_op)
    {
        *status = MATH_ERROR;
        return UNSAFE_RESULT;
    }
    *left_op = *left_op / right_op;
    return *left_op ;
}

/*************************** Transition Handlers ********************************/

static void Eval(int *status)
{
    double right_oprnd = *((double*)StackPeek(g_operands_stack));
    double* left_oprnd = NULL;
    operator_ty stack_op = g_operators[g_inputs[(unsigned char)*((char*)StackPeek(g_operators_stack))]];

    assert(status != NULL);

    StackPop(g_operands_stack);
    left_oprnd = (double*)StackPeek(g_operands_stack);

    *left_oprnd =  stack_op.action_func(left_oprnd, right_oprnd, status);
    StackPop(g_operators_stack);
}

static calc_state_ty OperandHandler(int *status, char **input)
{
    double operand = strtod(*input, input);

    assert(status != NULL);
    assert(input != NULL);
    assert(*input != NULL);
    
    if ( FAILURE == StackPush(g_operands_stack, &operand))
    {
        *status = FAILURE;
        errno = EPERM;
        perror("StackPush Failure");
        return ERROR; 
    }

    return WAIT_OPERATOR; 
}

static calc_state_ty OperatorHandler(int *status, char **input)
{
    operator_ty stack_op = g_operators[g_inputs[(unsigned char)(*((char*)StackPeek(g_operators_stack)))]];
    operator_ty curr_op = g_operators[(g_inputs[(unsigned char)(**input)])];

    assert(status != NULL);
    assert(input != NULL);
    assert(*input != NULL);

    while (curr_op.precedence <= stack_op.precedence)
    {
       Eval(status);

       if (MATH_ERROR == *status)
        {
            return ERROR;
        }
        stack_op = g_operators[g_inputs[(unsigned char)(*((char*)StackPeek(g_operators_stack)))]];
    }

    if ( FAILURE == StackPush(g_operators_stack, *input))
    {
        *status = FAILURE;
        errno = EPERM;
        perror("StackPush Failure");
        return ERROR; 
    }
    ++(*input);
    return WAIT_OPERAND;
}


static calc_state_ty OpenParanHandler(int *status, char **input)
{
    assert(status != NULL);
    assert(input != NULL);
    assert(*input != NULL);

    if ( FAILURE == StackPush(g_operators_stack, *input))
    {
        *status = FAILURE;
        errno = EPERM;
        perror("StackPush Failure");
        return ERROR; 
    }
    ++(*input);
    return WAIT_OPERAND; 
}

static calc_state_ty CloseParanHandler(int *status, char **input)
{
    assert(status != NULL);
    assert(input != NULL);
    assert(*input != NULL);

    while (OPEN_P_CHAR != *((char*)StackPeek(g_operators_stack)))
    {
        if(DUMMY_CHAR == *((char*)StackPeek(g_operators_stack)))
        {
            *status = SYNTAX_ERROR;
            return ERROR;
        }
        Eval(status);

        if (SUCCESS != *status)
        {
            return ERROR;
        }
    }

    StackPop(g_operators_stack);
    ++(*input);
    return WAIT_OPERATOR; 
}

static calc_state_ty ErrorHandler(int *status, char **input)
{
    assert(status != NULL);
    assert(input != NULL);
    assert(*input != NULL);

    *status = SYNTAX_ERROR;
    return ERROR;
}

static calc_state_ty EOIHandler(int *status, char **input)
{
    assert(status != NULL);
    assert(input != NULL);
    assert(*input != NULL);

    while (DUMMY_CHAR != *((char*)StackPeek(g_operators_stack)))
    {
        if (StackSize(g_operands_stack) < MIN_OPERANDS_FOR_OP)
        {
            *status = SYNTAX_ERROR;
            return ERROR;   
        }
        
        Eval(status);

        if (SUCCESS != *status)
        {
            return ERROR;
        }
    }
    return ERROR;
}

/*****************************************************************************/
/************************** Calculator Driver (API)***************************/
/*****************************************************************************/

double Calculate(const char *input, int *status)
{
    calc_state_ty curr_state = WAIT_OPERAND;
    char dummy_op = DUMMY_CHAR;
    double res = 0;
    /* Declare and initialize the transition table */
    static int initialized = LUTS_UNINITIALIZED;

    assert(input != NULL);
    
    *status = SUCCESS;                            
    g_operators_stack = StackCreate(EXP_MAX_LEN + 1, SYMBOL_SIZE); /* +1 IS for dummy */
    
    if ( NULL == g_operators_stack)
    {
        *status = FAILURE;
        errno = EPERM;
        perror("StackCreate Failure");
        return ERROR; 
    }    

    g_operands_stack = StackCreate(EXP_MAX_LEN, SYMBOL_SIZE);

    if ( NULL == g_operands_stack)
    {
        *status = FAILURE;
        StackDestroy(g_operators_stack);
        errno = EPERM;
        perror("StackCreate Failure");
        return ERROR; 
    }

    if ( FAILURE == StackPush(g_operators_stack,&dummy_op))
    {
        *status = FAILURE;
        errno = EPERM;
        perror("StackPush Failure");
        return ERROR; 
    }

    if (!initialized)
    {
        InitCalcHandlersLUT();
        InitInputsLUT();
        InitCalcOperatorsArray();
        initialized = LUTS_INITIALIZED;
    }


    while (ERROR != curr_state)
    {
        curr_state = g_handlers_lut[curr_state][g_inputs[(unsigned char)*input]](status, (char**)&input);
    }

    if (SUCCESS != *status)
    {
        return 0;
    }

    res = *((double*)StackPeek(g_operands_stack));

    StackDestroy(g_operands_stack);
    StackDestroy(g_operators_stack);
    return res;
}