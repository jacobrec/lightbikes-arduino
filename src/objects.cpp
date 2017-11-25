#include "objects.h"

Grid_t::Grid_t(int w, int h, Driver_t *d1, Driver_t *d2) {
    this->width  = w;
    this->height = h;
    this->tiles  = new Tile[width * height / 4](); // divide by 4, as 4 tiles are encoded into one bytes

    // creates new bikes facing eachother at opposite ends of the arena and assignes the bikes to the drivers
    this->bike1  = new Bike_t(width - 4, height / 2, 1, WEST, d1);
    this->bike2  = new Bike_t(3, height / 2-1, 2, EAST, d2);
    d1->setBike(this->bike1);
    d2->setBike(this->bike2);

    // build a wall wround the edge of the arena, the type of wall is set to 0 to indicate unowned walls
    for(int i = 0; i < width; i++){
        this->makeWall(i,0,0);
        this->makeWall(i,height-1,0);
    }
    for(int i = 0; i < height; i++){
        this->makeWall(0,i,0);
        this->makeWall(width-1,i,0);
    }
}

Tile Grid_t::getTile(int x, int y) {
    char tileBlock   = this->tiles[(x / 2 + y / 2 * this->width/2)]; // things are divided by two so the correct datablock is selected
    Tile out;

    // this switch statement determines which part of the datablock is selected by using the x and y
    switch (((x % 2) << 1) | (y % 2)) {// sets out equal to just the two bits for the location
        case 0b00: // top left
            out = 0b00000011 & tileBlock;
            break;

        case 0b10: // top right
            out = (0b00001100 & tileBlock) >> 2;
            break;

        case 0b01: // bottom left
            out = (0b00110000 & tileBlock) >> 4;
            break;

        case 0b11: // bottom right
            out = (0b11000000 & tileBlock) >> 6;
            break;
    }

    return(out & 0b11); // the & 0b11 is not nessecary, but it has a negligible speed differnce and makes me feel better
}

void Grid_t::makeWall(int x, int y, int playerNumber) {
    int  tileBlock = this->tiles[(x / 2 + y / 2 * this->width/2)]; // grabs the datablock from the array of tiles
    Tile inp       = ((playerNumber) + 1) & 0b11;// sets the tile to the data for the wall, 10 and 11 are the wall types,
    // so that is why the plus one is there. the & 0b11 is not nesseciry, but it has a negligible speed differnce and makes me feel better

    // this switch statement determines which part of the datablock is selected by using the x and y
    switch (((x % 2) << 1) | (y % 2)) {// sets the proper location in the tile Datablock to the new info
        case 0b00: // top left
            tileBlock &= 0b11111100;
            tileBlock |= inp << 0;
            break;

        case 0b10: // top right
            tileBlock &= 0b11110011;
            tileBlock |= inp << 2;
            break;

        case 0b01: // bottom left
            tileBlock &= 0b11001111;
            tileBlock |= inp << 4;
            break;

        case 0b11: // bottom right
            tileBlock &= 0b00111111;
            tileBlock |= inp << 6;
            break;
    }
     this->tiles[(x / 2 + y / 2 * this->width/2)] = tileBlock; // sets the datablock to the newly set data
}

// creates a new bike with the assigned values
Bike_t::Bike_t(int x, int y, int id, Direction_t dir, Driver_t *driver) {
    this->x       = x;
    this->y       = y;
    this->id      = id;
    this->isAlive = true;

    this->currentDirection = dir;
    this->driver           = driver;
}

void Bike_t::drive(Grid_t *grid) {
    // Driver determines how it drives, takes in grid, and pops out a direction for the bike
    Turn_t turn = this->driver->steer(grid);

    // calculates new direction by turning the current direction, +4 is so turning left while going north is not an negitive
    this->currentDirection = (Direction_t)((turn + this->currentDirection + 4) % 4);

    // based on the this->currentDirection
    switch (this->currentDirection) {
        case NORTH:
            this->y++;
            break;

        case WEST:
            this->x--;
            break;

        case SOUTH:
            this->y--;
            break;

        case EAST:
            this->x++;
            break;
    }

}

void Driver_t::setBike(Bike_t *bike) { // this sets the refence to the bike, this could have been part of the constructor, but the drivers are created before the bike
    this->myBike = bike;
}
