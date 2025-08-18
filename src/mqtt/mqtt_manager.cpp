#include "mqtt_manager.h"

#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

const char* mqtt_server = "192.168.1.142";
const int mqtt_port = 1883;
const char* mqtt_user = "esp32weather";
const char* mqtt_password = "esp32weather";

const String deviceInfo =
    "\"device\":{"
    "\"identifiers\":[\"esp32weather\"],"
    "\"name\":\"ESP32 Weather Station\","
    "\"model\":\"ESP32\","
    "\"manufacturer\":\"YourName\""
    "}";

String getClientId() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char buf[32];
  sprintf(buf, "ESP32WeatherClient_%02X%02X%02X", mac[3], mac[4], mac[5]);
  return String(buf);
}

void mqttReconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");
    String clientId = getClientId();
    if (mqttClient.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected!");

      // Temperature
      const char* tempConfigTopic = "homeassistant/sensor/esp32weather_temperature/config";
      String tempConfigPayload =
          "{"
          "\"name\":\"ESP32 Temperature\","
          "\"state_topic\":\"home/esp32weather/temperature\","
          "\"unit_of_measurement\":\"°C\","
          "\"device_class\":\"temperature\","
          "\"unique_id\":\"esp32weather_temperature\"," +
          deviceInfo + "}";
      mqttClient.publish(tempConfigTopic, tempConfigPayload.c_str(), true);

      // Humidity
      const char* humConfigTopic = "homeassistant/sensor/esp32weather_humidity/config";
      String humConfigPayload =
          "{"
          "\"name\":\"ESP32 Humidity\","
          "\"state_topic\":\"home/esp32weather/humidity\","
          "\"unit_of_measurement\":\"%\","
          "\"device_class\":\"humidity\","
          "\"unique_id\":\"esp32weather_humidity\"," +
          deviceInfo + "}";
      mqttClient.publish(humConfigTopic, humConfigPayload.c_str(), true);

      // Pressure
      const char* presConfigTopic = "homeassistant/sensor/esp32weather_pressure/config";
      String presConfigPayload =
          "{"
          "\"name\":\"ESP32 Pressure\","
          "\"state_topic\":\"home/esp32weather/pressure\","
          "\"unit_of_measurement\":\"hPa\","
          "\"device_class\":\"pressure\","
          "\"unique_id\":\"esp32weather_pressure\"," +
          deviceInfo + "}";
      mqttClient.publish(presConfigTopic, presConfigPayload.c_str(), true);

      // IAQ
      const char* iaqConfigTopic = "homeassistant/sensor/esp32weather_iaq/config";
      String iaqConfigPayload =
          "{"
          "\"name\":\"ESP32 IAQ\","
          "\"state_topic\":\"home/esp32weather/iaq\","
          "\"unit_of_measurement\":\"\","
          "\"unique_id\":\"esp32weather_iaq\"," +
          deviceInfo + "}";
      mqttClient.publish(iaqConfigTopic, iaqConfigPayload.c_str(), true);

    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void publishFloat(const char* topic, float value) {
  char buf[16];
  dtostrf(value, 6, 2, buf);
  mqttClient.publish(topic, buf, true);
}

void mqttInit() {
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttReconnect();
}

void mqttLoop() {
  if (!mqttClient.connected()) {
    mqttReconnect();
  }
  mqttClient.loop();
}
