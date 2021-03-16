/**
 * @file states.h
 * @author Andreas Netteland og Steffen Folåsen
 * @brief Containing all the functions for the states
 * @version 1.0
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef STATES_H
#define STATES_H

////////////////////////////////////////////////////////////////////////////////
// ENTRY STATES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The Entry state for the ElevatorInit state. See sheet of FSM for 
 * overview.
 * 
 */
void EntryStateElevatorInit(void);

/**
 * @brief The Entry state for the ElevatorStandStill state. See sheet of FSM for 
 * overview.
 * 
 */
void EntryStateElevatorStandStill(void);

/**
 * @brief The Entry state for the ElevatorGoingUp state. See sheet of FSM for 
 * overview.
 * 
 */
void EntryStateElevatorGoingUp(void);

/**
 * @brief The Entry state for the ElevatorGoingDown state. See sheet of FSM for 
 * overview.
 * 
 */
void EntryStateElevatorGoingDown(void);

/**
 * @brief The Entry state for ElevatorEmergency state. See sheet of FSM for
 * overview.
 * 
 */
void EntryStateElevatorEmergency(void);

/**
 * @brief The Entry state for ElevatorError state. See sheet of FSM for overview.
 * 
 */
void EntryStateElevatorError(void);

////////////////////////////////////////////////////////////////////////////////
// DO STATES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The Do state for the ElevatorInit state. See sheet of FSM for overview.
 * 
 */
void DoStateElevatorInit(void);

/**
 * @brief The Do state for the ElevatorStandStill state. See sheet of FSM for 
 * overview.
 * 
 */
void DoStateElevatorStandStill(void);

/**
 * @brief The Do state for the ElevatorGoingUp state. See sheet of FSM for 
 * overview.
 * 
 */
void DoStateElevatorGoingUp(void);

/**
 * @brief The Do state for the ElevatorGoingDown state. See sheet of FSM for 
 * overview.
 * 
 */
void DoStateElevatorGoingDown(void);

/**
 * @brief The Do state for the ElevatorEmergency state. See sheet of FSM for 
 * overview.
 * 
 */
void DoStateElevatorEmergency(void);

/**
 * @brief The Do state for the ElevatorError state. See sheet of FSM for 
 * overview.
 * 
 */
void DoStateElevatorError(void);

////////////////////////////////////////////////////////////////////////////////
// EXIT STATES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The Exit state for the ElevatorInit state. See sheet of FSM for 
 * overview.
 * 
 */
void ExitStateElevatorInit(void);

/**
 * @brief The Exit state for the ElevatorStandStill state. See sheet of FSM for 
 * overview.
 * 
 */
void ExitStateElevatorStandStill(void);

/**
 * @brief The Exit state for the ElevatorGoingUp state. See sheet of FSM for 
 * overview.
 * 
 */
void ExitStateElevatorGoingUp(void);

/**
 * @brief The Exit state for the ElevatorGoingDown state. See sheet of FSM for 
 * overview.
 * 
 */
void ExitStateElevatorGoingDown(void);

/**
 * @brief The Exit state for the ElevatorEmergency state. See sheet of FSM for 
 * overview.
 * 
 */
void ExitStateElevatorEmergency(void);

/**
 * @brief The Exit state for the ElevatorError state. See sheet of FSM for 
 * overview.
 * 
 */
void ExitStateElevatorError(void);

#endif // STATES_H