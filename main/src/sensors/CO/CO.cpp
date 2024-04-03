#include "CO.h"

void COSensor::init()
{
  gas = DFRobot_GAS_I2C(&Wire, I2C_ADDRESS);
  while (!gas.begin())
  {
    Serial.println("CO not found!");
    delay(500);
  }
  Serial.println("CO is connected successfully!");

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