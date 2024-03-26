#include <Arduino.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>
#include "../GasSensor.cpp"

SensirionI2CScd4x scd4x;

void printUint16Hex(uint16_t value)
{
  Serial.print(value < 4096 ? "0" : "");
  Serial.print(value < 256 ? "0" : "");
  Serial.print(value < 16 ? "0" : "");
  Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2)
{
  Serial.print("Serial: 0x");
  printUint16Hex(serial0);
  printUint16Hex(serial1);
  printUint16Hex(serial2);
  Serial.println();
}

void init_CO2()
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

void test_CO2()
{
  uint16_t error;
  char errorMessage[256];

  delay(100);

  // Read Measurement
  uint16_t co2 = 0;
  float temperature = 0.0f;
  float humidity = 0.0f;
  bool isDataReady = false;
  error = scd4x.getDataReadyFlag(isDataReady);
  if (error)
  {
    Serial.print("Error trying to execute getDataReadyFlag(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
    return;
  }
  if (!isDataReady)
  {
    return;
  }
  error = scd4x.readMeasurement(co2, temperature, humidity);
  if (error)
  {
    Serial.print("Error trying to execute readMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  else if (co2 == 0)
  {
    Serial.println("Invalid sample detected, skipping.");
  }
  else
  {
    Serial.print("Co2:");
    Serial.print(co2);
    Serial.print("\t");
    Serial.print("Temperature:");
    Serial.print(temperature);
    Serial.print("\t");
    Serial.print("Humidity:");
    Serial.println(humidity);
  }
}

class CO2Sensor : public GasSensor
{
public:
  CO2Sensor(std::unique_ptr<BLECharacteristic> &bleCharacteristic)
      : GasSensor(bleCharacteristic)
  {
    init_CO2();
  }

  std::string getName() const override
  {
    return "CO2";
  }

  std::string getUnits() const override
  {
    return "ppm";
  }

  float getGasConcentration() override
  {
    safeRead();
    return co2;
  }

  float getTemperature() override
  {
    safeRead();
    return temperature;
  }

  float getHumidity() override
  {
    safeRead();
    return humidity;
  }

private:
  uint16_t error;
  uint16_t co2;
  float temperature;
  float humidity;

  bool checkDataReady() const
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

  void safeRead()
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
      else if (co2 == 0)
      {
        Serial.println("Invalid sample detected, skipping.");
        co2 = old_co2;
        temperature = old_temperature;
        humidity = old_humidity;
      }
    }
  }
};