#include "CO.h"

#define I2C_ADDRESS 0x74
DFRobot_GAS_I2C gas(&Wire, I2C_ADDRESS);

void init()
{
  while (!gas.begin())
  {
    Serial.println("NO Deivces !");
    delay(500);
  }
  Serial.println("The device is connected successfully!");

  gas.changeAcquireMode(gas.PASSIVITY);
  delay(500);

  gas.setTempCompensation(gas.ON);
}

COSensor::COSensor()
    : GasSensor()
{
  init();
}

std::string COSensor::getName() const
{
  return "CO";
}

std::map<std::string, SensorData> COSensor::getData()
{
  if (gas.dataIsAvailable())
  {
    data["Temperature"] = SensorData(gas.readTempC(), "C");
    data["CO"] = SensorData(gas.readGasConcentrationPPM(), "ppm");
  }
  else
  {
    Serial.println("CO data not available");
  }
  return data;
}