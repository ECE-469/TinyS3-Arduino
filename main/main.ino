#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

BLECharacteristic *co_char = NULL;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  ble_init();
  co_char = get_co_characteristic();
}

int i = 0;

void loop()
{
  delay(2000);
  i++;
  co_char->setValue(i);
  co_char->notify();
}