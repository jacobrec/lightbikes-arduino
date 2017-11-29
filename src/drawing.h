#ifndef _DRAWING_H_
#define _DRAWING_H_

#include "objects.h"

void setUpGraphics();
void drawGrid(Grid_t *grid);
void render(Grid_t *grid);
void drawRect(int x, int y, uint16_t colour);
void generateMenuScreen(char* textCap);
void drawName(int index, const char* driver, int highlighted, int driverID);

#endif
