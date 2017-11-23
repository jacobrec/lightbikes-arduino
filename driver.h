#ifndef _DRIVER_H_
#define _DRIVER_H_
#include "objects.h"

class StayingAlive_Driver : public Driver_t{
public:
    Turn_t steer(Grid_t *grid);
};

class UserL_Driver : public Driver_t{
public:
    Turn_t steer(Grid_t *grid);
};


#endif
