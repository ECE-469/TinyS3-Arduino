#ifndef GASSENSOR_H
#define GASSENSOR_H

#include <string>
#include <limits>
#include <memory>
#include <map>
#include "../bluetooth/BLE.h"

#define NEGATIVE_INFINITY (-std::numeric_limits<float>::max())

struct SensorData
{
  float value;
  std::string units;

  SensorData(float value = NEGATIVE_INFINITY, std::string units = "")
      : value(value), units(units) {}
  SensorData(const SensorData &data)
      : value(data.value), units(data.units) {}
  SensorData(std::string units) : value(NEGATIVE_INFINITY), units(units) {}
};

class GasSensor
{
public:
  GasSensor(){};
  ~GasSensor(){};

  // Pure virtual methods to be implemented by derived classes
  virtual std::string getName() const = 0;
  virtual std::map<std::string, SensorData> getData() = 0;

protected:
  std::map<std::string, SensorData> data;
};

#endif