#include <iostream>
#include <opencv2>

class Server{
public:
    void getImage(); //gets and processes image from camera
    void handleOrder(); //receives order
    void routeBuild(); //builds route according to camera output
    void robotControl(); //makes the robot move
};

class Camera{
public:
    void cHandleCommunication(); //handles communication with the server
};

class Dispencer{
public:
    const float x, y; //constant coordinates of the dispencer
    void dHandleCommunication(); //handles communication with the server
};

class Robot{
public:
    float x, y; //coordinates
    void rHandleCommunication(); //handles communication with the server
};

class Customer{
public:
    float x, y; //coordinates
    void requestOrder(); //makes an order request to the server
    void receiveOrder(); //receives order from robot
};

int main() {
    std::cout << "Not working yet..." << std::endl;
    return 0;
}
