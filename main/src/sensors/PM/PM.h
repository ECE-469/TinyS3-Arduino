#ifndef PM_H
#define PM_H

#include "../GasSensor.h"
#include "../../lib/particulate-matter/Adafruit_PM25AQI.h"
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

private:
  Adafruit_PM25AQI aqi;
  float pm;

  void
  init();
};

#endif