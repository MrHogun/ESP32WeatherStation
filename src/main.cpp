#include <Arduino.h>

#include "sensors/bme680_sensor.h"
#include "weather/api/weather_api.h"
#include "wifi/wifi_manager.h"

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  fetchWeather();
  bme680Init();
}

void loop() {
  bme680Update();
  printBme680Data();
  Serial.println("----------------------------------");
  fetchWeather();
  Serial.println("----------------------------------");

  delay(60000);
}