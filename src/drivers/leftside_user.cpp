// IMPORTANT: this file is only to be included into drivers.cpp and nowhere else

#define JOY_VERT          A1 /* should connect A1 to pin VRx */
#define JOY_HORIZ         A0 /* should connect A0 to pin VRy */
#define ANALOG_IN_SIZE    1023
int number = 10;


Direction_t getJoystickDirection(Direction_t current) {
    // reads in analog stick readings, and maps it to a positive negitive scale so 0 is neutral
    int y_joy = map(analogRead(JOY_VERT), 0, ANALOG_IN_SIZE, -ANALOG_IN_SIZE, ANALOG_IN_SIZE);
    int x_joy = map(analogRead(JOY_HORIZ), 0, ANALOG_IN_SIZE, -ANALOG_IN_SIZE, ANALOG_IN_SIZE);


    if (abs(y_joy) > abs(x_joy)) {             // if the y axis is pushed more then the x axis
        if (abs(y_joy) > ANALOG_IN_SIZE / 2) { // return north or south depending on the direction the jotsyick is pressed
            return((y_joy > 0) ? NORTH : SOUTH);
        }
    }
    else if (abs(x_joy) > abs(y_joy)) {        // if the x axis is pushed more then the y axis
        if (abs(x_joy) > ANALOG_IN_SIZE / 2) { // return east or west depending on the direction the jotsyick is pressed
            return((x_joy < 0) ? WEST : EAST);
        }
    }
    return(current); // if no direction can be determined, then return the players currentDirection
}

Turn_t UserL_Driver::steer(Grid_t *grid) {
    // determine the direction to turn by subracting the  joystick direction from the currentDirection
    // in most legal moves it will be 1 or zero, unless the currentDirection and joystick direction are north and west in which case it will be +-3
    int turn = (getJoystickDirection(this->myBike->currentDirection) - this->myBike->currentDirection);

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
