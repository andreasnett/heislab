#include "queue.h"
#include <stdbool.h>
#include "hardware.h"


struct Queue queueConstructor() {
    struct Queue que = {
        .firstFloor = 0,
        .lastFloor = 0
    };
    for (int i = 0; i < NUMBER_OF_FLOORS; ++i){
        que.floor[i].up = 0;
        que.floor[i].down = 0;
    }
    return que;
};


int queueAdd(struct Queue* queue, int floor, enum Direction direction) {
    if(floor == FIRST_FLOOR){
        if (direction == UP){
            hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
        }
        else if (direction == INSIDE){
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
        }
        queue->firstFloor = 1;
        return 1;
    }
    else if (floor == LAST_FLOOR){
        if (direction == DOWN){
            hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
        }
        else if (direction == INSIDE){
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
        }    
        queue->lastFloor = 1;
        return 1;
    }
    else {
        if (direction == UP) {
            queue->floor[floor - 1].up = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
        } 
        else if (direction == DOWN) {
            queue->floor[floor - 1].down = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
        }
        else if (direction == INSIDE){
            queue->floor[floor - 1].up = 1;
            queue->floor[floor - 1].down = 1;
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
        }
        return 1;
    }
    return 0;
};


int queuePop(struct Queue* queue, int floor) {
    if(floor == FIRST_FLOOR){
        queue->firstFloor = 0;
    }
    else if (floor == LAST_FLOOR){
        queue->lastFloor = 0;
    }
    else {
        queue->floor[floor - 1].down = 0;
        queue->floor[floor - 1].up = 0;
    }
    hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
    return 0;
};

void queueClearAll(struct Queue *queue){
    for (int i = 0; i <= LAST_FLOOR; ++i){
        queuePop(queue, i);
    }    
}

int queueCheckStop(struct Queue queue, int floor, enum Direction direction) {
    if(floor == FIRST_FLOOR){
        return queue.firstFloor;
    }
    else if (floor == LAST_FLOOR){
        return queue.lastFloor;
    }
    else {
        if (direction == UP){
            return queue.floor[floor - 1].up;
        }
        else if (direction == DOWN){
            return queue.floor[floor - 1].down;
        }
    }
    return 0;
}

int queueCheckCall(int *floor, enum Direction *direction){
    if (hardware_read_order(FIRST_FLOOR, HARDWARE_ORDER_UP)){
        *floor = FIRST_FLOOR;
        *direction = UP;
        return 1;
    }
    else if (hardware_read_order(FIRST_FLOOR, HARDWARE_ORDER_INSIDE)){
        *floor = FIRST_FLOOR;
        *direction = INSIDE;
        return 1;
    }
    else if (hardware_read_order(LAST_FLOOR, HARDWARE_ORDER_DOWN)){
        *floor = LAST_FLOOR;
        *direction = DOWN;
        return 1;
    }
    else if (hardware_read_order(LAST_FLOOR, HARDWARE_ORDER_INSIDE)){
        *floor = LAST_FLOOR;
        *direction = INSIDE;
        return 1;
    }
    else{
        for (int i = 0; i < NUMBER_OF_FLOORS; ++i){
            if (hardware_read_order(i + 1, HARDWARE_ORDER_UP)){
                *floor = i + 1;
                *direction = UP;
                return 1;    
            }
            else if (hardware_read_order(i + 1, HARDWARE_ORDER_DOWN)){
                *floor = i + 1;
                *direction = DOWN;
                return 1;
            }
            else if (hardware_read_order(i + 1, HARDWARE_ORDER_INSIDE)){
                *floor = i + 1;
                *direction = INSIDE;
                return 1;
            }
        }
    }
    return 0;
}

int queueCheckFloorSensor(int *floor){
    if (hardware_read_floor_sensor(FIRST_FLOOR)){
        *floor = FIRST_FLOOR;
        return 1;
    }
    else if (hardware_read_floor_sensor(LAST_FLOOR)){
        *floor = LAST_FLOOR;
        return 1;
    } 
    else{
        for (int i = 0; i < NUMBER_OF_FLOORS; ++i){
            if (hardware_read_floor_sensor(i + 1)){
                *floor = i + 1;
                return 1;
            }
        }
    }
    return 0;
}

int queueCheckNewTarget(struct Queue queue, int currentFloor, int *newTargetFloor){
    if (currentFloor == FIRST_FLOOR){
        if (queue.lastFloor){
            *newTargetFloor = LAST_FLOOR;
            return 1;
        }
        for (int i = NUMBER_OF_FLOORS - 1; i >= 0; --i){
            if (queue.floor[i].up || queue.floor[i].down){
                *newTargetFloor = i + 1;
                return 1;
            }
        }
    }
    else if (currentFloor == LAST_FLOOR){
        if (queue.firstFloor){
            *newTargetFloor = FIRST_FLOOR;
            return 1;
        }
        for (int i = 0; i < NUMBER_OF_FLOORS; ++i){
            if (queue.floor[i].up || queue.floor[i].down){
                *newTargetFloor = i + 1;
                return 1;
            }
        }  
    }
    for (int i = 0; i < NUMBER_OF_FLOORS; ++i){
        if ((currentFloor == i + 1) && ((i - NUMBER_OF_FLOORS/2) >= 0)){
            if (queue.lastFloor){
                *newTargetFloor = LAST_FLOOR;
                return 1;
            }
            for (int i = NUMBER_OF_FLOORS - 1; i >= 0; --i){
                if (queue.floor[i].up || queue.floor[i].down){
                    *newTargetFloor = i + 1;
                    return 1;
                }
            }
            if (queue.firstFloor){
                *newTargetFloor = FIRST_FLOOR;
                return 1;
            }
        }
        else if ((currentFloor == i + 1) && ((i - NUMBER_OF_FLOORS/2) < 0)){
            if (queue.firstFloor){
                *newTargetFloor = FIRST_FLOOR;
                return 0;
            }
            for (int i = 0; i < NUMBER_OF_FLOORS; ++i){
                if (queue.floor[i].up || queue.floor[i].down){
                    *newTargetFloor = i + 1;
                    return 1;
                }
            }
            if (queue.lastFloor){
                *newTargetFloor = LAST_FLOOR;
                return 1;
            }
        }
    }
    return 0;
}