#include "O3.h"

O3Sensor::O3Sensor(BLE &ble)
    : GasSensor(ble)
{
}

std::string O3Sensor::getName() const
{
  return "O3";
}

std::string O3Sensor::getUnits() const
{
  return "ppb";
}

float O3Sensor::getGasConcentration()
{
  return Ozone.readOzoneData(COLLECT_NUMBER);
}

void O3Sensor::init()
{
  while (!Ozone.begin(Ozone_IICAddress))
  {
    Serial.println("I2c device number error !");
    delay(1000);
  }
  Serial.println("I2c connect success !");
  Ozone.setModes(MEASURE_MODE_PASSIVE);
}