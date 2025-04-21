#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

WiFiClientSecure espClient;
PubSubClient client(espClient);

void mqtt_setup() {
    espClient.setInsecure();
    client.setServer(MQTT_BROKER_URL, MQTT_BROKER_PORT);
}

void mqtt_connect(int connectionAttempsDelay = 2000) {
    while (!client.connected()) {
        Serial.print("Attempting to connect to MQTT broker...");
        if (client.connect(MQTT_BROKER_CLIENT_ID, MQTT_BROKER_USERNAME, MQTT_BROKER_PASSWORD)) {
            Serial.println("Connected to the broker!");
        } else {
            Serial.print("Failed with error code: ");
            Serial.println(client.state());
            delay(connectionAttempsDelay);  
        }
    }
}

void publish_message(const char* message) {
    if (client.publish(MQTT_BROKER_TOPIC, message)) {
        Serial.println("Message published successfully!");
    } else {
        Serial.println("Failed to publish the message.");
    }
}

void mqtt_loop() {
    client.loop();
}

bool mqtt_connected() {
    return client.connected();
}