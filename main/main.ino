#include "src/sensors/sensors.h"
#include "src/bluetooth/BLE.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

std::vector<std::unique_ptr<GasSensor>> sensors;
BLE *ble;

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&...args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

void setup()
{
  Serial.begin(115200);

  ble = new BLE();

  delay(500); // Ensure all sensors are powered

  Serial.println("Initializing Sensors");

  sensors.push_back(make_unique<CO2Sensor>());
  sensors.push_back(make_unique<COSensor>());
  sensors.push_back(make_unique<O3Sensor>());
  sensors.push_back(make_unique<UVSensor>());
  sensors.push_back(make_unique<VOCNOXSensor>());
  sensors.push_back(make_unique<PMSensor>());

  Serial.println("All Sensors Initialized!");

  delay(5000); // Allow sensors to acclimate
}

void loop()
{
  float tempAvg = 0;
  float humdAvg = 0;
  int tempCount = 0;
  int humdCount = 0;
  std::map<std::string, SensorData> allSensorData;
  for (const auto &sensor : sensors)
  {
    std::map<std::string, SensorData> sensorData = sensor->getData();
    for (const auto &data : sensorData)
    {
      if (data.first == "Temperature" && data.second.value > NEGATIVE_INFINITY)
      {
        tempAvg += data.second.value;
        tempCount++;
      }
      else if (data.first == "Humidity" && data.second.value > NEGATIVE_INFINITY)
      {
        humdAvg += data.second.value;
        humdCount++;
      }
      else
      {
        allSensorData[data.first] = data.second;
      }
    }
  }
  if (tempCount > 0)
  {
    allSensorData["Temperature"] = SensorData(tempAvg / tempCount, "C");
  }
  if (humdCount > 0)
  {
    allSensorData["Humidity"] = SensorData(humdAvg / humdCount, "%");
  }
  Serial.println("Average Temp: " + String(allSensorData["Temperature"].value) + allSensorData["Temperature"].units.c_str());
  Serial.println("Average Humd: " + String(allSensorData["Humidity"].value) + allSensorData["Humidity"].units.c_str());

  ble->send_data(allSensorData);

  delay(10000);
}