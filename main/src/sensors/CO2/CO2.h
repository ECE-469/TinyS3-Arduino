#ifndef CO2_H
#define CO2_H

#include "../GasSensor.h"
#include <Arduino.h>
#include <SensirionI2CScd4x.h>
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
  uint16_t error;
  uint16_t co2;
  float temperature;
  float humidity;

  bool checkDataReady() const;

  void safeRead();
};

#endif