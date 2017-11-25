// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
MainMenuScreen::MainMenuScreen() {// this is the constructor
}
int i = 0;
void MainMenuScreen::frame() { // this runs every frame
    Serial.print("Changing screens: ");
    Serial.println(i++);
    this->changeScreen(new GameScreen(new StayingAlive_Driver(), new StayingAlive_Driver()));
}

MainMenuScreen::~MainMenuScreen() { // this is the destructor. any pointer variables you must delete here
}
