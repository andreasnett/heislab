/**
 * @file queue.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H

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

struct Queue QueueConstructor();
void addToQueue(struct Queue* queue, int floor, enum Direction direction);
void popFromQueue(struct Queue* queue, int floor, enum Direction direction);
bool checkStop(struct Queue queue, int floor, enum Direction direction);

#endif // QUEUE_H