#pragma once

void bme680Init();

void bme680Update();

extern float bme680Temperature;
extern float bme680Humidity;
extern float bme680Pressure;
extern float bme680Iaq;