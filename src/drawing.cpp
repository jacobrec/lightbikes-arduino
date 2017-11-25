#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "drawing.h"

#define TFT_DC            9
#define TFT_CS            10

#define DISPLAY_WIDTH     320
#define DISPLAY_HEIGHT    240
#define TILE_SIZE         5

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

bool isSetup = false; // one time flag to see if setup should run



void setup(Grid_t *grid) {
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);

    isSetup = true;
    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (grid->getTile(x, y) == 0b01) {
                drawRect(x, y, ILI9341_GREEN);
            }
        }
    }
}

void ifGameOverDraw(Grid_t *grid) {
}

void render(Grid_t *grid) {
    if (!isSetup) {
        setup(grid);
    }


    drawRect(grid->bike1->x, grid->bike1->y, ILI9341_BLUE);
    drawRect(grid->bike2->x, grid->bike2->y, ILI9341_RED);

    ifGameOverDraw(grid);
}

// A convinence method
void drawRect(int x, int y, uint16_t colour) {
    tft.fillRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, colour);
}
