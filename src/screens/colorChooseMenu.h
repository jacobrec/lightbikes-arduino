class ColorSelectScreen : public Screen {
private:
	int currentColor1;
	int currentColor2;
	uint16_t fetchColor(int color);
	Driver_t* d1;
	Driver_t* d2;
public:
    ColorSelectScreen(Driver_t* d1, Driver_t* d2);
    ~ColorSelectScreen();

    void frame();
};
