#include <Arduino.h>
#include "screenManager.h"

#define MILLIS_PER_CYCLE    150           /* in milliseconds */

int main() {
    init();             // begin arduino stuff
    Serial.begin(9600); // start serial moniter

    setUpGraphics();    // initializes the graphics system, as well as draws boarder


    ScreenManager *screens = new ScreenManager(MILLIS_PER_CYCLE); // screen manager manages which screen to display
    screens->setScreen(new MainMenuScreen());                     //set the starting screen
    // main game loop
    while (true) {
        screens->manageScreen(); // tells screen to update
    }

    delete screens;

    Serial.flush();
    Serial.end();

    return(0);
}
