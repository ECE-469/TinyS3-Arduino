#include <BLEDevice.h>
#include <memory>

#define NEGATIVE_INFINITY -std::numeric_limits<float>::max();

class GasSensor
{
public:
  GasSensor(std::unique_ptr<BLECharacteristic> &bleCharacteristic)
      : bleCharacteristic_(std::move(bleCharacteristic))
  {
    if (!bleCharacteristic_)
    {
      throw std::invalid_argument("BLECharacteristic must be provided");
    }
  }

  virtual ~GasSensor() {}

  void readAndSendData()
  {
    float gasConcentration = getGasConcentration();
    sendDataViaBLE(gasConcentration);
  }

  // Virtual method to get the name of the sensor
  virtual std::string getName() const = 0;

  // Virtual method to get the units of the sensor
  virtual std::string getUnits() const = 0;

  // Virtual method to get the gas concentration from the sensor
  virtual float getGasConcentration()
  {
    return NEGATIVE_INFINITY;
  };

  // Method to send data via BLE
  void sendDataViaBLE(const float concentration)
  {
    // Convert to list of bytes
    byte bytes[sizeof(float)];
    memcpy(bytes, &concentration, sizeof(float));

    // Set the characteristic value and notify
    bleCharacteristic_->setValue(bytes, sizeof(bytes));
    bleCharacteristic_->notify();
  }

  virtual float getTemperature()
  {
    return NEGATIVE_INFINITY;
  }

  virtual float getHumidity()
  {
    return NEGATIVE_INFINITY;
  }

protected:
  std::unique_ptr<BLECharacteristic> bleCharacteristic_;
};