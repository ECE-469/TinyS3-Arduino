#include "bluetooth/init.cpp"
#include "sensors/CO.cpp"

BLECharacteristic *CO_characteristic = NULL;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  ble_init();
  CO_characteristic = get_CO_characteristic();

  init_CO();
}

void loop()
{
  float coConcentration = get_CO_concentration();
  Serial.println("CO Concentration: " + String(coConcentration) + " ppm");

  // Convert the float to a byte array
  byte coConcentrationBytes[sizeof(float)];
  memcpy(coConcentrationBytes, &coConcentration, sizeof(float));

  Serial.println("CO Concentration Bytes: " + String(coConcentrationBytes[0]) + " " + String(coConcentrationBytes[1]) + " " + String(coConcentrationBytes[2]) + " " + String(coConcentrationBytes[3]));

  // Set the characteristic value and notify
  CO_characteristic->setValue(coConcentrationBytes, sizeof(coConcentrationBytes));
  CO_characteristic->notify();
  delay(1000);
}