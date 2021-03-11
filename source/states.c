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
    printf("Entry state ElevatorStandStill\n");

}
void EntryStateElevatorGoingUp(void){
    printf("Entry state ElevatorStandGoingUp\n");
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    hardware_command_door_open(0);
}

void EntryStateElevatorGoingDown(void){
    printf("Entry state ElevatorStandGoingDown\n");
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
}

void EntryStateElevatorEmergency(void){
    printf("Entry state ElevatorEmergency\n");
    hardware_command_stop_light(1);
    if(queueCheckFloorSensor(&elevator->elevatorStatus.currentFloor)){
        hardware_command_door_open(1);
        elevator->doorOpen = true;
    }
    queueClearAll(&elevator->elevatorQueue);
    while(hardware_read_stop_signal()){

    }
}

void EntryStateElevatorError(void){
    printf("Entry state ElevatorError\n");

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
    enum Direction callDirection = DOWN;
    int calledFloor = FLOOR_NONE;

    hardware_command_stop_light(0);

    if(queueCheckCall(&calledFloor, &callDirection)){
        queueAdd(&elevator->elevatorQueue, calledFloor,
        callDirection);
        if ((calledFloor == elevator->elevatorStatus.currentFloor)){
            if ((elevator->elevatorStatus.targetFloor - elevator->elevatorStatus.currentFloor) > 0){
                elevator->elevatorStatus.currentFloor = elevator->elevatorStatus.currentFloor + 1;
                elevator->elevatorStatus.targetFloor = calledFloor;
            }
            else if ((elevator->elevatorStatus.targetFloor - elevator->elevatorStatus.currentFloor) < 0){
                elevator->elevatorStatus.currentFloor = elevator->elevatorStatus.currentFloor - 1;
                elevator->elevatorStatus.targetFloor = calledFloor;
            }
        }
        else if (calledFloor < elevator->elevatorStatus.currentFloor){
            elevator->elevatorStatus.targetFloor = calledFloor;
        }
        else if(calledFloor > elevator->elevatorStatus.currentFloor){
            elevator->elevatorStatus.targetFloor = calledFloor;
        }
        if (elevator->doorOpen){
            start_t = clock();
        }
        fsmSetNextState(STATE_elevatorStandStill);
    }
}

void DoStateElevatorError(void){

}


////////////////////////////////////////////////////////////////////////////////
// EXIT STATES
////////////////////////////////////////////////////////////////////////////////

void ExitStateElevatorInit(void){
    printf("Exit state ElevatorInit\n");

}

void ExitStateElevatorStandStill(void){
    printf("Exit state ElevatorStandStill\n");
    
}

void ExitStateElevatorGoingUp(void){
    printf("Exit state ElevatorGoingUp\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    queueCheckNewTarget(elevator->elevatorQueue, elevator->elevatorStatus.currentFloor,
    &elevator->elevatorStatus.targetFloor);
}

void ExitStateElevatorGoingDown(void){
    printf("Exit state ElevatorGoingDown\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    queueCheckNewTarget(elevator->elevatorQueue, elevator->elevatorStatus.currentFloor,
    &elevator->elevatorStatus.targetFloor);
    
}

void ExitStateElevatorEmergency(void){
    printf("Exit state ElevatorEmergency\n");
}

void ExitStateElevatorError(void){
    printf("Exit state ElevatorError\n");

}
