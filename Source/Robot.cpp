#include <stdlib.h>
#include <mosquitto.h>
#include <string.h>
#include "Robot.h"

#define MQTT_SERVER     "localhost"
#define KEEP_ALIVE      60
#define MQTT_PORT       1883
#define MQTT_PUB_TOPIC  "/qqqqq"
#define MQTT_QOS_LEVEL  2
#define MSG_MAX_SIZE    512

Robot::Robot(std::string mqtt_host, int mqtt_port){
};

void Robot::sendtoserver(const char* data)
{
    bool clean_session = true;
    struct mosquitto* mosq = NULL;
    mosq = mosquitto_new(NULL, clean_session, NULL);
    mosquitto_connect(mosq, MQTT_SERVER, MQTT_PORT, KEEP_ALIVE);
    mosquitto_publish(mosq, NULL, MQTT_PUB_TOPIC, strlen(data), data, 0, 0);
    mosquitto_destroy(mosq);
}

void Robot::moveForward()
{
    sendtoserver("{ \"cmd\":\"forward\", \"val\": 0.1, \"spd\": 0.1}");
}

void Robot::rotateLeft()
{
    sendtoserver("{ \"cmd\":\"left\", \"val\": 0.1, \"spd\": 0.1}");
}

void Robot::rotateRight()
{
    sendtoserver("{ \"cmd\":\"right\", \"val\": 0.1, \"spd\": 0.1}");
}

void Robot::waitingMode()
{
    sendtoserver("{ \"cmd\":\"right\", \"val\": 0.1, \"spd\": 0.1}");
}
