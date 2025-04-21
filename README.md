## ESP32 Rain Sensor with MQTT
This project is a smart rain detection system built with an ESP32 microcontroller and a digital rain sensor. When rain is detected, the ESP32 sends a message to a cloud-based MQTT broker (HiveMQ) wifi connection.

### Features
Rain detection via digital sensor (connected to GPIO 19)

Modular C++ codebase (separated into MQTT utilities, Wi-Fi utilities, and main logic)

Designed for low-power and efficient data transmission

### Tech Stack
ESP32 (C++)

MQTT (HiveMQ Cloud)

WiFiClientSecure for TLS

PubSubClient for MQTT communication
