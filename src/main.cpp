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
  Serial.println("---------------------------");
  Serial.print("Температура: ");
  Serial.print(bme680Temperature);
  Serial.println(" °C");
  Serial.print("Вологість: ");
  Serial.print(bme680Humidity);
  Serial.println(" %");
  Serial.print("Тиск: ");
  Serial.print(bme680Pressure);
  Serial.println(" hPa");
  Serial.print("IAQ: ");
  Serial.println(bme680Iaq);

  delay(3000);
}