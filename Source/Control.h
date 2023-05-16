#pragma once
#include "Robot.h"
#include "Cam.h"

class Control
{
private:
	int status;
	bool flag = 1;

	Robot *bot;
	Cam *cam;
public:
	Control(Cam* cam, Robot* bot);
	void operating();
	void moving();
};
