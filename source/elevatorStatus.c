#include <stdlib.h> //For free function

#include "elevatorStatus.h"

struct ElevatorStatus *ElevatorStatus;

int ElevatorStatusConstructor(void){
    ElevatorStatus = (struct ElevatorStatus *)malloc(sizeof(ElevatorStatus));

    return 0;
}

void ElevatorStatusDesctructor(void){
    free(ElevatorStatus);
}