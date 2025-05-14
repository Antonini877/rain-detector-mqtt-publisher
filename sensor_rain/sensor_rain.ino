#include "wifi_utils.h"
#include "mqtt_utils.h"

#define SENSOR_PIN 19
#define CHECK_INTERVAL 1000
#define MESSAGE_INTERVAL 10000
#define TEMPERATURE_THRESHOLD 50

unsigned long lastCheck = 0;
unsigned long lastSent = 0;

void checkSensor(unsigned long now);
bool isRaining();
float readTemperature();
void checkTemperature();

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  wifiConnect();
  mqttSetup();
  mqttConnect();
}

void loop() {
  mqttLoop();

  if (!isWifiConnected()) {
    Serial.println("Wi-Fi desconectado, reconectando...");
    wifiConnect();
  }

  if (!isMqttConnected()) {
    Serial.println("MQTT desconectado, reconectando...");
    mqttConnect();
  }

  unsigned long now = millis();
  
  if (now - lastCheck >= CHECK_INTERVAL) {
    lastCheck = now;
    checkRainSensor(now);
    checkTemperatureSensor();
  }

}

void checkRainSensor(unsigned long now) {
  if (isRaining() && (now - lastSent > MESSAGE_INTERVAL)) {
    publishMessage("Rain detected!");
    lastSent = now;
  }
}

bool isRaining() {
  return digitalRead(SENSOR_PIN) == LOW;
}

void checkTemperature() {
  float temperature = readTemperature();
  
  if (temperature > TEMPERATURE_THRESHOLD) {
    Serial.println("[STATUS] - Too hot");
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

float checkTemperatureSensor() {
  int raw = analogRead(ESP32_TEMPERATURE_SENSOR);
  float voltage = raw * 3.3 / 4095.0;
  float temperature = (voltage - 0.5) * 100;
  return temperature;
}


