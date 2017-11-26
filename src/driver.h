#ifndef _DRIVER_H_
#define _DRIVER_H_
#include "objects.h"

// useful functions that all drivers might want to use
Turn_t getTurn(Direction_t to, Direction_t from);

// This file is only to be used to include headers from the driver folder
#include "drivers/staying_alive_ai.h"
#include "drivers/leftside_user.h"


#endif
