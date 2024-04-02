#include "PM.h"

PMSensor::PMSensor(BLE &ble)
    : GasSensor(ble)
{
  init();
}

std::string PMSensor::getName() const
{
  return "PM";
}

std::string PMSensor::getUnits() const
{
  return "count";
}

float PMSensor::getGasConcentration()
{
  PM25_AQI_Data data;

  if (!aqi.read(&data))
  {
    Serial.println("Could not read from AQI");
    delay(50); // try again in a bit!
    return NEGATIVE_INFINITY;
  }
  // Serial.println("AQI reading success");

  // Serial.println();
  // Serial.println(F("---------------------------------------"));
  // Serial.println(F("Concentration Units (standard)"));
  // Serial.println(F("---------------------------------------"));
  // Serial.print(F("PM 1.0: "));
  // Serial.print(data.pm10_standard);
  // Serial.print(F("\t\tPM 2.5: "));
  // Serial.print(data.pm25_standard);
  // Serial.print(F("\t\tPM 10: "));
  // Serial.println(data.pm100_standard);
  // Serial.println(F("Concentration Units (environmental)"));
  // Serial.println(F("---------------------------------------"));
  // Serial.print(F("PM 1.0: "));
  // Serial.print(data.pm10_env);
  // Serial.print(F("\t\tPM 2.5: "));
  // Serial.print(data.pm25_env);
  // Serial.print(F("\t\tPM 10: "));
  // Serial.println(data.pm100_env);
  // Serial.println(F("---------------------------------------"));
  // Serial.print(F("Particles > 0.3um / 0.1L air:"));
  // Serial.println(data.particles_03um);
  // Serial.print(F("Particles > 0.5um / 0.1L air:"));
  // Serial.println(data.particles_05um);
  // Serial.print(F("Particles > 1.0um / 0.1L air:"));
  // Serial.println(data.particles_10um);
  // Serial.print(F("Particles > 2.5um / 0.1L air:"));
  // Serial.println(data.particles_25um);
  // Serial.print(F("Particles > 5.0um / 0.1L air:"));
  // Serial.println(data.particles_50um);
  // Serial.print(F("Particles > 10 um / 0.1L air:"));
  // Serial.println(data.particles_100um);
  // Serial.println(F("---------------------------------------"));
  return data.pm25_standard;
}

void PMSensor::init()
{
  aqi = Adafruit_PM25AQI();
  if (!aqi.begin_I2C())
  {
    Serial.println("Could not find PM 2.5 sensor!");
    while (1)
      delay(10);
  }

  Serial.println("PM25 found!");
}