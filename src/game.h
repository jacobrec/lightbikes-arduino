#ifndef _GAME_H_
#define _GAME_H_


#include "objects.h"

void update(Grid_t *grid);
void addWall(Bike_t *bike, Grid_t *grid);
void checkCollision(Bike_t *bike, Grid_t *grid);

Grid_t *initWorld(int width, int height);

#endif
