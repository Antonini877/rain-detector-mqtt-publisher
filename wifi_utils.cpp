#include <WiFi.h>
#include "secrets.h"

void wifi_connect() {
  WiFi.begin(SECRET_SSID, SECRET_PASSWORD);

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tries++;
    if (tries > 20) {
      Serial.println("Failed to connect to Wi-Fi!");
      return;
    }
  }

  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
