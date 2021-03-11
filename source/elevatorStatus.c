#include <stdlib.h> //For free function

#include "elevatorStatus.h"

struct ElevatorStatus ElevatorStatusConstructor(void){
    struct ElevatorStatus status;
    status.currentFloor = 3;
    status.direction = DOWN;
    status.calledFloor = 0;
    status.targetFloor = 0;
    return status;
}


void ElevatorStatusDesctructor(struct ElevatorStatus *elevatorStatus) {
    free(elevatorStatus);
}
