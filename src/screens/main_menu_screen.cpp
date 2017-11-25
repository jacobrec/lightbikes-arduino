// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
MainMenuScreen::MainMenuScreen() { // this is the constructor
}

void MainMenuScreen::frame() { // this runs every frame
    this->changeScreen(new GameScreen(new StayingAlive_Driver(), new StayingAlive_Driver()));
}

MainMenuScreen::~MainMenuScreen() { // this is the destructor. any pointer variables you must delete here
}
