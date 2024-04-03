#ifndef CO_H
#define CO_H

#include "../../lib/carbon-monoxide/DFRobot_MultiGasSensor.h"
#include "../GasSensor.h"
#include <string>

class COSensor : public GasSensor
{
public:
  COSensor();

  std::string getName() const override;
  std::map<std::string, SensorData> getData() override;
};

#endif