// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
MainMenuScreen::MainMenuScreen() { // this is the constructor
    tft.fillScreen(0x0100);
    this->lastOn = 0;
}

void MainMenuScreen::frame() { // this runs every frame
    tft.setTextColor(0x0380);
    tft.setTextSize(3);
    tft.setCursor(getCursorCentered("Lightbikes", 0, 320, 3), 10);
    tft.println("Lightbikes");
    tft.setCursor(45, 150);
    tft.setTextSize(1);
    tft.setTextColor(0x0380);
    if (this->lastOn % 7 == 0) {
        tft.setTextColor(0x0100);
        tft.println("Press anywhere on the screen to start");
    }
    else{
        tft.setTextColor(0x0380);
        tft.println("Press anywhere on the screen to start");
    }
    this->lastOn++;


    TSPoint p = touch_screen.getPoint();

    if (p.z > 50) { //pressure detect
        //Serial.println("started");
        this->changeScreen(new DriverSelectScreen); //if press, move to driver select
    }
}

MainMenuScreen::~MainMenuScreen() { // this is the destructor. any pointer variables you must delete here
}
