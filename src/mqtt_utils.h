#ifndef MQTT_UTILS_H
#define MQTT_UTILS_H

#include <PubSubClient.h>

void mqtt_setup();
void mqtt_connect(int connectionAttempsDelay = 2000);
void publish_message(const char* message);
void mqtt_loop();
bool mqtt_connected();

#endif
