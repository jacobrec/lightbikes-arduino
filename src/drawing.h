#ifndef _DRAWING_H_
#define _DRAWING_H_

#include "objects.h"

void setUpGraphics(Grid_t *grid);
void render(Grid_t *grid);
void drawRect(int x, int y, uint16_t colour);

#endif
