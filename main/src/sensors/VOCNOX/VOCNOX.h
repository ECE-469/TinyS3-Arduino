#ifndef VOCNOX_H
#define VOCNOX_H

#include "../GasSensor.h"
#include <Arduino.h>
#include "../../lib/vocnox/SensirionI2CSvm41.h"
#include <Wire.h>
#include <string>

class VOCNOXSensor : public GasSensor
{
public:
  VOCNOXSensor(BLE &ble);

  std::string getName() const override;
  std::map<std::string, SensorData> getData() override;

private:
  SensirionI2CSvm41 svm41;
  std::map<std::string, SensorData> data;
  // float voc;
  // float nox;
  // float temp;
  // float humd;

  void init();
};

#endif