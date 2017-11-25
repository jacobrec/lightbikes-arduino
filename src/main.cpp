#include <Arduino.h>

#include "objects.h"
#include "game.h"
#include "drawing.h"



int main() {
    init();
    Serial.begin(9600);
    Serial.println("Starting program");

    //setup game
    Grid_t* grid = initWorld(64, 48);

    // main game loop
    while(true){
        Serial.println("updating starting");
        update(grid); // updates game world
        Serial.println("rendering starting");
        render(grid); // renders the world
        Serial.println("waiting for delay");
        delay(50);// 50 is milliseconds

    }

    Serial.flush();
    Serial.end();

    return 0;
}
