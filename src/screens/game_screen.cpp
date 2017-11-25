// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
GameScreen::GameScreen(Driver_t *d1, Driver_t *d2) {
    this->grid = initWorld(64, 48, d1, d2);  // create a new grid, the central game world object, of size 64x48
    setUpGraphics(grid);                     // initializes the graphics system, as well as draws boarder
}

void GameScreen::frame() {
    update(this->grid);            // updates game world
    render(this->grid);            // renders the world

    if(!this->grid->isGamePlaying){// if it's game over, wait a bit then return to the menu
        delay(1000 * 5);// 5 seconds
        this->changeScreen(new MainMenuScreen());
    }
}

GameScreen::~GameScreen(){
    delete this->grid;
}
