#include "PM.h"

PMSensor::PMSensor(BLE &ble)
    : GasSensor(ble)
{
  init();
}

std::string PMSensor::getName() const
{
  return "PM2.5";
}

std::map<std::string, SensorData> PMSensor::getData()
{
  PM25_AQI_Data pmData;

  if (!aqi.read(&pmData))
  {
    Serial.println("Could not read from AQI");
    delay(50); // try again in a bit!
    return data;
  }
  std::map<std::string, SensorData> newData;
  newData["PM1.0"] = SensorData(pmData.pm10_standard, "ug/m3");
  newData["PM2.5"] = SensorData(pmData.pm25_standard, "ug/m3");
  newData["PM10"] = SensorData(pmData.pm100_standard, "ug/m3");
  newData["PM1.0_env"] = SensorData(pmData.pm10_env, "ug/m3");
  newData["PM2.5_env"] = SensorData(pmData.pm25_env, "ug/m3");
  newData["PM10_env"] = SensorData(pmData.pm100_env, "ug/m3");
  data = newData;
  return data;
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
}

void PMSensor::init()
{
  aqi = Adafruit_PM25AQI();
  while (!aqi.begin_I2C())
  {
    Serial.println("Could not find PM 2.5 sensor!");
    delay(100);
  }

  data["PM1.0"] = SensorData("ug/m3");
  data["PM2.5"] = SensorData("ug/m3");
  data["PM10"] = SensorData("ug/m3");
  data["PM1.0_env"] = SensorData("ug/m3");
  data["PM2.5_env"] = SensorData("ug/m3");
  data["PM10_env"] = SensorData("ug/m3");

  Serial.println("PM25 connected!");
}