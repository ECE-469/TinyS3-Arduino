#include "UV.h"

UVSensor::UVSensor()
    : GasSensor()
{
  init();
}

std::string UVSensor::getName() const
{
  return "UV";
}

std::map<std::string, SensorData> UVSensor::getData()
{
  if (!ltr.newDataAvailable())
  {
    Serial.println("No new UV data available");
    return data;
  }
  float uvReading = ltr.readUVS();
  data["UV"] = SensorData(uvReading, "mW/cm^2");
  return data;
}

void UVSensor::init()
{
  ltr = Adafruit_LTR390();

  delay(250);

  if (!ltr.begin())
  {
    Serial.println("UV not found!");
    return;
  }
  Serial.println("UV connected!");

  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);

  data["UV"] = SensorData("mW/cm^2");
  initialized = true;
}