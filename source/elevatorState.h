#ifndef ELEVATORSTATE_H
#define ELEVATORSTATE_H

#include <stdbool.h>

typedef struct ElevatorState {
    char direction;
    int targetFloor;
    int currentFloor;
} ElevatorState;

ElevatorState* ElevatorStateConstructor();
void ElevatorStateDesctructor(ElevatorState*);
void setState(ElevatorState*, int, int);
void getState(ElevatorState*);


#endif