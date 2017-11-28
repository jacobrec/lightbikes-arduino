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



void setUpGraphics() {
    // set up for tft
    tft.begin();
    tft.setRotation(3);
    tft.setTextSize(5);
}

void drawGrid(Grid_t *grid) {
    tft.fillScreen(ILI9341_BLACK);
    // these loops draws the inital board state
    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (grid->getTile(x, y) == 1) {
                drawRect(x, y, ILI9341_GREEN); // draw border
            }
        }
    }
}

void ifGameOverDraw(Grid_t *grid) {
    tft.setCursor(70, 60); // these numbers were carefully selected through trial and error

    if (!grid->bike2->getAlive() && !grid->bike1->getAlive()) {
        tft.println("Draw :("); // sad face is so all three messages have the same number of charectors
    }
    else if (!grid->bike2->getAlive()) {
        tft.println("P1 Wins");
    }
    else if (!grid->bike1->getAlive()) {
        tft.println("P2 Wins");
    }
    else{
        return;
    }
    tft.setCursor(20, 10); // these numbers were carefully selected through trial and error
    tft.println("Game over!");
}

void render(Grid_t *grid) {
    drawRect(grid->bike1->getX(), grid->bike1->getY(), ILI9341_BLUE);
    drawRect(grid->bike2->getX(), grid->bike2->getY(), ILI9341_RED);

    ifGameOverDraw(grid);
}

// A convinence method
void drawRect(int x, int y, uint16_t colour) {
    tft.fillRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, colour);
}
