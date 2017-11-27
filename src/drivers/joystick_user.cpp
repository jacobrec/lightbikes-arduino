// IMPORTANT: this file is only to be included into drivers.cpp and nowhere else
#define LEFT_JOY_VERT      A1 /* should connect A1 to pin VRx of left joystick*/
#define LEFT_JOY_HORIZ     A0 /* should connect A0 to pin VRy of right joystick*/

#define RIGHT_JOY_VERT     A1 /* should connect A1 to pin VRx of left joystick*/
#define RIGHT_JOY_HORIZ    A0 /* should connect A0 to pin VRy of right joystick*/



#define ANALOG_IN_SIZE     1023

Joystick_Driver::Joystick_Driver(uint8_t pinX, uint8_t pinY) {
    this->pinX = pinX;
    this->pinY = pinY;
}

Direction_t Joystick_Driver::getJoystickDirection(Direction_t current) {
    // reads in analog stick readings, and maps it to a positive negitive scale so 0 is neutral
    int y_joy = map(analogRead(this->pinY), 0, ANALOG_IN_SIZE, -ANALOG_IN_SIZE, ANALOG_IN_SIZE);
    int x_joy = map(analogRead(this->pinX), 0, ANALOG_IN_SIZE, -ANALOG_IN_SIZE, ANALOG_IN_SIZE);


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

Turn_t Joystick_Driver::steer(Grid_t *grid) {
    return(getTurn(getJoystickDirection(this->myBike->getDirection()), this->myBike->getDirection()));
}



Joystick_Driver *createUserR_Driver() {
    return(new Joystick_Driver(RIGHT_JOY_VERT, RIGHT_JOY_HORIZ));
}

Joystick_Driver *createUserL_Driver() {
    return(new Joystick_Driver(LEFT_JOY_VERT, LEFT_JOY_HORIZ));
}
