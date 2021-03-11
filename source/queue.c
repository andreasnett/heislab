#include "queue.h"
#include <stdbool.h>
#include "elevator.h"
#include "hardware.h"


struct Queue queueConstructor() {
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


int queueAdd(struct Queue* queue, int floor, enum Direction direction) {
    switch (floor)
    {
    case 1:
        if (direction == UP){
            hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
        }
        else if (direction == INSIDE){
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
        }
        queue->floorOne = true;
        break;
    case 2:
        if (direction == UP) {
            queue->floorTwo.up = true;
            hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
        } 
        else if (direction == DOWN) {
            queue->floorTwo.down = true;
            hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
        }
        else if (direction == INSIDE){
            queue->floorTwo.up = true;
            queue->floorTwo.down = true;
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
        }
        break;
    case 3:
        if (direction == UP) {
            queue->floorThree.up = true;
            hardware_command_order_light(floor, HARDWARE_ORDER_UP, 1);
        } 
        else if (direction == DOWN) {
            queue->floorThree.down = true;
            hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
        }
        else if (direction == INSIDE){
            queue->floorThree.up = true;
            queue->floorThree.down = true;
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
        }
        break;
    case 4:
        if (direction == DOWN){
            hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 1);
        }
        else if (direction == INSIDE){
            hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 1);
        }    
        queue->floorFour = true;
        break;
    default:
        return 1; //Error, floor out of range
        break;
    }
    return 0;
};


int queuePop(struct Queue* queue, int floor) {
    switch (floor)
    {
    case FLOOR_ONE:
        queue->floorOne = false;
        break;
    case FLOOR_TWO:
        queue->floorTwo.up = false;
        queue->floorTwo.down = false;
        break;
    case FLOOR_THREE:
        queue->floorThree.up = false;
        queue->floorThree.down = false;
        break;
    case FLOOR_FOUR:
        queue->floorFour = false;
        break;
    default:
        return 1; //Error, floor out of range
        break;
    }
    hardware_command_order_light(floor, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_DOWN, 0);
    hardware_command_order_light(floor, HARDWARE_ORDER_INSIDE, 0);
    return 0;
};

int queueClearAll(struct Queue *queue){

}

int queueCheckStop(struct Queue this, int floor, enum Direction direction) {
    if (floor < 1 || floor > 4) {
        // invalid options
        return false;
    };
    switch (floor)
    {
    case 1:
        return this.floorOne;
        break;
    case 2:
        if (direction == UP) {
            return this.floorTwo.up;
        } 
        else if (direction == DOWN) {
            return this.floorTwo.down;
        } 
        else return false;
        break;
    case 3:
        if (direction == UP) {
            return this.floorThree.up;
        } else if (direction == DOWN) {
            return this.floorThree.down;
        } else return false;
        break;
    case 4:
        return this.floorFour;
        break;
    default:
        return false;
        break;
    }
}

int queueCheckCall(int *floor, enum Direction *direction){
    if (hardware_read_order(FLOOR_ONE, HARDWARE_ORDER_UP)){
        *floor = FLOOR_ONE;
        *direction = UP;
        return 1;
    }
    else if (hardware_read_order(FLOOR_ONE, HARDWARE_ORDER_INSIDE)){
        *floor = FLOOR_ONE;
        *direction = INSIDE;
        return 1;
    } 
    else if (hardware_read_order(FLOOR_TWO, HARDWARE_ORDER_UP)){
        *floor = FLOOR_TWO;
        *direction = UP;
        return 1;
    }
    else if (hardware_read_order(FLOOR_TWO, HARDWARE_ORDER_DOWN)){
        *floor = FLOOR_TWO;
        *direction = DOWN;
        return 1;
    }
    else if (hardware_read_order(FLOOR_TWO, HARDWARE_ORDER_INSIDE)){
        *floor = FLOOR_TWO;
        *direction = INSIDE;
        return 1;
    }
    else if (hardware_read_order(FLOOR_THREE, HARDWARE_ORDER_UP)){
        *floor = FLOOR_THREE;
        *direction = UP;
        return 1;
    }
    else if (hardware_read_order(FLOOR_THREE, HARDWARE_ORDER_DOWN)){
        *floor = FLOOR_THREE;
        *direction = DOWN;
        return 1;
    }
    else if (hardware_read_order(FLOOR_THREE, HARDWARE_ORDER_INSIDE)){
        *floor = FLOOR_THREE;
        *direction = INSIDE;
        return 1;
    }
    else if (hardware_read_order(FLOOR_FOUR, HARDWARE_ORDER_DOWN)){
        *floor = FLOOR_FOUR;
        *direction = DOWN;
        return 1;
    }
    else if (hardware_read_order(FLOOR_FOUR, HARDWARE_ORDER_INSIDE)){
        *floor = FLOOR_FOUR;
        *direction = INSIDE;
        return 1;
    }
    return 0;
}

int queueCheckFloorSensor(int *floor){
    if (hardware_read_floor_sensor(FLOOR_ONE)){
        *floor = FLOOR_ONE;
        return 1;
    }
    else if (hardware_read_floor_sensor(FLOOR_TWO)){
        *floor = FLOOR_TWO;
        return 1;
    } 
    else if (hardware_read_floor_sensor(FLOOR_THREE)){
        *floor = FLOOR_THREE;
        return 1;
    }
    else if (hardware_read_floor_sensor(FLOOR_FOUR)){
        *floor = FLOOR_FOUR;
        return 1;
    }
    else{
        *floor = FLOOR_NONE;
        return 1;
    }
    return 0;
}