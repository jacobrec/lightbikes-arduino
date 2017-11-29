// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
MainMenuScreen::MainMenuScreen() { // this is the constructor
    tft.fillScreen(ILI9341_BLACK);
}

void MainMenuScreen::frame() { // this runs every frame
    tft.setTextSize(3);
    tft.setCursor(63, 3);
    tft.println("Lightbikes");
    tft.setCursor( 45, 150);
    tft.setTextSize(1);
    tft.println("Press anywhere on the screen to start");
    TSPoint p = touch_screen.getPoint();

    if (p.z > 100) //pressure detect
    {
        Serial.println("started");
        this->changeScreen(new DriverSelectScreen); //if press, move to driver select
    }
}

MainMenuScreen::~MainMenuScreen() { // this is the destructor. any pointer variables you must delete here
}
