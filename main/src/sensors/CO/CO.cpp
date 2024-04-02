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

std::map<std::string, SensorData> COSensor::getData()
{
  std::map<std::string, SensorData> data;
  data["CO"] = SensorData(gas.readGasConcentrationPPM(), "ppm");
  return data;
}