#include "game.h"
#include "driver.h"

Grid_t *initWorld(int width, int height) {// returns a new grid with a width of 36, a height of 28 and sets the two drivers to be StayingAlive_Driver
    return(new Grid_t(width, height, new StayingAlive_Driver(), new StayingAlive_Driver()));
}

void update(Grid_t *grid) {
    grid->isGamePlaying = (grid->bike1->isAlive && grid->bike2->isAlive);

    // the update method first adds a wall in the bikes current locations, then moves the bike, then checks to see if the bike hit anything
    if (grid->isGamePlaying) {// only updates if both bikes are alive
        addWall(grid->bike1, grid);
        addWall(grid->bike2, grid);

        grid->bike1->drive(grid);
        grid->bike2->drive(grid);

        checkCollision(grid->bike1, grid);
        checkCollision(grid->bike2, grid);

    }
}

void addWall(Bike_t *bike, Grid_t *grid) {// this leaves a trail of the wall behind it as it travels
    grid->makeWall(bike->x, bike->y, bike->id);
}

void checkCollision(Bike_t *bike, Grid_t *grid) {
    if (grid->getTile(bike->x, bike->y) == 0b00) { // safe, 0b00 is the empty tile code
        if (grid->bike1->x == grid->bike2->x && grid->bike1->y == grid->bike2->y) { // if the bikes collided, set this one to dead
            bike->isAlive = false;
        }
    }
    else{ // the bike hit a wall and should be dead
        bike->isAlive = false;
    }
}
