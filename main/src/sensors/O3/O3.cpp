#include "O3.h"

O3Sensor::O3Sensor(BLE &ble)
    : GasSensor(ble)
{
  init();
}

std::string O3Sensor::getName() const
{
  return "O3";
}

std::map<std::string, SensorData> O3Sensor::getData()
{
  std::map<std::string, SensorData> data;
  data["O3"] = SensorData(Ozone.readOzoneData(COLLECT_NUMBER), "ppb");
  return data;
}

void O3Sensor::init()
{
  while (!Ozone.begin(Ozone_IICAddress))
  {
    Serial.println("I2c device number error!");
    delay(1000);
  }
  Serial.println("I2c connected!");
  Ozone.setModes(MEASURE_MODE_PASSIVE);
}