#include <DFRobot_MultiGasSensor.h>
#include "CO.h"

#define I2C_ADDRESS 0x74
DFRobot_GAS_I2C gas(&Wire, I2C_ADDRESS);

void init_CO()
{
  while (!gas.begin())
  {
    Serial.println("NO Deivces !");
    delay(1000);
  }
  Serial.println("The device is connected successfully!");

  gas.changeAcquireMode(gas.PASSIVITY);
  delay(1000);

  gas.setTempCompensation(gas.OFF);
}

COSensor::COSensor(BLE &ble)
    : GasSensor(ble)
{
  init_CO();
}

std::string COSensor::getName() const
{
  return "CO";
}

std::string COSensor::getUnits() const
{
  return "ppm";
}

float COSensor::getGasConcentration()
{
  return gas.readGasConcentrationPPM();
}