#include "weather_api.h"

#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "../../utils/time/time_format.h"
#include "../parser/weather_parser.h"

const char* apiKey = "bf6e046b0b5c260cb1815fe350e7c6d5";
const char* cityId = "707471";

String buildWeatherApiUrl(const char* cityId, const char* apiKey) {
  String url = "http://api.openweathermap.org/data/2.5/weather?";
  url += "id=" + String(cityId);
  url += "&appid=" + String(apiKey);
  url += "&units=metric";
  url += "&lang=ua";
  return url;
}

bool fetchWeather() {
  String apiUrl = buildWeatherApiUrl(cityId, apiKey);

  HTTPClient http;
  http.begin(apiUrl);

  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();

    WeatherData data;
    if (parseWeatherJson(payload, data)) {
      Serial.print("Температура: ");
      Serial.println(data.temperature);
      Serial.print("Відчувається як: ");
      Serial.println(data.feelsLike);
      Serial.print("Мінімальна температура: ");
      Serial.println(data.tempMin);
      Serial.print("Максимальна температура: ");
      Serial.println(data.tempMax);
      Serial.print("Вологість: ");
      Serial.println(data.humidity);
      Serial.print("Тиск: ");
      Serial.println(data.pressure);
      Serial.print("Вітер (швидкість): ");
      Serial.println(data.windSpeed);
      Serial.print("Вітер (порив): ");
      Serial.println(data.windGust);
      Serial.print("Вітер (напрям): ");
      Serial.println(data.windDeg);
      Serial.print("Хмарність: ");
      Serial.println(data.clouds);
      Serial.print("Основна погода: ");
      Serial.println(data.weatherMain);
      Serial.print("Опис: ");
      Serial.println(data.weatherDescription);
      Serial.print("Іконка: ");
      Serial.println(data.weatherIcon);
      Serial.print("Місто: ");
      Serial.println(data.location);
      Serial.print("Країна: ");
      Serial.println(data.country);
      Serial.print("Схід сонця: ");
      Serial.println(formatTimeHM(data.sunrise, data.timezone));
      Serial.print("Захід сонця: ");
      Serial.println(formatTimeHM(data.sunset, data.timezone));
    } else {
      Serial.println("Помилка парсингу JSON!");
    }
    http.end();
    return true;
  } else {
    Serial.println("HTTP error: ");
    Serial.println(httpCode);
    http.end();
    return false;
  }
}
