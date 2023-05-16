#pragma once
#include <string>

class Robot 
{
public:
    Robot(std::string mqtt_host, int mqtt_port);

    void moveForward();
    void rotateLeft();
    void rotateRight();
    void waitingMode();

    void sendtoserver(const char* data);
};
