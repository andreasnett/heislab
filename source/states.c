
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
    hardware_command_stop_light(1);
    if(queueCheckFloorSensor(&elevator->elevatorStatus.currentFloor)){
        hardware_command_door_open(1);
        elevator->doorOpen = true;
    }
    queueClearAll(&elevator->elevatorQueue);
}

void EntryStateElevatorError(void){
    printf("Set state ElevatorError\n");

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
    int calledFloor = FLOOR_NONE;

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

    if(queueCheckCall(&calledFloor, &elevator->elevatorStatus.direction)){
        if (elevator->elevatorStatus.currentFloor == calledFloor){
            hardware_command_door_open(1);
            elevator->doorOpen = true;
            start_t = clock();
        }
        else{
            queueAdd(&elevator->elevatorQueue, calledFloor, elevator->elevatorStatus.direction);
        }
        if (calledFloor > elevator->elevatorStatus.targetFloor){
            elevator->elevatorStatus.targetFloor = calledFloor;
        }
        else if((calledFloor < elevator->elevatorStatus.targetFloor)){
            elevator->elevatorStatus.targetFloor = calledFloor;
        }
    }

    if ((elevator->elevatorStatus.targetFloor > elevator->elevatorStatus.currentFloor) 
        && !elevator->doorOpen){
        fsmSetNextState(STATE_elevatorGoingUp);    
    }
    else if ((elevator->elevatorStatus.targetFloor < elevator->elevatorStatus.currentFloor) 
        && !elevator->doorOpen){
        fsmSetNextState(STATE_elevatorGoingDown);    
    }
}

void DoStateElevatorGoingUp(void){
    enum Direction callDirection = UP;
    int calledFloor = FLOOR_NONE;

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

    if(queueCheckCall(&calledFloor, &callDirection)){
        queueAdd(&elevator->elevatorQueue, calledFloor,
        callDirection);
        if (calledFloor > elevator->elevatorStatus.targetFloor){
            elevator->elevatorStatus.targetFloor = calledFloor;
        }
    }

    if(queueCheckFloorSensor(&elevator->elevatorStatus.currentFloor)){
        hardware_command_floor_indicator_on(elevator->elevatorStatus.currentFloor);
        if(queueCheckStop(elevator->elevatorQueue, elevator->elevatorStatus.currentFloor, UP)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);
            elevator->doorOpen = true;
            start_t = clock();
            queuePop(&elevator->elevatorQueue, elevator->elevatorStatus.currentFloor);
        }
        else if (elevator->elevatorStatus.currentFloor == elevator->elevatorStatus.targetFloor){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);
            elevator->doorOpen = true;
            start_t = clock();
            queuePop(&elevator->elevatorQueue, elevator->elevatorStatus.currentFloor);
            fsmSetNextState(STATE_elevatorStandStill);
        }
    }
}


void DoStateElevatorGoingDown(void){
    enum Direction callDirection = DOWN;
    int calledFloor = FLOOR_NONE;

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
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }

    if(queueCheckCall(&calledFloor, &callDirection)){
        queueAdd(&elevator->elevatorQueue, calledFloor,
        callDirection);
        if (calledFloor < elevator->elevatorStatus.targetFloor){
            elevator->elevatorStatus.targetFloor = calledFloor;
        }
    }

    if(queueCheckFloorSensor(&elevator->elevatorStatus.currentFloor)){
        hardware_command_floor_indicator_on(elevator->elevatorStatus.currentFloor);
        if(queueCheckStop(elevator->elevatorQueue, elevator->elevatorStatus.currentFloor, DOWN)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);
            elevator->doorOpen = true;
            start_t = clock();
            queuePop(&elevator->elevatorQueue, elevator->elevatorStatus.currentFloor);
        }
        else if (elevator->elevatorStatus.currentFloor == elevator->elevatorStatus.targetFloor){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);
            elevator->doorOpen = true;
            start_t = clock();
            queuePop(&elevator->elevatorQueue, elevator->elevatorStatus.currentFloor);
            fsmSetNextState(STATE_elevatorStandStill);
        }
    }
}

void DoStateElevatorEmergency(void){
    while(!hardware_read_stop_signal()){

    }
    if (elevator->doorOpen){
        start_t = clock();
    }
    fsmSetNextState(STATE_elevatorStandStill);
    hardware_command_stop_light(0);

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
    queueCheckNewTarget(elevator->elevatorQueue, elevator->elevatorStatus.currentFloor,
    &elevator->elevatorStatus.targetFloor);
}

void ExitStateElevatorGoingDown(void){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    queueCheckNewTarget(elevator->elevatorQueue, elevator->elevatorStatus.currentFloor,
    &elevator->elevatorStatus.targetFloor);
    
}

void ExitStateElevatorEmergency(void){

}

void ExitStateElevatorError(void){

}
