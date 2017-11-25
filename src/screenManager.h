#include <Arduino.h>

#include "driver.h"
#include "drawing.h"
#include "objects.h"
#include "game.h"


class Screen;
class ScreenManager;

class Screen {
private:
    ScreenManager *sm;
public:
    void setManager(ScreenManager *sm);
    virtual void frame();
    void changeScreen(Screen *screen);
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

#include "screens/game_screen.h"
#include "screens/main_menu_screen.h"
