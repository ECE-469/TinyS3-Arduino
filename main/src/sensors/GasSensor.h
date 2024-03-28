#ifndef GASSENSOR_H
#define GASSENSOR_H

#include <string>
#include <memory>
#include <limits>
#include <memory>
#include "../bluetooth/BLE.h"

#define NEGATIVE_INFINITY (-std::numeric_limits<float>::max())

class GasSensor
{
public:
  GasSensor(BLE &ble);
  virtual ~GasSensor();

  void readAndSendData();

  // Pure virtual methods to be implemented by derived classes
  virtual std::string getName() const = 0;
  virtual std::string getUnits() const = 0;
  virtual float getGasConcentration() = 0;

  // Virtual methods with default implementations
  virtual float getTemperature();
  virtual float getHumidity();

protected:
  // Pointer to the BLECharacteristic
  std::unique_ptr<BLECharacteristic> bleCharacteristic_;

private:
  void sendConcentrationViaBLE(const float concentration);
};

#endif // GASSENSOR_H