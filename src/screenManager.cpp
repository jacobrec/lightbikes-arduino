#include "screenManager.h"
#define LEFT_JOY_VERT      A1 /* should connect A1 to pin VRx of left joystick*/
#define LEFT_JOY_HORIZ     A0 /* should connect A0 to pin VRy of right joystick*/

#define RIGHT_JOY_VERT     A5 /* should connect A1 to pin VRx of left joystick*/
#define RIGHT_JOY_HORIZ    A4 /* should connect A0 to pin VRy of right joystick*/

#define ANALOG_IN_SIZE     1023

TouchScreen touch_screen = TouchScreen(4, A2, A3, 5, 300);


void Screen::setManager(ScreenManager *sm) {
    this->sm = sm;
}

void Screen::changeScreen(Screen *screen) {
    this->sm->setScreen(screen);
}

ScreenManager::ScreenManager(int millisPerFrame) {
    this->frameCount     = 0;
    this->millisPerFrame = millisPerFrame;
    this->currentScreen  = NULL;
}

void ScreenManager::manageScreen() {
    this->currentScreen->frame();
    ensureFrameRate(); // delay for constant frame rate
}

/*
 * This function ensures a constant Frame Rate to the best of it's ability
 * if the updating and rendering of the game take less time then the defined
 * milliseconds per frame, then it delays by the amount of time to needed so
 * the time for the frame to be constant.
 */
void ScreenManager::ensureFrameRate() {
    long diff = this->frameCount * this->millisPerFrame - millis();

    if (diff > 0) {
        delay(diff);
    }
    this->frameCount++;
}

void ScreenManager::setScreen(Screen *screen) {
    screen->setManager(this);

    delete this->currentScreen;

    this->currentScreen = screen;
    this->frameCount    = millis() / millisPerFrame; // initialize the framecount variable, this is used to get a constant framerate
}

ScreenManager::~ScreenManager() {
    delete this->currentScreen;
}

int joyControl(int driverID) {
    int y_joy;

    if (driverID == 1) { //determine which joystick controlling
        int y_joy = map(analogRead(LEFT_JOY_VERT), 0, ANALOG_IN_SIZE, -ANALOG_IN_SIZE, ANALOG_IN_SIZE);
    }
    else{
        int y_joy = map(analogRead(RIGHT_JOY_VERT), 0, ANALOG_IN_SIZE, -ANALOG_IN_SIZE, ANALOG_IN_SIZE);
    }

    if (abs(y_joy) > ANALOG_IN_SIZE / 2) { // return north or south depending on the direction the jotsyick is pressed
        return((y_joy > 0) ? 1 : -1);
    }
    else{
        return(0);
    }
}

#include "screens/game_screen.cpp"
#include "screens/main_menu_screen.cpp"
#include "screens/driverChooseMenu.cpp"
