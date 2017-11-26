// IMPORTANT: this file is only to be included into drivers.h and nowhere else
class UserL_Driver : public Driver_t {
public:
    Turn_t steer(Grid_t *grid);
};
