
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
    printf("Set state ElevatorStandStill\n");

}
void EntryStateElevatorGoingUp(void){
    printf("Set state ElevatorStandGoingUp\n");
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    hardware_command_door_open(0);
}

void EntryStateElevatorGoingDown(void){
    printf("Set state ElevatorStandGoingDown\n");
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
}

void EntryStateElevatorEmergency(void){
    printf("Set state ElevatorEmergency\n");
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
    else if (elevator->doorOpen && ((current_t - start_t)/1000000 >= 3)){
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

    if ((elevator->elevatorStatus.calledFloor > elevator->elevatorStatus.targetFloor) 
        && !elevator->doorOpen){
            elevator->elevatorStatus.targetFloor = elevator->elevatorStatus.calledFloor;
            fsmSetNextState(STATE_elevatorGoingUp);
        }
        else if((elevator->elevatorStatus.calledFloor < elevator->elevatorStatus.targetFloor) 
            && !elevator->doorOpen){
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
    
    current_t = clock();
    if (elevator->doorOpen && hardware_read_obstruction_signal()){
        start_t = clock();
    }
    else if (elevator->doorOpen && ((current_t - start_t)/1000000 >= 3)){
        hardware_command_door_open(0);
        elevator->doorOpen = false;
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
    }

    if(queueCheckCall(&elevator->elevatorStatus.calledFloor, 
    &callDirection)){
        queueAdd(&elevator->elevatorQueue, elevator->elevatorStatus.calledFloor,
        callDirection);
        if (elevator->elevatorStatus.calledFloor > elevator->elevatorStatus.targetFloor){
            elevator->elevatorStatus.targetFloor = elevator->elevatorStatus.calledFloor;
        }
    }

    if(queueCheckFloorSensor(&elevator->elevatorStatus.currentFloor)){
        if(queueCheckStop(elevator->elevatorQueue, elevator->elevatorStatus.currentFloor, UP)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);
            elevator->doorOpen = true;
            start_t = clock();
            queuePop(&elevator->elevatorQueue, elevator->elevatorStatus.currentFloor);
        }
    }

    if (elevator->elevatorStatus.currentFloor == elevator->elevatorStatus.targetFloor){
        fsmSetNextState(STATE_elevatorStandStill);
    }
}

void DoStateElevatorGoingDown(void){
    if (!hardware_read_stop_signal()){
        fsmSetNextState(STATE_elevatorEmergency);
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
