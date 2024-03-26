#include "bluetooth/init.cpp"
#include "sensors/CO.cpp"
#include "sensors/CO2.cpp"
#include <vector>
#include <memory>

BLECharacteristic *CO_characteristic = NULL;

std::vector<std::unique_ptr<GasSensor>> sensors;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLE *ble = new BLE();

  sensors.push_back(std::make_unique<COSensor>(std::move(ble->get_CO_characteristic())));
  sensors.push_back(std::make_unique<CO2Sensor>(std::move(ble->get_CO2_characteristic())));
}

void loop()
{

  for (const auto &sensor : sensors)
  {
    sensor->readAndSendData();
  }
  delay(500);
}