/**
 * @file fsmControllerer.c
 * @author Steffen Folåsen & Andreas Netteland
 * @brief 
 * @version 1.0
 * @date 2021-03-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdlib.h> //For free function
#include <stdio.h>
#include "fsm.h"
#include "states.h"

////////////////////////////////////////////////////////////////////////////////
// STRUCTS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Global struct for controlling the FSM. Needs to be initialized with
 * @p fsmControllerConstructor()
 * 
 */
struct FSMController *fsmController;

/**
 * @brief Contains all allowed transistions from a currentState to a nextState.
 * For a better representation of the FSM, see (TODO)
 * 
 */
const struct FSMController allowedStateTransitions[] = {
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

int fsmCheckChangeValidity(){
    for (int i = 0; i < sizeof(allowedStateTransitions); ++i){
        if ((fsmController->currentState == allowedStateTransitions[i].currentState)
        && (fsmController->nextState == allowedStateTransitions[i].nextState)){
            return 0;
        }
    }
    //if((fsmController->currentState == STATE_elevatorEmergency)&&(fsmController->nextState == STATE_elevatorStandStill)){
    //    return 0;
    //}
    fsmSetNextState(STATE_elevatorError);
    return 1;
}

void fsmChangeState(void){

    switch (fsmController->currentState)
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

    fsmController->currentState = fsmController->nextState;

    switch (fsmController->nextState)
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

int fsmControllerConstructor(void){
    fsmController = (struct FSMController*)malloc(sizeof(struct FSMController));
    fsmController->currentState = STARTUP;
    fsmController->nextState = STATE_elevatorInit;

    return 0;
}

void fsmControllerDestructor(void){
    free(fsmController);
}

void fsmRun(void){
    if (fsmController->currentState == fsmController->nextState){
        switch (fsmController->currentState)
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
        fsmCheckChangeValidity();
        fsmChangeState();
    }
}

void fsmSetNextState(enum ElevatorStates nextState){
    fsmController->nextState = nextState;
}
