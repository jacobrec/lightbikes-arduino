class DriverSelectScreen : public Screen {
private:
    int highlightDriver1;
    int highlightDriver2;
    Driver_t *getNewDriver(int mode);

public:
    DriverSelectScreen();
    ~DriverSelectScreen();

    void frame();
};
