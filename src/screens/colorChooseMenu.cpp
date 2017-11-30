#define Y1                     120
#define Y2                     100
#define Y3                     140
#define X_LEFT                 55
#define X_RIGHT                225
#define SQUARE_SIZE            41

#define COLOUR_COUNT           7

const char *COLOUR_MENU_MESSAGE = "Choose your colour";


uint16_t ColorSelectScreen::fetchColor(int color) {
    //Serial.print("Fetching color");
    switch (color) {
        case 0: return(ILI9341_RED);

        case 1: return(ILI9341_BLUE);

        case 2: return(ILI9341_GREEN);

        case 3: return(ILI9341_CYAN);

        case 4: return(ILI9341_MAGENTA);

        case 5: return(ILI9341_YELLOW);

        case 6: return(ILI9341_WHITE);
    }
    return(0);
}

ColorSelectScreen::ColorSelectScreen(Driver_t *d1, Driver_t *d2) { // this is the constructor
    tft.setTextSize(2);
    tft.setCursor(60, 5);
    tft.fillScreen(ILI9341_BLACK);
    generateMenuScreen(COLOUR_MENU_MESSAGE, "Start");
    this->currentColor1 = 0;
    this->currentColor2 = 1;
    this->d1            = d1;
    this->d2            = d2;
    tft.fillTriangle(X_LEFT - 35, Y1, X_LEFT - 15, Y2, X_LEFT - 15, Y3, ILI9341_WHITE);
    tft.fillTriangle(X_LEFT + 75, Y1, X_LEFT + 55, Y2, X_LEFT + 55, Y3, ILI9341_WHITE);
    tft.fillTriangle(X_RIGHT - 35, Y1, X_RIGHT - 15, Y2, X_RIGHT - 15, Y3, ILI9341_WHITE);
    tft.fillTriangle(X_RIGHT + 75, Y1, X_RIGHT + 55, Y2, X_RIGHT + 55, Y3, ILI9341_WHITE);
    tft.fillRect(X_LEFT, Y2, SQUARE_SIZE, SQUARE_SIZE, ColorSelectScreen::fetchColor(currentColor1));
    tft.fillRect(X_RIGHT, Y2, SQUARE_SIZE, SQUARE_SIZE, ColorSelectScreen::fetchColor(currentColor2));
}

void ColorSelectScreen::frame() { // this runs every frame
    int oldColor1 = currentColor1;
    int oldColor2 = currentColor2;

    TSPoint p = touch_screen.getPoint();

    if (p.z > 50) { //pressure detect
        //SerialPrintf("p.x: %d, p.y %d, p.z: %d\r\n",p.x,p.y,p.z);
        if (p.x > 360 && p.x < 600) {
            if (p.y > 720 && p.y < 1000) { //for triangle 1
                //Serial.print("- color 1");
                currentColor1 = wrapAround(--currentColor1, COLOUR_COUNT);
            }
            else if (p.y > 490 && p.y < 680) { //triangle 2
                //Serial.print("+ color 1");
                currentColor1 = wrapAround(++currentColor1, COLOUR_COUNT);
            }
            else if (p.y > 280 && p.y < 470) { //triangle 3
                //Serial.print("- color 2");
                currentColor2 = wrapAround(--currentColor2, COLOUR_COUNT);
            }
            else if (p.y > 0 && p.y < 260) { //triangle 4
                //Serial.print("+ color 2");
                currentColor2 = wrapAround(++currentColor2, COLOUR_COUNT);
            }
        }
        else if (p.x > 740) {
            if (p.y < 470) { //back
                //this->changeScreen(new DriverSelectScreen);
                this->changeScreen(new GameScreen(d1, d2, ColorSelectScreen::fetchColor(currentColor1), ColorSelectScreen::fetchColor(currentColor2)));
            }
            else if (p.y > 450) { //start
                this->changeScreen(new DriverSelectScreen);
                //this->changeScreen(new GameScreen(d1, d2, ColorSelectScreen::fetchColor(currentColor1), ColorSelectScreen::fetchColor(currentColor2)));
            }
        }
        // Serial.println(currentColor1);
        // Serial.println(currentColor2);
    }
    if (oldColor1 != currentColor1 || oldColor2 != currentColor2) {
        //Serial.print("Printing rect");
        tft.fillRect(X_LEFT, Y2, SQUARE_SIZE, SQUARE_SIZE, ColorSelectScreen::fetchColor(currentColor1));
        tft.fillRect(X_RIGHT, Y2, SQUARE_SIZE, SQUARE_SIZE, ColorSelectScreen::fetchColor(currentColor2));
    }
}

ColorSelectScreen::~ColorSelectScreen() { // this is the destructor. any pointer variables you must delete here
}
