#pragma once
#include <Arduino.h>

void mqttInit();
void mqttLoop();
void mqttReconnect();

void publishFloat(const char* topic, float value);
