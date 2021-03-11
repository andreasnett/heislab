/**
 * @file elevatorStatus.h
 * @author Andreas Netteland og Steffen Folåsen
 * @brief The internal states of the elevator
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ELEVATORSTATE_H
#define ELEVATORSTATE_H

#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// DEFINES
////////////////////////////////////////////////////////////////////////////////

enum Direction{
    UP,
    DOWN,
    INSIDE
};

struct ElevatorStatus {
    enum Direction direction;   
    int targetFloor;
    int currentFloor;
};

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
/**
 * Instanciate a new ElevatorStatus
 * @returns the new ElevatorStatus struct
 */
struct ElevatorStatus ElevatorStatusConstructor(void);

/**
 * Set the status of the elevator
 * @param targetFloor the floor the elevator is headed to
 * @param currentFloor the floor the elevator is currently at
 */
void setElevatorStatus(int targetFloor, int currentFloor);



#endif //ELEVATORSTATE_H