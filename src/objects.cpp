#include "objects.h"

Grid_t::Grid_t(int w, int h, Driver_t *d1, Driver_t *d2, uint16_t colour1, uint16_t colour2) {
    this->width  = w;
    this->height = h;
    this->tiles  = new Tile[width * height / 4](); // divide by 4, as 4 tiles are encoded into one bytes

    // creates new bikes facing eachother at opposite ends of the arena and assignes the bikes to the drivers
    this->bike1 = new Bike_t(3, height / 2, 1, WEST, d1, colour1);
    this->bike2 = new Bike_t(width - 4, height / 2 - 1, 2, EAST, d2, colour2);
    d1->setBike(this->bike1);
    d2->setBike(this->bike2);

    // build a wall wround the edge of the arena
    for (int i = 0; i < width; i++) {
        this->makeWall(i, 0);
        this->makeWall(i, height - 1);
    }
    for (int i = 0; i < height; i++) {
        this->makeWall(0, i);
        this->makeWall(width - 1, i);
    }
}

Tile Grid_t::getTile(int x, int y) {
    int  tileBlock = this->tiles[(x / 4 + (y / 2) * (this->width / 4))]; // grabs the datablock from the array of tiles
    Tile out;

    // this switch statement determines which part of the datablock is selected by using the x and y
    int blockNum = ((x % 4)) + ((y % 2) * 4);

    out = (tileBlock & (1 << blockNum)) >> blockNum;

    return(out & 0b1); // the & 0b1 is not nessecary, but it has a negligible speed differnce and makes me feel better
}

void Grid_t::makeWall(int x, int y) {
    int tileBlock = this->tiles[(x / 4 + (y / 2) * (this->width / 4))];  // grabs the datablock from the array of tiles

    int blockNum = ((x % 4)) + ((y % 2) * 4);

    tileBlock |= (0b1 << blockNum);

    this->tiles[(x / 4 + (y / 2) * (this->width / 4))] = tileBlock; // sets the datablock to the newly set data
}

// creates a new bike with the assigned values
Bike_t::Bike_t(int x, int y, int id, Direction_t dir, Driver_t *driver, uint16_t colour) {
    this->x       = x;
    this->y       = y;
    this->id      = id;
    this->isAlive = true;

    this->currentDirection = dir;
    this->driver           = driver;
    this->colour          = colour;
}

void Bike_t::drive(Grid_t *grid) {
    // Driver determines how it drives, takes in grid, and pops out a direction for the bike to go
    Turn_t turn = this->driver->steer(grid);

    // calculates new direction by turning the current direction, +4 is so turning left while going north is not an negitive
    this->currentDirection = (Direction_t)((turn + this->currentDirection + 4) % 4);

    // changed the bikes position based on it's current direction
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

void Driver_t::setBike(Bike_t *bike) { // this sets the reference to the bike, this could have been part of the constructor, but the drivers are created before the bike
    this->myBike = bike;
}

Bike_t::~Bike_t() {
    delete this->driver;
}

Grid_t::~Grid_t() {
    delete this->tiles;
    delete this->bike1;
    delete this->bike2;
}

Driver_t::~Driver_t() {
    // has a pointer to myBike, but the deleting of that is handled in the destructor of grid_t
}
