#include "../util.h"



void colourAndAddToQueue(LittleGrid *cellGrid, CellQueue *que, int x, int y, int w, uint8_t colour) {
    if (cellGrid->getTile(x, y) == 0b00) {
        Cell c;
        c.loc = (uint16_t)(x + y * w);
        c.colour = colour;
        que->push(c);
        cellGrid->makeWall(x, y, colour);
    }
}

int freeRam() {
    extern int __heap_start, *__brkval;
    int        v;

    return((int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval));
}

// this function takes in the grid and a direction, and it assumes it has travelled to that new location specified by the turn
// then it counts up how many squares on the grid that it can get to before the opponent and returns that number
// dying should return 0
int Possession_Driver::calculatePossession(Grid_t *grid, Turn_t turn) {
    int mx; int my;         // my x and y position
    int ox; int oy;         // other bikes x and y position

    //int startRam = freeRam();

    int         w        = grid->width;
    int         h        = grid->height;
    CellQueue * que      = new CellQueue();
    LittleGrid *cellGrid = new LittleGrid(w, h);

    if (grid->bike1 == this->myBike) {
        mx = grid->bike1->getX();
        my = grid->bike1->getY();
        ox = grid->bike2->getX();
        oy = grid->bike2->getY();
    }
    else{
        mx = grid->bike2->getX();
        my = grid->bike2->getY();
        ox = grid->bike1->getX();
        oy = grid->bike1->getY();
    }
    cellGrid->makeWall(mx, my, 3);
    cellGrid->makeWall(ox, oy, 3);

    Direction_t toGo = (Direction_t)((turn + this->myBike->getDirection() + 4) % 4);
    switch (toGo) {
        case NORTH:
            my++;
            break;

        case WEST:
            mx--;
            break;

        case SOUTH:
            my--;
            break;

        case EAST:
            mx++;
            break;
    }


    // all locations are now ready for testing posession



    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (grid->getTile(x, y) != 0) {
                cellGrid->makeWall(x, y, 3);
            }
        }
    }
    // Un comment these next few lines to avoid ties
    // Although, ties are not losses and going kamazai does decrease losses
    // cellGrid->makeWall(ox+1, oy, 3);
    // cellGrid->makeWall(ox-1, oy, 3);
    // cellGrid->makeWall(ox, oy+1, 3);
    // cellGrid->makeWall(ox, oy-1, 3);


    if (cellGrid->getTile(mx, my) != 0) { // if would die, return 0
        delete que;
        delete cellGrid;
        // if (startRam > freeRam()) {
        //     SerialPrintf("Losing memory, started with %d but now we only have %d", startRam, freeRam());
        // }
        return(-32768);               // smallest int
    }

    cellGrid->makeWall(mx, my, 3);

    Cell c;
    c.loc = (uint16_t)(ox + oy * w);
    c.colour = 2;
    que->push(c);
    c.loc = (uint16_t)(mx + my * w);
    c.colour = 1;
    que->push(c);

    int mine   = 0;
    int theres = 0;


    while (que->getLength() > 0) {
        c = que->dequeue();
        int x = c.loc % w;
        int y = c.loc / w;
        cellGrid->makeWall(x, y, c.colour);

        if (c.colour == 1) {
            mine++;
        }
        else if (c.colour == 2) {
            theres++;
        }
        colourAndAddToQueue(cellGrid, que, x, y - 1, w, c.colour);
        colourAndAddToQueue(cellGrid, que, x, y + 1, w, c.colour);
        colourAndAddToQueue(cellGrid, que, x - 1, y, w, c.colour);
        colourAndAddToQueue(cellGrid, que, x + 1, y, w, c.colour);
    }


    delete que;
    delete cellGrid;
    // if (startRam > freeRam()) {
    //     SerialPrintf("Losing memory, started with %d but now we only have %d", startRam, freeRam());
    // }

    return(mine - theres);
}

Turn_t Possession_Driver::steer(Grid_t *grid) {
    int lPos = this->calculatePossession(grid, LEFT);
    int rPos = this->calculatePossession(grid, RIGHT);
    int sPos = this->calculatePossession(grid, STRAIGHT);

    int turnOrder[3] = { STRAIGHT, LEFT, RIGHT };
    int posOrder[3]  = { sPos, lPos, rPos };

    parallelSort(posOrder, turnOrder, 3);

    return((Turn_t)turnOrder[0]);
}

void Possession_Driver::swap(int *a, int *b) {
    int temp = *a;

    *a = *b;
    *b = temp;
}

void Possession_Driver::parallelSort(int *comparer, int *latched, int size) {
    int i, j;

    for (i = 0; i < size - 1; i++) { // bubble sort as there is only three elements ever
        for (j = 0; j < size - i - 1; j++) {
            if (comparer[j] < comparer[j + 1]) {
                swap(&comparer[j], &comparer[j + 1]);
                swap(&latched[j], &latched[j + 1]);
            }
        }
    }
}

LittleGrid::LittleGrid(int w, int h) {
    this->width  = w;
    this->height = h;
    this->tiles  = new Tile[width * height / 4](); // divide by 4, as 4 tiles are encoded into one bytes
}

Tile LittleGrid::getTile(int x, int y) {
    if (x > this->width || x < 0 || y > this->height || y < 0) {
        return(0b11);
    }
    int  tileBlock = this->tiles[(x / 2 + (y / 2) * (this->width / 2))]; // grabs the datablock from the array of tiles
    Tile out;

    // this switch statement determines which part of the datablock is selected by using the x and y
    int blockNum = ((x % 2)) + ((y % 2) * 2);

    out = (tileBlock & ((0b11 << (blockNum * 2)))) >> (blockNum * 2);

    return(out & 0b11); // the & 0b11 is not nessecary, but it has a negligible speed differnce and makes me feel better
}

void LittleGrid::makeWall(int x, int y, uint8_t colour) {
    if (x >= this->width || x < 0 || y >= this->height || y < 0) {
        return;
    }
    int tileBlock = this->tiles[(x / 2 + (y / 2) * (this->width / 2))];  // grabs the datablock from the array of tiles

    int blockNum = ((x % 2)) + ((y % 2) * 2);

    tileBlock &= ((0b11 << (blockNum * 2)) ^ 0b11111111); // clears location
    tileBlock |= (0b11 & colour) << (blockNum * 2);

    this->tiles[(x / 2 + (y / 2) * (this->width / 2))] = tileBlock; // sets the datablock to the newly set data
}

LittleGrid::~LittleGrid() {
    delete this->tiles;
}
