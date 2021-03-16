/**
 * @file queue.h
 * @author Andreas Netteland og Steffen Folåsen
 * @brief The queue that keeps track of floors to visit
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <hardware.h>
#include "elevatorStatus.h"

////////////////////////////////////////////////////////////////////////////////
// DEFINES
////////////////////////////////////////////////////////////////////////////////

#define FIRST_FLOOR 0
#define NUMBER_OF_FLOORS HARDWARE_NUMBER_OF_FLOORS - 2
#define LAST_FLOOR NUMBER_OF_FLOORS + 1
#define FLOOR_NONE -1

/**
 * @brief Floor thet is called with up or down button. If the floor is called
 * from the elevator, both will be high.
 * 
 */
struct Floor{
    int up;
    int down;
};

/**
 * @brief Queue that contains a first and last floor. To add more floors, the
 * HARDWARE_NUMBER_OF_FLOORS in hardware.h should be changed. 
 * 
 * @note first and last floor only contain one value, as these only have one
 * button
 * 
 */
struct Queue {
    int firstFloor;
    struct Floor floor[NUMBER_OF_FLOORS];
    int lastFloor;
};

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Instanciate the queue. It makes every parameter in the @p Queue struct 0
 * @returns struct Queue a new queue
 */ 
struct Queue queueConstructor();

/**
 * @brief Add some floor and direction to the queue
 * @param queue a pointer to a queue struct cointaing the queue for floor calls
 * @param floor which floor to add
 * @param direction which direction to add
 * @returns int 0 if no floor was added, else 1
 */ 
int queueAdd(struct Queue *queue, int floor, enum Direction direction);

/**
 * @brief Remove some floor and direction from the queue 
 * @param queue a pointer to a queue struct cointaing the queue for floor calls
 * @param floor which floor to remove
 * @returns int 0, error handling can be added later
 */ 
int queuePop(struct Queue *queue, int floor);

/**
 * @brief Clear all calls from the queue
 * @param queue the queue to be cleared
 */
void queueClearAll(struct Queue *queue);

/**
 * @brief Check if the button for some floor is pressed
 * @param floor pointer to which floor button is pressed
 * @param direction pointer to which direction the button is pressed
 * @returns int 1 if the button is pressed for some floor and direction, else 0
 */ 
int queueCheckCall(int *floor, enum Direction *direction);

/**
 * @brief Check if some floor and direction is present in the queue
 * @param queue the queue to check
 * @param floor the floor to check
 * @param direction the direction to check
 * @returns int 1 if the floor and direction is present in the queue, else 0
 */
int queueCheckStop(struct Queue queue, int floor, enum Direction direction);

/**
 * @brief Checks all floor sensors
 * 
 * @param floor a point to a floor value that the floor sensor is active, if no
 * floorsensor is acitve, this value is unchanged
 * @return int 0 if no floor sensor is active, else 1
 */
int queueCheckFloorSensor(int *floor);

/**
 * @brief Checks for a new target floor when the final targer floor is reached
 * 
 * @param queue The @p Queue sturct to check
 * @param currentFloor current floor the elevator is located
 * @param newTargetFloor a pointer to a new target floor, remains unchanged if
 * there is no new target floor
 * @return int 0 if there are no new target floor, else 1
 */
int queueCheckNewTarget(struct Queue queue, int currentFloor, int *newTargetFloor);

#endif // QUEUE_H