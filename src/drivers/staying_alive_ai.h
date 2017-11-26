// IMPORTANT: this file is only to be included into drivers.h and nowhere else
class StayingAlive_Driver : public Driver_t {
public:
    Turn_t getNearSafeDirection(Grid_t *grid, Direction_t dir);
    Turn_t steer(Grid_t *grid);
};
