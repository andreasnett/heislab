/**
 * @file elevator.h
 * @author Andreas Netteland og Steffen Folåsen
 * @brief The elevator and its member functions
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <time.h> //for the clock
#include "elevatorStatus.h"
#include "queue.h"

////////////////////////////////////////////////////////////////////////////////
// DEFINES
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Struct containing all parameters for the elevator. Also contains values
 * for if emergencyStop is on (0/1), the door is open (0/1) and if the elevator
 * is operating in the loop after an emergency (0/1).
 * 
 */
struct Elevator {
    struct Queue elevatorQueue;
    struct ElevatorStatus elevatorStatus;
    int emergencyStop;
    int doorOpen;
    int afterEmergency;
};

////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

extern struct Elevator *elevator;
clock_t start_t, current_t;

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Instanciate a new Elevator. Uses a global variable on the heap.
 */ 
int ElevatorConstructor(void);

/**
 * @brief Deletes the global Elevator from the heap.
 */
int ElevatorDestructor(void);

#endif //ELEVATORSTATE_H