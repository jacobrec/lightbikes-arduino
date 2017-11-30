uint16_t ColorSelectScreen::fetchColor(int color)
{
	Serial.print("Fetching color");
	switch (color)
	{
		case 0: return(ILI9341_RED);
		case 1: return(ILI9341_BLUE);
		case 2: return(ILI9341_GREEN);
		case 3: return(ILI9341_CYAN);
		case 4: return(ILI9341_MAGENTA);
		case 5: return(ILI9341_YELLOW);
		case 6: return(ILI9341_WHITE);
	}
}

ColorSelectScreen::ColorSelectScreen(Driver_t* d1, Driver_t* d2) { // this is the constructor
	tft.setTextSize(2);
	tft.setCursor(60, 5);
	tft.fillScreen(ILI9341_BLACK);
	generateMenuScreen("Choose your color");
	this->currentColor1 = 0;
	this->currentColor2 = 1;
	this->d1 = d1;
	this->d2 = d2;
	tft.fillTriangle(20, 120, 40, 100, 40, 140, ILI9341_WHITE);
	tft.fillTriangle(130, 120, 110, 100, 110, 140, ILI9341_WHITE);
	tft.fillTriangle(190, 120, 210, 100, 210, 140, ILI9341_WHITE);
	tft.fillTriangle(300, 120, 280, 100, 280, 140, ILI9341_WHITE);
	tft.fillRect(55, 102, 41, 41, ColorSelectScreen::fetchColor(currentColor1));
	tft.fillRect(225, 102, 41, 41, ColorSelectScreen::fetchColor(currentColor2));
}

void ColorSelectScreen::frame() { // this runs every frame
	int oldColor1 = currentColor1;
	int oldColor2 = currentColor2;

    TSPoint p = touch_screen.getPoint();

    if (p.z > 50) //pressure detect
    {
		SerialPrintf("p.x: %d, p.y %d, p.z: %d\r\n",p.x,p.y,p.z);
		if(p.x > 360 && p.x < 600)
		{
			if (p.y > 720 && p.y < 1000) //for triangle 1
			{
				//Serial.print("- color 1");
				currentColor1 = wrapAround(--currentColor1, 0, 6);
			}
			else if (p.y > 490 && p.y < 680) //triangle 2
			{
				//Serial.print("+ color 1");
				currentColor1 = wrapAround(++currentColor1, 0, 6);
			}
			else if (p.y > 280 && p.y < 470) //triangle 3
			{
				//Serial.print("- color 2");
				currentColor2 = wrapAround(--currentColor2, 0, 6);
			}
			else if (p.y > 0 && p.y < 260) //triangle 4
			{
				//Serial.print("+ color 2");
				currentColor2 = wrapAround(++currentColor2, 0, 6);
			}
		}
		else if (p.x > 740)
		{
			if ( p.y < 470) //back
			{
				//this->changeScreen(new DriverSelectScreen);
				this->changeScreen(new GameScreen(d1, d2, ColorSelectScreen::fetchColor(currentColor1), ColorSelectScreen::fetchColor(currentColor2)));
			}
			else if (p.y > 450) //start
			{
				this->changeScreen(new DriverSelectScreen);
				//this->changeScreen(new GameScreen(d1, d2, ColorSelectScreen::fetchColor(currentColor1), ColorSelectScreen::fetchColor(currentColor2)));
			}
		}
		Serial.println(currentColor1);
		Serial.println(currentColor2);
    }
	if (oldColor1 != currentColor1 || oldColor2 != currentColor2)
	{
		Serial.print("Printing rect");
		tft.fillRect(55, 102, 41, 41, ColorSelectScreen::fetchColor(currentColor1));
		tft.fillRect(225, 102, 41, 41, ColorSelectScreen::fetchColor(currentColor2));
	}
}

ColorSelectScreen::~ColorSelectScreen() { // this is the destructor. any pointer variables you must delete here
}
