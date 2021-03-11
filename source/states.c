
#include <stdio.h>
#include "states.h"
#include "hardware.h"
#include "queue.h"
#include "elevatorStatus.h"
#include "elevator.h"
#include "fsm.h"

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
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
}

void EntryStateElevatorGoingDown(void){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
}

void EntryStateElevatorEmergency(void){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
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
        fsmSetNextState(STATE_elevatorStandStill);
    }  
}

void DoStateElevatorStandStill(void){

    if (hardware_read_stop_signal()){
        fsmSetNextState(STATE_elevatorEmergency);
        return;
    }

    current_t = clock();
    if (elevator->doorOpen && hardware_read_obstruction_signal()){
        start_t = clock();
    }
    else if (elevator->doorOpen && ((current_t - start_t)/1000000 == 3)){
        hardware_command_door_open(0);
        elevator->doorOpen = false;
    }

    if(queueCheckCall(&elevator->elevatorStatus.calledFloor, 
    &elevator->elevatorStatus.direction)){

        if (elevator->elevatorStatus.currentFloor == elevator->elevatorStatus.calledFloor){
            hardware_command_door_open(1);
            elevator->doorOpen = true;
            start_t = clock();
        }
        else{
            queueAdd(&elevator->elevatorQueue, elevator->elevatorStatus.calledFloor,
            elevator->elevatorStatus.direction);
        }
    }

    if ((elevator->elevatorStatus.calledFloor > elevator->elevatorStatus.targetFloor) && 
        (elevator->elevatorStatus.direction == UP) && !elevator->doorOpen){
            elevator->elevatorStatus.targetFloor = elevator->elevatorStatus.calledFloor;
            fsmSetNextState(STATE_elevatorGoingUp);
        }
        else if((elevator->elevatorStatus.calledFloor < elevator->elevatorStatus.targetFloor) && 
        (elevator->elevatorStatus.direction == DOWN) && !elevator->doorOpen){
            elevator->elevatorStatus.targetFloor = elevator->elevatorStatus.calledFloor;
            fsmSetNextState(STATE_elevatorGoingDown);
    }
}

void DoStateElevatorGoingUp(void){
    enum Direction callDirection;

    if (hardware_read_stop_signal()){
        fsmSetNextState(STATE_elevatorEmergency);
        return;
    }

    if(queueCheckCall(&elevator->elevatorStatus.calledFloor, 
    &callDirection)){
        queueAdd(&elevator->elevatorQueue, elevator->elevatorStatus.calledFloor,
        callDirection);
        if (elevator->elevatorStatus.calledFloor > elevator->elevatorStatus.targetFloor){
            elevator->elevatorStatus.targetFloor = elevator->elevatorStatus.calledFloor;
        }
    }

}

void DoStateElevatorGoingDown(void){
    if (!hardware_read_stop_signal()){
        fsmSetNextState(STATE_elevatorInit);
        return;
    }
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
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void ExitStateElevatorGoingDown(void){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void ExitStateElevatorEmergency(void){

}

void ExitStateElevatorError(void){

}
