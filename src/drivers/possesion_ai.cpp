// this function takes in the grid and a direction, and it assumes it has travelled to that new location specified by the turn
// then it counts up how many squares on the grid that it can get to before the opponent and returns that number
// dying should return 0
uint16_t Possession_Driver::calculatePossession(Grid_t *grid, Turn_t turn) {
    int mx; int my; // my x and y position
    int ox; int oy; // other bikes x and y position

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

    if(grid->getTile(mx, my) == 1){ // if would die, return 0
        return 0;
    }

    // TODO: calculate how many squares I can get to before opponent
    // return that number



    return(5);
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
            if (comparer[j] > comparer[j + 1]) {
                swap(&comparer[j], &comparer[j + 1]);
                swap(&latched[j], &latched[j + 1]);
            }
        }
    }
}
