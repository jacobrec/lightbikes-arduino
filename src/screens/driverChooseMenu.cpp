// IMPORTANT: this file is only to be included into screenManager.cpp and nowhere else
#define LEFT_JOY_VERT      A1 /* should connect A1 to pin VRx of left joystick*/
#define LEFT_JOY_HORIZ     A0 /* should connect A0 to pin VRy of right joystick*/

#define RIGHT_JOY_VERT     A5 /* should connect A1 to pin VRx of left joystick*/
#define RIGHT_JOY_HORIZ    A4 /* should connect A0 to pin VRy of right joystick*/

Driver_t DriverSelectScreen::getNewDriver(int mode)
{
	int highlight;
	if(mode == 1){
		highlight = this->highlightDriver1;
	}else if (mode == 2){
		highlight = this->highlightDriver2;
	}
	switch (highlight)
	{
		case 0:
			if (mode == 1)
			{
				return(Joystick_Driver(LEFT_JOY_HORIZ, LEFT_JOY_VERT));
			}
			else
			{
				return(Joystick_Driver(RIGHT_JOY_HORIZ, RIGHT_JOY_VERT));
			}
		case 1:
			return(Stalker_Driver());
		case 2:
			return(Runner_ai());
		case 3:
			return(StayingAlive_Driver());
		case 4:
			return(Possession_Driver());
	}
}

DriverSelectScreen::DriverSelectScreen() { // this is the constructor
	generateMenuScreen("Choose your driver");
	this->highlightDriver1 = 0;
	this->highlightDriver2 = 0;
}

void DriverSelectScreen::frame() { // this runs every frame
	for (int i = 0; i < 5; i++)
	{
		drawName(i, driverNames[i], highlightDriver1, 1); //drivers is str of driver types
		drawName(i, driverNames[i], highlightDriver2, 2);
	}

	highlightDriver1 += joyControl(1); //check for new inputs
	highlightDriver2 += joyControl(2);

	highlightDriver1 = constrain(highlightDriver1, 0, 4);//keep values of highlight between 0 and 4;
	highlightDriver2 = constrain(highlightDriver2, 0 ,4);

	// TSPoint p = ts.getPoint();
	// 
    // if (p.z > 500) //pressure detect
    // {
    //     if (p.x > 170 && p.y > 220) //hitbox for start
	// 	{
	// 		Driver_t d1 = this->getNewDriver(1);
	// 		Driver_t d2 = this->getNewDriver(2);
	// 		this->changeScreen(new GameScreen(&d1, &d2));
	// 		//this->changeScreen(new ColorSelectScreen();)
	// 	}
	// 	else if (p.x < 155 && p.y > 220) //hitbox for back
	// 	{
	// 		this->changeScreen(new MainMenuScreen());
	// 	}
    // }
}

DriverSelectScreen::~DriverSelectScreen() { // this is the destructor. any pointer variables you must delete here
	//delete this->highlightDriver1;
	//delete this->highlightDriver2;
}
