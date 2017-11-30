// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
MainMenuScreen::MainMenuScreen() { // this is the constructor
    tft.fillScreen(ILI9341_BLACK);
    this->lastOn = 0;
}

void MainMenuScreen::frame() { // this runs every frame
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.setCursor(63, 3);
    tft.println("Lightbikes");
    tft.setCursor(45, 150);
    tft.setTextSize(1);
    tft.setTextColor(ILI9341_WHITE);
    if (this->lastOn % 7 == 0) {
        tft.setTextColor(ILI9341_BLACK);
        tft.println("Press anywhere on the screen to start");
    }
    else{
        tft.setTextColor(ILI9341_WHITE);
        tft.println("Press anywhere on the screen to start");
    }
    this->lastOn++;


    TSPoint p = touch_screen.getPoint();

    if (p.z > 100) { //pressure detect
        Serial.println("started");
        this->changeScreen(new DriverSelectScreen); //if press, move to driver select
    }
}

MainMenuScreen::~MainMenuScreen() { // this is the destructor. any pointer variables you must delete here
}
