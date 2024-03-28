#ifndef CO_H
#define CO_H

#include "../GasSensor.h"
#include <string>

class COSensor : public GasSensor
{
public:
  COSensor(BLE &ble);

  std::string getName() const override;

  std::string getUnits() const override;

  float getGasConcentration() override;
};

#endif // CO_H