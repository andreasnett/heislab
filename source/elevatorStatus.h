/**
 * @file elevatorStatus.h
 * @author Andreas Netteland og Steffen Folåsen
 * @brief 
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
    int calledFloor;
    int currentFloor;
};

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
/**
 * Instanciate a new elevatorStatus
 * @returns 
 * 
 */
struct ElevatorStatus ElevatorStatusConstructor(void);
void ElevatorStatusDesctructor(void);
void setElevatorStatus(int targetFloor, int currentFloor);
void getElevatorStatus();


#endif //ELEVATORSTATE_H