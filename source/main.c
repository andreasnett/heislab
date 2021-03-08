#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "stateController.h"
#include "elevatorStatus.h"
#include "elevator.h"

static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

int elevator_init(){
    int error = 0;
    error = hardware_init();
    if(error){
        fprintf(stderr, "Unable to initialize hardware\n");
        return 1;
    }

    error = StateConstructor();
    if (error){
        fprintf(stderr, "Unable to initialize the StateConstructor\n" );
        return 2;
    }

    error = ElevatorConstructor();
    if (error){
        fprintf(stderr,"Unable to initialize the Elevator struct\n" );
        return 3;
    }
    return 0;
}


int main(){
    int error = elevator_init();
    if(error){
        fprintf(stderr, "Unable to initialize the elevator\n");
        exit(1);
    }
    
    while(1){
        StateLoop();
    }  

    return 0;
}
