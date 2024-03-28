#include "src/sensors/CO2/CO2.h"
#include "src/sensors/CO/CO.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<GasSensor>> sensors;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLE *ble = new BLE();

  sensors.push_back(std::unique_ptr<COSensor>(new COSensor(*ble)));
  sensors.push_back(std::unique_ptr<CO2Sensor>(new CO2Sensor(*ble)));
}

void loop()
{

  for (const auto &sensor : sensors)
  {
    sensor->readAndSendData();
  }
  delay(5000);
}