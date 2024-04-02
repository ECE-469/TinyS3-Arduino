#ifndef UV_H
#define UV_H

#include "../GasSensor.h"
#include "../../lib/ultraviolet/Adafruit_LTR390.h"
#include <Arduino.h>
#include <Wire.h>
#include <string>

class UVSensor : public GasSensor
{
public:
  UVSensor(BLE &ble);

  std::string getName() const override;

  std::string getUnits() const override;

  float getGasConcentration() override;

private:
  Adafruit_LTR390 ltr;
  float uvReading;

  void init();
};

#endif