#include <Arduino.h>
#include "screenManager.h"

#define MILLIS_PER_CYCLE    150           /* in milliseconds */

int main() {
    init();             // begin arduino stuff
    Serial.begin(9600); // start serial moniter

    setUpGraphics();    // initializes the graphics system, as well as draws boarder


    ScreenManager *screens = new ScreenManager(MILLIS_PER_CYCLE); // screen manager manages which screen to display
    screens->setScreen(new MainMenuScreen());                     //set the starting screen
    screens->setScreen(new GameScreen(new Possession_Driver, new Runner_ai(), ILI9341_RED, ILI9341_BLUE));
    // main game loop
    while (true) {
        screens->manageScreen(); // tells screen to update
    }

    delete screens;

    Serial.flush();
    Serial.end();

    return(0);
}
