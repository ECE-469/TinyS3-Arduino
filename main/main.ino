#include "src/sensors/CO2/CO2.h"
#include "src/sensors/CO/CO.h"
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

  // sensors.push_back(make_unique<COSensor>(*ble));
  // sensors.push_back(std::unique_ptr<CO2Sensor>(new CO2Sensor(*ble)));

  Serial.println("All Sensors Initialized!");
}

void loop()
{
  for (const auto &sensor : sensors)
  {
    if (sensor->getName() == "CO2")
    {
      Serial.println(sensor->getHumidity());
      Serial.println(sensor->getTemperature());
    }
    Serial.println(sensor->getGasConcentration());
  }
  delay(5000);
}