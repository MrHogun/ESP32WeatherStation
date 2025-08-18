#include <Arduino.h>

#include "mqtt/mqtt_manager.h"
#include "sensors/bme680_sensor.h"
#include "weather/api/weather_api.h"
#include "wifi/wifi_manager.h"

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  // fetchWeather();
  bme680Init();
  mqttInit();
}

void loop() {
  bme680Update();
  publishFloat("home/esp32weather/temperature", bme680Temperature);
  publishFloat("home/esp32weather/humidity", bme680Humidity);
  publishFloat("home/esp32weather/pressure", bme680Pressure);
  publishFloat("home/esp32weather/iaq", bme680Iaq);
  mqttLoop();

  Serial.println("----------------------------------");
  printBme680Data();

  delay(60000);
}