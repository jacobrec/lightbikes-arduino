// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
MainMenuScreen::MainMenuScreen() { // this is the constructor
}

void MainMenuScreen::frame() { // this runs every frame
    tft.fillScreen(ILI9341_GREEN);
    this->changeScreen(new GameScreen(createUserL_Driver(), new Runner_ai()));
}

MainMenuScreen::~MainMenuScreen() { // this is the destructor. any pointer variables you must delete here
}
