#include <Arduino.h>

#include "driver.h"
#include "screenManager.h"

#define MILLISPERCYCLE    50           /* 50 is milliseconds */

int main() {
    init();             // begin arduino stuff
    Serial.begin(9600); // start serial moniter


    ScreenManager *screens = new ScreenManager(MILLISPERCYCLE);                               // screen manager manages which screen to display
    screens->setScreen(new GameScreen(new StayingAlive_Driver(), new StayingAlive_Driver())); //set the starting screen

    // main game loop
    while (true) {
        screens->manageScreen(); // tells screen to update
    }

    Serial.flush();
    Serial.end();

    return(0);
}
