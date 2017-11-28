#include "screenManager.h"

extern Adafruit_ILI9341 tft;

void Screen::setManager(ScreenManager *sm) {
    this->sm = sm;
}

void Screen::changeScreen(Screen *screen) {
    this->sm->setScreen(screen);
}

ScreenManager::ScreenManager(int millisPerFrame) {
    this->frameCount     = 0;
    this->millisPerFrame = millisPerFrame;
    this->currentScreen  = NULL;
}

void ScreenManager::manageScreen() {
    this->currentScreen->frame();
    ensureFrameRate(); // delay for constant frame rate
}

/*
 * This function ensures a constant Frame Rate to the best of it's ability
 * if the updating and rendering of the game take less time then the defined
 * milliseconds per frame, then it delays by the amount of time to needed so
 * the time for the frame to be constant.
 */
void ScreenManager::ensureFrameRate() {
    long diff = this->frameCount * this->millisPerFrame - millis();

    if (diff > 0) {
        delay(diff);
    }
    this->frameCount++;
}

void ScreenManager::setScreen(Screen *screen) {
    screen->setManager(this);

    delete this->currentScreen;

    this->currentScreen = screen;
    this->frameCount    = millis() / millisPerFrame; // initialize the framecount variable, this is used to get a constant framerate
}

ScreenManager::~ScreenManager() {
    delete this->currentScreen;
}

#include "screens/game_screen.cpp"
#include "screens/main_menu_screen.cpp"
