#include "queue.h"
#include <stdbool.h>


struct Queue QueueConstru1ctor() {
    struct Queue que = {
        .floorOne = false,
        .floorTwo.down = false,
        .floorTwo.up = false,
        .floorThree.down = false,
        .floorThree.up = false,
        .floorFour = false
    };
    return que;
};


//bool checkStop(struct Queue this, int floor, enum Direction direction) {
//    if (floor < 1 || floor > 4) {
//        // invalid options
//        return false;
//    };
//    switch (floor)
//    {
//    case 1:
//        return this.floorOne;
//        break;
//    case 2:
//        if (direction == UP) {
//            return this.floorTwo.up;
//        } else if (direction == DOWN) {
//            return this.floorTwo.down
//        } else return false;
//        break;
//    case 3:
//        if (direction == UP) {
//            return this.floorThree.up;
//        } else if (direction == DOWN) {
//            return this.floorThree.down
//        } else return false;
//        break;
//    case 4:
//        return this.floorFour;
//        break;
//    default:
//        return false;
//        break;
//    }
//}
//
//
//void addToQueue(struct Queue* queue, int floor, enum Direction direction) {
//    if (floor < 1 || floor > 4) {
//        // invalid options
//        return false;
//    };
//    switch (floor)
//    {
//    case 1:
//        queue->floorOne = true;
//        break;
//    case 2:
//        if (direction == UP) {
//            queue->floorTwo.up = true;
//        } else if (direction == DOWN) {
//            queue->floorTwo.down = true
//        }
//        break;
//    case 3:
//        if (direction == UP) {
//            queue->floorThree.up = true;
//        } else if (direction == DOWN) {
//            queue->floorThree.down = true
//        }
//        break;
//    case 4:
//        queue->floorFour = true;
//        break;
//    default:
//        /* noop */
//        break;
//    }
//};
//
//
//void popFromQueue(struct Queue* queue, int floor, enum Direction direction) {
//    if (floor < 1 || floor > 4) {
//        // invalid options
//        return;
//    };
//    switch (floor)
//    {
//    case 1:
//        queue->floorOne = false;
//        break;
//    case 2:
//        if (direction == UP) {
//            queue->floorTwo.up = false;
//        } else if (direction == DOWN) {
//            queue->floorTwo.down = false
//        }
//        break;
//    case 3:
//        if (direction == UP) {
//            queue->floorThree.up = false;
//        } else if (direction == DOWN) {
//            queue->floorThree.down = false
//        }
//        break;
//    case 4:
//        queue->floorFour = false;
//        break;
//    default:
//        /* noop */
//        break;
//    }
//};

