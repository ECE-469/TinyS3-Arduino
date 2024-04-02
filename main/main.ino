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

  sensors.push_back(make_unique<CO2Sensor>(*ble));
  sensors.push_back(make_unique<COSensor>(*ble));
  sensors.push_back(make_unique<O3Sensor>(*ble));
  sensors.push_back(make_unique<UVSensor>(*ble));
  sensors.push_back(make_unique<VOCNOXSensor>(*ble));
  sensors.push_back(make_unique<PMSensor>(*ble));

  Serial.println("All Sensors Initialized!");
}

void loop()
{
  for (const auto &sensor : sensors)
  {
    std::string name = sensor->getName();
    Serial.print("\n");
    Serial.println(name.c_str());
    if (name == "CO2" || name == "VOC+NOX")
    {
      Serial.println("Humidity: " + String(sensor->getHumidity()));
      Serial.println("Temperature: " + String(sensor->getTemperature()));
    }
    Serial.println("Concentration: " + String(sensor->getGasConcentration()) + sensor->getUnits().c_str());
  }
  delay(5000);
}