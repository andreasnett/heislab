#ifndef STATES_H
#define STATES_H

////////////////////////////////////////////////////////////////////////////////
// ENTRY STATES
////////////////////////////////////////////////////////////////////////////////

void EntryStateElevatorInit(void);
void EntryStateElevatorStandStill(void);
void EntryStateElevatorGoingUp(void);
void EntryStateElevatorGoingDown(void);
void EntryStateElevatorEmergency(void);
void EntryStateElevatorError(void);

////////////////////////////////////////////////////////////////////////////////
// DO STATES
////////////////////////////////////////////////////////////////////////////////

void DoStateElevatorInit(void);
void DoStateElevatorStandStill(void);
void DoStateElevatorGoingUp(void);
void DoStateElevatorGoingDown(void);
void DoStateElevatorEmergency(void);
void DoStateElevatorError(void);

////////////////////////////////////////////////////////////////////////////////
// EXIT STATES
////////////////////////////////////////////////////////////////////////////////

void ExitStateElevatorInit(void);
void ExitStateElevatorStandStill(void);
void ExitStateElevatorGoingUp(void);
void ExitStateElevatorGoingDown(void);
void ExitStateElevatorEmergency(void);
void ExitStateElevatorError(void);

#endif // STATES_H