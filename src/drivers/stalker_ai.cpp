int Stalker_Driver::distanceAfterTurn(Turn_t turn, Grid_t *grid) {
    Direction_t toGo = (Direction_t)((turn + this->myBike->getDirection() + 4) % 4);
    int         x    = this->myBike->getX();
    int         y    = this->myBike->getY();

    switch (toGo) {
        case NORTH:
            y++;
            break;

        case WEST:
            x--;
            break;

        case SOUTH:
            y--;
            break;

        case EAST:
            x++;
            break;
    }
    int ox = this->myBike != grid->bike1 ? grid->bike1->getX() : grid->bike2->getX();
    int oy = this->myBike != grid->bike1 ? grid->bike1->getY() : grid->bike2->getY();

    return(abs(ox - x) + abs(oy - y));
}

void Stalker_Driver::swap(int *a, int *b) {
    int temp = *a;

    *a = *b;
    *b = temp;
}

void Stalker_Driver::parallelSort(int *comparer, int *latched, int size) {
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

bool Stalker_Driver::isTurnSafe(Turn_t turn, Grid_t *grid) {
    Direction_t toGo = (Direction_t)((turn + this->myBike->getDirection() + 4) % 4);
    int         x    = this->myBike->getX();
    int         y    = this->myBike->getY();

    switch (toGo) {
        case NORTH:
            y++;
            break;

        case WEST:
            x--;
            break;

        case SOUTH:
            y--;
            break;

        case EAST:
            x++;
            break;
    }
    return(grid->getTile(x, y) == 0b00);
}

Turn_t Stalker_Driver::steer(Grid_t *grid) {
    int lDist = this->distanceAfterTurn(LEFT, grid);
    int rDist = this->distanceAfterTurn(RIGHT, grid);
    int sDist = this->distanceAfterTurn(STRAIGHT, grid);

    int turnOrder[3] = { STRAIGHT, LEFT, RIGHT };
    int distOrder[3] = { sDist, lDist, rDist };

    parallelSort(distOrder, turnOrder, 3);

    for (int i = 0; i < 3; i++) {
        if (isTurnSafe((Turn_t)turnOrder[i], grid)) {
            return((Turn_t)turnOrder[i]);
        }
    }

    return(STRAIGHT);
}
