#include "GasSensor.h"

GasSensor::GasSensor(BLE &ble)
{
  ble_ = std::unique_ptr<BLE>(new BLE(ble));
}

GasSensor::~GasSensor() {}

void GasSensor::readAndSendData()
{
  float gasConcentration = getGasConcentration();
  sendConcentrationViaBLE(gasConcentration);
}

float GasSensor::getGasConcentration()
{
  return NEGATIVE_INFINITY;
}

void GasSensor::sendConcentrationViaBLE(const float concentration)
{
  // Convert to list of bytes
  byte bytes[sizeof(float)];
  memcpy(bytes, &concentration, sizeof(float));

  // Set the characteristic value and notify
  std::string name = getName();
  Serial.println(name.c_str());
  BLECharacteristic *characteristic = ble_->get_characteristic(name);
  characteristic->setValue(bytes, sizeof(bytes));
  characteristic->notify();
}

float GasSensor::getTemperature()
{
  return NEGATIVE_INFINITY;
}

float GasSensor::getHumidity()
{
  return NEGATIVE_INFINITY;
}