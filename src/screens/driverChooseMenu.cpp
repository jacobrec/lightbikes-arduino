// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
#define LEFT_JOY_VERT      A1 /* should connect A1 to pin VRx of left joystick*/
#define LEFT_JOY_HORIZ     A0 /* should connect A0 to pin VRy of right joystick*/

#define RIGHT_JOY_VERT     A5 /* should connect A1 to pin VRx of left joystick*/
#define RIGHT_JOY_HORIZ    A4 /* should connect A0 to pin VRy of right joystick*/


const char *driverNames[5] = {
    "Player",
    "Hunter",
    "Coward",
    "Survivor",
    "Smarter"
};

Driver_t *DriverSelectScreen::getNewDriver(int mode) {
    int highlight;

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
}

DriverSelectScreen::DriverSelectScreen() { // this is the constructor
    this->highlightDriver1 = 0;
    this->highlightDriver2 = 0;
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(2);
    generateMenuScreen("Choose your driver");

    for (int i = 0; i < 5; i++) {
        drawName(i, driverNames[i], highlightDriver1, 1); //drivers is str of driver types
        drawName(i, driverNames[i], highlightDriver2, 2);
    }
}

void DriverSelectScreen::frame() {                        // this runs every frame
    int oH1 = highlightDriver1;
    int oH2 = highlightDriver2;

    highlightDriver1 = constrain(highlightDriver1 + joyControl(1), 0, 4); //keep values of highlight between 0 and 4;
    highlightDriver2 = constrain(highlightDriver2 + joyControl(2), 0, 4);

    if (oH1 != highlightDriver1) {
        for (int i = 0; i < 5; i++) {
            drawName(i, driverNames[i], highlightDriver1, 1); //drivers is str of driver types
        }
    }
    if (oH2 != highlightDriver2) {
        for (int i = 0; i < 5; i++) {
            drawName(i, driverNames[i], highlightDriver2, 2);
        }
    }

    TSPoint p = touch_screen.getPoint();


    if (p.z > 100) {                  //pressure detect
        if (p.x > 500 && p.y < 500) { //hitbox for start
            Driver_t *d1 = this->getNewDriver(1);
            Driver_t *d2 = this->getNewDriver(2);
            this->changeScreen(new GameScreen(d1, d2, ILI9341_RED, ILI9341_BLUE));
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
