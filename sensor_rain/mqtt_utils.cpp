#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

WiFiClientSecure espClient;
PubSubClient client(espClient);

void mqttSetup() {
    espClient.setInsecure();
    client.setServer(MQTT_BROKER_URL, MQTT_BROKER_PORT);
}

void mqttConnect(int connectionAttempsDelay = 2000, int Maxtries = 20) {
    int tries = 0;
    while (!client.connected() && tries < Maxtries) {
        Serial.print("Attempting to connect to MQTT broker...");
        if (client.connect(MQTT_BROKER_CLIENT_ID, MQTT_BROKER_USERNAME, MQTT_BROKER_PASSWORD)) {
            Serial.println("Connected to the broker!");
        } else {
            Serial.print("Failed with error code: ");
            Serial.println(client.state());
            delay(connectionAttempsDelay);  
        }
        tries++;
    }
}

void publishMessage(const char* message) {
    if (client.publish(MQTT_BROKER_TOPIC, message)) {
        Serial.println("Message published successfully!");
    } else {
        Serial.println("Failed to publish the message.");
    }
}

void mqttLoop() {
    client.loop();
}

bool isMqttConnected() {
    return client.connected();
}