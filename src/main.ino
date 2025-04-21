#include "wifi_utils.h"
#include "mqtt_utils.h"

#define SENSOR_PIN 19

bool isRaining();

void setup() {
  pinMode(SENSOR_PIN, INPUT);  
  Serial.begin(9600);

  wifi_connect();
  mqtt_setup();  
}

void loop() {
  if (!mqtt_connected()) {
    mqtt_connect();
  }
  mqtt_loop();

  if (isRaining()) {
    publish_message("Rain detected!");
    delay(5000);  
  }

  delay(1000);
}

bool isRaining() {
  return digitalRead(SENSOR_PIN) == LOW;
}
