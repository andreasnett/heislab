/**
 * @file stateController.h
 * @author Steffen Folåsen & Andreas Netteland
 * @brief 
 * @version 1.0
 * @date 2021-03-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef STATECONTROLLER_H
#define STATECONTROLLER_H

////////////////////////////////////////////////////////////////////////////////
// DEFINES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Containg all possible states in the FSM. For more info, see (TODO)
 * 
 */
enum ElevatorStates {
    STATE_elevatorInit = 0,
    STATE_elevatorStandStill,
    STATE_elevatorGoingUp,
    STATE_elevatorGoingDown,
    STATE_elevatorEmergency,
    STATE_elevatorError
};

/**
 * @brief Cointains the FSMs current state, and next requested state. If no
 * next state is requested, then currentState = nextState.
 * 
 */
struct StateControll{
    enum ElevatorStates currentState;
    enum ElevatorStates nextState;
};

////////////////////////////////////////////////////////////////////////////////
// STRUCTS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Global struct for controlling the FSM. Needs to be initialized with
 * @p StateConstructor()
 * 
 */
extern struct StateControll *stateControll;

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocates memory for the global @p stateControll struct. Also sets
 * next state to STATE_elevatorInit
 * 
 */
int StateConstructor(void);

/**
 * @brief Frees memory for the global @p stateControll struct.
 * 
 */
void StateDestructor(void);

/**
 * @brief Everytime this function is called, it will call the function for 
 * the currentState. If a new state is set, StateLoop will call the Exit
 * function for the current state, and entry function for the Next, before
 * continuing the Do state for the new state.
 * 
 */
void StateLoop(void);

/**
 * @brief 
 * 
 * @param nextState 
 */
void StateSetNext(enum ElevatorStates nextState);

#endif // STATECONTROLLER_H