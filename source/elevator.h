#ifndef ELEVATOR_H
#define ELEVATOR_H


#include "elevatorStatus.h"
#include "queue.h"

struct Elevator {
    struct Queue elevatorQueue;
    struct ElevatorStatus elevatorStatus;
    bool emergencyStop;
    bool active;
};

extern struct Elevator *elevator;

int ElevatorConstructor(void);
int ElevatorDestructor(void);

#endif //ELEVATORSTATE_H