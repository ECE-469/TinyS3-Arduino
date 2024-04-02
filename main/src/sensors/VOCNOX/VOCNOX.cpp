#include "VOCNOX.h"

VOCNOXSensor::VOCNOXSensor(BLE &ble)
    : GasSensor(ble)
{
  init();
}

std::string VOCNOXSensor::getName() const
{
  return "VOC+NOX";
}

std::string VOCNOXSensor::getUnits() const
{
  return "ppm";
}

float VOCNOXSensor::getTemperature()
{
  return temp;
}

float VOCNOXSensor::getHumidity()
{
  return humd;
}

float VOCNOXSensor::getGasConcentration()
{
  uint16_t error;
  char errorMessage[256];

  // Read Measurement
  float humidity;
  float temperature;
  float vocIndex;
  float noxIndex;
  error = svm41.readMeasuredValues(humidity, temperature, vocIndex, noxIndex);
  if (error)
  {
    Serial.print("Error trying to execute readMeasuredValues(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  else
  {
    temp = temperature;
    humd = humidity;
    voc = vocIndex;
    nox = noxIndex;
  }

  return nox;
}

void VOCNOXSensor::init()
{
  Wire.begin();

  uint16_t error;
  char errorMessage[256];

  svm41.begin(Wire);

  error = svm41.deviceReset();
  if (error)
  {
    Serial.print("Error trying to execute deviceReset(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }

  // Delay to let the serial monitor catch up
  delay(1000);

  uint8_t serialNumber[32];
  uint8_t serialNumberSize = 32;
  error = svm41.getSerialNumber(serialNumber, serialNumberSize);
  if (error)
  {
    Serial.print("Error trying to execute getSerialNumber(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  else
  {
    Serial.print("SerialNumber:");
    Serial.println((char *)serialNumber);
  }

  uint8_t firmwareMajor;
  uint8_t firmwareMinor;
  bool firmwareDebug;
  uint8_t hardwareMajor;
  uint8_t hardwareMinor;
  uint8_t protocolMajor;
  uint8_t protocolMinor;
  error = svm41.getVersion(firmwareMajor, firmwareMinor, firmwareDebug,
                           hardwareMajor, hardwareMinor, protocolMajor,
                           protocolMinor);

  if (error)
  {
    Serial.print("Error trying to execute getVersion(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  else
  {
    Serial.print("Firmware version: ");
    Serial.print(firmwareMajor);
    Serial.print(".");
    Serial.print(firmwareMinor);
    Serial.print("\t");
    Serial.print("FirmwareDebug: ");
    Serial.println(firmwareDebug);
    Serial.print("Hardware version: ");
    Serial.print(hardwareMajor);
    Serial.print(".");
    Serial.println(hardwareMinor);
    Serial.print("Protocol version: ");
    Serial.print(protocolMajor);
    Serial.print(".");
    Serial.print(protocolMinor);
    Serial.println();
  }

  // Start Measurement
  error = svm41.startMeasurement();
  if (error)
  {
    Serial.print("Error trying to execute startMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
}