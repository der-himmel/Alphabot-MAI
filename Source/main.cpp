#include <iostream>
#include <string>
#include "Cam.h"
#include "Control.h"
#include "Robot.h"

#define mqtt_host "192.168.1.4"
#define mqtt_port 1883

using namespace std;
using namespace cv;


int main()
{
    Robot* bot = new Robot(mqtt_host, mqtt_port);
    Cam* cam = new Cam(0);

    Control* control = new Control(cam, bot);

    control->operating();
}
