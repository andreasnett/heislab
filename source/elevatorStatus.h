/**
 * @file elevatorStatus.h
 * @author Andreas Netteland og Steffen Folåsen
 * @brief The internal states of the elevator
 * @version 1.0
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ELEVATORSTATE_H
#define ELEVATORSTATE_H

////////////////////////////////////////////////////////////////////////////////
// DEFINES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Struct for containing call direction
 * 
 */
enum Direction{
    UP,
    DOWN,
    INSIDE
};

/**
 * @brief struct cointaining the last current floor of the elevator, as well as
 * a target floor which is the floor furthest away in the queue depending on
 * the elevators direction 
 * 
 */
struct ElevatorStatus {
    enum Direction direction;   
    int targetFloor;
    int currentFloor;
};

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Instanciate a new ElevatorStatus
 * @returns the new ElevatorStatus struct
 */
struct ElevatorStatus ElevatorStatusConstructor(void);

#endif //ELEVATORSTATE_H