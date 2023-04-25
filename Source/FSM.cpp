#include "RobotContr.h"
#include "Robot.h"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

RobotContr::RobotContr(Camera* cam, Robot* bot) {
  this->status = 0;
  this->robot = bot;
  this->cam = cam;
}

void RobotContr::start() {
  for (...) {
    this->cam->updateFrame();
    driving();
  }
}

void RobotContr::driving() {
  switch (this->status) {
      
  case 0:
    cout << "Idle";
    this->status = 1;
      
  case 1:
    cout << "Getting drink";
    this->status = 2;
      
  case 2:
    cout << "Robot is moving";
    this->status = 3;
      
  case 3:
    cout << "Robot rotating";
    this->status = 0;    
  }
}
