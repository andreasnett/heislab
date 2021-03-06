/**
 * @file fsmControllerer.h
 * @author Steffen Folåsen & Andreas Netteland
 * @brief The finite state machine for the elevator
 * @version 1.0
 * @date 2021-03-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FSM_H
#define FSM_H

////////////////////////////////////////////////////////////////////////////////
// DEFINES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Containg all possible states in the FSM. Also contains a startup value
 * that is 
 * 
 */
enum ElevatorStates {
    STARTUP = 0,
    STATE_elevatorInit,
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
struct FSMController{
    enum ElevatorStates currentState;
    enum ElevatorStates nextState;
};

////////////////////////////////////////////////////////////////////////////////
// STRUCTS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Global struct for controlling the FSM. Needs to be initialized with
 * @c fsmControllerConstructor()
 * 
 */
extern struct FSMController *fsmController;

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocates memory for the global @c fsmController struct. Also sets
 * next state to STATE_elevatorInit
 * 
 */
int fsmControllerConstructor(void);

/**
 * @brief Frees memory for the global @c fsmController struct.
 * 
 */
void fsmControllerDestructor(void);

/**
 * @brief Everytime this function is called, it will call the function for 
 * the currentState. If a new state is set, StateLoop will call the Exit
 * function for the current state, and entry function for the Next, before
 * continuing the Do state for the new state.
 * 
 */
void fsmRun(void);

/**
 * @brief Sets next state in the @p fsmController struct.
 * 
 * @param nextState the next state
 */
void fsmSetNextState(enum ElevatorStates nextState);

#endif // FSM_H