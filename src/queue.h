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

#include <stdio.h>
#include <stdbool.h>

struct Floor{
    bool up;
    bool down;
};

struct callQueue {
    struct Floor floorOne;
    struct Floor floorTwo;
    struct Floor floorThree;
    struct Floor floorFour;
};

#endif // QUEUE_H