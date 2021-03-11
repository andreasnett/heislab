/**
 * @file elevator.h
 * @author Andreas Netteland og Steffen Folåsen
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <time.h>
#include "elevatorStatus.h"
#include "queue.h"

struct Elevator {
    struct Queue elevatorQueue;
    struct ElevatorStatus elevatorStatus;
    bool emergencyStop;
    bool doorOpen;
    bool active;
};

extern struct Elevator *elevator;
clock_t start_t, current_t, total_t;

int ElevatorConstructor(void);
int ElevatorDestructor(void);

#endif //ELEVATORSTATE_H