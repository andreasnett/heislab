/**
 * @file stateController.c
 * @author Steffen Folåsen & Andreas Netteland
 * @brief 
 * @version 1.0
 * @date 2021-03-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdlib.h> //For free function

#include "stateController.h"
#include "states.h"

////////////////////////////////////////////////////////////////////////////////
// STRUCTS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Global struct for controlling the FSM. Needs to be initialized with
 * @p StateConstructor()
 * 
 */
struct StateControll *stateControll;

/**
 * @brief Contains all allowed transistions from a currentState to a nextState.
 * For a better representation of the FSM, see (TODO)
 * 
 */
const struct StateControll allowedStateTransitions[] = {
    {STARTUP, STATE_elevatorInit},
    {STATE_elevatorInit, STATE_elevatorStandStill},
    {STATE_elevatorStandStill, STATE_elevatorGoingDown},
    {STATE_elevatorStandStill, STATE_elevatorGoingUp},
    {STATE_elevatorStandStill, STATE_elevatorEmergency},
    {STATE_elevatorGoingUp, STATE_elevatorStandStill},
    {STATE_elevatorGoingUp, STATE_elevatorEmergency},
    {STATE_elevatorGoingDown, STATE_elevatorStandStill},
    {STATE_elevatorGoingDown, STATE_elevatorEmergency},
    {STATE_elevatorEmergency, STATE_elevatorStandStill}
};


////////////////////////////////////////////////////////////////////////////////
// LOCAL FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

int StateCheckChangeValidity(){
    for (int i = 0; i < sizeof(*allowedStateTransitions); ++i){
        if ((stateControll->currentState == allowedStateTransitions[i].currentState)
        && (stateControll->nextState == allowedStateTransitions[i].nextState)){
            return 0;
        }
    }
    StateSetNext(STATE_elevatorError);
    return 1;
}

void StateChange(void){

    switch (stateControll->currentState)
    {
    case STATE_elevatorInit:
        ExitStateElevatorInit();
        break;
    case STATE_elevatorStandStill:
        ExitStateElevatorStandStill();
        break;
    case STATE_elevatorGoingUp:
        ExitStateElevatorGoingUp();
        break;
    case STATE_elevatorGoingDown:
        ExitStateElevatorGoingDown();
        break;
    case STATE_elevatorEmergency:
        ExitStateElevatorEmergency();
        break;
    case STATE_elevatorError:
        ExitStateElevatorError();
        break; 
    default:
        break;
    }

    stateControll->currentState = stateControll->nextState;

    switch (stateControll->nextState)
    {
    case STATE_elevatorInit:
        EntryStateElevatorInit();
        break;
    case STATE_elevatorStandStill:
        EntryStateElevatorStandStill();
        break;
    case STATE_elevatorGoingUp:
        EntryStateElevatorGoingUp();
        break;
    case STATE_elevatorGoingDown:
        EntryStateElevatorGoingDown();
        break;
    case STATE_elevatorEmergency:
        EntryStateElevatorEmergency();
        break;
    case STATE_elevatorError:
        EntryStateElevatorError();
        break; 
    default:
        break;
    }

}

////////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

int StateConstructor(void){
    stateControll = (struct StateControll*)malloc(sizeof(struct StateControll));
    stateControll->currentState = STARTUP;
    stateControll->nextState = STATE_elevatorInit;

    return 0;
}

void StateDestructor(void){
    free(stateControll);
}

void StateLoop(void){
    if (stateControll->currentState == stateControll->nextState){
        switch (stateControll->currentState)
        {
        case STATE_elevatorInit:
            DoStateElevatorInit();
            break;
        case STATE_elevatorStandStill:
            DoStateElevatorStandStill();
            break;
        case STATE_elevatorGoingUp:
            DoStateElevatorGoingUp();
            break;
        case STATE_elevatorGoingDown:
            DoStateElevatorGoingDown();
            break;
        case STATE_elevatorEmergency:
            DoStateElevatorEmergency();
            break;
        case STATE_elevatorError:
            DoStateElevatorError();
            break; 
        default:
            break;
        }
    }
    else{
        StateCheckChangeValidity();
        StateChange();
    }
}

void StateSetNext(enum ElevatorStates nextState){
    stateControll->nextState = nextState;
}
