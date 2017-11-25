#include <Arduino.h>

#include "objects.h"
#include "game.h"
#include "drawing.h"

#define millisPerCycle    50 /* 50 is milliseconds */
void ensureFrameRate(long frameCount);

int main() {
    init();
    Serial.begin(9600);

    //setup game
    Grid_t *grid       = initWorld(64, 48);
    long    frameCount = 0;

    // main game loop
    while (true) {
        update(grid); // updates game world
        render(grid); // renders the world
        ensureFrameRate(frameCount++);
    }

    Serial.flush();
    Serial.end();

    return(0);
}

void ensureFrameRate(long frameCount) {
    long diff = frameCount * millisPerCycle - millis();

    if (diff > 0) {
        delay(diff);
    }
}
