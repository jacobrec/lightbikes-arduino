// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
#define ROSTER_COUNT           5
const char *DRIVER_MENU_MESSAGE = "Choose your driver";

const char *driverNames[ROSTER_COUNT] = {
    " Player ",
    " Hunter ",
    " Coward ",
    "Survivor",
    " Keeper "
};

Driver_t *DriverSelectScreen::getNewDriver(int mode) {
    int highlight = 0;

    if (mode == 1) {
        highlight = this->highlightDriver1;
    }
    else if (mode == 2) {
        highlight = this->highlightDriver2;
    }
    switch (highlight) {
        case 0:
            if (mode == 1) {
                return(createUserL_Driver());
            }
            else{
                return(createUserR_Driver());
            }

        case 1:
            return(new Stalker_Driver());

        case 2:
            return(new Runner_ai());

        case 3:
            return(new StayingAlive_Driver());

        case 4:
            return(new Possession_Driver());
    }
    return(NULL);
}

DriverSelectScreen::DriverSelectScreen() { // this is the constructor
    this->highlightDriver1 = 0;
    this->highlightDriver2 = 0;
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);

    tft.setCursor(50, 5);
    generateMenuScreen(DRIVER_MENU_MESSAGE, "Next");


    for (int i = 0; i < ROSTER_COUNT; i++) {
        drawName(i, driverNames[i], highlightDriver1, 1); //drivers is str of driver types
        drawName(i, driverNames[i], highlightDriver2, 2);
    }
}

void DriverSelectScreen::frame() {                        // this runs every frame
    int oH1 = highlightDriver1;
    int oH2 = highlightDriver2;


    highlightDriver1 = wrapAround(highlightDriver1 + joyControl(1), ROSTER_COUNT); //keep values of highlight between 0 and 4;
    highlightDriver2 = wrapAround(highlightDriver2 + joyControl(2), ROSTER_COUNT);

    if (oH1 != highlightDriver1) {
        for (int i = 0; i < ROSTER_COUNT; i++) {
            drawName(i, driverNames[i], highlightDriver1, 1); //drivers is str of driver types
        }
    }
    if (oH2 != highlightDriver2) {
        for (int i = 0; i < ROSTER_COUNT; i++) {
            drawName(i, driverNames[i], highlightDriver2, 2);
        }
    }

    TSPoint p = touch_screen.getPoint();


    if (p.z > 50) {                   //pressure detect
        if (p.x > 500 && p.y < 500) { //hitbox for start
            Driver_t *d1 = this->getNewDriver(1);
            Driver_t *d2 = this->getNewDriver(2);
            this->changeScreen(new ColorSelectScreen(d1, d2));
            //this->changeScreen(new ColorSelectScreen();
        }
        else if (p.x > 500 && p.y > 500) { //hitbox for back
            this->changeScreen(new MainMenuScreen());
        }
    }
}

DriverSelectScreen::~DriverSelectScreen() { // this is the destructor. any pointer variables you must delete here
    //delete this->highlightDriver1;
    //delete this->highlightDriver2;
}
