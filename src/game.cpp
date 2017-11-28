#include "game.h"
#include "driver.h"

Grid_t *initWorld(int width, int height, Driver_t *d1, Driver_t *d2) { // returns a new grid and sets the two drivers
    // setup code can go here
    return(new Grid_t(width, height, d1, d2));
}

void update(Grid_t *grid) {
    grid->isGamePlaying = (grid->bike1->getAlive() && grid->bike2->getAlive());

    // the update method first moves the bike, then checks to see if the bike hit anything  then adds a wall in the bikes current locations
    // this order is so there is no advantage to being either player, for example in a head on collision, players will now both die instead of just one
    if (grid->isGamePlaying) { // only updates if both bikes are alive


        grid->bike1->drive(grid);
        grid->bike2->drive(grid);

        checkCollision(grid->bike1, grid);
        checkCollision(grid->bike2, grid);

        addWall(grid->bike1, grid);
        addWall(grid->bike2, grid);
    }
}

void addWall(Bike_t *bike, Grid_t *grid) { // this leaves a trail of the wall behind it as it travels
    grid->makeWall(bike->getX(), bike->getY());
}

void checkCollision(Bike_t *bike, Grid_t *grid) {
    if (grid->getTile(bike->x, bike->y) == 0b00) {                                  // safe, 0b00 is the empty tile code
        if (grid->bike1->x == grid->bike2->x && grid->bike1->y == grid->bike2->y) { // if the bikes collided, set this one to dead
            bike->isAlive = false;
        }
    }
    else{ // the bike hit a wall and should be dead
        bike->isAlive = false;
    }
}
