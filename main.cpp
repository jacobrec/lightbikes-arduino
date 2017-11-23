#include "objects.h"
#include "game.h"
#include "drawing.h"
#include <Arduino.h>



int main() {

    // setup game
    Grid_t* grid = initWorld();

    // main game loop
    while(true){
        update(grid); // updates game world
        render(grid); // renders the world
        delay(100);// 100 is milliseconds

    }

    return 0;
}
