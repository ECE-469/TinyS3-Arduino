#ifndef CO_H
#define CO_H

#include "../../lib/carbon-monoxide/DFRobot_MultiGasSensor.h"
#include "../GasSensor.h"

#define I2C_ADDRESS 0x74

class COSensor : public GasSensor
{
public:
  COSensor();

  std::string getName() const override;
  std::map<std::string, SensorData> getData() override;

private:
  void init();
  DFRobot_GAS_I2C gas;
};

#endif