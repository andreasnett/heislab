#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "fsm.h"
#include "elevatorStatus.h"
#include "elevator.h"

int main_init(){
    int error = 0;
    error = hardware_init();
    if(error){
        fprintf(stderr, "Unable to initialize hardware\n");
        return 1;
    }

    error = fsmControllerConstructor();
    if (error){
        fprintf(stderr, "Unable to initialize the fsmController struct\n" );
        return 2;
    }

    error = ElevatorConstructor();
    if (error){
        fprintf(stderr,"Unable to initialize the Elevator struct\n" );
        return 3;
    }
    return 0;
}

int main_cleanup(){
    fsmControllerDestructor();
    ElevatorDestructor();
    return 0;
}

int main(){
    int error = main_init();
    if(error){
        fprintf(stderr, "Unable to initialize the elevator\n");
        exit(1);
    }
    while(1){
        fsmRun();
    }

    main_cleanup();

    return 0;
}
