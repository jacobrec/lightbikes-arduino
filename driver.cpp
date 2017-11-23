#include "driver.h"
#include "objects.h"

Turn_t StayingAlive_Driver::steer(Grid_t *grid) {
    bool isNorthSafe;
    bool isSouthSafe;
    bool isEastSafe;
    bool isWestSafe;

    int x = this->myBike->x;
    int y = this->myBike->y;

    // checks the tiles around it to see what direction is safe
    isNorthSafe = (grid->getTile(x, y + 1) == 0b00);
    isSouthSafe = (grid->getTile(x, y - 1) == 0b00);
    isEastSafe  = (grid->getTile(x + 1, y) == 0b00);
    isWestSafe  = (grid->getTile(x - 1, y) == 0b00);


    // check if straight is safe, if it is, return straight
    switch (this->myBike->currentDirection) {
        case NORTH:
            if (isNorthSafe) {
                return(STRAIGHT);
            }
            break;

        case EAST:
            if (isEastSafe) {
                return(STRAIGHT);
            }
            break;

        case SOUTH:
            if (isSouthSafe) {
                return(STRAIGHT);
            }
            break;

        case WEST:
            if (isWestSafe) {
                return(STRAIGHT);
            }
            break;
    }

    // check if right is safe, if it is, return right
    switch (this->myBike->currentDirection) {
        case NORTH:
            if (isEastSafe) {
                return(RIGHT);
            }
            break;

        case EAST:
            if (isSouthSafe) {
                return(RIGHT);
            }
            break;

        case SOUTH:
            if (isWestSafe) {
                return(RIGHT);
            }
            break;

        case WEST:
            if (isNorthSafe) {
                return(RIGHT);
            }
            break;
    }

    // check if left is safe, if it is, return left
    switch (this->myBike->currentDirection) {
        case NORTH:
            if (isWestSafe) {
                return(LEFT);
            }
            break;

        case EAST:
            if (isNorthSafe) {
                return(LEFT);
            }
            break;

        case SOUTH:
            if (isEastSafe) {
                return(LEFT);
            }
            break;

        case WEST:
            if (isSouthSafe) {
                return(LEFT);
            }
            break;
    }

    // if nothing is safe, go straight and accept death
    return(STRAIGHT);
}


Turn_t UserL_Driver::steer(Grid_t *grid) {
    // Jarrett add this function
    return(STRAIGHT);
}
