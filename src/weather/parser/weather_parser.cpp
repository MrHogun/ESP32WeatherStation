#include "weather_parser.h"

#include <ArduinoJson.h>

bool parseWeatherJson(const String& json, WeatherData& data) {
  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    return false;
  }

  data.temperature = doc["main"]["temp"].as<float>();
  data.feelsLike = doc["main"]["feels_like"].as<float>();
  data.tempMin = doc["main"]["temp_min"].as<float>();
  data.tempMax = doc["main"]["temp_max"].as<float>();
  data.humidity = doc["main"]["humidity"].as<float>();
  data.pressure = doc["main"]["pressure"].as<float>();
  data.windSpeed = doc["wind"]["speed"].as<float>();
  data.windGust = doc["wind"]["gust"].as<float>();
  data.windDeg = doc["wind"]["deg"].as<int>();
  data.clouds = doc["clouds"]["all"].as<int>();
  data.weatherMain = String(doc["weather"][0]["main"].as<const char*>());
  data.weatherDescription = String(doc["weather"][0]["description"].as<const char*>());
  data.weatherIcon = String(doc["weather"][0]["icon"].as<const char*>());
  data.location = String(doc["name"].as<const char*>());
  data.country = String(doc["sys"]["country"].as<const char*>());
  data.sunrise = doc["sys"]["sunrise"].as<unsigned long>();
  data.sunset = doc["sys"]["sunset"].as<unsigned long>();
  data.timezone = doc["timezone"].as<int>();

  return true;
}