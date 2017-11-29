#ifndef _GAME_H_
#define _GAME_H_


#include "objects.h"

void update(Grid_t *grid);
void addWall(Bike_t *bike, Grid_t *grid);
void checkCollision(Bike_t *bike, Grid_t *grid);

Grid_t *initWorld(int width, int height, Driver_t *d1, Driver_t *d2, uint16_t colour1, uint16_t colour2);

#endif
