#ifndef CO2_H
#define CO2_H

#include "../GasSensor.h"
#include "../../lib/carbon-dioxide/SensirionI2CScd4x.h"
#include <Arduino.h>
#include <Wire.h>
#include <string>

class CO2Sensor : public GasSensor
{
public:
  CO2Sensor(BLE &ble);

  std::string getName() const override;

  std::string getUnits() const override;

  float getGasConcentration() override;

  float getTemperature() override;

  float getHumidity() override;

private:
  SensirionI2CScd4x scd4x;
  uint16_t error;
  uint16_t co2;
  float temperature;
  float humidity;

  bool checkDataReady();
  void safeRead();
  void init();
  void printUint16Hex(uint16_t value);
  void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2);
};

#endif