#include <Arduino.h>

#include "objects.h"
#include "game.h"
#include "drawing.h"

#define millisPerCycle    50           /* 50 is milliseconds */
void ensureFrameRate(long frameCount); // Predeclare function

int main() {
    init();             // begin arduino stuff
    Serial.begin(9600); // start serial moniter


    //setup game
    Grid_t *grid = initWorld(64, 48);            // create a new grid, the central world object of size 64x48
    setUpGraphics(grid);                         // initializes the graphics system, as well as draws boarder
    long frameCount = millis() / millisPerCycle; // initialize the framecount variable, this is used to get a constant framerate


    // main game loop
    while (true) {
        update(grid);                  // updates game world
        render(grid);                  // renders the world
        ensureFrameRate(frameCount++); // delay for constant frame rate
    }

    Serial.flush();
    Serial.end();

    return(0);
}

/*
 * This function ensures a constant Frame Rate to the best of it's ability
 * if the updating and rendering of the game take less time then the defined
 * milliseconds per frame, then it delays by the amount of time to needed so
 * the time for the frame to be constant.
 */
void ensureFrameRate(long frameCount) {
    long diff = frameCount * millisPerCycle - millis();

    if (diff > 0) {
        delay(diff);
    }
}
