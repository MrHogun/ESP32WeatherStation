#include <Arduino.h>

struct WeatherData {
  float temperature;          // main.temp
  float feelsLike;            // main.feels_like
  float tempMin;              // main.temp_min
  float tempMax;              // main.temp_max
  float humidity;             // main.humidity
  float pressure;             // main.pressure
  float windSpeed;            // wind.speed
  float windGust;             // wind.gust
  int windDeg;                // wind.deg
  int clouds;                 // clouds.all
  String weatherMain;         // weather[0].main
  String weatherDescription;  // weather[0].description
  String weatherIcon;         // weather[0].icon
  String location;            // name
  String country;             // sys.country
  unsigned long sunrise;      // sys.sunrise
  unsigned long sunset;       // sys.sunset
  int timezone;               // timezone (seconds offset from UTC)
};

bool parseWeatherJson(const String& json, WeatherData& data);
