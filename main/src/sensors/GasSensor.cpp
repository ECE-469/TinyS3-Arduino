#include "GasSensor.h"

GasSensor::GasSensor(BLE &ble)
{
  ble_ = std::unique_ptr<BLE>(new BLE(ble));
}

GasSensor::~GasSensor() {}

std::map<std::string, SensorData> GasSensor::readAndSendData()
{
  std::map<std::string, SensorData> data = getData();
  for (const auto &entry : data)
  {
    sendConcentrationViaBLE(entry.second);
  }
  return data;
}

void GasSensor::sendConcentrationViaBLE(const SensorData &data)
{
  // Convert to list of bytes
  byte bytes[sizeof(float)];
  memcpy(bytes, &data.value, sizeof(float));

  // Set the characteristic value and notify
  std::string name = getName();
  Serial.println(name.c_str());
  BLECharacteristic *characteristic = ble_->get_characteristic(name);
  characteristic->setValue(bytes, sizeof(bytes));
  characteristic->notify();
}