// IMPORTANT: this file is only to be included into drivers.h and nowhere else
class Joystick_Driver : public Driver_t {
private:
    uint8_t pinX; uint8_t pinY;
    Direction_t getJoystickDirection(Direction_t current);
    bool isOld;

public:
    Joystick_Driver(uint8_t pinX, uint8_t pinY, bool isOld);
    Turn_t steer(Grid_t *grid);
};


Joystick_Driver *createUserR_Driver();
Joystick_Driver *createUserL_Driver();
