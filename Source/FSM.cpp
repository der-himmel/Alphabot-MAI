#include "Robot_contr.h"
#include "robot.h"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Robot_control::Robot_control(Camera* cam, Robot* bot) {
  this->status = 0;
  this->robot = bot;
  this->cam = cam;
}

void Robot_control::start() {
  for (;;) {
    this->cam->updateImage();
    piloting();
    if (waitKey(33) == 27) break;
  }
}

void Robot_control::piloting() {
  switch (this->status) {
      
  case 0:
    cout << "Waiting...";
    this->status = 1;
      
  case 1:
    cout << "Getting drink...";
    this->status = 2;
      
  case 2:
    cout << "Robot is moving...";
    this->status = 3;
      
  case 3:
    cout << "Robot rotating...";
    this->status = 4;
      
  case 4:
    cout << "Order finished";
    this->status = 0;
      
  }
}
