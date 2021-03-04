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

struct Floor{
    bool up;
    bool down;
};

struct callQueue {
    bool floorOne;
    struct Floor floorTwo;
    struct Floor floorThree;
    bool floorFour;
};

typedef struct Queue {
    struct callQueue map;
} Queue;

Queue* QueueConstructor();
void QueueDestructor(Queue*);
void addToQueue(Queue*, int);
void popFromQueue(Queue*, int);
bool checkStop(Queue*, int);

#endif // QUEUE_H