#include <stdlib.h> //For free function

#include "elevatorStatus.h"

struct ElevatorStatus ElevatorStatusConstructor(void){
    struct ElevatorStatus status;
    status.currentFloor = 3;
    status.direction = DOWN;
    status.targetFloor = 0;
    return status;
}
