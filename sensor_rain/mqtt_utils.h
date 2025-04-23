#ifndef MQTT_UTILS_H
#define MQTT_UTILS_H

#include <PubSubClient.h>

void mqttSetup();
void mqttConnect(int connectionAttempsDelay = 2000, int Maxtries = 20);
void publishMessage(const char* message);
void mqttLoop();
bool isMqttConnected();

#endif
