#include <stdlib.h>
#include <stdbool.h>

typedef enum state {
    STATE_elevatorInit = 0,
    STATE_elevatorStandStill,
    STATE_elevatorGoingUp,
    STATE_elevatorGoingDown,
    STATE_elevatorEmergency
    STATE_elevatorError
}