/*
  Name: Idan Nave
  Project: State Machine Implementation for accepting a Zero-Wrapped string
  Reviewer: Ahmad
  Date: 01/10/2023
  Version: 1.0
*/
/******************************** Libraries  *********************************/

#include <assert.h>             /* assert() */
#include <stdio.h>              /* printf */
#include <stdlib.h>
#include <stddef.h>             /* size_t */

/*****************************************************************************/
/********************************* Type Definitions **************************/
/*****************************************************************************/

#define INPUT_RANGE    2 /*0 or 1*/

/*For all FSM Cases*/
typedef enum
{
    ERROR,
    START,
    ACQIRE,
    ACCEPTED,
    NUM_STATES
} fsm_state_t;

/*For FSMbyFuncsTransitionTable*/
typedef void (*transition_function_ty)(fsm_state_t*);
typedef enum {FALSE = 0, TRUE} fsm_boolean_ty;

/*****************************************************************************/
/******************************* FSM Transitions *****************************/
/*****************************************************************************/

/****************** PROTOTYPE *********************** IMPLEMENTATION *********/
void transitionToERROR(fsm_state_t* curr_state) { *curr_state = ERROR; }
void transitionToSTART(fsm_state_t* curr_state) { *curr_state = START; }
void transitionToACQIRE(fsm_state_t* curr_state) { *curr_state = ACQIRE; }
void transitionToACCEPTED(fsm_state_t* curr_state) { *curr_state = ACCEPTED; }

/*****************************************************************************/
/************************************ FSM Driver *****************************/
/*****************************************************************************/

/* Initialize the FSM */
static void InitializeTransitionsLUT(fsm_state_t *state, transition_function_ty transition_table[NUM_STATES][INPUT_RANGE])
{
    /* You can set the initial state and transition table here */
    /*{"ERROR","START","ACQIRE","ACCEPTED"}*/
    *state = START;

    transition_table[START][0] = transitionToACQIRE;
    transition_table[START][1] = transitionToERROR;

    transition_table[ACQIRE][0] = transitionToACCEPTED;
    transition_table[ACQIRE][1] = transitionToACQIRE;

    transition_table[ACCEPTED][0] = transitionToACCEPTED;
    transition_table[ACCEPTED][1] = transitionToACQIRE;

    transition_table[ERROR][0] = transitionToERROR;
    transition_table[ERROR][1] = transitionToERROR;
}

static int ZeroWrappedInputFSM(char* events_sequence)
{
    size_t i = 0;
    fsm_state_t curr_state;

    /* Declare and initialize the transition table */
    static int initialized = 0;
    static transition_function_ty transition_table[NUM_STATES][INPUT_RANGE]={0};

    /*Array to map enum values to strings*/
    static const char* states_strs[] = {"ERROR","START","ACQIRE","ACCEPTED"};

    if (!initialized)
    {
        /* Initialize the FSM */
        InitializeTransitionsLUT(&curr_state, transition_table);
        initialized = 1;
    }

    for (; events_sequence[i] != '\0'; i++)
    {
        char event = events_sequence[i] - '0';
        if (event >= 0 && event <= 1)
        {
            transition_table[curr_state][(unsigned char)event](&curr_state);
            printf("Event: %c, FSM Transitions into State: %s\n", events_sequence[i], states_strs[curr_state]);
        }
        else
        {
            printf("Invalid Event: %c\n", events_sequence[i]);
        }
    }
    return 0;
}

int main()
{
    char events_sequence1[] = "01201021";
    char events_sequence2[] = "01010110";
    ZeroWrappedInputFSM(events_sequence1);
    ZeroWrappedInputFSM(events_sequence2);
    return 0;
}