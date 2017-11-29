// IMPORTANT: this file is only to be included into screenManager.h and nowhere else
class GameScreen : public Screen {
private:
    Grid_t *grid;
public:
    GameScreen(Driver_t *d1, Driver_t *d2, uint16_t colour1, uint16_t colour2);
    ~GameScreen();

    void frame();
};
