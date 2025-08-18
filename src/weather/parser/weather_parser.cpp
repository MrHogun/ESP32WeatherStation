#include "weather_parser.h"

#include <ArduinoJson.h>

bool parseWeatherJson(const String& json, WeatherData& data) {
  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    return false;
  }

  data.temperature = doc["main"]["temp"] | 0.0;
  data.feelsLike = doc["main"]["feels_like"] | 0.0;
  data.tempMin = doc["main"]["temp_min"] | 0.0;
  data.tempMax = doc["main"]["temp_max"] | 0.0;
  data.humidity = doc["main"]["humidity"] | 0.0;
  data.pressure = doc["main"]["pressure"] | 0.0;
  data.windSpeed = doc["wind"]["speed"] | 0.0;
  data.windGust = doc["wind"]["gust"] | 0.0;
  data.windDeg = doc["wind"]["deg"] | 0;
  data.clouds = doc["clouds"]["all"] | 0;
  data.weatherMain = String(doc["weather"][0]["main"] | "");
  data.weatherDescription = String(doc["weather"][0]["description"] | "");
  data.weatherIcon = String(doc["weather"][0]["icon"] | "");
  data.location = String(doc["name"] | "");
  data.country = String(doc["sys"]["country"] | "");
  data.sunrise = doc["sys"]["sunrise"] | 0;
  data.sunset = doc["sys"]["sunset"] | 0;
  data.timezone = doc["timezone"] | 0;

  return true;
}