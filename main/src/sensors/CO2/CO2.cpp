#include "CO2.h"

CO2Sensor::CO2Sensor(BLE &ble)
    : GasSensor(ble)
{
  init();
}

std::string CO2Sensor::getName() const
{
  return "CO2";
}

std::map<std::string, SensorData> CO2Sensor::getData()
{
  safeRead();
  std::map<std::string, SensorData> data;
  data["CO2"] = SensorData(co2, "ppm");
  data["Temperature"] = SensorData(temperature, "°C");
  data["Humidity"] = SensorData(humidity, "%");
  return data;
}

bool CO2Sensor::checkDataReady()
{
  char errorMessage[256];
  bool isDataReady = false;
  uint16_t e = scd4x.getDataReadyFlag(isDataReady);
  if (e)
  {
    Serial.print("Error trying to execute getDataReadyFlag(): ");
    errorToString(e, errorMessage, 256);
    Serial.println(errorMessage);
    return false;
  }
  return isDataReady;
}

void CO2Sensor::safeRead()
{
  char errorMessage[256];
  uint16_t old_co2 = co2;
  float old_temperature = temperature;
  float old_humidity = humidity;
  if (checkDataReady())
  {
    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error)
    {
      Serial.print("Error trying to execute readMeasurement(): ");
      errorToString(error, errorMessage, 256);
      Serial.println(errorMessage);
      co2 = old_co2;
      temperature = old_temperature;
      humidity = old_humidity;
    }
    else if (co2 <= 0)
    {
      Serial.println("Invalid sample detected, skipping.");
      co2 = old_co2;
      temperature = old_temperature;
      humidity = old_humidity;
    }
  }
}

void CO2Sensor::printUint16Hex(uint16_t value)
{
  Serial.print(value < 4096 ? "0" : "");
  Serial.print(value < 256 ? "0" : "");
  Serial.print(value < 16 ? "0" : "");
  Serial.print(value, HEX);
}

void CO2Sensor::printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2)
{
  Serial.print("Serial: 0x");
  printUint16Hex(serial0);
  printUint16Hex(serial1);
  printUint16Hex(serial2);
  Serial.println();
}

void CO2Sensor::init()
{

  while (!Serial)
  {
    delay(100);
  }

  Wire.begin();

  uint16_t error;
  char errorMessage[256];

  scd4x.begin(Wire);

  // stop potentially previously started measurement
  error = scd4x.stopPeriodicMeasurement();
  if (error)
  {
    Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }

  uint16_t serial0;
  uint16_t serial1;
  uint16_t serial2;
  error = scd4x.getSerialNumber(serial0, serial1, serial2);
  if (error)
  {
    Serial.print("Error trying to execute getSerialNumber(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  else
  {
    printSerialNumber(serial0, serial1, serial2);
  }

  // Start Measurement
  error = scd4x.startPeriodicMeasurement();
  if (error)
  {
    Serial.print("Error trying to execute startPeriodicMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }

  Serial.println("Waiting for first measurement... (5 sec)");
}