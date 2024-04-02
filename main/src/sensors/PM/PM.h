#ifndef PM_H
#define PM_H

#include "../GasSensor.h"
#include <Arduino.h>
#include <Wire.h>
#include <string>

class PMSensor : public GasSensor
{
public:
  PMSensor(BLE &ble);

  std::string getName() const override;

  std::string getUnits() const override;

  float getGasConcentration() override;
  float getTemperature() override;
  float getHumidity() override;

private:
  float pm;

  void init();
};

#endif