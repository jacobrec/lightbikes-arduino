#include "../util.h"


void colourAndAddToQueue(LittleGrid *cellGrid, List_t *q, int x, int y, int w, Cell *cn) {
    if (cellGrid->getTile(x, y) == 0b00) {
        cn->loc = x + y * w;
        push(q, cn);
        cellGrid->makeWall(x, y, cn->colour);
    }
}

// this function takes in the grid and a direction, and it assumes it has travelled to that new location specified by the turn
// then it counts up how many squares on the grid that it can get to before the opponent and returns that number
// dying should return 0
int Possession_Driver::calculatePossession(Grid_t *grid, Turn_t turn) {
    int         mx; int my; // my x and y position
    int         ox; int oy; // other bikes x and y position
    Direction_t oDir;

    if (grid->bike1 == this->myBike) {
        mx   = grid->bike1->getX();
        my   = grid->bike1->getY();
        ox   = grid->bike2->getX();
        oy   = grid->bike2->getY();
        oDir = grid->bike2->getDirection();
    }
    else{
        mx   = grid->bike2->getX();
        my   = grid->bike2->getY();
        ox   = grid->bike1->getX();
        oy   = grid->bike1->getY();
        oDir = grid->bike1->getDirection();
    }

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

    switch (oDir) {
        case NORTH:
            oy++;
            break;

        case WEST:
            ox--;
            break;

        case SOUTH:
            oy--;
            break;

        case EAST:
            ox++;
            break;
    }


    // all locations are now ready for testing posession

    if (grid->getTile(mx, my) != 0) { // if would die, return 0
        return(-32768);               // smallest int
    }

    // appologies for mixing c and c++ memory allocations
    // I wanted to reuse a list object I had already created
    int         w        = grid->width;
    int         h        = grid->height;
    List_t *    q        = createList(sizeof(Cell));
    LittleGrid *cellGrid = new LittleGrid(w, h);

    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (grid->getTile(x, y) != 0) {
                cellGrid->makeWall(x, y, 3);
            }
        }
    }


    Cell *c = (Cell * )malloc(sizeof(Cell));
    c->loc    = mx + my * w;
    c->colour = 1;
    push(q, c);

    c->loc    = ox + oy * w;
    c->colour = 2;
    push(q, c);

    int mine   = 0;
    int theres = 0;

    free(c);

    while (q->length > 0) {
        c = (Cell * )dequeue(q);
        int x = c->loc % w;
        int y = c->loc / w;
        cellGrid->makeWall(x, y, c->colour);

        Cell *cn = (Cell *)malloc(sizeof(Cell));
        cn->colour = c->colour;
        if (cn->colour == 1) {
            mine++;
        }
        else if (cn->colour == 2) {
            theres++;
        }
        free(c);

        if (cellGrid->getTile(x, y) == 0b00) {
            colourAndAddToQueue(cellGrid, q, x, y - 1, w, cn);
            colourAndAddToQueue(cellGrid, q, x, y + 1, w, cn);
            colourAndAddToQueue(cellGrid, q, x - 1, y, w, cn);
            colourAndAddToQueue(cellGrid, q, x + 1, y, w, cn);
        }

        free(cn);
    }

    delete cellGrid;
    destroyList(q);
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

    out = tileBlock & ((0b11 << (blockNum * 2)) >> (blockNum * 2));

    return(out & 0b11); // the & 0b11 is not nessecary, but it has a negligible speed differnce and makes me feel better
}

void LittleGrid::makeWall(int x, int y, uint8_t colour) {
    int tileBlock = this->tiles[(x / 2 + (y / 2) * (this->width / 2))];  // grabs the datablock from the array of tiles

    int blockNum = ((x % 2)) + ((y % 2) * 2);

    tileBlock &= ((0b11 << (blockNum * 2)) ^ 0b11111111); // clears location
    tileBlock |= (0b11 & colour) << (blockNum * 2);

    this->tiles[(x / 2 + (y / 2) * (this->width / 2))] = tileBlock; // sets the datablock to the newly set data
}

LittleGrid::~LittleGrid() {
    delete this->tiles;
}
