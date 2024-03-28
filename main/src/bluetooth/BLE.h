#ifndef BLE_H
#define BLE_H

#include <Arduino.h>
#include "UUIDs.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
// #include <BLE2902.h>
#include <map>
#include <string>

#define DEVICE_NAME "TinyS3 Arduino"

using UUID = std::string;
using SENSOR_NAME = std::string;

extern std::map<SENSOR_NAME, UUID> sensor_uuid_map;

class CustomServerCallbacks : public BLEServerCallbacks
{
public:
  void onConnect(BLEServer *pServer);
  void onDisconnect(BLEServer *pServer);
};

class BLE
{
public:
  BLE();
  BLECharacteristic *get_characteristic(std::string name);

private:
  std::map<UUID, BLECharacteristic *> characteristic_map;

  void _init_characteristics(BLEService *pService);
  void _init_advertising();
  BLECharacteristic *create_characteristic(const UUID uuid, BLEService *pService);
};

#endif // BLE_H