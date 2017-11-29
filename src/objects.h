#ifndef _OBJECTS_H_
#define _OBJECTS_H_
#include <Arduino.h>

// define directional enums, the values are set for easy turning, see void Bike_t::drive(Grid_t *grid) in objects.cpp for example
enum Direction_t { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };
enum Turn_t { LEFT = -1, RIGHT = 1, STRAIGHT = 0 };


typedef char   Tile; // info about the tile, 0b00000000 if tile is empty, 0b00000001 if wall

// predeclare classes so they can reference each other
class Bike_t;
class Driver_t;

// Grid holds the tiles and bikes, as well as some other data about the arena
class Grid_t {
private:
    Tile *tiles; // tiles are stored with 8 tiles per byte. tiles[0] holds the 8 tiles that are in the top left corner in a rectangle formation, this is to save space on the arduinos limited memory
public:
    // height and width/2 must be divisible by 2 due to the encoding, this encoding however uses 12.5% of the memory it would otherwise use
    Grid_t(int height, int width, Driver_t *d1, Driver_t *d2, uint16_t colour1, uint16_t colour2);
    ~Grid_t();

    Tile getTile(int x, int y);
    void makeWall(int x, int y);

    int     height;
    int     width;
    Bike_t *bike1;
    Bike_t *bike2;

    bool isGamePlaying;
};



class Bike_t {
private:
    Driver_t *  driver; // the driver of a bike is what determines it's steering behavior, like whether it's an A.I. or player
    Direction_t currentDirection;
    int         x;
    int         y;
    int         id;
    bool        isAlive;
    uint16_t    colour;
public:
    Bike_t(int x, int y, int id, Direction_t, Driver_t *, uint16_t);
    ~Bike_t();

    void drive(Grid_t *grid);

    int getX() {
        return(this->x);
    }

    int getY() {
        return(this->y);
    }

    int getAlive() {
        return(this->isAlive);
    }

    int getID() {
        return(this->id);
    }
    uint16_t getColour(){
        return this->colour;
    }

    friend void checkCollision(Bike_t *bike, Grid_t *grid);

    Direction_t getDirection() {
        return(this->currentDirection);
    }
};

// this class is extended to get the different driver types, both player and A.I. ones
class Driver_t {
protected:
    Bike_t *myBike;
public:

    virtual ~Driver_t();

    void setBike(Bike_t *bike);

    virtual Turn_t steer(Grid_t *grid) { // this method is to be extended to form the differnt behaviors of the driver types
        return(STRAIGHT);
    }
};


#endif
