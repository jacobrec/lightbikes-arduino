// IMPORTANT: this file is only to be included into screenManager.h and nowhere else
class MainMenuScreen : public Screen {
private:
    int lastOn;
public:
    MainMenuScreen();
    ~MainMenuScreen();

    void frame();
};
