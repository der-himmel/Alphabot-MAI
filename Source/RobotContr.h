#pragma once

#include "Robot.h"
#include "Camera.h"


class Robot_contr {
private:
  Robot *robot;
  Camera *cam;
  Position *pos;
  int status;
public:
  Robot_control(Camera* cam, Robot* bot);
  void start();
  void driving();
};
