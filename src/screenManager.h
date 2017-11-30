#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <TouchScreen.h>

#include "driver.h"
#include "drawing.h"
#include "objects.h"
#include "game.h"
#include "util.h"


class Screen;
class ScreenManager;

class Screen {
private:
    ScreenManager *sm;
public:
    void setManager(ScreenManager *sm);
    virtual void frame();
    void changeScreen(Screen *screen);

    virtual ~Screen() {
    };
};


class ScreenManager {
private:
    long    frameCount;
    int     millisPerFrame;
    Screen *currentScreen;
    void ensureFrameRate();

public:
    ScreenManager(int millisPerFrame);
    ~ScreenManager();
    void manageScreen();
    void setScreen(Screen *screen);
};

int joyControl(int driverID);

int wrapAround(int var, int count);

#include "screens/game_screen.h"
#include "screens/main_menu_screen.h"
#include "screens/driverChooseMenu.h"
#include "screens/colorChooseMenu.h"

#endif
