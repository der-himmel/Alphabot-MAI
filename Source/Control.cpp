#include "opencv2/opencv.hpp"
#include <iostream>
#include <Windows.h>
#include "Control.h"
#include "Robot.h"
#include "Cam.h"

Control::Control(Cam* cam, Robot* bot)
{
	this->flag = 1;
	this->status = 0;
	this->cam = cam;
	this->bot = bot;
}

void Control::operating() 
{
	while(1)
	{
		cam->update();
		moving();
	}
}

void Control::moving()
{
	switch (status)
	{
	case 0:
	{
		while (this->flag)
		{
			if (GetKeyState(VK_RSHIFT) & 0x8000)
			{
				std::cout << "Order received!";
				Sleep(1000);
				system("cls");
				flag = 0;
			}
			else
			{
				bot->waitingMode();
			}
		}
	}
	case 1:
		if (this->cam->angle > 10)
		{
			status = 3;
		}
		else
		{
			status = 2;
		}

		if (cam->dist >= 400)
		{
			bot->moveForward();
		}
		else
		{
			status = 0;
			std::cout << "Order delivered.";
		}

	case 2:
		bot->rotateLeft();
		break;

	case 3:
		bot->rotateRight();
		break;
	}
}
