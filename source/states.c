
#include <stdio.h>
#include "states.h"
#include "hardware.h"
#include "queue.h"
#include "elevatorStatus.h"
#include "elevator.h"
#include "stateController.h"

////////////////////////////////////////////////////////////////////////////////
// ENTRY STATES
////////////////////////////////////////////////////////////////////////////////

void EntryStateElevatorInit(void){
    if(hardware_read_floor_sensor(FLOOR_ONE)){
        elevator->elevatorStatus.currentFloor = FLOOR_ONE;
    }
    else{

        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
}

void EntryStateElevatorStandStill(void){

}
void EntryStateElevatorGoingUp(void){

}

void EntryStateElevatorGoingDown(void){

}

void EntryStateElevatorEmergency(void){

}

void EntryStateElevatorError(void){

}


////////////////////////////////////////////////////////////////////////////////
// DO STATES
////////////////////////////////////////////////////////////////////////////////

void DoStateElevatorInit(void){
    if(hardware_read_floor_sensor(FLOOR_ONE)){
        elevator->elevatorStatus.currentFloor = FLOOR_ONE;
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        StateSetNext(STATE_elevatorStandStill);
    }  
}

void DoStateElevatorStandStill(void){

    if(queueCheckCall(elevator->elevatorStatus.targetFloor, 
    elevator->elevatorStatus.direction)){

        if (elevator->elevatorStatus.currentFloor == elevator->elevatorStatus.targetFloor){
            hardware_command_door_open(1);
            
        }

        queueAdd(&elevator->elevatorQueue, elevator->elevatorStatus.targetFloor,
        elevator->elevatorStatus.direction);

    }
}

void DoStateElevatorGoingUp(void){

}

void DoStateElevatorGoingDown(void){

}

void DoStateElevatorEmergency(void){

}

void DoStateElevatorError(void){

}


////////////////////////////////////////////////////////////////////////////////
// EXIT STATES
////////////////////////////////////////////////////////////////////////////////

void ExitStateElevatorInit(void){

}

void ExitStateElevatorStandStill(void){

}

void ExitStateElevatorGoingUp(void){

}

void ExitStateElevatorGoingDown(void){

}

void ExitStateElevatorEmergency(void){

}

void ExitStateElevatorError(void){

}
