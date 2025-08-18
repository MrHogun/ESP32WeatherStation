#include "wifi_manager.h"

#include <WiFi.h>

const char* ssid = "HogunHome";
const char* password = "adecU7oXjFMoAF5L";

void connectToWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
}