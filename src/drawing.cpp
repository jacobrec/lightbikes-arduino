#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "drawing.h"

#define TFT_DC            9
#define TFT_CS            10

#define DISPLAY_WIDTH     320
#define DISPLAY_HEIGHT    240
#define TILE_SIZE         10

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
    tft.setTextColor(ILI9341_WHITE);
    if (!grid->bike2->getAlive() && !grid->bike1->getAlive()) {
        tft.println(F(" Draw ")); // sad face is so all three messages have the same number of charectors
    }
    else if (!grid->bike2->getAlive()) {
        tft.println(F("P1 Wins")); // F() to save on ram
    }
    else if (!grid->bike1->getAlive()) {
        tft.println(F("P2 Wins")); // F() to save on ram
    }
    else{
        return;
    }
    tft.setCursor(17, 10); // these numbers were carefully selected through trial and error
    tft.println(F("Game over!"));
}

void render(Grid_t *grid) {
    drawRect(grid->bike1->getX(), grid->bike1->getY(), grid->bike1->getColour());
    drawRect(grid->bike2->getX(), grid->bike2->getY(), grid->bike2->getColour());

    ifGameOverDraw(grid);
}

// A convinence method
void drawRect(int x, int y, uint16_t colour) {
    tft.fillRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, colour);
}

void generateMenuScreen(const char* textCap, const char* nextPrompt) {
    //Serial.println("Printing menu template");
    tft.setTextSize(2);
    tft.drawLine(0, 40, 320, 40, ILI9341_WHITE);
    tft.drawLine(0, 200, 320, 200, ILI9341_WHITE);
    tft.drawLine(160, 40, 160, 240, ILI9341_WHITE);
    tft.drawLine(161, 40, 161, 240, ILI9341_WHITE);

    tft.setCursor(getCursorCentered(textCap, 0, 320), 5);
    tft.println(textCap);
    tft.setCursor(getCursorCentered("Back", 0, 160), 215);
    tft.println(F("Back"));
    tft.setCursor(getCursorCentered(nextPrompt, 161, 320), 215);
    tft.println(nextPrompt);
}

void drawName(int index, const char driver[], int highlighted, int driverID) {
    // 15 is the vertical span of a size-2 character
    // (including the one pixel of padding below)
    if (driverID == 1) {
        tft.setCursor(33, 20 * index + 50);
    }
    else{
        tft.setCursor(195, 20 * index + 50);
    }

    //changes the highlighing of restaurants
    if (index == highlighted) {
        tft.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
    }
    else {
        tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    }

    tft.println(driver);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
}


int getCursorCentered(const char* str, int xStart, int xEnd) //finds where cursor should be placed
                                                             //such that the text is centered
{
    int stringlen = getLength(str);
    int boxCenter = (xEnd - xStart)/2;

    return(boxCenter - (stringlen/2)*6*2 +xStart); //returns the center of box offset by half the char
                                                   //length, then adds that to starting point of box
                                                   //*6*2 is for changing txt size, currently set for size 2
}

int getLength(const char* str) //gets str length cuz i couldn't make the included one work
{
    int length = 0;
    while(true) //will loop for each non NULL value and counts amount of char
    {
        if (str[length] == '\0')
        {
            break;
        }
        else
        {
            length++;
        }
    }
    Serial.print(length);
    return(length);
}
