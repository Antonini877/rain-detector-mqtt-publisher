#include "wifi_utils.h"
#include "mqtt_utils.h"

#define SENSOR_PIN 19
#define CHECK_INTERVAL 1000      
#define MESSAGE_INTERVAL 10000   

void checkSensor(unsigned long now);
bool isRaining();

unsigned long lastCheck = 0;
unsigned long lastSent = 0;

void setup() {
  pinMode(SENSOR_PIN, INPUT);  
  Serial.begin(9600);

  wifiConnect();
  
  mqttSetup();  
  mqttConnect();
}

void loop() {
  
  mqttLoop();

  if (!isWifiConnected()) {
    Serial.println("Wi-Fi disconnected, reconnecting...");
    wifiConnect();
  }

  if (!isMqttConnected()) {
    Serial.println("MQTT disconnected, reconnecting...");
    mqttConnect();
  }

  unsigned long now = millis();
  
  if (now - lastCheck >= CHECK_INTERVAL) {
    lastCheck = now;
    checkSensor(now);
  }
}

void checkSensor(unsigned long now){

  if (isRaining() && (now - lastSent > MESSAGE_INTERVAL)) {
    publishMessage("Rain detected!");
    lastSent = now;
  }

}

bool isRaining() {
  return digitalRead(SENSOR_PIN) == LOW;
}
