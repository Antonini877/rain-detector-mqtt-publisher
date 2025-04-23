#include <WiFi.h>
#include "secrets.h"

void wifiConnect() {
  WiFi.begin(SECRET_SSID, SECRET_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)   {
    delay(500);
    Serial.println("Wi-Fi not connected, retrying...");
  }

  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

bool isWifiConnected() {
  return WiFi.status() == WL_CONNECTED;
}
