#include "src/sensors/sensors.h"
#include <vector>
#include <memory>

std::vector<std::unique_ptr<GasSensor>> sensors;

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&...args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

void setup()
{
  Serial.begin(115200);

  BLE *ble = new BLE();

  delay(500); // Ensure all sensors are powered

  sensors.push_back(make_unique<CO2Sensor>());
  sensors.push_back(make_unique<COSensor>());
  sensors.push_back(make_unique<O3Sensor>());
  sensors.push_back(make_unique<UVSensor>());
  sensors.push_back(make_unique<VOCNOXSensor>());
  sensors.push_back(make_unique<PMSensor>());

  Serial.println("All Sensors Initialized!");

  delay(1000); // Allow sensors to acclimate
}

void loop()
{

  for (const auto &sensor : sensors)
  {
    std::string name = sensor->getName();
    Serial.print("\n");
    Serial.println(name.c_str());
    std::map<std::string, SensorData> sensorData = sensor->getData();
    for (const auto &data : sensorData)
    {
      Serial.println(String(data.first.c_str()) + ": " + String(data.second.value) + data.second.units.c_str());
    }
  }
  delay(40000);
}