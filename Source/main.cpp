#include <iostream>
#include <opencv2>
#include "Robot.h"
#include "RobotContr.h"
#include "Cam.h"

class Server{
public:
    void getImage(); //gets and processes image from camera
    void handleOrder(); //receives order
    void routeBuild(); //builds route according to camera output
    void robotControl(); //makes the robot move
};

class Dispencer{
private:
    float x, y; //constant coordinates of the dispencer
public:
    void dHandleCommunication(); //handles communication with the server
};

class Customer{
private:
    float x, y; //coordinates
public:
    void requestOrder(); //makes an order request to the server
    void receiveOrder(); //receives order from robot
};

int main() {
    Cam *cam = new Cam(0);
    Robot *robot = new Robot();
    RobotContr *rcontr = new RobotContr(cam, robot);
    std::cout << "Not working yet..." << std::endl;
    return 0;
}
