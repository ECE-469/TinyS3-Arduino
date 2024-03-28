#include "GasSensor.h"

GasSensor::GasSensor(BLE &ble)
{
  if (!bleCharacteristic_)
  {
    throw std::invalid_argument("BLECharacteristic must be provided");
  }
  BLECharacteristic *characteristic = ble.get_characteristic(getName());
  bleCharacteristic_ = std::unique_ptr<BLECharacteristic>(new BLECharacteristic(*characteristic));
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
  bleCharacteristic_->setValue(bytes, sizeof(bytes));
  bleCharacteristic_->notify();
}

float GasSensor::getTemperature()
{
  return NEGATIVE_INFINITY;
}

float GasSensor::getHumidity()
{
  return NEGATIVE_INFINITY;
}