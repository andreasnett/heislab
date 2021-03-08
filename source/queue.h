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
#define FLOOR_ONE 0
#define FLOOR_TWO 1
#define FLOOR_THREE 2
#define FLOOR_FOUR 3


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

struct Queue queueConstructor();
int queueAdd(struct Queue* queue, int floor, enum Direction direction);
int queuePop(struct Queue* queue, int floor, enum Direction direction);
int queueCheckCall(int floor, enum Direction direction);
bool queueCheckStop(struct Queue queue, int floor, enum Direction direction);

#endif // QUEUE_H