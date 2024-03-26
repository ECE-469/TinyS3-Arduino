/*!
  * @file  initiativereport.ino
  * @brief The sensor actively reports all data
  * @n Experimental method: Connect the sensor communication pin to the main control, then burn codes into it.
  * @n Communication mode selection, dial switch SEL:0: IIC, 1: UART
@n I2C address selection, the default I2C address is 0x74, A1 and A0 are combined into 4 types of IIC addresses
                | A1 | A0 |
                | 0  | 0  |    0x74
                | 0  | 1  |    0x75
                | 1  | 0  |    0x76
                | 1  | 1  |    0x77   default i2c address
  * @n Experimental phenomenon: Print all data via serial port
*/
#include <DFRobot_MultiGasSensor.h>
#include "../GasSensor.cpp"

#define I2C_ADDRESS 0x74
DFRobot_GAS_I2C gas(&Wire, I2C_ADDRESS);

void init_CO()
{
  while (!gas.begin())
  {
    Serial.println("NO Deivces !");
    delay(1000);
  }
  Serial.println("The device is connected successfully!");

  gas.changeAcquireMode(gas.PASSIVITY);
  delay(1000);

  gas.setTempCompensation(gas.OFF);
}

class COSensor : public GasSensor
{
public:
  COSensor(std::unique_ptr<BLECharacteristic> &bleCharacteristic)
      : GasSensor(bleCharacteristic)
  {
    init_CO();
  }

  std::string getName() const override
  {
    return "CO";
  }

  std::string getUnits() const override
  {
    return "ppm";
  }

  float getGasConcentration() const override
  {
    return gas.readGasConcentrationPPM();
  }
};