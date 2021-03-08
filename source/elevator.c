
#include <stdlib.h> //For free function
#include "elevator.h"


struct Elevator *elevator;

int ElevatorConstructor(void){
    elevator = (struct Elevator*)malloc(sizeof(struct Elevator));
    elevator->elevatorQueue = queueConstructor();
    elevator->elevatorStatus = ElevatorStatusConstructor();
    elevator->emergencyStop = 0;
    elevator->active = 0;
    return 0;
}

int ElevatorDestructor(void){
    free(elevator);
    return 0;
}