#include <Arduino.h>
#include "driver.h"
#include "objects.h"
#include "util.h"

// useful functions that all drivers might want to use
Turn_t getTurn(Direction_t to, Direction_t from){
    // to and from are both direction enums, which are the north west, east, and south in a logical order so addition and subtraction with turns will make sense
    int turn = (to - from);

    // if its magnitude is 3, then it is a legal move, and needs to be converted to the correct turn, a 1 or -1
    // this only occurs when traveling north or west, and turning west or north
    if (abs(turn) == 3) {
        turn /= -3;
    }

    switch (turn) { // if the turn is not 0 or 2, it is a left or right turn and return that.
        case RIGHT: // turn is 1
            return(RIGHT);

        case LEFT: // turn is -1
            return(LEFT);
    }
    // otherwise if it is 0 or 2, either theyre turning straight, so return that. Or, they are trying to turn backwards, whcih is illegal, so also return straight
    return(STRAIGHT);
}



// This file is only to be used to include the drivers from the drivers folder
// <DRIVERS>
#include "drivers/staying_alive_ai.cpp"
#include "drivers/joystick_user.cpp"
#include "drivers/stalker_ai.cpp"
#include "drivers/runner_ai.cpp"
#include "drivers/possesion_ai.cpp"


// this is done too keep the project organized, we wanted to keep all the drivers in one sub folder, but
// we could not figure out how to change the arduino makefile to accommodate a hierarchical format like that
