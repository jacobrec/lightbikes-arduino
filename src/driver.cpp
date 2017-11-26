#include <Arduino.h>
#include "driver.h"
#include "objects.h"

// This file is only to be used to include the drivers from the drivers folder
#include "drivers/staying_alive_ai.cpp"
#include "drivers/leftside_user.cpp"

// this is done too keep the project organized, we wanted to keep all the drivers in one sub folder, but
// we could not figure out how to change the arduino makefile to accommodate a hierarchical format like that
