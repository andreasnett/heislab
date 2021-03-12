#ifndef STATES_H
#define STATES_H

////////////////////////////////////////////////////////////////////////////////
// ENTRY STATES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * 
 */
void EntryStateElevatorInit(void);

/**
 * @brief 
 * 
 */
void EntryStateElevatorStandStill(void);

/**
 * @brief 
 * 
 */
void EntryStateElevatorGoingUp(void);

/**
 * @brief 
 * 
 */
void EntryStateElevatorGoingDown(void);

/**
 * @brief 
 * 
 */
void EntryStateElevatorEmergency(void);

/**
 * @brief 
 * 
 */
void EntryStateElevatorError(void);

////////////////////////////////////////////////////////////////////////////////
// DO STATES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * 
 */
void DoStateElevatorInit(void);

/**
 * @brief 
 * 
 */
void DoStateElevatorStandStill(void);

/**
 * @brief 
 * 
 */
void DoStateElevatorGoingUp(void);

/**
 * @brief 
 * 
 */
void DoStateElevatorGoingDown(void);

/**
 * @brief 
 * 
 */
void DoStateElevatorEmergency(void);

/**
 * @brief 
 * 
 */
void DoStateElevatorError(void);

////////////////////////////////////////////////////////////////////////////////
// EXIT STATES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * 
 */
void ExitStateElevatorInit(void);

/**
 * @brief 
 * 
 */
void ExitStateElevatorStandStill(void);

/**
 * @brief 
 * 
 */
void ExitStateElevatorGoingUp(void);

/**
 * @brief 
 * 
 */
void ExitStateElevatorGoingDown(void);

/**
 * @brief 
 * 
 */
void ExitStateElevatorEmergency(void);

/**
 * @brief 
 * 
 */
void ExitStateElevatorError(void);

#endif // STATES_H