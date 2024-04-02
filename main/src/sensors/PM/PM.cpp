#include "PM.h"

PMSensor::PMSensor(BLE &ble)
    : GasSensor(ble)
{
  init();
}

std::string PMSensor::getName() const
{
  return "PM";
}

std::string PMSensor::getUnits() const
{
  return "ppm";
}

float PMSensor::getGasConcentration()
{
  return 0;
}

void PMSensor::init()
{
}