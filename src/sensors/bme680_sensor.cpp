#include "bme680_sensor.h"

#include <Wire.h>
#include <bsec.h>

const float TEMP_CALIBRATION = -4.0;

float bme680Temperature = 0;
float bme680Humidity = 0;
float bme680Pressure = 0;
float bme680Iaq = 0;

Bsec bme680;

void bme680Init() {
  Wire.begin();
  bme680.begin(BME680_I2C_ADDR_SECONDARY, Wire);

  if (bme680.status != BSEC_OK) {
    Serial.println("BME680 sensor initialization failed");
    while (1);
  }

  bsec_virtual_sensor_t sensors[4] = {
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
      BSEC_OUTPUT_RAW_PRESSURE,
      BSEC_OUTPUT_IAQ,
  };
  bme680.updateSubscription(sensors, 4, BSEC_SAMPLE_RATE_LP);
}

void bme680Update() {
  if (bme680.run()) {
    bme680Temperature = bme680.temperature + TEMP_CALIBRATION;
    bme680Humidity = bme680.humidity;
    bme680Pressure = bme680.pressure / 100.0;
    bme680Iaq = bme680.iaq;
  }
}