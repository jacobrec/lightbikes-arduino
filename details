Use a MVC(Model, View, Controller) pattern
https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller

The model will include:
the grid,
the bike,

The view will include:
gridRenderer,

The controller will include:
World Controller
Bike controllers
    A.I.
    Player

Titlescreen will be independent however will use the mvc parts to display titlescreen


## Model
enum Direction{
    UP, LEFT, RIGHT, DOWN
};
struct Bike{
    int x;
    int y;
    Direction d;
    bool isAlive;
};
enum TileType {EMPTY = 0, BIKE_ONE, BIKE_TWO, BIKE_ONE_TILE, BIKE_TWO_TILE};
enum GridState {BATTLING = 0, WINNER_ONE, WINNER_TWO};
struct Grid{

    TileType tiles[32][24]; // screen size is 320x240 in landscape mode so we need something that squarely divides both. These values should be defined somewhere not hard coded in

    Bike b1;
    Bike b2;

    GridState currentState;
}
## View
render like a simpler version of this maybe?
http://www.fltron.com/

only really needs to draw a square of the right colour at the bikes current location
will need to draw a win screen when grid state is not battling

## Controller
GridController
Will need to call both bike controllers as well as check for win conditions


### BikeController
A class that handles the bikes

public:
void moveLeft(); // These 3 functions will do actual moving
void moveRight();
void moveForward();
bool isAlive(); // Checks if the bike is currently alive

void doMove(); // Determines the direction to move by calling calculateMove() as well as calls didCrash() and addLine()

Bike b; // Reference to the bike object

private:
virtual void calculateMove(); // overridden by player or A.I.
void didCrash(); // calculates if the move will lead to crashing, take into account the headcase
void addLine(); // adds line to grid

Both players and A.I. extend BikeController, doMove() uses it's controller
