#include "weather_api.h"

#include <ArduinoJson.h>
#include <HTTPClient.h>

const char* apiKey = "bf6e046b0b5c260cb1815fe350e7c6d5";
const char* cityId = "707471";

bool fetchWeather() {
  String apiUrl =
      "http://api.openweathermap.org/data/2.5/weather?id=" + String(cityId) +
      "&appid=" + String(apiKey) + "&units=metric";

  HTTPClient http;
  http.begin(apiUrl);

  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
    http.end();
    return true;
  } else {
    Serial.println("HTTP error: ");
    Serial.println(httpCode);
    http.end();
    return false;
  }
}
