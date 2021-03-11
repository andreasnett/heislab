/**
 * @file queue.h
 * @author Andreas Netteland og Steffen Folåsen
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H
#define FLOOR_ONE 0
#define FLOOR_TWO 1
#define FLOOR_THREE 2
#define FLOOR_FOUR 3
#define FLOOR_NONE 4


#include <stdbool.h>
#include "elevatorStatus.h"

struct Floor{
    bool up;
    bool down;
};

struct Queue {
    bool floorOne;
    struct Floor floorTwo;
    struct Floor floorThree;
    bool floorFour;
};

/**
 * Instanciate the queue
 * @returns a new queue
 */ 
struct Queue queueConstructor();

/**
 * Add some floor and direction to the queue
 * @param queue pointer to which queue to add floor and direction too
 * @param floor which floor to add
 * @param direction which direction to add
 * @returns whether the function failed
 */ 
int queueAdd(struct Queue *queue, int floor, enum Direction direction);

/**
 * Remove some floor and direction from the queue 
 * @param queue pointer to which queue to remove floor and direction from
 * @param floor which floor to remove
 * @param direction which direction to remove
 * @returns whether the function failed
 */ 
int queuePop(struct Queue *queue, int floor, enum Direction direction);

/**
 * Clear all calls from the queue
 * @param queue the queue to be cleared
 * @returns whether the function failed
 */
int queueClearAll(struct Queue *queue);

/**
 * Check if the button for some floor is pressed in
 * @param floor pointer to which floor is pressed in
 * @param direction pointer to which direction is pressed in
 * @returns whether the button is pressed for some floor and direction
 */ 
int queueCheckCall(int *floor, enum Direction *direction);

/**
 * Check if some floor and direction is present in the queue
 * @param queue the queue to check
 * @param floor the floor to check
 * @param direction the direction to check
 * @returns whether the floor and direction is present in the queue
 */
bool queueCheckStop(struct Queue queue, int floor, enum Direction direction);

#endif // QUEUE_H