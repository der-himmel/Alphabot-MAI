#include <iostream>
#include <string>
#include <Windows.h>
#include "Cam.h"
#include "Control.h"
#include "Robot.h"

#define mqtt_host "192.168.1.68"
#define mqtt_port 1883

using namespace std;
using namespace cv;


int main()
{
    //Robot* bot = new Robot(mqtt_host, mqtt_port);
    Robot* bot = new Robot();
    Cam* cam = new Cam(0);

    cout << "Robot and Camera instances successfully created" << endl;
    Sleep(1000);

    Control* control = new Control(cam, bot);

    control->operating();
}
