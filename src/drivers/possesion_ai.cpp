uint16_t Possession_Driver::calculatePossession(Grid_t *grid, Turn_t test) {

    
    return(test);
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
