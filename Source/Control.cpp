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
};

void Control::operating() 
{
	while(1)
	{
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
			if (GetKeyState(VK_RSHIFT) & 0x08000)
			{
				this->flag = 0;
				std::cout << "Order received!" << std::endl;
				Sleep(1000);
				this->status = 1;
			}
			else
			{
				bot->waitingMode();
				cam->update();
				std::cout << "Waiting..." << std::endl;
				Sleep(100);
			}
		}
	}
	case 1:
		cam->update();
		
		if (cam->dist >= 150 & abs(cam->angle) < 10)
		{
			std::cout << cam->dist << ' ';
			bot->moveForward();
			std::cout << "Forward..." << std::endl;
			break;
		}
		else if (cam->dist < 150)
		{
			std::cout << "Order delivered!" << std::endl;
			Sleep(1000);
			this->flag = 1;
			status = 0;
			break;
		}
		else 
		{
			status = 2;
			break;
		}
	case 2:
		cam->update();

		if (cam->angle > 0)
		{
			std::cout << "angle = " << cam->angle << ' ';
			status = 4;
			break;
		}
		else if (cam->angle < 0 & cam->angle >= -30)
		{
			std::cout << "angle = " << cam->angle << ' ';
			status = 3;
			break;
		}

	case 3:
		bot->rotateLeft();
		std::cout << "Left..." << std::endl;
		status = 1;
		break;

	case 4:
		bot->rotateRight();
		std::cout << "Right..." << std::endl;
		status = 1;
		break;
	}
}
